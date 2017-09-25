#pragma once

#pragma unmanaged 
#include "opencv2\core\core.hpp"
#pragma managed 

namespace Fugro
{
  namespace OpenCV
  {
    using namespace cv;

    public ref class MatArrayBase abstract
    {
    private:
      size_t memoryPressure;

    protected:
      MatArrayBase(const Mat& mat);
      !MatArrayBase();
      ~MatArrayBase();

      void AssertRowIndexInRange(int index, System::String^ paramName);
      void AssertColumnIndexInRange(int index, System::String^ paramName);

    internal:
      Mat* mat;

    public:

      property int ChannelCount
      {
        int get()
        {
          auto count = this->mat->channels();

          System::GC::KeepAlive(this);

          return count;
        }
      }

      property int Rows
      {
        int get()
        {
          auto rows = this->mat->rows;

          System::GC::KeepAlive(this);

          return rows;
        }
      }

      property int Columns
      {
        int get()
        {
          auto cols = this->mat->cols;

          System::GC::KeepAlive(this);

          return cols;
        }
      }

    };
  }
}
