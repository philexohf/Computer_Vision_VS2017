#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi�ǵ���"        //Ϊ���ڱ��ⶨ��ĺ� 

Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);//��ʼ�������������

void on_GoodFeaturesToTrack(int, void*)  // ��Ӧ�������ƶ���Ϣ�Ļص�����
{
	//�Ա���С�ڵ���1ʱ�Ĵ���
	if (g_maxCornerNumber <= 1) { g_maxCornerNumber = 1; }

	//Shi-Tomasi�㷨
	vector<Point2f> corners;
	double qualityLevel = 0.01;//�ǵ���ɽ��ܵ���С����ֵ
	double minDistance = 10;//�ǵ�֮�����С����
	int blockSize = 3;//���㵼������ؾ���ʱָ��������Χ
	double k = 0.04;//Ȩ��ϵ��
	Mat copy = g_srcImage.clone();	//����Դͼ��һ����ʱ�����У���Ϊ����Ȥ����

	//����Shi-Tomasi�ǵ���
	goodFeaturesToTrack(g_grayImage,//����ͼ��
		corners,//��⵽�Ľǵ���������
		g_maxCornerNumber,//�ǵ���������
		qualityLevel,//�ǵ���ɽ��ܵ���С����ֵ
		minDistance,//�ǵ�֮�����С����
		Mat(),//����Ȥ����
		blockSize,//���㵼������ؾ���ʱָ��������Χ
		false,//��ʹ��Harris�ǵ���
		k);//Ȩ��ϵ��


	//���������Ϣ
	cout << "\t>�˴μ�⵽�Ľǵ�����Ϊ��" << corners.size() << endl;

	//���Ƽ�⵽�Ľǵ�
	int r = 4;
	for (int i = 0; i < corners.size(); i++)
	{
		//���������ɫ���Ƴ��ǵ�
		circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255),
			g_rng.uniform(0, 255)), -1, 8, 0);
	}

	//��ʾ���´���
	imshow(WINDOW_NAME, copy);
}

int main()
{
	g_srcImage = imread("./image/1.jpg", 1);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

	//�������ںͻ���������������ʾ�ͻص�������ʼ��
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("���ǵ���", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack);
	imshow(WINDOW_NAME, g_srcImage);
	on_GoodFeaturesToTrack(0, 0);

	waitKey(0);
}
