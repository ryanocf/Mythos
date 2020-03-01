// https://github.com/sstokic-tgm/Gladiatorcheatz-v2.1/blob/master/math/Vector.hpp
// https://github.com/A200K/AssaultCube_Hack/blob/master/AssaultCube%20Hack/Classes.h
#pragma once
#include <sstream>

class v3
{
public:
    
    v3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    v3(float f_x, float f_y, float f_z)
    {
        x = f_x;
        y = f_y;
        z = f_z;
    }

    v3(const float* f_n)
    {
        x = f_n[0];
        y = f_n[1];
        z = f_n[2];
    }

    __inline bool is_valid() const // not used in this project but just in case I ever need it.
    {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    float length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    float length_sqr(void) const
    {
        return (x * x + y * y + z * z);
    }

    float dist_to_sqr(const v3& v3_n) const
    {
        v3 delta;

        delta.x = x - v3_n.x;
        delta.y = y - v3_n.y;
        delta.z = z - v3_n.z;

        return delta.length_sqr();
    }

    void normalize()
    {
        float f_length = this->length();
        if (f_length) {
            x *= 1 / f_length;
            y *= 1 / f_length;
            z *= 1 / f_length;
        }
    }

    v3& operator=(const v3& v3_n)
    {
        x = v3_n.x;
        y = v3_n.y;
        z = v3_n.z;
        return *this;
    }

    v3 operator-(void) const
    {
        return v3(-x, -y, -z);
    }

    v3 operator+(const v3& v3_n) const
    {
        return v3(x + v3_n.x, y + v3_n.y, z + v3_n.z);
    }

    v3 operator+(float f_n) const
    {
        return v3(x + f_n, y + f_n, z + f_n);
    }

    v3 operator-(const v3& v3_n) const
    {
        return v3(x - v3_n.x, y - v3_n.y, z - v3_n.z);
    }

    v3 operator-(float f_n) const
    {
        return v3(x - f_n, y - f_n, z - f_n);
    }

    v3 operator*(float f_n) const
    {
        return v3(x * f_n, y * f_n, z * f_n);
    }

    v3 operator*(const v3& v3_n) const
    {
        return v3(x * v3_n.x, y * v3_n.y, z * v3_n.z);
    }

    v3 operator/(float f_n) const
    {
        return v3(x / f_n, y / f_n, z / f_n);
    }

    v3 operator/(const v3& v3_n) const
    {
        return v3(x / v3_n.x, y / v3_n.y, z / v3_n.z);
    }

    bool operator==(const v3& v3_n) const
    {
        return (v3_n.x == x) && (v3_n.y == y) && (v3_n.z == z);
    }

    bool operator!=(const v3& v3_n) const
    {
        return (v3_n.x != x) || (v3_n.y != y) || (v3_n.z != z);
    }

    v3& operator+=(const v3& v3_n)
    {
        x += v3_n.x;
        y += v3_n.y;
        z += v3_n.z;
        return *this;
    }

    v3& operator-=(const v3& v3_n)
    {
        x -= v3_n.x;
        y -= v3_n.y;
        z -= v3_n.z;
        return *this;
    }

    v3& operator*=(float f_n)
    {
        x *= f_n;
        y *= f_n;
        z *= f_n;
        return *this;
    }

    v3& operator*=(const v3& v3_n)
    {
        x *= v3_n.x;
        y *= v3_n.y;
        z *= v3_n.z;
        return *this;
    }

    v3& operator/=(const v3& v3_n)
    {
        x /= v3_n.x;
        y /= v3_n.y;
        z /= v3_n.z;
        return *this;
    }

    v3& operator+=(float f_n)
    {
        x += f_n;
        y += f_n;
        z += f_n;
        return *this;
    }

    v3& operator/=(float f_n)
    {
        x /= f_n;
        y /= f_n;
        z /= f_n;
        return *this;
    }

    v3& operator-=(float f_n)
    {
        x -= f_n;
        y -= f_n;
        z -= f_n;
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

    float x, y, z;
};