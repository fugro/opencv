#include "Kernel.h"

#pragma unmanaged 
#include "opencv2\imgproc\imgproc.hpp"
#pragma managed 

using namespace Fugro::OpenCV;
using namespace System;
using namespace System::Runtime::InteropServices;

Kernel::Kernel(const Mat& mat) : MatArrayBase(mat)
{

}

Mat CreateFromArray(array<double>^ kernel)
{
  GCHandle handle = GCHandle::Alloc(kernel, GCHandleType::Pinned);
  try
  {
    System::IntPtr ptr = handle.AddrOfPinnedObject();

    Mat tempMat(kernel->Length, 1, CV_64F, ptr.ToPointer());

    Mat result;
    tempMat.copyTo(result);
    
    return result;
  }
  finally
  {
    handle.Free();
  }
}

Kernel::Kernel(array<double>^ kernel) :MatArrayBase(CreateFromArray(kernel))
{

}

double Kernel::At(int column, int row)
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

Kernel^ Kernel::GetGaussianKernel(int size, double sigma)
{
  auto mat = cv::getGaussianKernel(size, sigma);

  return gcnew Kernel(mat);
}
