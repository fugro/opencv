#pragma once

#pragma unmanaged 
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\video\tracking.hpp"
#pragma managed 

#include "MatArray.h"
#include "DoubleArray.h"
#include "Enumerations.h"
#include "Contour.h"
#include "OpticalFlowResult.h"

namespace Fugro
{
  namespace OpenCV
  {
    using namespace cv;

    using namespace System::Collections::Generic;
    using namespace System::Windows::Media::Imaging;

    public ref class ImageArray sealed : public MatArray < ImageArray^ >
    {
    internal:
      ImageArray(const Mat& image);

    public:
      ImageArray(BitmapSource^ bitmapSource);
      ImageArray(array<unsigned char>^ pixels, int width, int height);
      ImageArray(System::String^ fileName);

      /// <summary>
      /// Gets a particular element.
      /// </summary>
      /// <exception cref="System::ArgumentOutOfRangeException"></exception>
      unsigned char At(int column, int row);

      /// <summary>
      /// Calculates an optical flow for a sparse feature set using the iterative Lucas-Kanade method with pyramids.
      /// </summary>
      IEnumerable<OpticalFlowResult>^ CalculateOpticalFlowPyrLK(ImageArray^ nextImage, IEnumerable<DoublePoint>^ previousPoints);

      /// <summary>
      /// Calculates an optical flow for a sparse feature set using the iterative Lucas-Kanade method with pyramids.
      /// </summary>
      IEnumerable<OpticalFlowResult>^ CalculateOpticalFlowPyrLK(ImageArray^ nextImage, IEnumerable<DoublePoint>^ previousPoints, Int32Size winSize, int maxLevel);

      /// <summary>
      /// Finds edges in an image using the Canny algorithm.
      /// </summary>
      /// <param name="threshold1">first threshold for the hysteresis procedure.</param>
      /// <param name="threshold2">second threshold for the hysteresis procedure.</param>
      ImageArray^ Canny(double threshold1, double threshold2);

      /// <summary>
      /// Refines the corner locations.
      /// </summary>
      /// <param name="corners">Initial coordinates of the input corners and refined coordinates provided for output.</param>
      /// <param name="windowSize">Half size of the search window.</param>
      IEnumerable<DoublePoint>^ CornerSubPixel(IEnumerable<DoublePoint>^ corners, Int32Size windowSize, int maxIteration, double terminationCriteria);

      /// <summary>
      /// Extracts a rectangular region of interest (roi) from the image.
      /// </summary>
      /// <remarks>Roi will be clipped if it exceeds image.</remarks>
      ImageArray^ ExtractRoi(System::Windows::Int32Rect roi);

      /// <summary>
      /// Finds contours in a binary image.
      /// </summary>
      /// <param name="mode">Contour retrieval mode.</param>
      /// <param name="method">Contour approximation method.</param>
      IEnumerable<Contour^>^ FindContours(ContourRetrievalMode mode, ContourApproximationMethod method);

      array<unsigned char>^ CopyPixels();

      unsigned char GetSubPixelValue(double x, double y);

      /// <summary>
      /// Determines strong corners on an image.
      /// </summary>
      /// <param name="maximumCorners">Maximum number of corners to return. If there are more corners than are found, the strongest of them are returned.</param>
      /// <param name="qualityLevel">Parameter characterizing the minimal accepted quality of image corners.</param>
      /// <param name="minimumDistance">Minimum possible Euclidean distance between the returned corners.</param>
      /// <param name="roi">Sets a region of interest.</param>
      IEnumerable<DoublePoint>^ GoodFeaturesToTrack(int maximumCorners, double qualityLevel, int minimumDistance, System::Windows::Int32Rect roi);

      /// <summary>
      /// Determines strong corners on an image.
      /// </summary>
      /// <param name="maximumCorners">Maximum number of corners to return. If there are more corners than are found, the strongest of them are returned.</param>
      /// <param name="qualityLevel">Parameter characterizing the minimal accepted quality of image corners.</param>
      /// <param name="minimumDistance">Minimum possible Euclidean distance between the returned corners.</param>
      IEnumerable<DoublePoint>^ GoodFeaturesToTrack(int maximumCorners, double qualityLevel, int minimumDistance);

      /// <summary>
      /// Compares a template against overlapped image regions.
      /// </summary>
      DoubleArray^ MatchTemplate(ImageArray^ templateImage, TemplateMatchingMethod matchMethod);

      /// <summary>                
      /// Saves an image to a specified file.                
      /// </summary>                
      void Save(System::String^ fileName);

      /// <summary>
      /// Set pixels to the specified value.
      /// </summary>
      void SetTo(unsigned char value);

      /// <summary>
      /// Apply sobel operator on the image.
      /// </summary>
      /// <param name="xOrder">The order of the derivative in x direction.</param>
      /// <param name="yOrder">The order of the derivative in y direction.</param>
      /// <param name="filterSize">Size of the extended Sobel kernel. It must be 1, 3, 5, or 7.</param>
      DoubleArray^ Sobel(int xOrder, int yOrder, int filterSize);

      /// <summary>
      /// Apply sobel operator on the image.
      /// </summary>
      /// <param name="xOrder">The order of the derivative in x direction.</param>
      /// <param name="yOrder">The order of the derivative in y direction.</param>
      /// <param name="filterSize">Size of the extended Sobel kernel. It must be 1, 3, 5, or 7.</param>
      /// <param name="scale">Scale factor for the computed derivative values.</param>
      DoubleArray^ Sobel(int xOrder, int yOrder, int filterSize, double scale);

      /// <summary>
      /// Perform basic thresholding operation
      /// </summary>
      /// <param name="value">The threshold value with respect to which the thresholding operation is made.</param>
      /// <param name="maxValue">The value used with the Binary thresholding operations (to set the chosen pixels).</param>
      /// <param name="type">One of the thresholding operations.</param>
      ImageArray^ Threshold(unsigned char value, unsigned char maxValue, ThresholdType type);

      /// <summary>
      /// Converts image to DoubleArray.
      /// </summary>
      DoubleArray^ ToDoubleArray();

      /// <summary>
      /// Converts an image from one color space to another.
      /// </summary>
      ImageArray^ ConvertColor(ColorConversion conversion);

      /// <summary>
      /// Transforms an image to compensate for lens distortion.
      /// </summary>
      ImageArray^ Undistort(DoubleArray^ cameraMatrix, DoubleArray^ distortionCoefficients);
    };
  };
}