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

#include <map>
#include <vector>
#include <bitset>
#include <obb/logbook.h>
#include <obb/io/kbhit.h>
#include <obb/io/mouse.h>
#include <obb/ui/export.h>
#include <queue>
#include <variant>

namespace obb::ui
{


/*!
 * \brief The event class
 *
 * \note Inpired from the new SFML-3.0 event model : https://www.sfml-dev.org/documentation/3.0.0/
 *       I want to explore the same approche here...
 */
struct OBBTUILIB event
{

    std::bitset<64> events{0}; ///< => 2xu32 ?


    /*!
     * \brief The command class
     */
    struct OBBTUILIB command
    {
        enum code : U64
        {
            CANCEL,
            OK,
            DISMISS,
            ACCEPTED,
            CLOSE,
            OPEN,

            //...
            NO_CMD
        }val{command::code::NO_CMD};

        command(command::code cval): val(cval){};
        rem::cc state{rem::cc::notexist};
    };

    /*!
     * \brief The keypress class
     */
    struct OBBTUILIB keypress
    {
        io::kbhit   key{};
    };


    /*!
     * \brief The file input class
     */
    struct OBBTUILIB finput
    {
        u8* data{nullptr};
    };

    /*!
     * \brief The mouse class
     */
    struct OBBTUILIB mouse
    {
        io::mouse data{};
    };

    struct OBBTUILIB resize
    {
        ui::size dim{};
    };

    template<typename evt> event(const evt& e);

    using queue = std::queue<event>;
    std::variant< event::command, event::keypress, event::finput, event::mouse, event::resize > data;



    ////////////////////////////////////////////////////////////
    /// \brief Check current event_type
    ///
    /// \tparam `EVT` Type of the event_type to check against
    ///
    /// \return `true` if the current event_type matches given template parameter
    ///
    ////////////////////////////////////////////////////////////
    template <typename EVT> [[nodiscard]] bool is() const;

    ////////////////////////////////////////////////////////////
    /// \brief Attempt to get specified event event_type
    ///
    /// \tparam `event_type` Type of the desired event event_type
    ///
    /// \return Address of current event event_type, otherwise `nullptr`
    ///
    ////////////////////////////////////////////////////////////
    template <typename EVT> [[nodiscard]] const EVT* get() const;

    ////////////////////////////////////////////////////////////
    /// \brief Apply a visitor to the event
    ///
    /// \param visitor The visitor to apply
    ///
    /// \return The result of applying the visitor to the event
    ///
    ////////////////////////////////////////////////////////////
    template <typename T> decltype(auto) visit(T&& visitor) const;



private:
    ////////////////////////////////////////////////////////////
    // Helper functions
    ////////////////////////////////////////////////////////////
    template <typename T, typename... Ts> [[nodiscard]] static constexpr bool is_in_params_pack(const std::variant<Ts...>*)
    {
        return (std::is_same_v<T, Ts> || ...);
    }

    template <typename T> static constexpr bool is_event_type = is_in_params_pack<T>(decltype (&data)(nullptr));


    rem::cc translate();

};



}

#include <obb/ui/event.inline>

////////////////////////////////////////////////////////////
/// \class obb::ui::event
/// \ingroup events
///
/// `obb::ui::event` holds all the information about a system event
/// that just happened. Events are retrieved using the
/// `obb::io::listener::loop->signal` from `obb::ui::application::poll_event()` functions.
///
/// A `ui::event` instance contains the event_type of the event
/// (mouse moved, key pressed, window closed, ...) as well
/// as the details about this particular event. Each event
/// corresponds to a different event_type struct which contains
/// the data required to process that event.
///
/// Event event_types are event types belonging to `ui::event`,
/// such as `ui::event::command` or `ui::event::mouse`.
///
/// The way to access the current active event event_type is via
/// `ui::event::get<>`. This member function returns the address
/// of the event event_type struct if the event event_type matches the
/// active event, otherwise it returns `nullptr`.
///
/// `ui::event::is` is used to check the active event event_type
/// without actually reading any of the corresponding event data.
///
/// \code
/// while (const std::optional event = application::poll_event())
/// {
///     // Application close request by escape key pressed: exit
///     if (event->is<ui::event::command>() ||
///         (event->is<ui::event::key_press>() &&
///          event->get<ui::event::key_press>()->key.code == io::kbhit::ESC))
///         Application::app().terminate(rem::cc::terminate);
///
///     // ui::console::resize signal:
///     if (const auto* resized = event->get<ui::event::console_resize>())
///     {
///         book::status() << "Console resize: " << color::yellow << resized->dim.to_string() << color::z << book::endl;
///         //...
///     }
///
///     // etc ...
/// }
/// \endcode
///
////////////////////////////////////////////////////////////
