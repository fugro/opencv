#pragma once

#pragma unmanaged 
#include "opencv2\core\core.hpp"
#pragma managed

namespace Fugro
{
  namespace OpenCV
  {
    public value class DoublePoint
    {
    public:
      DoublePoint(double x, double y)
      {
        this->x = x;
        this->y = y;
      }

      property double X
      {
        double get()
        {
          return x;
        }
      }

      property double Y
      {
        double get()
        {
          return y;
        }
      }

      virtual System::String^ ToString() override
      {
        return System::String::Format("{0}, {1}", x, y);
      }

      static operator DoublePoint(System::Windows::Point point)
      {
        return DoublePoint(point.X, point.Y);
      }

      static operator System::Windows::Point(DoublePoint point)
      {
        return System::Windows::Point(point.x, point.y);
      }

    internal:
      static operator DoublePoint(cv::Point2d point)
      {
        return DoublePoint(point.x, point.y);
      }

      static operator DoublePoint(cv::Point2f point)
      {
        return DoublePoint(point.x, point.y);
      }

      static operator DoublePoint(cv::Point2i point)
      {
        return DoublePoint(point.x, point.y);
      }

      static operator cv::Point2d(DoublePoint point)
      {
        return cv::Point2d(point.x, point.y);
      }

      static explicit operator cv::Point2f(DoublePoint point)
      {
        return cv::Point2f((float)point.x, (float)point.y);
      }

    private:
      double x;
      double y;
    };

    public value class Int32Point
    {
    public:
      Int32Point(int x, int y)
      {
        this->x = x;
        this->y = y;
      }

      property int X
      {
        int get()
        {
          return x;
        }
      }

      property int Y
      {
        int get()
        {
          return y;
        }
      }

      virtual System::String^ ToString() override
      {
        return System::String::Format("{0}, {1}", x, y);
      }

      static operator Int32Point(System::Drawing::Point point)
      {
        return Int32Point(point.X, point.Y);
      }

      static operator System::Drawing::Point(Int32Point point)
      {
        return System::Drawing::Point(point.x, point.y);
      }

    internal:
      static operator Int32Point(cv::Point2i point)
      {
        return Int32Point(point.x, point.y);
      }

      static operator cv::Point2i(Int32Point point)
      {
        return cv::Point2i(point.x, point.y);
      }

    private:
      int x;
      int y;
    };

    public value class Int32Size
    {
    public:
      Int32Size(int width, int height)
      {
        this->width = width;
        this->height = height;
      }

      virtual System::String^ ToString() override
      {
        return System::String::Format("{0}, {1}", width, height);
      }

    internal:
      static operator Int32Size(cv::Size2i size)
      {
        return Int32Size(size.width, size.height);
      }

      static operator cv::Size2i(Int32Size size)
      {
        return cv::Size2i(size.width, size.height);
      }

    public:
      property int Width
      {
        int get()
        {
          return width;
        }
      }

      property int Height
      {
        int get()
        {
          return height;
        }
      }

    private:
      int width;
      int height;
    };
  };
}
