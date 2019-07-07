#include "MatArrayBase.h"
#include <msclr\marshal_cppstd.h> 

using namespace Fugro::OpenCV;
using namespace System;


MatArrayBase::MatArrayBase(const Mat& mat)
{
  this->mat = new Mat(mat);
  
  auto sizeInBytes = this->mat->total() * this->mat->elemSize();
  if (sizeInBytes > 0)
  {
    this->memoryPressure = sizeInBytes;
    GC::AddMemoryPressure(sizeInBytes);
  }
  else
  {
    this->memoryPressure = 0;
  }
}

MatArrayBase::!MatArrayBase()
{
  delete this->mat;
  this->mat = nullptr;
  if (this->memoryPressure > 0)
  {
    GC::RemoveMemoryPressure(this->memoryPressure);
    this->memoryPressure = 0;
  } 
}

MatArrayBase::~MatArrayBase()
{
  this->!MatArrayBase();
}

void MatArrayBase::AssertRowIndexInRange(int index, System::String^ paramName)
{
  if (index < 0 || index >= this->Rows)
  {
    throw gcnew ArgumentOutOfRangeException(paramName);
  }
}

void MatArrayBase::AssertColumnIndexInRange(int index, System::String^ paramName)
{
  if (index < 0 || index >= this->Columns)
  {
    throw gcnew ArgumentOutOfRangeException(paramName);
  }
}

