
/** MxN forward transform (2D)
*  \param bitDepth              [in]  bit depth
*  \param residual              [in]  residual block
*  \param stride                [in]  stride of residual block
*  \param coeff                 [out] transform coefficients
*  \param width                 [in]  width of transform
*  \param height                [in]  height of transform
*  \param useDST                [in]
*  \param maxLog2TrDynamicRange [in]

*/

#include "fast_dct.h"
#include "rom.h"
#include "defs.h"

void xTrMxN( const int bitDepth, const Pel *residual, size_t stride, TCoeff *coeff, size_t width, size_t height, bool useDST, const int maxLog2TrDynamicRange )
{
  const int iWidth  = (int)width;
  const int iHeight = (int)height;

  const Int TRANSFORM_MATRIX_SHIFT = g_transformMatrixShift[TRANSFORM_FORWARD];

  const Int shift_1st = (g_aucLog2[iWidth] +  bitDepth + TRANSFORM_MATRIX_SHIFT) - maxLog2TrDynamicRange;
  const Int shift_2nd = g_aucLog2[iHeight] + TRANSFORM_MATRIX_SHIFT;

  UInt iSkipWidth  = ( iWidth  > JVET_C0024_ZERO_OUT_TH ? iWidth  - JVET_C0024_ZERO_OUT_TH : 0 );
  UInt iSkipHeight = ( iHeight > JVET_C0024_ZERO_OUT_TH ? iHeight - JVET_C0024_ZERO_OUT_TH : 0 );

  CHECK( shift_1st < 0, "Negative shift" );
  CHECK( shift_2nd < 0, "Negative shift" );

  ALIGN_DATA( MEMORY_ALIGN_DEF_SIZE, TCoeff block[MAX_TU_SIZE * MAX_TU_SIZE] );
  ALIGN_DATA( MEMORY_ALIGN_DEF_SIZE, TCoeff   tmp[MAX_TU_SIZE * MAX_TU_SIZE] );
  
  for( Int y = 0; y < iHeight; y++ )
  {
    for( Int x = 0; x < iWidth; x++ )
    {
      block[( y * iWidth ) + x] = residual[( y * stride ) + x];
    }
  }

  {
    switch (iWidth)
    {
    case 2:     fastForwardDCT2_B2(block, tmp, shift_1st, iHeight, 0, iSkipWidth);  break;
    case 4:     fastForwardDCT2_B4(block, tmp, shift_1st, iHeight, 0, iSkipWidth);  break;
    case 8:     fastForwardDCT2_B8  (block, tmp, shift_1st, iHeight, 0, iSkipWidth);  break;
    case 16:    fastForwardDCT2_B16 (block, tmp, shift_1st, iHeight, 0, iSkipWidth);  break;
    case 32:    fastForwardDCT2_B32 (block, tmp, shift_1st, iHeight, 0, iSkipWidth);  break;
    case 64:    fastForwardDCT2_B64 (block, tmp, shift_1st+ COM16_C806_TRANS_PREC, iHeight, 0, iSkipWidth);  break;
    case 128:   fastForwardDCT2_B128(block, tmp, shift_1st+ COM16_C806_TRANS_PREC, iHeight, 0, iSkipWidth);  break;
    default:
      THROW( "Unsupported transformation size" ); break;
    }
  }

  {
    switch (iHeight)
    {
    case 2:     fastForwardDCT2_B2(tmp, coeff, shift_2nd, iWidth, iSkipWidth, iSkipHeight);  break;
    case 4:     fastForwardDCT2_B4(tmp, coeff, shift_2nd, iWidth, iSkipWidth, iSkipHeight);  break;
    case 8:     fastForwardDCT2_B8  (tmp, coeff, shift_2nd, iWidth, iSkipWidth, iSkipHeight);  break;
    case 16:    fastForwardDCT2_B16 (tmp, coeff, shift_2nd, iWidth, iSkipWidth, iSkipHeight);  break;
    case 32:    fastForwardDCT2_B32 (tmp, coeff, shift_2nd, iWidth, iSkipWidth, iSkipHeight);  break;
    case 64:    fastForwardDCT2_B64 (tmp, coeff, shift_2nd+ COM16_C806_TRANS_PREC, iWidth, iSkipWidth, iSkipHeight);  break;
    case 128:   fastForwardDCT2_B128(tmp, coeff, shift_2nd+ COM16_C806_TRANS_PREC, iWidth, iSkipWidth, iSkipHeight);  break;
    default:
      THROW( "Unsupported transformation size" ); break;
    }
  }
}


/** MxN inverse transform (2D)
*  \param bitDepth              [in]  bit depth
*  \param coeff                 [in]  transform coefficients
*  \param residual              [out] residual block
*  \param stride                [out] stride of the residual block
*  \param width                 [in]  width of transform
*  \param height                [in]  height of transform
*  \param useDST                [in]
*  \param maxLog2TrDynamicRange [in]
*/
void xITrMxN( const int bitDepth, const TCoeff *coeff, Pel *residual, size_t stride, size_t width, size_t height, bool useDST, const int maxLog2TrDynamicRange )
{
  const Int TRANSFORM_MATRIX_SHIFT = g_transformMatrixShift[TRANSFORM_INVERSE];
  const int iWidth  = (int)width;
  const int iHeight = (int)height;


  Int shift_1st = TRANSFORM_MATRIX_SHIFT + 1; //1 has been added to shift_1st at the expense of shift_2nd
  Int shift_2nd = (TRANSFORM_MATRIX_SHIFT + maxLog2TrDynamicRange - 1) - bitDepth;
  const TCoeff clipMinimum = -(1 << maxLog2TrDynamicRange);
  const TCoeff clipMaximum =  (1 << maxLog2TrDynamicRange) - 1;

  UInt uiSkipWidth  = ( iWidth  > JVET_C0024_ZERO_OUT_TH ? iWidth  - JVET_C0024_ZERO_OUT_TH : 0 );
  UInt uiSkipHeight = ( iHeight > JVET_C0024_ZERO_OUT_TH ? iHeight - JVET_C0024_ZERO_OUT_TH : 0 );

  CHECK( shift_1st < 0, "Negative shift" );
  CHECK( shift_2nd < 0, "Negative shift" );

  ALIGN_DATA( MEMORY_ALIGN_DEF_SIZE, TCoeff block[MAX_TU_SIZE * MAX_TU_SIZE] );
  ALIGN_DATA( MEMORY_ALIGN_DEF_SIZE, TCoeff   tmp[MAX_TU_SIZE * MAX_TU_SIZE] );

  {
    switch (iHeight)
    {
    case   2: fastInverseDCT2_B2(coeff, tmp, shift_1st, iWidth, uiSkipWidth, uiSkipHeight, clipMinimum, clipMaximum); break;
    case   4: fastInverseDCT2_B4(coeff, tmp, shift_1st, iWidth, uiSkipWidth, uiSkipHeight, clipMinimum, clipMaximum); break;
    case   8: fastInverseDCT2_B8  (coeff, tmp, shift_1st, iWidth, uiSkipWidth, uiSkipHeight, clipMinimum, clipMaximum); break;
    case  16: fastInverseDCT2_B16 (coeff, tmp, shift_1st, iWidth, uiSkipWidth, uiSkipHeight, clipMinimum, clipMaximum); break;
    case  32: fastInverseDCT2_B32 (coeff, tmp, shift_1st, iWidth, uiSkipWidth, uiSkipHeight, clipMinimum, clipMaximum); break;
    case  64: fastInverseDCT2_B64 (coeff, tmp, shift_1st + COM16_C806_TRANS_PREC, iWidth, uiSkipWidth, uiSkipHeight, clipMinimum, clipMaximum); break;
    case 128: fastInverseDCT2_B128(coeff, tmp, shift_1st + COM16_C806_TRANS_PREC, iWidth, uiSkipWidth, uiSkipHeight, clipMinimum, clipMaximum); break;
    default:
      THROW( "Unsupported transformation size" ); break;
    }
  }

  {
    switch (iWidth)
    {
    case   2: fastInverseDCT2_B2(tmp, block, shift_2nd, iHeight,  0, uiSkipWidth, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    // Clipping here is not in the standard, but is used to protect the "Pel" data type into which the inverse-transformed samples will be copied
    case   4: fastInverseDCT2_B4(tmp, block, shift_2nd, iHeight, 0, uiSkipWidth, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    case   8: fastInverseDCT2_B8  (tmp, block, shift_2nd, iHeight, 0, uiSkipWidth, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    case  16: fastInverseDCT2_B16 (tmp, block, shift_2nd, iHeight, 0, uiSkipWidth, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    case  32: fastInverseDCT2_B32 (tmp, block, shift_2nd, iHeight, 0, uiSkipWidth, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    case  64: fastInverseDCT2_B64 (tmp, block, shift_2nd + COM16_C806_TRANS_PREC, iHeight, 0, uiSkipWidth, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    case 128: fastInverseDCT2_B128(tmp, block, shift_2nd + COM16_C806_TRANS_PREC, iHeight, 0, uiSkipWidth, std::numeric_limits<Pel>::min(), std::numeric_limits<Pel>::max()); break;
    default:
      THROW( "Unsupported transformation size" );
      break;
    }
  }

  for (Int y = 0; y < iHeight; y++)
  {
    for (Int x = 0; x < iWidth; x++)
    {
      residual[(y * stride)+x] = Pel(block[(y * width) + x]);
    }
  }
}
