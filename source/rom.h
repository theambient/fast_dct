
#pragma once

#include "defs.h"

#if RExt__HIGH_PRECISION_FORWARD_TRANSFORM
static const Int g_transformMatrixShift[TRANSFORM_NUMBER_OF_DIRECTIONS] = { 14, 6 };
#else
static const Int g_transformMatrixShift[TRANSFORM_NUMBER_OF_DIRECTIONS] = {  6, 6 };
#endif

extern const TMatrixCoeff g_aiT2  [TRANSFORM_NUMBER_OF_DIRECTIONS][  2][  2];
extern const TMatrixCoeff g_aiT4  [TRANSFORM_NUMBER_OF_DIRECTIONS][  4][  4];
extern const TMatrixCoeff g_aiT8  [TRANSFORM_NUMBER_OF_DIRECTIONS][  8][  8];
extern const TMatrixCoeff g_aiT16 [TRANSFORM_NUMBER_OF_DIRECTIONS][ 16][ 16];
extern const TMatrixCoeff g_aiT32 [TRANSFORM_NUMBER_OF_DIRECTIONS][ 32][ 32];
extern const TMatrixCoeff g_aiT64 [TRANSFORM_NUMBER_OF_DIRECTIONS][ 64][ 64];
extern const TMatrixCoeff g_aiT128[TRANSFORM_NUMBER_OF_DIRECTIONS][128][128];


extern SChar              g_aucLog2    [128 + 1];

void init_rom();
