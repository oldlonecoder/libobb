/******************************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                                        *
 *   serge.lussier@oldlonecoder.club                                                      *
 *                                                                                        *
 *                                                                                        *
 *   Unless otherwise specified, all code in this project is written                      *
 *   by the author (Serge Lussier)                                                        *
 *   and no one else then not even {copilot, chatgpt, or any other AI calamities}         *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply To the code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 ******************************************************************************************/


#pragma once

#include <lus/journal.h>
#include <lus/lexer/lexer_types.h>
//#include <lus++/defs.h>

#include <memory>
#include <vector>
#include <map>
#include <stack>

#include <lus/est/export.h>
namespace lus::est
{
/*!
 * @brief Arithmetic Logical Unit
 *
 *
 
 * @author &copy; 2014(using union),2020(using std::any),2022(back to union); Serge Lussier, oldlonecoder/bretzel/Bretzelus++/Bretzel, (lussier.serge@gmail.com/serge.lussier@oldlonecoder.club)
 *
 */

struct LUSESTLIB alu
{

    static std::string mNil;


    lex::type::T  T {lex::type::Float}; ///< Default Type.

    std::string text;
    union val
    {// Create std::string pool for managing assign-release cycle of std::string* in alu;
        std::string* t;
        float        d;
        void*        p;

        val& operator=(double v_)   { d = v_; return *this;}
        val& operator=(uint64_t v_) { d = v_; return *this;}
        val& operator=(int64_t v_)  { d = v_; return *this;}
        val& operator=(void* v_)    { p = v_; return *this;}
        val& operator=(std::string* v_) { t = v_; return *this;}
    }v = {0};

    enum  CNV {
        DEG,
        RAD
    };

    alu();

    alu(const alu&) = default;
    alu(double A_);
    alu(float A_);
    //alu(token* rhs);

    alu(const std::string & A_);
    alu(const char* A_);
    alu(void* A_);
    alu(alu&&) noexcept = default;
    alu(int8_t A_);
    alu(int16_t A_);
    alu(int32_t A_);
    alu(int64_t A_);
    alu(uint8_t A_);
    alu(uint16_t A_);
    alu(uint32_t A_);
    alu(uint64_t A_);
    alu(bool A_);



    alu& operator =(const alu & Lhs_);// { a = lf.a; T = lf.T; return *this; }
    alu& operator =(alu && rhs) noexcept = default;
    alu operator==(const alu & lf) const;

    [[nodiscard]] lex::type::T TypeOf() const { return T; } // [const] Sous r�serve; [const] provided that it is not screwing access...

#pragma region Huge_Overload
    template<typename oftype> [[nodiscard]]oftype value() const {

        //rem::debug() << lus::fn::function << "> this = " << lus::color::lightcyan3 <<  v.d << lus::color::reset << " : types: " << lex::glex_component::type_name(T) << lus::fn::endl;

        if constexpr ((std::is_same_v<oftype, std::string>) || (std::is_same_v<oftype, const std::string&>))
            return (T & lex::type::Text ? text : "");
        else
        if constexpr (std::is_same_v<oftype, const char*>)
            return (T & lex::type::Text ? text.c_str() : nullptr);
        else
        if constexpr (std::is_same_v<oftype, void*>)
            return v.p;
        else
        return static_cast<oftype>(
                T & lex::type::I8 ? v.d :
                T & lex::type::I16 ? v.d :
                T & lex::type::I32 ? v.d :
                T & lex::type::I64 ? v.d :
                T & lex::type::U8 ? v.d :
                T & lex::type::U16 ? v.d :
                T & lex::type::U32 ? v.d :
                T & lex::type::U64 ? v.d :
                T & lex::type::Bool ? v.d :
                T & lex::type::Float ? v.d : 0
            );
    }

    template<typename oftype> [[nodiscard]] oftype number() const
    {
        //rem::debug() << lus::fn::function << "> this = " << lus::color::lightcyan1 << v.d << lus::color::reset << " : types: " << lex::glex_component::type_name(T);
        if constexpr (std::is_same_v<oftype, void*>)
            return v.p;
        else
        if constexpr (std::is_same_v<oftype, std::string>)
            return (std::string)*this;
        else
        return static_cast<oftype>(T & lex::type::Number ? v.d:0);
    }

    template<lex::type::T V> bool is() const
    {
        return T == V;
    }

#pragma endregion Huge_Overload
    [[maybe_unused]]bool is_text() const { return T & lex::type::Text; }
    [[maybe_unused]] bool is_numeric() const { return T & lex::type::Number; }
    [[maybe_unused]] [[nodiscard]]std::string semantic() const {return lexer_component::type_name(T);}
    virtual ~alu();



    // Arithmetic operations overload between two alu's:

    // Binary operators:

    alu operator +(const alu & Rhs_) const;
    alu operator -(const alu & Rhs_);
    alu operator *(const alu & Rhs_) const;
    alu operator [](alu::CNV Cnv_);

    alu operator /(const alu & Rhs_);
    alu operator %(const alu & Rhs_) const;
    alu operator ^(const alu & Rhs_) const;
    alu operator <<(const alu & Lhs_) const;
    alu operator >>(const alu & Lhs_) const;
    alu operator |(const alu & Lhs_) const;
    alu operator &(const alu & Lhs_) const;
    alu operator ~();
    // assign operators:
    alu& operator +=(const alu & Rhs_);
    alu& operator -=(const alu & Rhs_);
    alu& operator *=(const alu & Rhs_);
    alu& operator /=(const alu & Rhs_);
    alu& operator %=(const alu & Rhs_);
    alu& operator |=(const alu & Rhs_);
    alu& operator &=(const alu & Rhs_);
    alu& operator ^=(const alu & Rhs_);

    alu& operator <<=(const alu & Rhs_);
    alu& operator >>=(const alu & Rhs_);


    // boolean operators:
    alu operator >(const alu & Rhs_);
    alu operator <(const alu & Rhs_);
    alu operator >=(const alu & Rhs_);
    alu operator <=(const alu & Rhs_);
    alu operator !=(const alu & Rhs_);
    alu operator ||(const alu & Rhs_);
    alu operator &&(const alu & Rhs_);

    bool operator !();
    //bool IsSet() { return r.has_value(); }
    operator bool() const;

    alu operator -();
    alu operator +();

    alu operator ++(int);
    alu operator ++();
    alu operator --();
    alu operator --(int);

    alu radical(const alu & Lhs_) const;
    //alu factorial(const alu & Lhs_) const; //?????
    alu factorial() const;
    bool type_size(const alu & Rhs_) const;
    std::string operator()()const { return (std::string) *this; }
    operator std::string() const;
    std::string to_str() const;
    alu& operator *() { return *this; }

    //    private:
    //    alu remove_substr_copy(const std::string& to_erase);
    //    alu completely_remove_substr_copy(const std::string& to_erase);
    //    alu& remove_substr(const std::string& to_erase);
    //    alu& completely_remove_substr(const std::string& to_erase);







    template<lex::type::T V> bool is() {
        return T == V;
    }

};
}
