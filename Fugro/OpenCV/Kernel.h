#pragma once

#include "MatArrayBase.h"
#include "Primitives.h"

namespace Fugro
{
  namespace OpenCV
  {
    public ref class Kernel sealed : MatArrayBase
    {
    protected:
      Kernel(const UMat& mat);

    public:
      Kernel(array<double>^ kernel);
      Kernel(array<double>^ kernel, int width, int height);

      /// <summary>
      /// Gets a particular element.
      /// </summary>
      /// <exception cref="System::ArgumentOutOfRangeException"></exception>
      double At(int column, int row);

      /// <summary>
      /// Returns Gaussian filter coefficients.
      /// </summary>
      /// <param name="size">Aperture size.It should be odd and positive</param>
      /// <param name="sigma">Gaussian standard deviation.</param>
      static Kernel^ GetGaussianKernel(int size, double sigma);
    };
  }
}