#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 

using namespace cv;

int main()
{
	Mat srcImage = imread("image/summer.png");
	Mat dstImage;

	namedWindow("src");
	namedWindow("GaussianBlur");

	imshow("src", srcImage);
	GaussianBlur(srcImage, dstImage, Size(21, 21), 0, 0);
	imshow("GaussianBlur", dstImage);

	waitKey(0);
}