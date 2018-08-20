#ifndef _HSLIB_VARIANT_H_INCLUDED_
#define _HSLIB_VARIANT_H_INCLUDED_

#include <string>
#include <ctime>

class Variant 
{
    public:
        enum VariantType { CHAR, SHORT, INT, LONG, FLOAT, DOUBLE, TIME, STRING };

    private:
        union {
            char c;
            short sh;
            int i;
            long l;
            float f;
            double d;
            struct tm t;
        } data;
        std::string s;
        VariantType type;

    public:
        Variant() : data(), s(), type(CHAR) { }
        ~Variant() { }

        Variant(char c) : data(), s(), type(CHAR)  { data.c = c; }
        Variant(short sh) : data(), s(), type(SHORT)  { data.sh = sh; }
        Variant(int i) : data(), s(), type(INT)  { data.i = i; }
        Variant(long l) : data(), s(), type(LONG)  { data.l = l; }
        Variant(float f) : data(), s(), type(FLOAT)  { data.f = f; }
        Variant(double d) : data(), s(), type(DOUBLE)  { data.d = d; }
        Variant(struct tm& t) : data(), s(), type(TIME) { data.t = t; }
        Variant(const std::string s)  : data(), s(), type(STRING)  { this->s = s; }

        const VariantType getType() const { return type; }

        inline const char toChar() const { return type == CHAR ? data.c : '\0'; }
        inline const short toShort() const { return type == SHORT ? data.sh : 0; }
        inline const int toInt() const { return type == INT ? data.i : 0; }
        inline const long toLong() const { return type == LONG ? data.l : 0L; }
        inline const float toFloat() const { return type == FLOAT ? data.f : 0.0f; }
        inline const double toDouble() const { return type == DOUBLE ? data.d : 0.0; }
        inline const struct tm toTime() const { struct tm _tm; return type == TIME ? data.t : _tm; }

        inline Variant& set(const char c) { data.c = c; type = CHAR; return *this; }
        inline Variant& set(const short sh) { data.sh = sh; type = SHORT; return *this; }
        inline Variant& set(const int i) { data.i = i; type = INT; return *this; }
        inline Variant& set(const long l) { data.l = l; type = LONG; return *this; }
        inline Variant& set(const float f) { data.f = f; type = FLOAT; return *this; }
        inline Variant& set(const double d) { data.d = d; type = DOUBLE; return *this; }
        inline Variant& set(const struct tm& t) { data.t = t; type = TIME; return *this; }
        inline Variant& set(const std::string s) { this->s = s; type = STRING; return *this; }

        const std::string toString() const;
};

#endif // _HSLIB_VARIANT_H_INCLUDED_
