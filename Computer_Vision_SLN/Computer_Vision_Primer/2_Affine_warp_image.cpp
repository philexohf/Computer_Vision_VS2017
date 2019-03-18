#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "src"					
#define WINDOW_NAME2 "Warp"       
#define WINDOW_NAME3 "Warp+Rotate" 

int main()
{
	//��1������׼��
	//��������㣬��������������
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//����һЩMat����
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	//��2������Դͼ����һЩ��ʼ��
	srcImage = imread("./image/1.jpg", 1);
	if (!srcImage.data) { printf("��ȡͼƬ����.\n"); return false; }
	// ����Ŀ��ͼ��Ĵ�С��������Դͼ��һ��
	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	//��3������Դͼ���Ŀ��ͼ���ϵ�������Լ������任
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));

	//��4����÷���任
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	//��5����Դͼ��Ӧ�øո���õķ���任
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

	//��6����ͼ��������ź�����ת
	// ������ͼ���е�˳ʱ����ת50����������Ϊ0.6����ת����
	Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	// ͨ���������תϸ����Ϣ�����ת����
	rotMat = getRotationMatrix2D(center, angle, scale);
	// ��ת�����ź��ͼ��
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, dstImage_warp);
	imshow(WINDOW_NAME3, dstImage_warp_rotate);

	waitKey(0);

}
