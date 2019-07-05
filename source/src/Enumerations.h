#pragma once

namespace Fugro
{
  namespace OpenCV
  {
    using namespace System;

    public enum class BorderInterpolation
    {
      Replicate = BORDER_REPLICATE,
      Constant = BORDER_CONSTANT,
      Reflect = BORDER_REFLECT,
      Wrap = BORDER_WRAP,
      Reflect101 = BORDER_REFLECT101,
      Transparent = BORDER_TRANSPARENT,
      Default = BORDER_DEFAULT,
      Isolated = BORDER_ISOLATED
    };

    public enum class ContourApproximationMethod
    {
      None = CHAIN_APPROX_NONE,
      Simple = CHAIN_APPROX_SIMPLE,
      TC89_L1 = CHAIN_APPROX_TC89_L1,
      TC89_KCOS = CHAIN_APPROX_TC89_KCOS,
    };

    public enum class ContourRetrievalMode
    {
      External = RETR_EXTERNAL,
      List = RETR_LIST,
      CComp = RETR_CCOMP,
      Tree = RETR_TREE,
    };

    [Flags]
    public enum class DftTransformations
    {
      None = 0,
      Scale = DFT_SCALE,
      Rows = DFT_ROWS,
      ComplexOutput = DFT_COMPLEX_OUTPUT,
      RealOutput = DFT_REAL_OUTPUT,
    };

    public enum class TemplateMatchingMethod
    {
      SquaredDifference = TM_SQDIFF,
      NormalizedSquaredDifference = TM_SQDIFF_NORMED,
      CrossCorrelation = TM_CCORR,
      NormalizedCrossCorrelation = TM_CCORR_NORMED,
      CorrelationCoefficient = TM_CCOEFF,
      NormalizedCorrelationCoefficient = TM_CCOEFF_NORMED
    };

    public enum class ThresholdType
    {
      Binary = THRESH_BINARY,
      BinaryInverted = THRESH_BINARY_INV,
      Truncated = THRESH_TRUNC,
      ToZero = THRESH_TOZERO,
      ToZeroInverted = THRESH_TOZERO_INV,
    };

    public enum class BayerFormat
    {
      BG = COLOR_BayerBG2BGR,
      GB = COLOR_BayerGB2BGR,
      RG = COLOR_BayerRG2BGR,
      GR = COLOR_BayerGR2BGR,
    };

    public enum class ColorConversion
    {
      BayerBG2BGR = COLOR_BayerBG2BGR,
      BayerGB2BGR = COLOR_BayerGB2BGR,
      BayerRG2BGR = COLOR_BayerRG2BGR,
      BayerGR2BGR = COLOR_BayerGR2BGR,
      BGR2HSV = COLOR_BGR2HSV,
      HSV2BGR = COLOR_HSV2BGR,
      GRAY2BGR = COLOR_GRAY2BGR,
      GRAY2BGRA = COLOR_GRAY2BGRA,
      BGR2GRAY = COLOR_BGR2GRAY,
      BGRA2GRAY = COLOR_BGRA2GRAY,
    };
  };
}
