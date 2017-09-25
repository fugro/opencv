#pragma once

#pragma unmanaged 
#include "opencv2\core\core.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#pragma managed 

#include "MatArrayBase.h"
#include "Enumerations.h"
#include "Kernel.h"

namespace Fugro
{
  namespace OpenCV
  {
    using namespace cv;

    using namespace System::Collections::Generic;
    using namespace System::Windows::Media::Imaging;

    generic <class T> where T : MatArrayBase
      public ref class MatArray abstract : MatArrayBase
    {

    internal:
      delegate T CreateDelegate(const Mat&);

      MatArray(const Mat&, CreateDelegate^);

    private:
      CreateDelegate^ create;

    public:

      /// <summary>                
      /// Computes an absolute value of each matrix element.               
      /// </summary>                
      T Abs();

      /// <summary>                
      /// Computes the per-element sum of two arrays                
      /// </summary>                
      T Add(T input);

      /// <summary>                
      /// Blurs an image using the box filter                
      /// </summary>  
      T MatArray<T>::BoxFilter(int w);

      /// <summary>
      /// Forms a border around an image.
      /// </summary>
      T CopyMakeBorder(int top, int bottom, int left, int right, BorderInterpolation borderType);

      /// <summary>                
      /// Performs per-element division of two arrays.
      /// </summary> 
      T Divide(T input);

      /// <summary>                
      /// Applies a separable linear filter to an image.                
      /// </summary>
      T Filter2DSeparable(Kernel^ kernelX, Kernel^ kernelY);

      /// <summary>                
      /// Blurs an image using a Gaussian filter.
      /// </summary> 
      /// <param name="kernelWidth">Gaussian kernel width. Must be positive and odd.</param>                
      /// <param name="kernelHeight">Gaussian kernel width. Must be positive and odd.</param>                
      /// <param name="sigmaX">Gaussian kernel standard deviation in X direction.</param>                
      /// <param name="sigmaY">Gaussian kernel standard deviation in Y direction.</param>                
      T GaussianBlur(int kernelWidth, int kernelHeight, double sigmaX, double sigmaY);

      /// <summary>
      /// Performs the per-element comparison (greater than) of two arrays.
      /// </summary>
      T MatArray<T>::GreaterThan(T other);

      /// <summary>
      /// Calculates an average(mean) of array elements.
      /// </summary>
      double MatArray<T>::Mean();

      /// <summary>                
      /// Creates one multi-channel array out of several single-channel ones.
      /// </summary> 
      T Merge(... array<T>^ channels);

      /// <summary>                
      /// Calculates the per-element scaled product of two arrays.                
      /// </summary>                
      /// <param name="input">Input array of the same size and the same type.</param>                
      T Multiply(T input);

      T Multiply(double scalar);

      /// <summary>                
      /// Raises every array element to a power.                
      /// </summary>                
      /// <param name="exponent">Exponent of power.</param>                
      T Pow(double exponent);

      /// <summary>                
      /// Resizes an image (using nearest neighbour interpolation!)              
      /// </summary>                
      /// <param name="newWidth">The width of the new image.</param>    
      /// <param name="newHeight">The height of the new image.</param>    
      T Resize(int newWidth, int newHeight);

      /// <summary>
      /// Smoothes an image and downsamples it.
      /// </summary>
      T PyrDown();

      /// <summary>
      /// Upsamples an image and then smoothes it.
      /// </summary>
      T PyrUp();

      /// <summary>
      /// Divides a multi-channel array into several single-channel arrays.
      /// </summary>
      array<T>^ Split();

      /// <summary>
      /// Calculates the per - element difference between two arrays or array and a scalar.
      /// </summary>
      T Substract(T other);

      /// <summary>                
      /// Calculates a square root of array elements.               
      /// </summary>               
      T Sqrt();

    };
  }
}