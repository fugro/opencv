#include "DoubleArray.h"
#include "ImageArray.h"

using namespace System;
using namespace Fugro::OpenCV;
using namespace System::Runtime::InteropServices;

DoubleArray^ CreateDoubleArray(const Mat& mat)
{
  return gcnew DoubleArray(mat);
}

DoubleArray::DoubleArray(const Mat& mat) : MatArray(mat, gcnew CreateDelegate(CreateDoubleArray))
{
  
}

Mat CreateFromArray(array<double>^ data, int width, int height)
{
  GCHandle handle = GCHandle::Alloc(data, GCHandleType::Pinned);
  try
  {
    System::IntPtr ptr = handle.AddrOfPinnedObject();

    Mat tempMat(height, width, CV_64F, ptr.ToPointer());

    Mat result;
    tempMat.copyTo(result);

    return result;
  }
  finally
  {
    handle.Free();
  }
}

DoubleArray::DoubleArray(array<double>^ data, int width, int height) : MatArray(CreateFromArray(data, width, height), gcnew CreateDelegate(CreateDoubleArray))
{
  
}

DoubleArray^ DoubleArray::Add(double scalar)
{
  Mat result;
  add(*this->mat, scalar, result);

  GC::KeepAlive(this);

  return gcnew DoubleArray(result);
}

double DoubleArray::At(int column, int row)
{
  AssertRowIndexInRange(row, "row");        
  AssertColumnIndexInRange(column, "column");
  
  if (this->mat->type() == CV_64F)
  {
    return this->mat->at<double>(row, column);
  }
  else
  {
    throw gcnew NotSupportedException(System::String::Format("At() is not supported on data type {0}.", this->mat->type()));
  }
}

array<double>^ DoubleArray::GetValues()
{
  array<double>^ result = gcnew array<double>(this->mat->size().area());

  Marshal::Copy(IntPtr(this->mat->data), result, 0, result->Length);

  GC::KeepAlive(this);

  return result;
}

DoubleArray^ DoubleArray::Divide(double scalar)
{
  Mat result;

  divide(*this->mat, scalar, result);
  
  GC::KeepAlive(this);

  return gcnew DoubleArray(result);
}

DoubleArray^ DoubleArray::Dft(DftTransformations flags)
{
  Mat result;

  dft(*this->mat, result, (int)flags);

  GC::KeepAlive(this);

  return gcnew DoubleArray(result);
}

DoubleArray^ DoubleArray::InverseDft(DftTransformations flags)
{
  Mat result;

  idft(*this->mat, result, (int)flags);

  GC::KeepAlive(this);

  return gcnew DoubleArray(result);
}

DoubleArray^ DoubleArray::Integral()
{
  Mat result;

  integral(*this->mat, result);

	GC::KeepAlive(this);

  return gcnew DoubleArray(result);
}

DoubleArray^ DoubleArray::Magnitude(DoubleArray^ other)
{
  Mat result;

  magnitude(*this->mat, *other->mat, result);

  GC::KeepAlive(this);
  GC::KeepAlive(other);

  return gcnew DoubleArray(result);
}

Int32Point DoubleArray::MaxLoc()
{ 
  cv::Point max;

  minMaxLoc(*this->mat, nullptr, nullptr, nullptr, &max);

  GC::KeepAlive(this);

  return max;
}

Int32Point DoubleArray::MinLoc()
{ 
  Point min;

  minMaxLoc(*this->mat, nullptr, nullptr, &min, nullptr);

  GC::KeepAlive(this);

  return min;
}

DoubleArray^ DoubleArray::MulSpectrums(DoubleArray^ other, bool conjugate, bool independentRows)
{
  Mat result;

  int flags = independentRows ? DFT_ROWS : 0;

  mulSpectrums(*this->mat, *other->mat, result, flags, conjugate);

  GC::KeepAlive(this);
  GC::KeepAlive(other);

  return gcnew DoubleArray(result);
}

DoubleArray^ DoubleArray::MulSpectrums(DoubleArray^ other, bool conjugate)
{
  return MulSpectrums(other, conjugate, false);
}

ImageArray^ DoubleArray::ToImageArray(double alpha, double beta)
{
  Mat result;
  mat->convertTo(result, CV_8UC1, alpha, beta);

  GC::KeepAlive(this);

  return gcnew ImageArray(result);
}

ImageArray^ DoubleArray::ToImageArray()
{
	Mat result;

  mat->convertTo(result, CV_8UC1);

  GC::KeepAlive(this);

	return gcnew ImageArray(result);
}

int Dft::GetOptimalSize(int vectorSize)
{
  return getOptimalDFTSize(vectorSize);
}
