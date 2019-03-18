#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat src, src_gray, dst, abs_dst;
	src = imread("./image/1.jpg");
	imshow("src", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);  // 高斯滤波消除噪声
	cvtColor(src, src_gray, COLOR_RGB2GRAY);  // RGB转灰度图
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);  // 使用Laplace算子
	convertScaleAbs(dst, abs_dst);  // 计算绝对值，并将结果转换成8位

	imshow("Laplace", abs_dst);
	waitKey(0);

}
