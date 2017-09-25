#include "MatArray.h"

using namespace System;
using namespace Fugro::OpenCV;

generic<class T>
MatArray<T>::MatArray(const Mat& mat, CreateDelegate^ create) : MatArrayBase(mat)
{
  this->create = create;
}

generic<class T>
T MatArray<T>::Abs()
{      
  Mat output;
  absdiff(*this->mat, Scalar::all(0), output);
 
  GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
T MatArray<T>::Add(T input)
{        
  Mat output;
  add(*this->mat, *input->mat, output);
 
  GC::KeepAlive(this);
  GC::KeepAlive(input);

  return this->create(output);
}

generic<class T>
T MatArray<T>::BoxFilter(int w)
{
  Mat output;

  cv::boxFilter(*this->mat, output, -1, Size(w, w));

	GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
T MatArray<T>::CopyMakeBorder(int top, int bottom, int left, int right, BorderInterpolation borderType)
{
  Mat output;

  copyMakeBorder(*this->mat, output, top, bottom, left, right, (int)borderType);

  GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
T MatArray<T>::Divide(T input)
{
  Mat output;
  divide(*this->mat, *input->mat, output);
  
  GC::KeepAlive(this);
  GC::KeepAlive(input);

  return this->create(output);
}

generic<class T>
T MatArray<T>::Filter2DSeparable(Kernel^ kernelX, Kernel^ kernelY)
{
  Mat output;
  sepFilter2D(*this->mat, output, -1, *kernelX->mat, *kernelY->mat);

  GC::KeepAlive(this);
  GC::KeepAlive(kernelX);
  GC::KeepAlive(kernelY);

  return this->create(output);
}

generic<class T>
T MatArray<T>::GaussianBlur(int kernelWidth, int kernelHeight, double sigmaX, double sigmaY)
{
  Size size(kernelWidth, kernelHeight);
  
  Mat output;
  cv::GaussianBlur(*this->mat, output, size, sigmaX, sigmaY);
  
  GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
double MatArray<T>::Mean()
{
	cv::Scalar result = mean(*this->mat);

	return result[0];
}

generic<class T>
T MatArray<T>::Merge(... array<T>^ channels)
{
  std::vector<Mat> output;
  output.push_back(*this->mat);

  for (int i = 0; i < channels->Length; ++i)
  {
    output.push_back(*channels[i]->mat);
  }

  Mat result;
  merge(output, result);

  GC::KeepAlive(this);
  GC::KeepAlive(channels);
  
  return this->create(result);
}

generic<class T>
T MatArray<T>::Multiply(T input)
{        
  Mat output;
  multiply(*this->mat, *input->mat, output);
  
  GC::KeepAlive(this);
  GC::KeepAlive(input);
  
  return this->create(output);
}

generic<class T>
T MatArray<T>::Multiply(double scalar)
{        
  Mat output(*this->mat * scalar);

  GC::KeepAlive(this);
  
  return this->create(output);
}

generic<class T>
T MatArray<T>::Pow(double exponent)
{        
  Mat output;
  pow(*this->mat, exponent, output);
  
  GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
T MatArray<T>::PyrDown()
{
  Mat output;
  pyrDown(*this->mat, output);

  GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
T MatArray<T>::PyrUp()
{
  Mat output;
  pyrUp(*this->mat, output);

  GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
T MatArray<T>::Resize(int newWidth, int newHeight)
{
	Size size = Size(newWidth, newHeight);
	
  Mat output;
  resize(*this->mat, output, size, 0, 0, INTER_NEAREST);

  GC::KeepAlive(this);

  return this->create(output);
}

generic<class T>
array<T>^ MatArray<T>::Split()
{
  std::vector<Mat> output;

  split(*this->mat, output);

  array<T>^ result = gcnew array<T>((int)output.size());
  for (size_t i = 0; i < output.size(); ++i)
  {
    result[(int)i] = this->create(output.at(i));
  }

  GC::KeepAlive(this);

  return result;
}

generic<class T>
T  MatArray<T>::Substract(T other)
{
  Mat output;
  subtract(*this->mat, *other->mat, output);

  GC::KeepAlive(this);
  GC::KeepAlive(other);
  
  return this->create(output);
}

generic<class T>
T  MatArray<T>::GreaterThan(T other)
{
  Mat output;
  compare(*this->mat, *other->mat, output, CMP_GT);

	GC::KeepAlive(this);
	GC::KeepAlive(other);

  return this->create(output);
}

generic<class T>
T MatArray<T>::Sqrt()
{        
  Mat output;
  sqrt(*this->mat, output);
  
  GC::KeepAlive(this);

  return this->create(output);
}