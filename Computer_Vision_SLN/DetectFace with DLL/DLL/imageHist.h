#pragma once
#include <opencv2/opencv.hpp>
using namespace cv;

namespace cvih {
	class ImageHist {
	public:
		static _declspec(dllexport) void imageHist(Mat srcImage);
	};
}
