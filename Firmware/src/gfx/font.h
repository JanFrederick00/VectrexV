
#pragma once
#include "graphics.h"

#define TEXT_BRIGHTNESS 32

const Vector4 _P_CHR_0[6] = {{0, 0}, {8, 0}, {8, 12}, {0, 12}, {0, 0}, {8, 12}};
const Vector4 _P_CHR_1[3] = {{4, 0}, {4, 12}, {3, 10}};
const Vector4 _P_CHR_2[6] = {{0, 12}, {8, 12}, {8, 7}, {0, 5}, {0, 0}, {8, 0}};
const Vector4 _P_CHR_3[7] = {{0, 12}, {8, 12}, {8, 0}, {0, 0}, {15, 0}, {0, 6}, {8, 6}};
const Vector4 _P_CHR_4[6] = {{0, 12}, {0, 6}, {8, 6}, {15, 0}, {8, 12}, {8, 0}};
const Vector4 _P_CHR_5[6] = {{0, 0}, {8, 0}, {8, 6}, {0, 7}, {0, 12}, {8, 12}};
const Vector4 _P_CHR_6[5] = {{0, 12}, {0, 0}, {8, 0}, {8, 5}, {0, 7}};
const Vector4 _P_CHR_7[4] = {{0, 12}, {8, 12}, {8, 6}, {4, 0}};
const Vector4 _P_CHR_8[8] = {{0, 0}, {8, 0}, {8, 12}, {0, 12}, {0, 0}, {15, 0}, {0, 6}, {8, 6}};
const Vector4 _P_CHR_9[5] = {{8, 0}, {8, 12}, {0, 12}, {0, 7}, {8, 5}};

const Shape4 CHR_0 = {false, TEXT_BRIGHTNESS, 6, _P_CHR_0};
const Shape4 CHR_1 = {false, TEXT_BRIGHTNESS, 3, _P_CHR_1};
const Shape4 CHR_2 = {false, TEXT_BRIGHTNESS, 6, _P_CHR_2};
const Shape4 CHR_3 = {false, TEXT_BRIGHTNESS, 7, _P_CHR_3};
const Shape4 CHR_4 = {false, TEXT_BRIGHTNESS, 6, _P_CHR_4};
const Shape4 CHR_5 = {false, TEXT_BRIGHTNESS, 6, _P_CHR_5};
const Shape4 CHR_6 = {false, TEXT_BRIGHTNESS, 5, _P_CHR_6};
const Shape4 CHR_7 = {false, TEXT_BRIGHTNESS, 4, _P_CHR_7};
const Shape4 CHR_8 = {false, TEXT_BRIGHTNESS, 8, _P_CHR_8};
const Shape4 CHR_9 = {false, TEXT_BRIGHTNESS, 5, _P_CHR_9};

const Vector4 _P_CHR_A[8] = {{0, 0}, {0, 8}, {4, 12}, {8, 8}, {8, 0}, {15, 0}, {0, 4}, {8, 4}};
const Vector4 _P_CHR_B[8] = {{0, 0}, {0, 12}, {4, 12}, {8, 10}, {4, 6}, {8, 2}, {4, 0}, {0, 0}};
const Vector4 _P_CHR_C[4] = {{8, 0}, {0, 0}, {0, 12}, {8, 12}};
const Vector4 _P_CHR_D[7] = {{0, 0}, {0, 12}, {4, 12}, {8, 8}, {8, 4}, {4, 0}, {0, 0}};
const Vector4 _P_CHR_E[7] = {{8, 0}, {0, 0}, {0, 12}, {8, 12}, {15, 0}, {0, 6}, {6, 6}};
const Vector4 _P_CHR_F[6] = {{0, 0}, {0, 12}, {8, 12}, {15, 0}, {0, 6}, {6, 6}};
const Vector4 _P_CHR_G[6] = {{6, 6}, {8, 4}, {8, 0}, {0, 0}, {0, 12}, {8, 12}};
const Vector4 _P_CHR_H[8] = {{0, 0}, {0, 12}, {15, 0}, {0, 6}, {8, 6}, {15, 0}, {8, 12}, {8, 0}};
const Vector4 _P_CHR_I[8] = {{0, 0}, {8, 0}, {15, 0}, {4, 0}, {4, 12}, {15, 0}, {0, 12}, {8, 12}};
const Vector4 _P_CHR_J[4] = {{0, 4}, {4, 0}, {8, 0}, {8, 12}};
const Vector4 _P_CHR_K[6] = {{0, 0}, {0, 12}, {15, 0}, {8, 12}, {0, 6}, {6, 0}};
const Vector4 _P_CHR_L[3] = {{8, 0}, {0, 0}, {0, 12}};
const Vector4 _P_CHR_M[5] = {{0, 0}, {0, 12}, {4, 8}, {8, 12}, {8, 0}};
const Vector4 _P_CHR_N[4] = {{0, 0}, {0, 12}, {8, 0}, {8, 12}};
const Vector4 _P_CHR_O[5] = {{0, 0}, {0, 12}, {8, 12}, {8, 0}, {0, 0}};
const Vector4 _P_CHR_P[5] = {{0, 0}, {0, 12}, {8, 12}, {8, 6}, {0, 5}};
const Vector4 _P_CHR_Q[8] = {{0, 0}, {0, 12}, {8, 12}, {8, 4}, {0, 0}, {15, 0}, {4, 4}, {8, 0}};
const Vector4 _P_CHR_R[8] = {{0, 0}, {0, 12}, {8, 12}, {8, 6}, {0, 5}, {15, 0}, {4, 5}, {8, 0}};
const Vector4 _P_CHR_S[8] = {{0, 2}, {2, 0}, {8, 0}, {8, 5}, {0, 7}, {0, 12}, {6, 12}, {8, 10}};
const Vector4 _P_CHR_T[5] = {{0, 12}, {8, 12}, {15, 0}, {4, 12}, {4, 0}};
const Vector4 _P_CHR_U[5] = {{0, 12}, {0, 2}, {4, 0}, {8, 2}, {8, 12}};
const Vector4 _P_CHR_V[3] = {{0, 12}, {4, 0}, {8, 12}};
const Vector4 _P_CHR_W[5] = {{0, 12}, {2, 0}, {4, 4}, {6, 0}, {8, 12}};
const Vector4 _P_CHR_X[5] = {{0, 0}, {8, 12}, {15, 0}, {0, 12}, {8, 0}};
const Vector4 _P_CHR_Y[6] = {{0, 12}, {4, 6}, {8, 12}, {15, 0}, {4, 6}, {4, 0}};
const Vector4 _P_CHR_Z[7] = {{0, 12}, {8, 12}, {0, 0}, {8, 0}, {15, 0}, {2, 6}, {6, 6}};

const Shape4 CHR_A = {false, TEXT_BRIGHTNESS, 8, _P_CHR_A};
const Shape4 CHR_B = {false, TEXT_BRIGHTNESS, 8, _P_CHR_B};
const Shape4 CHR_C = {false, TEXT_BRIGHTNESS, 4, _P_CHR_C};
const Shape4 CHR_D = {false, TEXT_BRIGHTNESS, 7, _P_CHR_D};
const Shape4 CHR_E = {false, TEXT_BRIGHTNESS, 7, _P_CHR_E};
const Shape4 CHR_F = {false, TEXT_BRIGHTNESS, 6, _P_CHR_F};
const Shape4 CHR_G = {false, TEXT_BRIGHTNESS, 6, _P_CHR_G};
const Shape4 CHR_H = {false, TEXT_BRIGHTNESS, 8, _P_CHR_H};
const Shape4 CHR_I = {false, TEXT_BRIGHTNESS, 8, _P_CHR_I};
const Shape4 CHR_J = {false, TEXT_BRIGHTNESS, 4, _P_CHR_J};
const Shape4 CHR_K = {false, TEXT_BRIGHTNESS, 6, _P_CHR_K};
const Shape4 CHR_L = {false, TEXT_BRIGHTNESS, 3, _P_CHR_L};
const Shape4 CHR_M = {false, TEXT_BRIGHTNESS, 5, _P_CHR_M};
const Shape4 CHR_N = {false, TEXT_BRIGHTNESS, 4, _P_CHR_N};
const Shape4 CHR_O = {false, TEXT_BRIGHTNESS, 5, _P_CHR_O};
const Shape4 CHR_P = {false, TEXT_BRIGHTNESS, 5, _P_CHR_P};
const Shape4 CHR_Q = {false, TEXT_BRIGHTNESS, 8, _P_CHR_Q};
const Shape4 CHR_R = {false, TEXT_BRIGHTNESS, 8, _P_CHR_R};
const Shape4 CHR_S = {false, TEXT_BRIGHTNESS, 8, _P_CHR_S};
const Shape4 CHR_T = {false, TEXT_BRIGHTNESS, 5, _P_CHR_T};
const Shape4 CHR_U = {false, TEXT_BRIGHTNESS, 5, _P_CHR_U};
const Shape4 CHR_V = {false, TEXT_BRIGHTNESS, 3, _P_CHR_V};
const Shape4 CHR_W = {false, TEXT_BRIGHTNESS, 5, _P_CHR_W};
const Shape4 CHR_X = {false, TEXT_BRIGHTNESS, 5, _P_CHR_X};
const Shape4 CHR_Y = {false, TEXT_BRIGHTNESS, 6, _P_CHR_Y};
const Shape4 CHR_Z = {false, TEXT_BRIGHTNESS, 7, _P_CHR_Z};


const Shape4 *DIGITS[10] = {
    &CHR_0,
    &CHR_1,
    &CHR_2,
    &CHR_3,
    &CHR_4,
    &CHR_5,
    &CHR_6,
    &CHR_7,
    &CHR_8,
    &CHR_9,
};

const Shape4 *LETTERS[26] = {
    &CHR_A,
    &CHR_B,
    &CHR_C,
    &CHR_D,
    &CHR_E,
    &CHR_F,
    &CHR_G,
    &CHR_H,
    &CHR_I,
    &CHR_J,
    &CHR_K,
    &CHR_L,
    &CHR_M,
    &CHR_N,
    &CHR_O,
    &CHR_P,
    &CHR_Q,
    &CHR_R,
    &CHR_S,
    &CHR_T,
    &CHR_U,
    &CHR_V,
    &CHR_W,
    &CHR_X,
    &CHR_Y,
    &CHR_Z,
};