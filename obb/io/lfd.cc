//
// Created by oldlonecoder on 27/12/24.
//

#include <lus/io/lfd.h>
#include <sys/ioctl.h>

//#include <utility>

namespace lus::io
{


lfd lfd::null_{"null",-1,0,0,0,nullptr};


lfd::lfd(std::string  a_id, int _file_num, u64 _window_block_size, u64 _operation_bits, int _polling_bits, u8* _buf_ptr):
_window_block_size(_window_block_size),
_bits(_operation_bits),
_poll_bits(_polling_bits),
_fd(_file_num)
{
    _id = a_id + " #" + std::to_string(_fd);
}


lfd::~lfd()
{
    if (_bits & lfd::EXT) return;
    delete[] _buffer_ptr;
    _read_ready.disconnect_all();
    _write_ready.disconnect_all();
}


lfd& lfd::operator<<(u8 u)
{
    if (full())
    {
        journal::error() << "Attempt to write into a full lfd";
        return *this;
    }
    *_head++ = u;
    return *this;
}


lfd& lfd::operator>>(u8& u)
{
    if(empty())
    {
        u = 0;
        return *this;
    }
    u = *_tail++;
    return *this;
}


u8& lfd::operator*()
{
    return *_tail;
}


size_t lfd::size() const
{
    return _head - _tail;
}

/*!
 * \brief lfd::init
 * Initializes the internal buffer to the required size of bytes. Zero'ing it, then assign its pointers.
 *
 * \return  accepted/done on exit method
 *
 * \note This version only implements the circular buffer.
 */
rem::cc lfd::init()
{

    if(!(_bits & lfd::EXT))
    {    delete [] _buffer_ptr;
        _buffer_ptr = new u8[_window_block_size+2];
    }

    std::memset(_buffer_ptr,0,_window_block_size);
    _tail = _head = _buffer_ptr;
    _end    = _buffer_ptr + _window_block_size;

    // ...

    return rem::cc::done;
}

bool lfd::full() { return _head >= _end; }
bool lfd::empty() { return _tail == _head; }
void lfd::pause() { _flags = {0,1,1,0}; }
void lfd::resume() { _flags = {1,0,0,0}; }
void lfd::terminate() { _flags = {0,1,0,1}; }
size_t lfd::free() { return _end - _head; }


void lfd::activate()
{
    _flags = {1,0,0,0};
}


void lfd::kill()
{
    _flags = {0,1,0,1};
}


void lfd::configure(u64 _opt, u64 _window_size, u64 _operation_bits)
{
    _bits = _operation_bits;
    _poll_bits = _opt;
    _window_block_size = _window_size;
    (void)init();
}



/*!
 * \brief lfd::_read
 * \return rem::action::cont or end
 *
 * \note
 *      This version only implements pre-allocated/configured linear buffer:
 *      _buffer_ptr <= _tail <= _head <= _end;
 */
rem::action lfd::_read()
{
    if(full())
    {
        journal::warning() << " buffer is full" << journal::endl;
        pause();
        return rem::action::cont;
    }

    if(_tail > _buffer_ptr) _push_left();

    ioctl(_fd,FIONREAD, &_waiting_bytes);
    //journal::debug() << " number of bytes to read in #" << color::yellow << _fd << color::reset << ":" << color::lime << _waiting_bytes << journal::endl;

    const auto nbytes = std::min(_waiting_bytes,free());
    //journal::write() << " effective number of bytes to read in #" << color::yellow << _fd << color::reset << ":" << color::lime << nbytes << journal::endl;
    if(!nbytes)
    {

        journal::message() << " triggering descriptor on zero-byte signal..." << journal::eol;
        //...
        return _zero_read(*this);
    }

    ::read(_fd, _head, nbytes);
    _head += nbytes;

    if(_bits & lfd::IMM)
    {
        auto c = rem::action::enter;
        while(!empty())
        {
            c = _read_ready(*this);
            if(c == rem::action::cont)
                continue;
            else
                return c;
        }
    }
    else
        if (full())
            return _read_ready(*this);

    //...
    return rem::action::cont;
}

void lfd::_push_left()
{
    if(empty() || full())
        return;

    auto width = _head - _tail;
    std::memmove(_buffer_ptr,_tail,width); // Yes, segment can overlap (memmove manual) ...
    _tail = _buffer_ptr;
    _head -= width;
}


}// namespace lux::io
