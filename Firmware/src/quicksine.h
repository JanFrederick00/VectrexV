#pragma once
#include <cstdint>

const uint8_t half_sine[128] = {255, 254, 254, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 247, 246, 245, 244, 242, 241, 239, 238, 236, 235, 233, 231, 229, 228, 226, 224, 221, 219, 217, 215, 213, 210, 208, 205, 203, 200, 198, 195, 193, 190, 187, 184, 182, 179, 176, 173, 170, 167, 164, 161, 158, 155, 152, 149, 146, 143, 139, 136, 133, 130, 127, 124, 121, 118, 115, 111, 108, 105, 102, 99, 96, 93, 90, 87, 84, 81, 78, 75, 72, 70, 67, 64, 61, 59, 56, 54, 51, 49, 46, 44, 41, 39, 37, 35, 33, 30, 28, 26, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0};

/// @brief returns an approximation of the sine function
/// @param x input value. Each 256 units of X represent one period of quicksine(x)
/// @return sinusoidal value, range 0..255
uint8_t quicksine(const int16_t x)
{
    const uint8_t frac = (x & 0x7F);
    const uint8_t whole = x >> 7;
    const uint8_t val = half_sine[frac];
    if (whole & 1)
        return 255 - val;
    return val;
}

uint8_t quickcos(const int16_t x) {return quicksine(x+64);}

int16_t iquicksine(const int16_t x) {
    int16_t s = quicksine(x);
    s <<= 1;
    s -= 256;
    return s;
}

int16_t iquickcos(const int16_t x) {return iquicksine(x+64);}