#pragma once

#pragma unmanaged 
#include "opencv2\imgproc\imgproc.hpp"
#pragma managed 

#include "EllipseInfo.h"
#include "Primitives.h"

namespace Fugro
{
  namespace OpenCV
  {
    using namespace cv;

    using namespace System::Collections::Generic;

    public ref class Contour
    {
    private:
      initonly array<DoublePoint>^ contour;
      initonly bool hasParentContour;

      Mat ConvertContour();

    internal:
      Contour(std::vector<Point> contourPoints, Vec4i hierarchy);

    public:
      Contour(array<DoublePoint>^ points);

      property IEnumerable<DoublePoint>^ Points
      {
        IEnumerable<DoublePoint>^ get()
        {
          return contour;
        }
      }

      property int Count
      {
        int get()
        {
          return contour->Length;
        }
      }

      property bool HasParentContour
      {
        bool get()
        {
          return hasParentContour;
        }
      }

      EllipseInfo FitEllipse();

      double ArcLength(bool isClosed);

      double ContourArea(bool isOriented);
    };
  }
}