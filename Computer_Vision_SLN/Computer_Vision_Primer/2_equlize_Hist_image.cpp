#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	srcImage = imread("./image/test.jpg", 1);

	if (!srcImage.data){ 
		printf("读取图片错误.\n"); 
		return false; 
	}

	namedWindow("src", 0);
	namedWindow("equalizeHist", 0);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);  // 转为灰度图
	imshow("src", srcImage);

	equalizeHist(srcImage, dstImage);  // 直方图均衡

	imshow("equalizeHist", dstImage);

	waitKey(0);
}