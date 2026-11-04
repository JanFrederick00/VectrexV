#pragma once
#include <cstdint>
#include "quicksine.h"

struct Vector
{
    int16_t x;
    int16_t y;

    int32_t lengthSquared() const
    {
        return x * x + y * y;
    }

    Vector rotate(uint8_t theta) const
    {
        int32_t sint = ((int32_t)quicksine(theta)) - 128;
        int32_t cost = ((int32_t)quickcos(theta)) - 128;

        return {
            {(int16_t)((x * cost - y * sint) >> 7)},
            {(int16_t)((x * sint + y * cost) >> 7)},
        };
    }

    inline void clampToScreen()
    {
        x &= 0b1111111111;
        y &= 0b1111111111;
    }

    bool IsOutOfBounds() const {
        if(x > 1023) return true;
        if(x < 0) return true;
        if(y > 1023) return true;
        if(y < 0) return true;
        return false;
    }
};

struct Vector8 {
    int8_t x;
    int8_t y;

    operator Vector() const { return{x,y};}
};
struct Vector4 {
    uint8_t x : 4, y : 4;

    operator Vector() const { return{x,y};}
};

static Vector operator-(const Vector &a, const Vector &b)
{
    return {(int16_t)(a.x - b.x), (int16_t)(a.y - b.y)};
}

static Vector operator+(const Vector &a, const Vector &b)
{
    return {(int16_t)(a.x + b.x), (int16_t)(a.y + b.y)};
}
static Vector operator<<(const Vector &a, const int b)
{
    return {(int16_t)(a.x << b), (int16_t)(a.y << b)};
}
static Vector operator>>(const Vector &a, const int b)
{
    return {(int16_t)(a.x >> b), (int16_t)(a.y >> b)};
}

struct Line
{
    Vector start;
    Vector end;
};

struct Shape
{
    bool closed;
    uint8_t stepSize;
    uint8_t pointsCount;
    const Vector *points;
};

struct Shape8
{
    bool closed;
    uint8_t stepSize;
    uint8_t pointsCount;
    const Vector8 *points;
};

struct Shape4
{
    bool closed;
    uint8_t stepSize;
    uint8_t pointsCount;
    const Vector4 *points;
};