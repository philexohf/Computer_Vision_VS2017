#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	VideoCapture cap("paris.mp4");
	namedWindow("video", 0);

	while (cap.isOpened())
	{
		Mat frame;  
		cap >> frame;  
		imshow("video", frame);
		waitKey(30);  
	}
	return 0;

}
