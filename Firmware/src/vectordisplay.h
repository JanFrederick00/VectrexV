#pragma once
#include <Arduino.h>
#include "pins.h"
#include "SPI.h"
#include "graphics.h"
#include "gfx/font.h"

SPIClass spi_dac(PIN_DAC_SDA, PC7, PIN_DAC_SCK);

class VectorDisplay
{
private:
    inline void WriteDACs(uint16_t X, uint16_t Y) const
    {
        const uint16_t mask = 0b1111111111;
        X &= mask;
        Y &= mask;
        X <<= 2;
        Y <<= 2;

        X = 0b0001000000000000 | X; // DAC ACTIVE, Gain = 0..4V
        Y = 0b0001000000000000 | Y; // DAC ACTIVE, Gain = 0..4V25

        GPIOC->BCR = 1 << 3; // digitalWrite(PIN_DAC_CS_X, LOW);
        spi_dac.transfer16(X);
        GPIOC->BSHR = 1 << 3; // digitalWrite(PIN_DAC_CS_X, HIGH);
        GPIOC->BCR = 1 << 4;  // digitalWrite(PIN_DAC_CS_Y, LOW);
        spi_dac.transfer16(Y);
        GPIOC->BSHR = 1 << 4; // digitalWrite(PIN_DAC_CS_Y, HIGH);

        GPIOC->BCR = 1 << 2; // digitalWrite(PIN_DAC_LATCH, LOW);
        // delayMicroseconds(1);
        GPIOC->BSHR = 1 << 2; // digitalWrite(PIN_DAC_LATCH, HIGH);
    }

public:
    inline void DrawLineSteps(const Line l, const uint8_t step_size) const
    {
        if (l.start.IsOutOfBounds() || l.end.IsOutOfBounds())
            return;
        const Vector diff = l.end - l.start;
        int32_t tempX = 0;
        int32_t tempY = 0;

        int32_t stepdiffx = diff.x * step_size;
        int32_t stepdiffy = diff.y * step_size;

        WriteDACs(l.start.x, l.start.y);
        delayMicroseconds(2);
        digitalWrite(PIN_BRIGHTNESS, HIGH);
        for (int32_t i = 0; i < 256; i += step_size)
        {
            tempX += stepdiffx;
            tempY += stepdiffy;

            const int16_t x = l.start.x + (tempX >> 8);
            const int16_t y = l.start.y + (tempY >> 8);

            WriteDACs(x, y);
        }
        digitalWrite(PIN_BRIGHTNESS, LOW);
    }

    void RECT(const int16_t minX, const int16_t minY, const int16_t maxX, const int16_t maxY, const uint8_t stepsize) const
    {
        DrawLineSteps({{minX, minY}, {maxX, minY}}, stepsize);
        DrawLineSteps({{maxX, minY}, {maxX, maxY}}, stepsize);
        DrawLineSteps({{maxX, maxY}, {minX, maxY}}, stepsize);
        DrawLineSteps({{minX, maxY}, {minX, minY}}, stepsize);
        // DrawLineSteps({{minX, minY}, {maxX, maxY}}, stepsize);
    }

    void SHAPE(const Shape &shape, const Vector &offset, const uint8_t scale = 0) const
    {
        for (uint8_t iPoint = 0; iPoint < (shape.closed ? shape.pointsCount : (shape.pointsCount - 1)); ++iPoint)
        {
            uint8_t iNextPoint = iPoint + 1;
            if (iNextPoint == shape.pointsCount)
                iNextPoint = 0;

            if (shape.points[iPoint].x == 32767 || shape.points[iNextPoint].x == 32767)
                continue;

            Line l = {(shape.points[iPoint] << scale) + offset, (shape.points[iNextPoint] << scale) + offset};
            DrawLineSteps(l, shape.stepSize);
        }
    }
    void SHAPE(const Shape4 &shape, const Vector &offset, const uint8_t scale = 0) const
    {
        for (uint8_t iPoint = 0; iPoint < (shape.closed ? shape.pointsCount : (shape.pointsCount - 1)); ++iPoint)
        {
            uint8_t iNextPoint = iPoint + 1;
            if (iNextPoint == shape.pointsCount)
                iNextPoint = 0;

            if (shape.points[iPoint].x == 15 || shape.points[iNextPoint].x == 15)
                continue;

            Line l = {(((const Vector)shape.points[iPoint]) << scale) + offset, (((const Vector)shape.points[iNextPoint]) << scale) + offset};
            DrawLineSteps(l, shape.stepSize);
        }
    }
    void SHAPE(const Shape8 &shape, const Vector &offset, const uint8_t scale = 0) const
    {
        for (uint8_t iPoint = 0; iPoint < (shape.closed ? shape.pointsCount : (shape.pointsCount - 1)); ++iPoint)
        {
            uint8_t iNextPoint = iPoint + 1;
            if (iNextPoint == shape.pointsCount)
                iNextPoint = 0;

            if (shape.points[iPoint].x == 127 || shape.points[iNextPoint].x == 127)
                continue;

            Line l = {(((const Vector)shape.points[iPoint]) << scale) + offset, (((const Vector)shape.points[iNextPoint]) << scale) + offset};
            DrawLineSteps(l, shape.stepSize);
        }
    }

    void SHAPE_ANGLE(const Shape &shape, uint8_t angle, const Vector &offset, const uint8_t scale = 0) const
    {
        for (uint8_t iPoint = 0; iPoint < (shape.closed ? shape.pointsCount : (shape.pointsCount - 1)); ++iPoint)
        {
            uint8_t iNextPoint = iPoint + 1;
            if (iNextPoint == shape.pointsCount)
                iNextPoint = 0;

            if (shape.points[iPoint].x == 32767 || shape.points[iNextPoint].x == 32767)
                continue;

            Line l = {(shape.points[iPoint].rotate(angle) << scale) + offset, (shape.points[iNextPoint].rotate(angle) << scale) + offset};
            DrawLineSteps(l, shape.stepSize);
        }
    }
    void SHAPE_ANGLE(const Shape8 &shape, uint8_t angle, const Vector &offset, const uint8_t scale = 0) const
    {
        for (uint8_t iPoint = 0; iPoint < (shape.closed ? shape.pointsCount : (shape.pointsCount - 1)); ++iPoint)
        {
            uint8_t iNextPoint = iPoint + 1;
            if (iNextPoint == shape.pointsCount)
                iNextPoint = 0;

            if (shape.points[iPoint].x == 127 || shape.points[iNextPoint].x == 127)
                continue;

            Line l = {(((const Vector)shape.points[iPoint]).rotate(angle) << scale) + offset, (((const Vector)shape.points[iNextPoint]).rotate(angle) << scale) + offset};
            DrawLineSteps(l, shape.stepSize);
        }
    }

    void GOTO(const Vector v) const
    {
        WriteDACs(v.x, v.y);
    }

    void HEXBYTE(const uint8_t b, const Vector pos) const
    {
        uint8_t lower = b & 0x0F;
        uint8_t upper = b >> 4;
        if (lower < 10)
            lower += '0';
        else
            lower += 'A' - 10;
        if (upper < 10)
            upper += '0';
        else
            upper += 'A' - 10;
        char buf[3] = {(char)upper, (char)lower, 0};
        TEXT(buf, pos);
    }

    void DECIMAL(uint16_t value, Vector pos) const
    {
        do
        {
            uint8_t v = value % 10;
            value = value / 10;
            SHAPE(*DIGITS[v], pos, 2);
            pos.x -= 50;
        } while (value > 0);
    }

    void TEXT(const char *text, Vector pos, uint8_t scale = 0) const
    {
        int i = 0;
        while (text[i])
        {
            const Shape4 *pShape = nullptr;
            if (text[i] >= '0' && text[i] <= '9')
            {
                pShape = DIGITS[text[i] - '0'];
            }
            else if (text[i] >= 'a' && text[i] <= 'z')
            {
                pShape = LETTERS[text[i] - 'a'];
            }
            else if (text[i] >= 'A' && text[i] <= 'Z')
            {
                pShape = LETTERS[text[i] - 'A'];
            }

            if (pShape)
            {
                SHAPE(*pShape, pos, 2 + scale);
            }
            pos.x += 50 << scale;
            if (pos.x >= (1023 - 50))
            {
                pos.x = 0;
                pos.y -= 70 << scale;
            }

            ++i;
        }
    }

    VectorDisplay()
    {
        pinMode(PIN_BRIGHTNESS, OUTPUT);
        digitalWrite(PIN_BRIGHTNESS, HIGH); // BEAM ON

        pinMode(PIN_DAC_SHUTDOWN, OUTPUT);
        digitalWrite(PIN_DAC_SHUTDOWN, HIGH); // DACs ON

        pinMode(PIN_DAC_LATCH, OUTPUT);
        digitalWrite(PIN_DAC_LATCH, HIGH);

        pinMode(PIN_DAC_CS_X, OUTPUT);
        pinMode(PIN_DAC_CS_Y, OUTPUT);
        digitalWrite(PIN_DAC_CS_X, HIGH);
        digitalWrite(PIN_DAC_CS_Y, HIGH);

        spi_dac.setDataMode(SPI_MODE0);
        spi_dac.begin();
        spi_dac.setClockDivider(1);
    }
};