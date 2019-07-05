#pragma once

#include "Primitives.h"

namespace Fugro
{
  namespace OpenCV
  {
    using namespace cv;

    public value class EllipseInfo
    {
    private:
      DoublePoint center;
      double majorRadius;
      double minorRadius;
      double orientationInDegrees;

    internal:
      EllipseInfo(RotatedRect boundingBox)
      {
        center = boundingBox.center;
        majorRadius = boundingBox.size.height / 2.0;
        minorRadius = boundingBox.size.width / 2.0;
        orientationInDegrees = boundingBox.angle;
      }

    public:
      property DoublePoint Center
      {
      public:
        DoublePoint get()
        {
          return center;
        }
      }

      property double MajorRadius
      {
      public:
        double get()
        {
          return majorRadius;
        }
      }

      property double MinorRadius
      {
      public:
        double get()
        {
          return minorRadius;
        }
      }

      property double OrientationInDegrees
      {
      public:
        double get()
        {
          return orientationInDegrees;
        }
      }
    };
  };
}