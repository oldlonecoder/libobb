/******************************************************************************************
*   Copyright (C) ...,2025,... by Serge Lussier                                          *
 *   serge.lussier@oldlonecoder.club / lussier.serge@gmail.com                            *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Codes ands files in this project is written          *
 *   by the author and owned by the auther (Serge Lussier), unless otherwise specified.   *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... or whatever -  apply to this project.                 *
 *   ----------------------------------------------------------------------------------   *
 *   NOTE : All code source that I am the only author, I reserve for myself, the rights to*
 *   make it to restricted private license.                                               *
 ******************************************************************************************/


#pragma once
#include <obb/io/lfd.h>
#include <sys/epoll.h>

namespace obb::io
{

class LUSIOLIB listener
{

    lfd::list _fds{};
    int _epoll_fd{-1};
    static constexpr int max_events{10};
    epoll_event _poll_events[listener::max_events]{};
    bool _kill{false};
public:
    listener() = default;
    listener(const std::string& obj_id);
    ~listener();
    std::pair<rem::cc, lfd&> attach(lfd&& fds); // ex.: attach({"terminal input channel", 0, 1024, EPOLLIN|EPOLLERR|EPOLLHUP,nullptr});
    rem::cc detach(int fnum);
    //std::pair<rem::cc, lfd&>  add_fd(lfd&& fds);
    //rem::cc init();
    rem::cc terminate();

    rem::cc run();         ///< blocking loop of polls
    rem::cc poll(int _fd); ///< One-shot poll check and consume at once.
    std::pair<rem::cc, io::lfd&> query_lfd(int fnum);
    rem::cc refresh_fds();

    rem::cc open();
    rem::cc close();

};


} // namespace lux::io
