//
// Created by oldlonecoder on 25-02-03.
//

#include <lus/io/listener.h>
#include <cerrno>

namespace lus::io
{


static lfd _null{};

listener::listener(const std::string& obj_id){}


listener::~listener()
{
    _fds.clear();
}




std::pair<rem::cc, lfd&> listener::attach(lfd&& fds)
{
    _fds.emplace_back(std::move(fds));
    epoll_event e{};
    auto& fd = _fds.back();
    fd.init();
    e.events = fd._poll_bits;
    e.data.fd = fd._fd;
    journal::info() << "attach new fd: " << color::yellow << fd._id << color::z << ":" <<journal::endl;

    if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd._fd, &e) < 0)
    {
        journal::error() << "epoll_ctl() failed: " << std::strerror(errno) << journal::endl;
        fd._flags.active = 0;
    }
    return {rem::cc::accepted, _fds.back()};
}


// std::pair<rem::cc, lfd&> listener::add_fd(lfd&& fds)
// {
//     _fds.emplace_back(std::move(fds));
//     journal::info() << "added " << color::aqua << _fds.back()._id << color::z << journal::endl;
//     return {rem::cc::accepted, _fds.back()};
// }


rem::cc listener::detach(int fnum)
{
    auto fdi = std::find_if(_fds.begin(), _fds.end(), [fnum](const auto& fd)->bool
        {
        return fnum == fd._fd;
    });

    if (fdi == _fds.end()) return rem::cc::rejected;
    journal::info() << "detach and remove lfd '" << fdi->_id << color::z << "' from this listener." << journal::endl;
    epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fdi->_fd, nullptr);
    _fds.erase(fdi);

    return rem::cc::accepted;
}



rem::cc listener::terminate()
{
    _kill = true;
    return rem::cc::accepted;
}


rem::cc listener::run()
{

    do
    {
        if (_fds.empty())
        {
            journal::warning() << color::yellow << "cancelling this listener: fd list is empty()..." << journal::endl;
            if (_epoll_fd > 2 )
                close();
            return rem::cc::rejected;
        }

        auto nevents = epoll_wait(_epoll_fd, _poll_events, listener::max_events,-1);
        journal::info() << color::yellow << nevents << color::z << " events:" << journal::endl;
        refresh_fds();
        if ((nevents <= 0) && (errno != EINTR))
        {
            journal::error() << "epoll_wait() failed: (events count = " << color::yellow << nevents << color::z << "): " << color::deeppink8 <<  strerror(errno) << journal::endl;
            return rem::cc::failed;
        }
        for (int n = 0; n < nevents; n++)
        {
            for (auto&fd : _fds)
            {
                if (fd._fd ==_poll_events[n].data.fd)
                {
                    if (_poll_events[n].events & EPOLLIN)
                    {
                        if (fd._flags.active)
                        {
                            auto a = fd._read();
                            //journal::debug() << color::aqua << fd._id << color::z << ": [" << static_cast<int>(a) << "] " << rem::to_string(a) << journal::endl;
                            if (a != rem::action::cont){
                                //journal::info() << "[" << a << "] active lfd to be killed."  << journal::endl;
                                fd.kill();
                            }
                        }
                        else
                            journal::debug() << " invoked lfd is NOT active." << journal::endl;
                    }
                    if ((_poll_events[n].events & EPOLLHUP) || (_poll_events[n].events & EPOLLERR))
                    {
                        journal::info() << " broken link on '" << color::aqua << fd._id << color::z <<  journal::endl;
                        fd.kill();
                        continue;
                    }
                }
            }
        }
    }
    while (!_kill);

    close();
    return rem::cc::done;
}

rem::cc listener::poll(int _fd)
{
    auto [r, f] = query_lfd(_fd);
    if(!r)
    {
        journal::error() << " file descriptor #" << color::red4 << _fd << color::z << " is not registered into this listener's group." << journal::eol;
        return r;
    }

    auto nevents = epoll_wait(_epoll_fd, _poll_events, listener::max_events,-1);
    journal::info() << color::yellow << nevents << color::z << " events:" << journal::endl;
    refresh_fds();

    if ((nevents <= 0) && (errno != EINTR))
    {
        journal::error() << "epoll_wait() failed: (events count = " << color::yellow << nevents << color::z << "): " << color::deeppink8 <<  strerror(errno) << journal::endl;
        return rem::cc::failed;
    }
    rem::action A{};
    if(f._fd == _poll_events[0].data.fd)
    {
        if (_poll_events[0].events & EPOLLIN)
        {
            if (f._flags.active)
            {
                A = f._read(); // Actual read and process input data signal
                //journal::debug() << color::aqua << fd._id << color::z << ": [" << static_cast<int>(a) << "] " << rem::to_string(a) << journal::endl;
                if (A != rem::action::cont){
                    journal::info() << "[" << A << "] active lfd to be killed."  << journal::endl;
                    f.kill();
                    return rem::cc::terminate;
                }
            }
            else
                journal::debug() << " invoked lfd is NOT active." << journal::endl;
        }
        else
        {
            if ((_poll_events[0].events & EPOLLHUP) || (_poll_events[0].events & EPOLLERR))
            {
                journal::info() << " broken link on '" << color::aqua << f._id << color::z <<  journal::endl;
                f.kill();
                return rem::cc::terminate;
            }
        }
        return rem::cc::empty;
    }

    return rem::cc::ready;
}




std::pair<rem::cc, lfd &> listener::query_lfd(int fnum)
{
    for(auto& fd : _fds)
        if(fd._fd == fnum)
            return {rem::cc::ready, fd};

    //auto i = std::find_if(_fds.begin(), _fds.end(), [&](const auto& c){ return fnum == c._fd; });
    //if(i != _fds.end()) return {rem::cc::ready,*i};

    // Yes returns valid lfd, but we can modify it as we wish - not a good idea. Only temporary solution.
    return {rem::cc::rejected, lfd::null_};
}



rem::cc listener::refresh_fds()
{
    for (auto& fd : _fds)
    {
        if (fd._flags.kill || fd._flags.del)
        {
            journal::info() << "removing lfd: '" << color::aqua << fd._id << color::z << journal::endl;
            if (fd._flags.kill)
                detach(fd._fd);
            else
                epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, fd._fd, nullptr);
        }
    }
    return rem::cc::done;
}


rem::cc listener::open()
{
    _epoll_fd = epoll_create1(0);
    if (_epoll_fd < 0)
    {
        journal::error() << "epoll_create1() failed: " << strerror(errno) << journal::endl;
        return rem::cc::rejected;
    }

    journal::info() << "listener opened: file # " << color::yellow << _epoll_fd << color::z;
    journal::write() << "ready to run" << journal::endl;

    return rem::cc::ready;
}


rem::cc listener::close()
{
    _fds.clear();
    ::close(_epoll_fd);
    journal::info() << "listener is closed clean." << journal::endl;
    return rem::cc::ok;
}


} // namespace lux::io
