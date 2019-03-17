#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

static void ContrastAndBright(int, void *);

int g_nContrastValue; //�Աȶ�ֵ
int g_nBrightValue;  //����ֵ
Mat g_srcImage, g_dstImage;

int main()
{
	g_srcImage = imread("./image/test.jpg");
	if (!g_srcImage.data){ 
		printf("��ȡͼƬ����.\n"); 
		return false; 
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	//�趨�ԱȶȺ����ȵĳ�ֵ
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//�����켣��
	createTrackbar("�Աȶȣ�", "��Ч��ͼ���ڡ�", &g_nContrastValue, 300, ContrastAndBright);
	createTrackbar("��   �ȣ�", "��Ч��ͼ���ڡ�", &g_nBrightValue, 200, ContrastAndBright);

	//���ûص�����
	ContrastAndBright(g_nContrastValue, 0);
	ContrastAndBright(g_nBrightValue, 0);

	//���һЩ������Ϣ
	cout << endl << "\t���гɹ���������������۲�ͼ��Ч��\n\n"
		<< "\t���¡�q����ʱ�������˳�\n";

	//���¡�q����ʱ�������˳�
	while (char(waitKey(1)) != 'q') {}

}

static void ContrastAndBright(int, void *)  // �ı�ͼ��ԱȶȺ�����ֵ�Ļص�����
{
	// ����forѭ����ִ������ g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
			}
		}
	}

	imshow("src", g_srcImage);
	imshow("dst", g_dstImage);
}

