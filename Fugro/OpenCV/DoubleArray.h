#pragma once

#pragma unmanaged 
#include "opencv2\core\core.hpp"
#pragma managed 

#include "MatArray.h"
#include "Enumerations.h"
#include "Primitives.h"

namespace Fugro
{
  namespace OpenCV
  {
    using namespace cv;

    ref class ImageArray;

    public ref class DoubleArray sealed : public MatArray<DoubleArray^>
    {
    internal:
      DoubleArray(const Mat& mat);

    public:
      DoubleArray(array<double>^ data, int width, int height);

      DoubleArray^ Add(double scalar);

      /// <summary>
      /// Gets a particular element.
      /// </summary>
      /// <exception cref="System::ArgumentOutOfRangeException"></exception>
      double At(int column, int row);

      /// <summary>
      /// Gets a particular element.
      /// </summary>
      /// <exception cref="System::ArgumentOutOfRangeException"></exception>
      double At(Int32Point point)
      {
        return At(point.X, point.Y);
      }

      /// <summary>                
      /// Get all the values of this array.
      /// </summary> 
      array<double>^ GetValues();

      /// <summary>                
      /// Performs per-element division of a scalar by an array.
      /// </summary> 
      DoubleArray^ Divide(double scalar);

      /// <summary>
      /// Performs a forward Discrete Fourier transformation.
      /// </summary>
      DoubleArray^ Dft(DftTransformations transformationFlags);

      /// <summary>
      /// Performs an inverse Discrete Fourier transformation.
      /// </summary>
      DoubleArray^ InverseDft(DftTransformations transformationFlags);

      /// <summary>
      /// Calculates the integral of an image.
      /// </summary>
      DoubleArray^ Integral();

      /// <summary>
      /// Calculates the magnitude of 2D vectors.
      /// </summary>
      DoubleArray^ Magnitude(DoubleArray^ other);

      /// <summary>
      /// Finds the global maximum in an array.
      /// </summary>
      Int32Point MaxLoc();

      /// <summary>
      /// Finds the global minimum in an array.
      /// </summary>
      Int32Point MinLoc();

      /// <summary>
      /// Performs the per-element multiplication of two Fourier spectrums.
      /// </summary>
      /// <param name="other">other array of the same size as current</param>
      /// <param name="conjugate">optional flag that conjugates the second input array before the multiplication (true) or not (false).</param>
      /// <param name="independentRows">value indicating whether that each row of src1 and src2 is an independent 1D Fourier spectrum.</param>
      DoubleArray^ MulSpectrums(DoubleArray^ other, bool conjugate, bool independentRows);

      /// <summary>
      /// Performs the per-element multiplication of two Fourier spectrums.
      /// </summary>
      /// <param name="other">other array of the same size as current</param>
      /// <param name="conjugate">optional flag that conjugates the second input array before the multiplication (true) or not (false).</param>
      DoubleArray^ MulSpectrums(DoubleArray^ other, bool conjugate);

      ImageArray^ ToImageArray();

      ImageArray^ ToImageArray(double alpha, double beta);
    };

    public ref struct Dft sealed
    {
      /// <summary>
      /// Returns the optimal DFT size for a given vector size.
      /// </summary>
      static int GetOptimalSize(int vectorSize);
    };
  }
}