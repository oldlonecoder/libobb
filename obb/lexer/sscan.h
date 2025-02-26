//
// Created by oldlonecoder on 24-06-14.
//

/******************************************************************************************
 *   Copyright (C) ...,2024,... by Serge Lussier                                          *
 *   serge.lussier@oldlonecoder.club                                                      *
 *   ----------------------------------------------------------------------------------   *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier).                                                       *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here.                    *
 *   Open source FREE licences also apply To the Code from the author (Serge Lussier)     *
 *   ----------------------------------------------------------------------------------   *
 *   Usual GNU FREE GPL-1,2, MIT... apply to this project.                                *
 ******************************************************************************************/



#pragma once

#include <lus/string.h>
#include <lus/lexer/export.h>
 
using namespace std::literals;

namespace lus
{

class LUSLEXERLIB sscan
{
    const char* m_end{nullptr};
    const char* m_pos{nullptr};
    const char* m_begin{nullptr};


public:

    using iterator = const char*;

    struct LUSLEXERLIB  [[maybe_unused]] context
    {
        sscan::iterator m_pos{nullptr};
        sscan::iterator m_begin{nullptr};
        rem::cc  Return{rem::cc::notimplemented};
        //...
    };

    struct LUSLEXERLIB numeric
    {
        private:
        static sscan empty;
        public:

        struct LUSLEXERLIB details
        {
            std::string_view seq;
            enum class base_size : char
            {
                Binary,Octal,Decimal, Hexadecimal

            }base{sscan::numeric::details::base_size::Decimal };
            enum class size_type: char
            {
                I8,U8,I16,U16,I32,U32,I64,U64,F32,F64,F128
            }size{size_type::F64};
            bool real{false};
            double value;

            [[nodiscard]] bool I8()   const {return size == size_type::I8; }
            [[nodiscard]] bool U8()   const {return size == size_type::U8; }
            [[nodiscard]] bool I16()  const {return size == size_type::I16; }
            [[nodiscard]] bool U16()  const {return size == size_type::U16; }
            [[nodiscard]] bool I32()  const {return size == size_type::I32; }
            [[nodiscard]] bool U32()  const {return size == size_type::U32; }
            [[nodiscard]] bool I64()  const {return size == size_type::I64; }
            [[nodiscard]] bool U64()  const {return size == size_type::U64; }
            [[nodiscard]] bool F32()  const {return size == size_type::F32; }
            [[nodiscard]] bool F64()  const {return size == size_type::F64; }
            [[nodiscard]] bool F128() const {return size == size_type::F128; }

            [[nodiscard]] bool Decimal() const { return base == base_size::Decimal; }
            [[nodiscard]] bool Binary() const { return base == base_size::Binary; }
            [[nodiscard]] bool Octal() const { return base == base_size::Octal; }
            [[nodiscard]] bool Hexadecimal() const { return base == base_size::Hexadecimal; }
            [[nodiscard]] bool Float() const { return real; }

            void scale_value();
        };

        using result = std::pair<rem::cc, sscan::numeric::details>;

        sscan& text{sscan::numeric::empty};

        std::string_view seq{};

        sscan::iterator m_end{nullptr};
        sscan::iterator m_pos{nullptr};
        sscan::iterator m_begin{nullptr};

        bool real{false};
        details num_details{};
        numeric() = default;
        explicit numeric(sscan& Tx);


        ~numeric() = default;
        rem::cc operator()();


        rem::cc base2();
        rem::cc base8();
        rem::cc base10();
        rem::cc base16();

        void sign();
    };

public:
    struct LUSLEXERLIB location_data
    {
        // { \n; \n\r; \r\n; \r }
        std::size_t line{0};
        std::size_t col{0};
        std::size_t offset{0};
        std::size_t prevline{0};
        std::size_t prevcol{0};
        location_data const & operator >> (std::string& out) const;
    };

    sscan() = default;
    explicit sscan(std::string_view Txt);

    sscan(sscan&& ) noexcept = default;
    sscan(sscan&  ) = default;
    ~sscan() = default;

    sscan& operator = (sscan&&) noexcept = default;
    sscan& operator = (sscan const &) = default;
    sscan& operator = (std::string_view view);

    location_data& location() { return m_location; }

    bool skip_ws();

    sscan::location_data& sync();

    bool eof();
    bool eof(sscan::iterator cc);

    rem::cc seek(int32_t Idx = 0);
    rem::cc step(int32_t Idx = -1);
    rem::cc seek_at(const std::string_view& seq, int32_t m_pos=-1);

    explicit operator bool() const;
    [[nodiscard]] inline bool empty() const { return m_end==m_begin;}

    auto operator*() const  { return *m_pos; }
    sscan::iterator operator()() const { return m_pos; }


    //  -   Need more check and use cases...:
    //    auto  operator +( size_t sz );
    //    string_scan&  operator += ( size_t sz );
    //------------------------------------------------
    bool         operator ++();
    bool         operator ++(int);

    //Scanners:
    sscan::numeric::result scan_number();
    std::pair<rem::cc, std::string_view> scan_literal_string();
    std::pair<rem::cc, std::string_view> scan_identifier();

    sscan::iterator start_sequence();
    std::pair<sscan::iterator,sscan::iterator> end_sequence();
    void back(sscan::iterator m_pos)
    {
        m_pos = m_pos;
        sync();
    }
    std::pair<sscan::iterator, sscan::iterator> scan(const std::function<rem::cc()>& ScannerFn);

    // ------------------------------------------------------------------
    void push_location();
    bool pop_location();

    void push();
    bool pop();


    std::string mark();

    // - Can only advance. For backward, juste save the current position.
    //    bool         operator --();
    //    bool         operator --(int);
    // -----------------------------------------------------------------------
    sscan::iterator begin();
    sscan::iterator end();


    rem::cc reposition(std::size_t Offset);


private:

    location_data m_location{};
    std::vector<std::pair<std::size_t,std::size_t>> m_points;
    std::stack<sscan::iterator> p_stack{};

};

} // CC
