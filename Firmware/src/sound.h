#pragma once
#include <Arduino.h>
#include "pins.h"

const uint16_t NOTE_ARR[12] = {
    22934,
    21646,
    20431,
    19285,
    18202,
    17181,
    16216,
    15306,
    14447,
    13636,
    12871,
    12149,
};

struct NoteDef
{
    uint16_t channel : 1, noteNumber : 7, time_to_next_event : 5, pwm : 3;
};

class Sound
{
public:
    enum SoundChannel : uint8_t
    {
        CH_A,
        CH_B
    };

    enum PulseWidth : uint8_t
    {
        FIFTYPERCENT = 1,
        TWENTYFIVEPERCENT = 2,
        TWELVEPERCENT = 3,
        SIXPERCENT = 4
    };

private:
    void init_timer(uint16_t prsc, uint16_t arr, uint16_t ccr, SoundChannel channel)
    {

        // Foutput = Fsystem / ((prsc+1)*(arr+1))
        // Duty = ccr/arr+1

        /*
       PIN_SOUNDA = PD2;  = T1CH1 / T2CH3
       PIN_SOUNDB = PD3;  = T1CH4 / T2CH2
       */

        TIM_TypeDef *tim = nullptr;
        switch (channel)
        {
        case SoundChannel::CH_A:
            tim = TIM1;
            break;
        case SoundChannel::CH_B:
            tim = TIM2;
            break;
        default:
            return;
        }
        TIM_Cmd(tim, DISABLE);

        TIM_TimeBaseInitTypeDef tbinit = {0};

        tbinit.TIM_ClockDivision = TIM_CKD_DIV1;
        tbinit.TIM_CounterMode = TIM_CounterMode_Up;
        tbinit.TIM_Prescaler = prsc;
        tbinit.TIM_Period = arr;
        TIM_TimeBaseInit(tim, &tbinit);

        TIM_OCInitTypeDef ocinit = {0};
        ocinit.TIM_OCMode = TIM_OCMode_PWM1;
        ocinit.TIM_OutputState = TIM_OutputState_Enable;
        ocinit.TIM_OCPolarity = TIM_OCPolarity_High;
        ocinit.TIM_Pulse = ccr;

        TIM_CtrlPWMOutputs(tim, ENABLE);

        switch (channel)
        {
        case SoundChannel::CH_A:
            TIM_OC1Init(tim, &ocinit);
            TIM_OC1PreloadConfig(tim, TIM_OCPreload_Enable);
            break;
        case SoundChannel::CH_B:
            TIM_OC2Init(tim, &ocinit);
            TIM_OC2PreloadConfig(tim, TIM_OCPreload_Enable);
            break;
        default:
            return;
        }

        TIM_ARRPreloadConfig(tim, ENABLE);
        TIM_Cmd(tim, ENABLE);
    }

public:
    Sound()
    {
        pinMode(PIN_SOUNDC, OUTPUT);
        digitalWrite(PIN_SOUNDC, LOW);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

        GPIO_InitTypeDef i = {0};
        i.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
        i.GPIO_Mode = GPIO_Mode_AF_PP;
        i.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_Init(GPIOD, &i);

        TurnOff(SoundChannel::CH_A);
        TurnOff(SoundChannel::CH_B);
    }

    void TurnOff(SoundChannel sc)
    {
        switch (sc)
        {
        case SoundChannel::CH_A:
            TIM_Cmd(TIM1, DISABLE);
            break;
        case SoundChannel::CH_B:
            TIM_Cmd(TIM2, DISABLE);
            break;
        }
    }

    void PlayNote(uint8_t noteNumber, SoundChannel channel, PulseWidth pwm = PulseWidth::FIFTYPERCENT)
    {
        if (noteNumber > 107)
        {
            TurnOff(channel);
            return;
        }

        uint8_t octave = noteNumber / 12;
        uint8_t note = noteNumber % 12;

        const int16_t arr = NOTE_ARR[note];
        const uint16_t prescaler = 1 << (8 - octave);
        const uint16_t ocr = arr >> (uint8_t)pwm;

        init_timer(prescaler - 1, arr - 1, ocr, channel);
    }

private:
    const NoteDef *currentTrack = nullptr;
    uint16_t currentTrackPosition = 0;
    uint16_t currentTrackLength = 0;
    uint8_t currentTrackNextEventCounter = 0;

public:
    void StartPlaying(const NoteDef *track, uint16_t track_length)
    {
        currentTrack = track;
        currentTrackPosition = 0;
        currentTrackLength = track_length;
        currentTrackNextEventCounter = 0;
    }

    void update()
    {
        if (currentTrack == nullptr)
            return;

        while (1)
        {
            if (currentTrackPosition >= currentTrackLength)
            {
                currentTrack = nullptr;
                return;
            }

            if (currentTrackNextEventCounter > 0)
            {
                currentTrackNextEventCounter--;
                return;
            }

            const NoteDef &note = currentTrack[currentTrackPosition];
            currentTrackNextEventCounter = note.time_to_next_event;
            ++currentTrackPosition;
            if (note.noteNumber == 0)
                continue;

            SoundChannel channel = note.channel == 1 ? SoundChannel::CH_B : SoundChannel::CH_A;
            if (note.noteNumber == 0x7F)
            {
                TurnOff(channel);
            } else {
                PlayNote(note.noteNumber, channel, (PulseWidth)note.pwm);
            }
        }
    }
};
