// https://github.com/sstokic-tgm/Gladiatorcheatz-v2.1/blob/master/math/Vector.hpp
// https://github.com/A200K/AssaultCube_Hack/blob/master/AssaultCube%20Hack/Classes.h
#pragma once
#include <sstream>

class v2
{
public:

    v2()
    {
        x = 0;
        y = 0;
    }

    v2(float f_x, float f_y)
    {
        x = f_x;
        y = f_y;
    }

    v2(const float* f_n)
    {
        x = f_n[0];
        y = f_n[1];
    }

    __inline bool is_valid() const // not used in this project but just in case I ever need it.
    {
        return std::isfinite(x) && std::isfinite(y);
    }

    float length() const
    {
        return sqrt(x * x + y * y);
    }

    float length_sqr(void) const
    {
        return (x * x + y * y);
    }

    float dist_to_sqr(const v2& v2_n) const
    {
        v2 delta;

        delta.x = x - v2_n.x;
        delta.y = y - v2_n.y;

        return delta.length_sqr();
    }

    void normalize()
    {
        float f_length = this->length();
        if (f_length) {
            x *= 1 / f_length;
            y *= 1 / f_length;
        }
    }

    v2& operator=(const v2& v2_n)
    {
        x = v2_n.x;
        y = v2_n.y;
        return *this;
    }

    v2 operator-(void) const
    {
        return v2(-x, -y);
    }

    v2 operator+(const v2& v2_n) const
    {
        return v2(x + v2_n.x, y + v2_n.y);
    }

    v2 operator+(float f_n) const
    {
        return v2(x + f_n, y + f_n);
    }

    v2 operator-(const v2& v2_n) const
    {
        return v2(x - v2_n.x, y - v2_n.y);
    }

    v2 operator-(float f_n) const
    {
        return v2(x - f_n, y - f_n);
    }

    v2 operator*(float f_n) const
    {
        return v2(x * f_n, y * f_n);
    }

    v2 operator*(const v2& v2_n) const
    {
        return v2(x * v2_n.x, y * v2_n.y);
    }

    v2 operator/(float f_n) const
    {
        return v2(x / f_n, y / f_n);
    }

    v2 operator/(const v2& v2_n) const
    {
        return v2(x / v2_n.x, y / v2_n.y);
    }

    bool operator==(const v2& v2_n) const
    {
        return (v2_n.x == x) && (v2_n.y == y);
    }

    bool operator!=(const v2& v2_n) const
    {
        return (v2_n.x != x) || (v2_n.y != y);
    }

    v2& operator+=(const v2& v2_n)
    {
        x += v2_n.x;
        y += v2_n.y;
        return *this;
    }

    v2& operator-=(const v2& v2_n)
    {
        x -= v2_n.x;
        y -= v2_n.y;
        return *this;
    }

    v2& operator*=(float f_n)
    {
        x *= f_n;
        y *= f_n;
        return *this;
    }

    v2& operator*=(const v2& v2_n)
    {
        x *= v2_n.x;
        y *= v2_n.y;
        return *this;
    }

    v2& operator/=(const v2& v2_n)
    {
        x /= v2_n.x;
        y /= v2_n.y;
        return *this;
    }

    v2& operator+=(float f_n)
    {
        x += f_n;
        y += f_n;
        return *this;
    }

    v2& operator/=(float f_n)
    {
        x /= f_n;
        y /= f_n;
        return *this;
    }

    v2& operator-=(float f_n)
    {
        x -= f_n;
        y -= f_n;
        return *this;
    }

    float& operator[](int i)
    {
        return ((float*)this)[i];
    }

    float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    float x, y;
};