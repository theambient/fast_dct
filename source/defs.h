
#pragma once

#include <algorithm>

#define RExt__HIGH_PRECISION_FORWARD_TRANSFORM 1
#define ALIGN_DATA(bits, what) what
#define CHECK(X, MSG)
#define THROW(X)

typedef short Pel;
typedef int Int;
typedef signed char SChar;
typedef unsigned int UInt;
typedef int TCoeff;
typedef short TMatrixCoeff;

enum TransformDirection
{
  TRANSFORM_FORWARD              = 0,
  TRANSFORM_INVERSE              = 1,
  TRANSFORM_NUMBER_OF_DIRECTIONS = 2
};

template <typename T> inline T Clip3 (const T minVal, const T maxVal, const T a) { return std::min<T> (std::max<T> (minVal, a) , maxVal); }  ///< general min/max clip


static const Int COM16_C806_TRANS_PREC =                            2;
static const Int JVET_C0024_ZERO_OUT_TH =                          32;
static const Int MIN_TU_SIZE =                                      4;
static const Int MAX_TU_SIZE =                                    128;
