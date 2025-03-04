#include <obb/io/vchar.h>
#include <obb/notify.h>
#include <obb/object.h>
#include <obb/geometry.h>
#include <obb/io/listener.h>
#include <obb/io/kbhit.h>
#include <obb/io/mouse.h>
#include <termios.h>

// https://www.xfree86.org/current/ctlseqs.html
#define SET_X10_MOUSE 9
#define SET_VT200_MOUSE 1000
#define SET_VT200_HIGHLIGHT_MOUSE 1001
#define SET_BTN_EVENT_MOUSE 1002
#define SET_ANY_EVENT_MOUSE 1003
// --------------------------------------------

namespace obb::io
{


class OBBIOLIB terminal : public object
{
    struct termios _saved{}, _this{};
    // - The other structs when I will implement and use sub terminals in virtual pty.
    // ...
    //--------------------------------------------------------------------------------------
    ui::rectangle  _geometry{}; ///< Has implied : inner cursor, topleft position and dimensions.
    ui::color::pair _colors{};  ///< Fallback/restore original/reset colors.

    u8 _flags{0};
    u8 _state{0};


    static constexpr u8 st_saved         = 1;
    static constexpr u8 st_mouse_enabled = 2;
    static constexpr u8 st_activated     = 4;
    static constexpr u8 st_raw_set       = 8;
    static constexpr u8 st_poll_started  = 0x10;
    static constexpr u8 st_poll_closed   = 0x20;
    static constexpr u8 st_caret_on      = 0x40;


    int _epoll_fd{-1};
    epoll_event _poll_events[4]{};
    lfd _fd0{};
    signals::notify_action<ui::rectangle> _window_resize_signal{"terminal resize signal notifier"};
    void resize_signal(int );
public:

    static constexpr u8 use_mouse               = 1;
    static constexpr u8 report_mouse_position   = 2;
    static constexpr u8 report_mouse_buttons    = 4;
    static constexpr u8 use_double_buffer       = 8;    ///< Also tells console to save and clear the initial screen then restore it at exit.
    static constexpr u8 auto_hide_caret         = 0x10; ///< Hide the caret when not on keyboard input prompt.


    enum caret_shapes: u8
    {
        def,
        bloc_blink,
        block_steady,
        under_blink,
        under_steady,
        vbar_blink,
        vbar_steady
    }cursor_shape{def};


    static constexpr auto LINE_WRAP                 = "7";
    static constexpr auto CRS_SHAPE                 = "25";
    static constexpr auto MOUSE_X10                 = "9 ";
    static constexpr auto SET                       = 'h';
    static constexpr auto RESET                     = 'l';
    static constexpr auto MOUSE_VT200               = "\x1b[?1000";
    static constexpr auto MOUSE_VT200_HL            = "\x1b[?1001";
    static constexpr auto MOUSE_REPORT_BUTTONS      = "\x1b[?1002";
    static constexpr auto MOUSE_REPORT_ANY          = "\x1b[?1003";
    static constexpr auto MOUSE_UTF8                = "\x1b[?1005";
    static constexpr auto MOUSE_SGR_EXT_MODE        = "\x1b[?1006";
    static constexpr auto MOUSE_URXVT_MODE          = "\x1b[?1015";
    static constexpr auto MOUSE_SGR_PIXEL_MODE      = "\x1b[?1016";
    static constexpr auto ALTERNATE_SCREEN          = "\x1b[?1049";
    static constexpr auto CSI                       = "\x1b[";
    static constexpr auto CSI_BOLD                  = "\x1b[1m";
    static constexpr auto CSI_UNDERLINE             = "\x1b[4m";
    static constexpr auto CSI_REVERSE               = "\x1b[7m";
    static constexpr auto CSI_STRIKETHROUGH         = "\x1b[35m";
    static constexpr auto CSI_UNDERLINE_PREVIOUS    = "\x1b[90m";
    static constexpr auto CSI_UNDERLINE_NEXT        = "\x1b[92m";
    static constexpr auto CSI_UNDERLINE_INCREMENT   = "\x1b[93m";
    static constexpr auto CSI_UNDERLINE_DECREMENT   = "\x1b[94m";

    terminal() = default;
    terminal(terminal* parent_term, const std::string& _name_id, ui::rectangle dim /* , ... */);
    ~terminal() override;

    rectangle geometry();
    rem::cc enable_mouse();
    rem::cc stop_mouse();
    rem::cc query_winch();
    rem::cc begin(std::string_view name_id);
    rem::cc end();

    void switch_alternate();
    void switch_back();
    void clear();
    void cursor_off();
    void cursor_on();
    bool cursor(ui::cxy xy);

    rem::cc render(vchar::bloc* blk, ui::cxy xy={0,0});
    rem::cc init_stdinput();

    struct OBBIOLIB event{
        enum evt {KEV,MEV,WIN,UND}type{evt::UND};
        union {
            mouse mev;
            kbhit kev;
            ui::size win;
        }data{};

        template<typename EVT> bool is(){
            if(type == KEV) return std::is_same<kbhit, EVT>();
            if(type == MEV) return std::is_same<mouse, EVT>();
            if(type == WIN) return std::is_same<ui::size, EVT>();
            return false;
        }
        operator bool() { return type != evt::UND; }

        using queue = std::deque<terminal::event>;
    };

    rem::cc poll_in();
    terminal& get_current();
    rem::cc enque(event&& ev);
    terminal::event::queue& events() { return _events; }
    void push_event(terminal::event&& ev);

private:

    rem::action parse_stdin(io::lfd& ifd);
    rem::cc stdin_proc();

    terminal::event::queue _events{};

    using termslist = std::map<std::string, terminal*>;
    static termslist terms;


    signals::notify_action<rectangle>& term_resize_signal();
};






} // namespace obb::io
