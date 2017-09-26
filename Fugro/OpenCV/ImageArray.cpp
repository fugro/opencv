#include "ImageArray.h"
#include <msclr\marshal_cppstd.h> 
#include "opencv2\imgcodecs\imgcodecs.hpp"
#include "opencv2\video\tracking.hpp"

using namespace System;
using namespace Fugro::OpenCV;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Media;

using namespace msclr::interop;

ImageArray^ CreateImageArray(const UMat& mat)
{
  return gcnew ImageArray(mat);
}

ImageArray::ImageArray(const UMat& image) : MatArray(image, gcnew CreateDelegate(CreateImageArray))
{
}

UMat CreateFromBitmapSource(BitmapSource^ bitmapSource)
{
  if (bitmapSource == nullptr)
  {
    throw gcnew ArgumentNullException("bitmapSource");
  }

  int stride = bitmapSource->PixelWidth * bitmapSource->Format.BitsPerPixel / 8;
  auto pixels = gcnew array<unsigned char>(bitmapSource->PixelHeight * stride);
  bitmapSource->CopyPixels(pixels, stride, 0);

  GCHandle handle = GCHandle::Alloc(pixels, GCHandleType::Pinned);

  try
  {
    System::IntPtr ptr = handle.AddrOfPinnedObject();

    int type;
    if (bitmapSource->Format == PixelFormats::Gray8)
    {
      type = CV_8UC1;
    }
    else if (bitmapSource->Format == PixelFormats::Bgr32 || bitmapSource->Format == PixelFormats::Bgra32)
    {
      type = CV_8UC4;
    }
    else if (bitmapSource->Format == PixelFormats::Bgr24)
    {
      type = CV_8UC3;
    }
    else
    {
      throw gcnew NotSupportedException(System::String::Format("Pixel format {0} is not supported.", bitmapSource->Format));
    }

    Mat image(bitmapSource->PixelHeight, bitmapSource->PixelWidth, type, ptr.ToPointer());

    UMat result;
    image.copyTo(result);

    return result;
  }
  finally
  {
    handle.Free();
  }
}

ImageArray::ImageArray(BitmapSource^ bitmapSource) : MatArray(CreateFromBitmapSource(bitmapSource), gcnew CreateDelegate(CreateImageArray))
{
}

UMat CreateFromArray(array<unsigned char>^ pixels, int width, int height)
{
  GCHandle handle = GCHandle::Alloc(pixels, GCHandleType::Pinned);
  try
  {
    System::IntPtr ptr = handle.AddrOfPinnedObject();

    Mat image(height, width, CV_8UC1, ptr.ToPointer());

    UMat result;
    image.copyTo(result);

    return result;
  }
  finally
  {
    handle.Free();
  }
}

ImageArray::ImageArray(array<unsigned char>^ pixels, int width, int height) : MatArray(CreateFromArray(pixels, width, height), gcnew CreateDelegate(CreateImageArray))
{
}

UMat CreateFromFile(System::String^ fileName)
{
  std::string standardString = marshal_as<std::string>(fileName);

  return imread(standardString, IMREAD_UNCHANGED).getUMat(ACCESS_READ);
}

ImageArray::ImageArray(System::String^ fileName) : MatArray(CreateFromFile(fileName), gcnew CreateDelegate(CreateImageArray))
{
}

array<unsigned char>^ ImageArray::CopyPixels()
{
  array<unsigned char>^ result = gcnew array<unsigned char>(Columns * Rows * ChannelCount);

  Marshal::Copy(IntPtr(this->mat->getMat(ACCESS_READ).data), result, 0, result->Length);

  GC::KeepAlive(this);

  return result;
}

unsigned char ImageArray::At(int column, int row)
{
  AssertRowIndexInRange(row, "row");
  AssertColumnIndexInRange(column, "column");

	try
	{
		if (this->mat->type() == CV_8UC1)
		{
			return this->mat->getMat(ACCESS_READ).at<unsigned char>(row, column);
		}
		else
		{
			throw gcnew NotSupportedException(System::String::Format("Data type {0} is not supported.", this->mat->type()));
		}
	}
	finally
	{
		GC::KeepAlive(this);
	}
}

IEnumerable<OpticalFlowResult>^ ImageArray::CalculateOpticalFlowPyrLK(ImageArray^ nextImage, IEnumerable<DoublePoint>^ previousPoints)
{
  return CalculateOpticalFlowPyrLK(nextImage, previousPoints, Int32Size(21, 21), 3);
}

IEnumerable<OpticalFlowResult>^ ImageArray::CalculateOpticalFlowPyrLK(ImageArray^ nextImage, IEnumerable<DoublePoint>^ previousPoints, Int32Size windowSize, int maxLevel)
{
  std::vector<Point2f> nextPts;
  std::vector<Point2f> prevPts;
  for each (auto point in previousPoints)
  {
    nextPts.push_back(static_cast<Point2f>(point));
    prevPts.push_back(static_cast<Point2f>(point));
  }

  Mat cvStatus;
  Mat cvError;

  calcOpticalFlowPyrLK(*this->mat, *nextImage->mat, prevPts, nextPts, cvStatus, cvError, windowSize, maxLevel);

  GC::KeepAlive(this);
  GC::KeepAlive(nextImage);

  auto result = gcnew List<OpticalFlowResult>();

  int i = 0;
  for each(auto point in nextPts)
  {
    result->Add(OpticalFlowResult(point, cvStatus.at<bool>(i), cvError.at<float>(i)));

    i++;
  }

  return result;
}

ImageArray^ ImageArray::Canny(double threshold1, double threshold2)
{
  UMat result;

  cv::Canny(*this->mat, result, threshold1, threshold2);

  GC::KeepAlive(this);

  return gcnew ImageArray(result);
}

IEnumerable<DoublePoint>^ ImageArray::CornerSubPixel(IEnumerable<DoublePoint>^ corners, Int32Size windowSize, int maxIteration, double terminationCriteria)
{
  std::vector<Point2f> opencvCorners;
  for each (auto point in corners)
  {
    opencvCorners.push_back(static_cast<Point2f>(point));
  }

  cornerSubPix(*this->mat, opencvCorners, windowSize, cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, maxIteration, terminationCriteria));

  GC::KeepAlive(this);

  auto result = gcnew List<DoublePoint>();
  for (size_t i = 0; i < opencvCorners.size(); i++)
  {
    result->Add(opencvCorners.at(i));
  }

  return result;
}

ImageArray^ ImageArray::ExtractRoi(System::Windows::Int32Rect roi)
{
  Rect roi2(roi.X, roi.Y, roi.Width, roi.Height);
  auto rect = roi2 & Rect(0, 0, Columns, Rows);

  auto result = UMat(*this->mat, rect);

  GC::KeepAlive(this);

  return gcnew ImageArray(result);
}

IEnumerable<Contour^>^ ImageArray::FindContours(ContourRetrievalMode mode, ContourApproximationMethod method)
{
  std::vector<std::vector<cv::Point>> contours;
  std::vector<Vec4i> hierarchy;

  findContours(*this->mat, contours, hierarchy, (int)mode, (int)method);

  int size = (int)contours.size();
  array<Contour^>^ result = gcnew array<Contour^>(size);
  for (int i = 0; i < size; i++)
  {
    result[i] = gcnew Contour(contours[i], hierarchy[i]);
  }

  GC::KeepAlive(this);

  return result;
}

unsigned char ImageArray::GetSubPixelValue(double x, double y)
{
  Mat patch;

  getRectSubPix(*this->mat, cv::Size2i(1, 1), Point2d(x, y), patch);

  GC::KeepAlive(this);

  return patch.at<Vec3b>(0, 0)[0];
}

IEnumerable<DoublePoint>^ ImageArray::GoodFeaturesToTrack(int maximumCorners, double qualityLevel, int minimumDistance, System::Windows::Int32Rect roi)
{
  std::vector<Point2f> corners;

  Mat mask(this->mat->rows, this->mat->cols, CV_8UC1, cv::Scalar::all(0));
  mask(Rect(roi.X, roi.Y, roi.Width, roi.Height)) = 255;

  goodFeaturesToTrack(*this->mat, corners, maximumCorners, qualityLevel, minimumDistance, mask);

  GC::KeepAlive(this);

  auto result = gcnew List<DoublePoint>();
  for (size_t i = 0; i < corners.size(); i++)
  {
    result->Add(corners.at(i));
  }

  return result;
}

IEnumerable<DoublePoint>^ ImageArray::GoodFeaturesToTrack(int maximumCorners, double qualityLevel, int minimumDistance)
{
  std::vector<Point2f> corners;

  goodFeaturesToTrack(*this->mat, corners, maximumCorners, qualityLevel, minimumDistance);

  GC::KeepAlive(this);

  auto result = gcnew List<DoublePoint>();
  for (size_t i = 0; i < corners.size(); i++)
  {
    result->Add(corners.at(i));
  }

  return result;
}

DoubleArray^ ImageArray::MatchTemplate(ImageArray^ templateImage, TemplateMatchingMethod matchMethod)
{
  Mat mat32;
  matchTemplate(*this->mat, *templateImage->mat, mat32, (int)matchMethod);

  UMat mat64;
  mat32.convertTo(mat64, CV_64F);

  GC::KeepAlive(this);
  GC::KeepAlive(templateImage);

  return gcnew DoubleArray(mat64);
}

void ImageArray::Save(System::String^ fileName)
{
  std::string standardString = marshal_as<std::string>(fileName);
  imwrite(standardString, *this->mat);

  GC::KeepAlive(this);
}

void ImageArray::SetTo(unsigned char value)
{ 
  this->mat->setTo(Scalar(value));

  GC::KeepAlive(this);
}

DoubleArray^ ImageArray::Sobel(int xOrder, int yOrder, int filterSize)
{
  return Sobel(xOrder, yOrder, filterSize, 1.0);
}

DoubleArray^ ImageArray::Sobel(int xOrder, int yOrder, int filterSize, double scale)
{
  UMat result;
  cv::Sobel(*this->mat, result, CV_64F, xOrder, yOrder, filterSize, scale);

  GC::KeepAlive(this);

  return gcnew DoubleArray(result);
}

ImageArray^ ImageArray::Threshold(unsigned char value, unsigned char maxValue, ThresholdType type)
{
  UMat result;
  threshold(*this->mat, result, value, maxValue, (int)type);

  GC::KeepAlive(this);

  return gcnew ImageArray(result);
}

DoubleArray^ ImageArray::ToDoubleArray()
{
  UMat result;

  mat->convertTo(result, CV_64F);

  GC::KeepAlive(this);

  return gcnew DoubleArray(result);
}

ImageArray^ ImageArray::ConvertColor(ColorConversion conversion)
{
  UMat result;

  try
  {
    cvtColor(*this->mat, result, (int)conversion);
  }
  catch (cv::Exception& e)
  {
    throw gcnew InvalidOperationException(gcnew System::String(e.msg.c_str()));
  }

  GC::KeepAlive(this);

  return gcnew ImageArray(result);
}

ImageArray^ ImageArray::Undistort(DoubleArray^ cameraMatrix, DoubleArray^ distortionCoefficients)
{
  Mat eye = Mat::eye(3, 3, CV_32F);

  Mat map1;
  Mat map2;
  initUndistortRectifyMap(*cameraMatrix->mat, *distortionCoefficients->mat, eye, *cameraMatrix->mat, this->mat->size(), CV_32FC1, map1, map2);

  UMat result;
  remap(*this->mat, result, map1, map2, INTER_NEAREST);

  GC::KeepAlive(this);
  GC::KeepAlive(cameraMatrix);
  GC::KeepAlive(distortionCoefficients);

  return gcnew ImageArray(result);
}
