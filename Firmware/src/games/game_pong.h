#pragma once

int16_t po_leftPlayer;
int16_t po_rightPlayer;
Vector po_ballPos;
Vector po_ballVel;
int16_t po_rightScore;
int16_t po_leftScore;
int16_t po_ballSpeed;
uint16_t po_showTimer;
bool po_paused;
uint8_t po_titlescreen;

const int16_t poPlayerHeight = 150;
const uint8_t PO_NUM_TRACES = 16;
const int PO_SHIFT = 4;
const uint8_t po_ball_halfsize = 10;

bool po_gs_has_gravity = true;
bool po_gs_serve_upwards = false;

Vector po_traces[PO_NUM_TRACES];

void po_initBall()
{
  po_ballPos = {(512 << PO_SHIFT), (512 << PO_SHIFT)};

  int16_t horizontalSpeed = po_ballSpeed;
  if (rand() & 1)
    horizontalSpeed = -horizontalSpeed;

  po_ballSpeed += 0x1 << PO_SHIFT;
  if (po_ballSpeed > 0x10 << PO_SHIFT)
    po_ballSpeed = 0x10 << PO_SHIFT;

  int16_t verticalSpeed = rand() % (9 << PO_SHIFT);
  if (verticalSpeed < (1 << PO_SHIFT))
    verticalSpeed = (1 << PO_SHIFT);
  if (rand() & 1)
    verticalSpeed = -verticalSpeed;

  po_ballVel = {horizontalSpeed, verticalSpeed};

  for (int i = 0; i < PO_NUM_TRACES; ++i)
    po_traces[i] = po_ballPos;

  po_showTimer = 45;
}

void init_pong()
{
  po_leftPlayer = 512;
  po_rightPlayer = 512;
  po_rightScore = 0;
  po_leftScore = 0;
  po_ballSpeed = 8 << PO_SHIFT;
  po_initBall();
  po_paused = false;
  po_titlescreen = 128;
}

int right_ai(Vector ballPos)
{
  if (po_ballVel.x < 0)
    return 0;
  if (ballPos.y < (po_rightPlayer - 17))
    return -1;
  if (ballPos.y > (po_rightPlayer + 17))
    return 1;
  return 0;
}

void update_pong()
{
  if (po_titlescreen)
  {
    --po_titlescreen;
    display.TEXT("TENNIS", {212, 440}, 1);
    display.TEXT("FOR ONE", {337, 370}, 0);

    if (controller.Pressed().A() || controller.Pressed().B() || controller.Pressed().X() || controller.Pressed().Y())
      po_titlescreen = 0;
    return;
  }

  if (controller.Pressed().L() || controller.Pressed().R())
    po_paused = !po_paused;

  if (!po_paused)
  {
    po_leftPlayer += controller.State().YAxis() * 14;
    po_rightPlayer += right_ai(po_traces[10]) * 6;

    if (po_leftPlayer > (1023 - (poPlayerHeight >> 1)))
      po_leftPlayer = 1023 - (poPlayerHeight >> 1);
    if (po_leftPlayer < (poPlayerHeight >> 1))
      po_leftPlayer = (poPlayerHeight >> 1);

    if (po_rightPlayer > (1023 - (poPlayerHeight >> 1)))
      po_rightPlayer = 1023 - (poPlayerHeight >> 1);
    if (po_rightPlayer < (poPlayerHeight >> 1))
      po_rightPlayer = (poPlayerHeight >> 1);
  }

  int16_t lp_min = po_leftPlayer - (poPlayerHeight >> 1);
  int16_t lp_max = po_leftPlayer + (poPlayerHeight >> 1);
  int16_t rp_min = po_rightPlayer - (poPlayerHeight >> 1);
  int16_t rp_max = po_rightPlayer + (poPlayerHeight >> 1);

  if (po_showTimer > 0)
    --po_showTimer;

  if (po_showTimer == 0 && !po_paused)
  {

    if (po_gs_has_gravity)
    {
      // gravity
      if (po_ballVel.y > -(9 << PO_SHIFT))
        po_ballVel.y -= 2;
    }

    po_ballPos = po_ballPos + po_ballVel;

    if (po_ballPos.y < 0)
    {
      po_ballPos.y = 0;
      po_ballVel.y = -po_ballVel.y;
    }
    else if (po_ballPos.y > (1023 << PO_SHIFT))
    {
      po_ballPos.y = (1023 << PO_SHIFT);
      po_ballVel.y = -po_ballVel.y;
    }

    if (po_ballPos.x < (20 << PO_SHIFT) && po_ballPos.y >= ((lp_min - po_ball_halfsize) << PO_SHIFT) && po_ballPos.y <= ((lp_max + po_ball_halfsize) << PO_SHIFT))
    {
      po_ballPos.x = (20 << PO_SHIFT);
      po_ballVel.x = -po_ballVel.x;
      if (po_gs_serve_upwards && po_ballVel.y < 0)
        po_ballVel.y = -po_ballVel.y;
    }
    else if (po_ballPos.x > (1003 << PO_SHIFT) && po_ballPos.y >= ((rp_min - po_ball_halfsize) << PO_SHIFT) && po_ballPos.y <= ((rp_max + po_ball_halfsize) << PO_SHIFT))
    {
      po_ballPos.x = (1003 << PO_SHIFT);
      po_ballVel.x = -po_ballVel.x;
      if (po_gs_serve_upwards && po_ballVel.y < 0)
        po_ballVel.y = -po_ballVel.y;
    }

    bool ballLost = false;
    if (po_ballPos.x < 0)
    {
      po_rightScore++;
      ballLost = true;
    }
    else if (po_ballPos.x > (1023 << PO_SHIFT))
    {
      po_leftScore++;
      ballLost = true;
    }

    if (ballLost)
    {
      po_initBall();
    }
  }

  auto dispBallPos = po_ballPos >> PO_SHIFT;
  if (!po_paused)
  {
    for (int i = PO_NUM_TRACES - 1; i >= 1; --i)
    {
      po_traces[i] = po_traces[i - 1];
    }
  }
  po_traces[0] = dispBallPos;

  display.DrawLineSteps({{0, 0}, {1023, 0}}, 1);
  display.DrawLineSteps({{0, 1023}, {1023, 1023}}, 1);
  display.RECT(0, lp_min, 20, lp_max, 16);
  display.RECT(1003, rp_min, 1023, rp_max, 16);
  display.DECIMAL(po_leftScore, {200, 900});
  display.DECIMAL(po_rightScore, {823, 900});

  if (po_showTimer > 0)
  {
    display.DrawLineSteps({po_ballPos >> PO_SHIFT, (po_ballPos >> PO_SHIFT) + (po_ballVel >> (PO_SHIFT - 2))}, 16);
  }

  if (po_paused)
  {
    display.TEXT("PAUSED", {362, 490});
  }
  else
  {
    display.RECT(dispBallPos.x - po_ball_halfsize, dispBallPos.y - po_ball_halfsize, dispBallPos.x + po_ball_halfsize, dispBallPos.y + po_ball_halfsize, 32);

    for (int i = 0; i < PO_NUM_TRACES - 1; ++i)
    {
      display.DrawLineSteps({po_traces[i], po_traces[i + 1]}, 32);
    }
  }
}

#define GAME_START init_pong
#define GAME_LOOP update_pong