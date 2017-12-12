
#pragma once

#include "defs.h"

////DCT-II transforms
void fastForwardDCT2_B2  (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2);
void fastInverseDCT2_B2  (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastForwardDCT2_B4  (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2);
void fastInverseDCT2_B4  (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastForwardDCT2_B8  (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2);
void fastInverseDCT2_B8  (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastForwardDCT2_B16 (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2);
void fastInverseDCT2_B16 (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastForwardDCT2_B32 (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2);
void fastInverseDCT2_B32 (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastForwardDCT2_B64 (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2);
void fastInverseDCT2_B64 (const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2, const TCoeff outputMinimum, const TCoeff outputMaximum);
void fastForwardDCT2_B128(const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2);
void fastInverseDCT2_B128(const TCoeff *src, TCoeff *dst, Int shift, Int line, Int iSkipLine, Int iSkipLine2, const TCoeff outputMinimum, const TCoeff outputMaximum);
