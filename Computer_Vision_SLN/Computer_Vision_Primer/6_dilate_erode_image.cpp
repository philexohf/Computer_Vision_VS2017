#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage;//ԭʼͼ��Ч��ͼ
int g_nTrackbarNumer = 0;//0��ʾ��ʴerode, 1��ʾ����dilate
int g_nStructElementSize = 3; //�ṹԪ��(�ں˾���)�ĳߴ�

void Process();//���ͺ͸�ʴ�Ĵ�����
void on_TrackbarNumChange(int, void *);//�ص�����
void on_ElementSizeChange(int, void *);//�ص�����

int main()
{
	g_srcImage = imread("./image/test.jpg");
	if (!g_srcImage.data) { printf("��ȡsrcImage����~�� \n"); return false; }

	imshow("src", g_srcImage);

	//���г��θ�ʴ��������ʾЧ��ͼ
	namedWindow("dst");
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));
	erode(g_srcImage, g_dstImage, element);
	imshow("dst", g_dstImage);

	//�����켣��
	createTrackbar("��ʴ/����", "dst", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�", "dst", &g_nStructElementSize, 21, on_ElementSizeChange);

	//���һЩ������Ϣ
	cout << endl << "\t���гɹ���������������۲�ͼ��Ч��~\n\n"
		<< "\t���¡�q����ʱ�������˳���\n";

	//��ѯ��ȡ������Ϣ������q���������˳�
	while (char(waitKey(1)) != 'q') {}

	return 0;
}

void Process()  // ��ʴ�����Ͳ���
{
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));

	//���и�ʴ�����Ͳ���
	if (g_nTrackbarNumer == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("dst", g_dstImage);
}

void on_TrackbarNumChange(int, void *)  // ��ʴ������֮���л����صĻص�����
{
	//��ʴ������֮��Ч���Ѿ��л����ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}

void on_ElementSizeChange(int, void *)  // ��ʴ�����Ͳ����ں˸ı�ʱ�Ļص�����
{
	//�ں˳ߴ��Ѹı䣬�ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}
