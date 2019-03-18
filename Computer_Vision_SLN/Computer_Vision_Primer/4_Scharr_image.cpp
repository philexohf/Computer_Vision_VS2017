#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	Mat src = imread("./image/1.jpg");
	imshow("src", src);

	Scharr(src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);  // X方向梯度
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("Scharr_X", abs_grad_x);

	Scharr(src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);  // Y方向梯度
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("Scharr_Y", abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);  // 合并梯度

	imshow("Scharr", dst);
	waitKey(0);

}
