#pragma once

#include "ImageArray.h"

using namespace System;
using namespace System::Windows;

namespace Fugro
{
  namespace OpenCV
  {
    public interface class IGrabCut
    {
      array<Byte>^ Iterate(ImageArray^ image, int iterationCount);

      property Int32Rect Roi
      {
        Int32Rect get();
        void set(Int32Rect value);
      }
    };

    public ref class GrabCut : public IGrabCut
    {
    private:
      Int32Rect roi;

    public:
      void AddForegroundPoint(System::Windows::Point point);
      void AddBackgroundPoint(System::Windows::Point point);
      virtual array<Byte>^ Iterate(ImageArray^ image, int iterationCount);

      virtual property Int32Rect Roi
      {
      public:
        Int32Rect get();
        void set(Int32Rect value);
      };
    };
  }
}