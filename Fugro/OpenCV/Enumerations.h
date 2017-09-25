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
      Code = CV_CHAIN_CODE,
      None = CV_CHAIN_APPROX_NONE,
      Simple = CV_CHAIN_APPROX_SIMPLE,
      TC89_L1 = CV_CHAIN_APPROX_TC89_L1,
      TC89_KCOS = CV_CHAIN_APPROX_TC89_KCOS,
      LinkRuns = CV_LINK_RUNS
    };

    public enum class ContourRetrievalMode
    {
      External = CV_RETR_EXTERNAL,
      List = CV_RETR_LIST,
      CComp = CV_RETR_CCOMP,
      Tree = CV_RETR_TREE,
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
      SquaredDifference = CV_TM_SQDIFF,
      NormalizedSquaredDifference = CV_TM_SQDIFF_NORMED,
      CrossCorrelation = CV_TM_CCORR,
      NormalizedCrossCorrelation = CV_TM_CCORR_NORMED,
      CorrelationCoefficient = CV_TM_CCOEFF,
      NormalizedCorrelationCoefficient = CV_TM_CCOEFF_NORMED
    };

    public enum class ThresholdType
    {
      Binary = CV_THRESH_BINARY,
      BinaryInverted = CV_THRESH_BINARY_INV,
      Truncated = CV_THRESH_TRUNC,
      ToZero = CV_THRESH_TOZERO,
      ToZeroInverted = CV_THRESH_TOZERO_INV,
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