#pragma once
#include <Arduino.h>
#include "pins.h"

struct ControllerState
{
  uint16_t data;

  bool B() const { return data & 1 << 15; }
  bool Y() const { return data & 1 << 14; }
  bool Select() const { return data & 1 << 13; }
  bool Start() const { return data & 1 << 12; }
  bool Up() const { return data & 1 << 11; }
  bool Down() const { return data & 1 << 10; }
  bool Left() const { return data & 1 << 9; }
  bool Right() const { return data & 1 << 8; }
  bool A() const { return data & 1 << 7; }
  bool X() const { return data & 1 << 6; }
  bool L() const { return data & 1 << 5; }
  bool R() const { return data & 1 << 4; }

  int16_t XAxis() const
  {
    if (Left())
      return -1;
    if (Right())
      return 1;
    return 0;
  }
  int16_t YAxis() const
  {
    if (Down())
      return -1;
    if (Up())
      return 1;
    return 0;
  }
};

static ControllerState operator^(const ControllerState &a, const ControllerState &b)
{
  return {(uint16_t)(a.data ^ b.data)};
}
static ControllerState operator&(const ControllerState &a, const ControllerState &b)
{
  return {(uint16_t)(a.data & b.data)};
}

class Controller
{
  ControllerState state = {0};
  ControllerState last_state = {0};
  ControllerState pressed = {0};

public:
  Controller()
  {
    pinMode(PIN_CTRL_CLK, OUTPUT);
    pinMode(PIN_CTRL_LATCH, OUTPUT);
    pinMode(PIN_CTRL_DATA, INPUT_PULLDOWN);

    digitalWrite(PIN_CTRL_LATCH, LOW);
    digitalWrite(PIN_CTRL_CLK, HIGH);
  }

  void Update()
  {
    uint16_t controller_state = 0;

    digitalWrite(PIN_CTRL_LATCH, HIGH);
    delayMicroseconds(5);
    digitalWrite(PIN_CTRL_LATCH, LOW);

    for (int i = 0; i < 16; ++i)
    {
      digitalWrite(PIN_CTRL_CLK, LOW);
      delayMicroseconds(5);
      controller_state <<= 1;
      if (digitalRead(PIN_CTRL_DATA) == LOW)
        controller_state |= 1;
      digitalWrite(PIN_CTRL_CLK, HIGH);
      delayMicroseconds(5);
    }

    if((controller_state & 0x0F) > 0) controller_state = 0; // No controller

    last_state = state;
    state = {controller_state};
    auto change = last_state ^ state;
    pressed = state & change;
  }

  ControllerState State() const { return state; }
  ControllerState Pressed() const { return pressed; }
};