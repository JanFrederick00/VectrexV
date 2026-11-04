#pragma once
#include <Arduino.h>

const uint8_t PIN_BRIGHTNESS = PC0;

// DACs
const uint8_t PIN_DAC_SHUTDOWN = PC1;
const uint8_t PIN_DAC_LATCH = PC2;
const uint8_t PIN_DAC_CS_X = PC3;
const uint8_t PIN_DAC_CS_Y = PC4;
const uint8_t PIN_DAC_SCK = PC5;
const uint8_t PIN_DAC_SDA = PC6;

// Sound
const uint8_t PIN_SOUNDA = PD2;
const uint8_t PIN_SOUNDB = PD3;
const uint8_t PIN_SOUNDC = PD0;

// Controller
const uint8_t PIN_CTRL_CLK = PD4;
const uint8_t PIN_CTRL_LATCH = PD5;
const uint8_t PIN_CTRL_DATA = PD6;