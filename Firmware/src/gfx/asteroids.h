#pragma once
#include "graphics.h"

// Graphics from Atari's Asteroids
// taken via https://www.computerarcheology.com/Arcade/Asteroids/VectorROM.html

// re-calculated to absolute positions

const Vector8 _P_AS_SHIP[5] = {{16, -24}, {-16, -24}, {-32, -40}, {0, 56}, {32, -40}};
const Shape8 AS_SHIP = {true, 16, 5, _P_AS_SHIP};      

const Vector8 _P_AS_SHIP_THRUST[3] = {{16, -24}, {0, -56}, {-16, -24}};
const Shape8 AS_SHIP_THRUST = {true, 8, 3, _P_AS_SHIP_THRUST};                     

const Vector8 _P_AS_UFO[12] = { {-16,8}, {16,8}, {40,-8}, {-40,-8}, {-16,-24}, {16,-24}, {40,-8}, {16,8}, {8,24}, {-8,24}, {-16,8}, {-40,-8} };
const Shape8 AS_UFO = { false, 16, 12, _P_AS_UFO };

const Vector8 _P_AS_ROCK1[10] = { {0,16}, {16,32}, {32,16}, {24,0}, {32,-16}, {8,-32}, {-16,-32}, {-32,-16}, {-32,16}, {-16,32} };
const Vector8 _P_AS_ROCK2[12] = { {16,8}, {32,16}, {16,32}, {0,24}, {-16,32}, {-32,16}, {-24,0}, {-32,-16}, {-16,-32}, {-8,-24}, {16,-32}, {32,-8} };
const Vector8 _P_AS_ROCK3[11] = { {-16,0}, {-32,-8}, {-16,-32}, {0,-8}, {0,-32}, {16,-32}, {32,-8}, {32,8}, {16,32}, {-8,32}, {-32,8} };
const Vector8 _P_AS_ROCK4[12] = { {8,0}, {32,8}, {32,16}, {8,32}, {-16,32}, {-8,16}, {-32,16}, {-32,-8}, {-16,-32}, {8,-24}, {16,-32}, {32,-16} };


const Shape8 AS_ROCK1 = { true, 32, 10, _P_AS_ROCK1 };
const Shape8 AS_ROCK2 = { true, 32, 12, _P_AS_ROCK2 };
const Shape8 AS_ROCK3 = { true, 32, 11, _P_AS_ROCK3 };
const Shape8 AS_ROCK4 = { true, 32, 12, _P_AS_ROCK4 };

const Shape8 AS_ROCK1_L = { true, 16, 10, _P_AS_ROCK1 };
const Shape8 AS_ROCK2_L = { true, 16, 12, _P_AS_ROCK2 };
const Shape8 AS_ROCK3_L = { true, 16, 11, _P_AS_ROCK3 };
const Shape8 AS_ROCK4_L = { true, 16, 12, _P_AS_ROCK4 };

const Vector8 _P_AS_SP_BULLET[2] = { {0,-2}, {0,2}};
const Shape8 AS_SP_BULLET = { false, 128, 2, _P_AS_SP_BULLET };

const Vector8 _P_AS_LIFE[5] = { {-12,-18}, {12,-18}, {24,-30}, {0,42}, {-24,-30} };
const Shape8 AS_LIFE = { true, 16, 5, _P_AS_LIFE };