#include "GrabCut.h"

#pragma unmanaged 
#include "opencv2\imgproc\imgproc.hpp"
#pragma managed 

using namespace Fugro::OpenCV;
using namespace System::Runtime::InteropServices;

Int32Rect GrabCut::Roi::get()
{
	return this->roi;
}

void GrabCut::Roi::set(Int32Rect value)
{
	this->roi = value;
}

void GrabCut::AddForegroundPoint(System::Windows::Point point)
{
	throw gcnew NotImplementedException();
}

void GrabCut::AddBackgroundPoint(System::Windows::Point point)
{
	throw gcnew NotImplementedException();
}

array<Byte>^ GrabCut::Iterate(ImageArray^ imageArray, int iterationCount)
{
  UMat image(*imageArray->mat);

	if (image.type() == CV_8UC4)
	{
		cvtColor(image, image, COLOR_BGRA2BGR);
	}
	if (image.type() == CV_8U)
	{
		cvtColor(image, image, COLOR_GRAY2BGR); 
	}
	else if (image.type() != CV_8UC3)
	{
		throw gcnew NotSupportedException("Image format is not supported.");
	}

	Mat mask(image.size(), CV_8UC1);
	mask.setTo(GC_BGD);
	
	cv::Rect rect(roi.X, roi.Y, roi.Width, roi.Height);
	rect.x = max(0, rect.x);
	rect.y = max(0, rect.y);
	rect.width = min(rect.width, image.cols - rect.x);
	rect.height = min(rect.height, image.rows - rect.y);
	
	(mask(rect)).setTo(GC_PR_FGD);

	//circle(mask, cv::Point(270, 64), radius, GC_FGD, thickness);
	//circle(mask, cv::Point(269, 65), radius, GC_FGD, thickness);
	//circle(mask, cv::Point(270, 65), radius, GC_FGD, thickness);
	
	Mat bgdModel, fgdModel;
	grabCut(image, mask, rect, bgdModel, fgdModel, iterationCount, GC_INIT_WITH_MASK);

	int dataSize = mask.cols * mask.rows;
	array<Byte>^ maskPixels = gcnew array<Byte>(dataSize);
	Marshal::Copy(IntPtr((void *)mask.data), maskPixels, 0, dataSize );
	
	for (int i = 0; i < maskPixels->Length; i++)
	{
		if (maskPixels[i] == GC_PR_FGD || maskPixels[i] == GC_FGD)
		{
			maskPixels[i] = 1;
		}
		else
		{
			maskPixels[i] = 0;
		}
	}

	return maskPixels;
}
