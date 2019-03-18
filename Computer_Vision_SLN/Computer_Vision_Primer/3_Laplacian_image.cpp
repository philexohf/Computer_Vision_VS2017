#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat src, src_gray, dst, abs_dst;
	src = imread("./image/1.jpg");
	imshow("src", src);

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);  // ��˹�˲���������
	cvtColor(src, src_gray, COLOR_RGB2GRAY);  // RGBת�Ҷ�ͼ
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);  // ʹ��Laplace����
	convertScaleAbs(dst, abs_dst);  // �������ֵ���������ת����8λ

	imshow("Laplace", abs_dst);
	waitKey(0);

}
