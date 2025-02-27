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

#include <obb/logbook.h>
#include <obb/notify.h>
#include <arpa/inet.h>
#include <obb/notify.h>
#include <obb/io/export.h>

using namespace obb::integers;
namespace obb::io
{

class OBBIOLIB lfd
{
    CLASSNAME(lfd)
    static lfd null_;
    u64 _block_size{0}; ///< Actual io kernel read buffer size ( fd,socket,...)
    u8* _buffer_ptr{nullptr}; ///< Either external or internal buffer pointer.
    u64 _window_block_size{0}; ///< Not circular mode: Expecting bytes window block size. In Circular mode : The length of the buffer.
    u64 _waiting_bytes{0};
    bool _extern{false}; ///< true = _buffer_ptr is external ( do not delete from this ).

    u8* _head{_buffer_ptr}; ///< Insert pointer
    u8* _tail{_head};
    u8* _end{_buffer_ptr}; ///< end pointer.

    int _fd{-1};
    std::string _id{"unnamed"};
    u16 _bits{0};
    u16  _poll_bits{0};

    struct flags
    {
        u8 active :1; ///< This lfd is active and monitored. - If not active then it is not monitored...Obviously ;)
        u8 del    :1; ///< This lfd is inactive , set to be removed from the epoll set but not 'killed'.
        u8 pause  :1; ///< This lfd is set to pause, stopping its polling activity until resumed by setting its active bit on.
        u8 kill   :1; ///< This lfd is set to be 'killed' - removed from the epoll set and from the listener's list.
    }_flags = {0,0,0,0};
    friend class listener;
public:

    std::string id() const { return _id; }

    using list = std::vector<lfd>;

    static constexpr u16 IMM    = 0x01; ///< Set = No pre-fill
    static constexpr u16 READ   = 0x02; ///< Set = READ slot
    static constexpr u16 WRITE  = 0x04; ///< Set = WRITE slot
    static constexpr u16 BLOC   = 0x08; ///< Set = Blocking. Unset = non-blocking.
    static constexpr u16 CIRC   = 0x10; ///< Set = Circular Fixed-size buffer. Unset = Segment block Window.
    static constexpr u16 EXT    = 0x40; ///< Set = _buffer_ptr_ is external

    lfd()=default;
    lfd(std::string  _id, int _file_num, u64 _window_block_size, u64 _operator_bits, int _polling_bits, u8* _buf_ptr=nullptr);
    lfd(const lfd& other)            =delete;
    lfd& operator=(const lfd& other) =delete;
    lfd(lfd&& other)                 =default;
    lfd& operator=(lfd&& other)      =default;

    ~lfd();


    u64& operator[](u64 i) { return ((u64*)_buffer_ptr)[i]; }
    u32& operator[](u32 i) { return ((u32*)_buffer_ptr)[i]; }
    u16& operator[](u16 i) { return ((u16*)_buffer_ptr)[i]; }
    u8&  operator[](u8 i)  { return _buffer_ptr[i]; }

    integers::i16 ntohs() const { return ::ntohs(static_cast<integers::i16>(*_tail)); }
    integers::i32 ntohl() const { return ::ntohl(static_cast<integers::i32>(*_tail)); }
    integers::i16 htons() const { return ::htons(static_cast<integers::i16>(*_tail)); }
    integers::i32 htonl() const { return ::htonl(static_cast<integers::i32>(*_tail)); }

    lfd& operator << (u8 u);
    lfd& operator >> (u8& u);
    u8&   operator*();

    [[nodiscard]] size_t size() const;

    rem::cc init();
    bool full();
    bool empty();
    size_t free();
    void activate();
    void kill();
    template<typename Class> i16 set_read_notify(Class* obj, rem::action(Class::*delegate_fn)(lfd&))
    {
        return _read_ready.connect(obj, delegate_fn);
    }

    template<typename Class> i16 set_write_notify(Class* obj, rem::action(Class::*delegate_fn)(lfd&))
    {
        return _read_ready.connect(obj, delegate_fn);
    }
    void configure(u64 _opt, u64 _window_size, u64 _operation_bits);


    void pause();
    void resume();
    void terminate();
    int fd() { return _fd; }
    u64 waiting_bytes() { return _waiting_bytes; }
    void clear() { _waiting_bytes = 0; _head=_tail=_buffer_ptr;  std::memset(_buffer_ptr,0,_window_block_size);}
private:
    signals::notify_action<lfd&> _read_ready {"read delegator"};
    signals::notify_action<lfd&> _write_ready{"write delegator"};
    signals::notify_action<lfd&> _zero_read  {"aero read delegator"};

    rem::action _read();
    rem::action _write();

    void _push_left();
    friend class ipoll;

};

};
