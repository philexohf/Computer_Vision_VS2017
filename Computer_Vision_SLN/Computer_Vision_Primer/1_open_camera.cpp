#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	VideoCapture cap(0);
	namedWindow("camera", 0);

	while (cap.isOpened())
	{
		Mat frame;
		cap >> frame;
		imshow("camera", frame);
		waitKey(30);
	}
	return 0;

}

