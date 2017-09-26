#pragma once

#include "DoubleArray.h"

namespace Fugro
{
  namespace OpenCV
  {
    public value class OpticalFlowResult
    {
    private:
      DoublePoint trackedPoint;
      bool status;
      double error;

    public:
      property DoublePoint TrackedPoint
      {
        DoublePoint get()
        {
          return trackedPoint;
        }
      }

      property bool Status
      {
        bool get()
        {
          return status;
        }
      }

      property double Error
      {
        double get()
        {
          return error;
        }
      }

    internal:
      OpticalFlowResult(DoublePoint trackedPoint, bool status, float error)
      {
        this->trackedPoint = trackedPoint;
        this->status = status;
        if (status)
        {
          this->error = error;
        }
      }
    };
  }
}