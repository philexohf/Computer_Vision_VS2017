#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat img = imread("image/summer.png");  // 读取当前目录下的图片.
	namedWindow("img", 0);  // 创建一个窗口，参数0表示窗口大小可改变.
	imshow("img", img);  // 显示图片，第一个参数是显示图像的窗口的名字，第二个参数是要显示的图像.

	waitKey(0);
	destroyAllWindows();

}
