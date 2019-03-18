#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("./image/test.jpg");
	namedWindow("src", 0);
	imshow("src", srcImage); 
	Mat dstImage, edge, grayImage;

	dstImage.create(srcImage.size(), srcImage.type());

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, edge, Size(5, 5));
	Canny(edge, edge, 30, 90, 3);
	namedWindow("Canny_edge", 0);
	imshow("Canny_edge", edge);

	waitKey(0);
	destroyAllWindows();
}
