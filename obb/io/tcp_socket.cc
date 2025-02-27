/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/


#include <obb/io/tcp_socket.h>
#include <obb/string.h>


namespace obb::io {


tcp_socket::tcp_socket(object* parent, const std::string& ii): object(parent,ii)
{
    m_ifd = 0;
}

tcp_socket::tcp_socket()
{
    m_ifd = 0;
}

tcp_socket::~tcp_socket()
{
}

int tcp_socket::create()
{
    m_fd = ::socket(PF_INET,SOCK_STREAM, 0);
    //u_int32_t options = ifd::O_BLOCK|ifd::O_BUF|ifd::O_READ|ifd::O_WRITE|ifd::O_WINDOWED;
    obb::string str;
    str << id() << ':' << m_fd;

    m_ifd = new lfd(str(), m_fd, 4096, lfd::IMM|lfd::READ|lfd::WRITE, EPOLLIN|EPOLLOUT|EPOLLHUP|EPOLLERR, nullptr);
    return m_fd;
}

void tcp_socket::set_sockfd(int fd)
{
    m_fd = fd;
    obb::string str;
    str << id() << ':' << m_fd;

    m_ifd = new lfd(str(), m_fd, 4096, lfd::IMM|lfd::READ|lfd::WRITE, EPOLLIN|EPOLLOUT|EPOLLHUP|EPOLLERR, nullptr);
}


hostent* tcp_socket::host(const char* node, uint port, sockaddr_in* _addr_in, std::string& NodeIP)
{
    hostent* he = gethostbyname(node);

    int a,b,c,d;

    obb::string SNodeIP = "%d.%d.%d.%d";


    if (!he ) {
        book::error() << "gethostbyname failed!!"  << book::endl;
        ///@todo traiter l'erreur du DNS
        return 0l;
    }

    // Pas de IPV6... c'est pas demain que cette version va arriver.... bon gre - malgre ...
    a = (int)((unsigned char)he->h_addr_list[0][0]);
    b = (int)((unsigned char)he->h_addr_list[0][1]);
    c = (int)((unsigned char)he->h_addr_list[0][2]);
    d = (int)((unsigned char)he->h_addr_list[0][3]);

    // Juste  pour le deboggage:
    book::info()
        << "host:"
        << he->h_name
        << " Adresse IP effective: " << a << "." << b <<"." << c<< "." << d
        << "   contenu de h_addr_list[0]:" << (unsigned long)he->h_addr_list[0] << " PORT:" << port << book::endl;
    ////////////////////////////////////////////////////////////////////////////////
    SNodeIP |a|b|c|d;
    NodeIP = SNodeIP();
    book::info() << "node=" << NodeIP;


    if (_addr_in) {
        memset(_addr_in, 0, sizeof(sockaddr_in));
        _addr_in->sin_family = AF_INET;
        _addr_in->sin_port   = htons(port);
        _addr_in->sin_addr.s_addr = inet_addr(NodeIP.c_str());
    }

    return he;
}

char* tcp_socket::machine_hostname()
{
    char h [128];
    int R = gethostname(h,127);
    if(!R){
        return strdup(h);
    }
    return 0;
}

int tcp_socket::mkaddr(void* addr, int* addr_len, const char* addr_str, const char* proto)
{
    obb::string saddress = addr_str;
    obb::string::word::list htokens{};

    auto n = saddress.words(htokens, false, ":");

    if (n!=2) return -1;
    std::string inaddress = **htokens.begin();
    std::string serviceport = *htokens.back();
    std::string protoc = proto;
    sockaddr_in* ap = (sockaddr_in*)addr;
    hostent* hp = 0;
    servent* sp = 0;
    char *cp;
    long lv;


    // Attribuer les valeurs par default

    protoc = protoc.empty() ? protoc : "tcp";


    // Initialiser la structure de l'adresse
    memset(ap,0, *addr_len);
    ap->sin_family  = AF_INET;
    ap->sin_port    = 0;
    ap->sin_addr.s_addr = INADDR_ANY;

    // integrer l'adresse hôte
    if ( inaddress != "*" ) {
        if (isdigit(inaddress[0])) {
            ap->sin_addr.s_addr = inet_addr(inaddress.c_str());
            if (ap->sin_addr.s_addr == INADDR_NONE) return -1;
        }
        else {
            // Assumer le host name
            if ( hp = gethostbyname(inaddress.c_str()); !hp ) return  -1;
            if (hp->h_addrtype != AF_INET) return -1;
            ap->sin_addr = *reinterpret_cast<in_addr *>((hp)->h_addr_list[0]);
        }
    }

    // Traiter le # du port

    if (serviceport != "*") {
        if ( isdigit(serviceport[0])) {
            lv=strtol(serviceport.c_str(),&cp,10);
            if (cp && *cp) return -1; // for now do nothing with cp. I  may use it later if detailed error is needed.
            if (lv<0 || lv>=65536) return -2;
            ap->sin_port = htons((short)lv);
        }
        else
        {
            std::cerr << "sp=" << serviceport << std::endl;
            sp = getservbyname(serviceport.c_str(), proto);
            if (sp) ap->sin_port = sp->s_port;
        }
    }

    *addr_len = sizeof(*ap);

    book::info() << "finalized socket addr infos [port]::" << ntohs(ap->sin_port) << book::endl;
    return 0;
}

} // namespace lux::io
