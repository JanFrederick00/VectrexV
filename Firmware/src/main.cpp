#include <Arduino.h>

#include "pins.h"
#include "vectordisplay.h"
#include "sound.h"
#include "controller.h"

VectorDisplay display;
//Sound sound;
Controller controller;

const uint32_t desired_frame_time = 15000; // us

#include "games/game_asteroids.h"

void setup()
{
  GAME_START();
}

void loop()
{
  uint32_t start = micros();
  controller.Update();

  GAME_LOOP();
  //sound.update();

  uint32_t end = micros();
  uint32_t time = end - start;

  if (time > desired_frame_time)
  {
    // Serial.println("Argh!");
  }
  else
  {
    uint32_t to_wait = desired_frame_time - time;
    delayMicroseconds(to_wait);
  }
}
