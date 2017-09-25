#include "Contour.h"

using namespace Fugro::OpenCV;
using namespace cv;

Contour::Contour(std::vector<cv::Point> contourPoints, Vec4i hierarchy)
{
  int size = (int)contourPoints.size();
  contour = gcnew array<DoublePoint>(size);

  for (int i = 0; i < size; i++)
  {
    contour[i] = contourPoints[i];
  }

  hasParentContour = hierarchy[3] != -1;
}

Contour::Contour(array<DoublePoint>^ points)
{
  contour = points;
  hasParentContour = false;
}

EllipseInfo Contour::FitEllipse()
{
  Mat points = ConvertContour();

  RotatedRect result = fitEllipse(points);

  return EllipseInfo(result);
}

double Contour::ArcLength(bool isClosed)
{
  Mat points = ConvertContour();

  return arcLength(points, isClosed);
}

double Contour::ContourArea(bool isOriented)
{
  Mat points = ConvertContour();

  return contourArea(points, isOriented);
}

Mat Contour::ConvertContour()
{
  Mat result;
  for each (auto point in contour)
  {
    result.push_back(static_cast<Point2f>(point));
  }

  return result;
}