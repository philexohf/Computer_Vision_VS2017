#include <opencv2\opencv.hpp> 
#include "cv.h"
#include <cxcore.h>
#include "highgui.h"
#include <math.h>
using namespace cv;
using namespace std;

//������ͨ������Сֵ����Сֵʱ���õĺ���
double min(double b, double g, double r)
{
	double result = b;
	if (result>g)
		result = g;
	if (result>r)
		result = r;
	return result;
};
double max(double a, double b)
{
	double MAX;
	if (a<b)
		MAX = b;
	else
		MAX = a;
	return MAX;
};
double min2(double a, double b)//�Ƚ�������ֵ�е���Сֵ������
{
	double MIN;
	if (a<b)
		MIN = a;
	else
		MIN = b;
	return MIN;
};
//��������൱��darkchannel�Ĺ��ܣ�����padarrayʱ��ʹ�õ��ǽ���Ե���ظ��Ƶķ���������matlab�Ľ���Ե��������,�����darkchannel���м��������ֵA
double doDarkChannel(IplImage* in, int patchsize)
{

	int height, width, step, channels;//ͼ��Ŀ��ߣ�����Ϣ��height��width������ͼ��ĳߴ磬Ҳ�����ͼ��ĳߴ磬step�����ͼ��jout�ģ�j��Ӧmatlab�����е�darkchannel�����ͼ��J��
	int i, j, k;//����ѭ���ı���
	uchar *data2;//����Ľ��ͼ���ָ��
	height = in->height;//��ȡ����ͼ��Ŀ�ߵ���Ϣ
	width = in->width;
	int patch = patchsize / 2;//ͼ��Ҫ���صı�Ե�Ŀ��
	IplImage* mout = cvCreateImage(cvSize(in->width + patchsize, in->height + patchsize), in->depth, in->nChannels);   //���ͼ�񱻾������غ�ͼ��Ŀ�ͼ��
	cvCopyMakeBorder(in, mout, cvPoint(patch, patch), IPL_BORDER_REPLICATE);//��������൱��padarray��mout�д��padarrry���ͼ��
	IplImage* jout = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);//darkchannel ����������J

	step = jout->widthStep / sizeof(uchar);//step�ǵ�ͨ�����ͼ��jout��widthstep
	data2 = (uchar *)jout->imageData;//ָ�����ͼ�������ͷ

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			cvSetImageROI(mout, cvRect(j, i, patchsize, patchsize));//��������ͼ��ģ�i��j���㴦patchsize��С��ͼ���
			IplImage*  patch_out = cvCreateImage(cvSize(patchsize, patchsize), in->depth, in->nChannels);//�洢��ͨ��ͼ������ʱ�ڴ�����ѭ�������õ����ڴ�������ѭ���������룬��ѭ�������ͷ�
			cvCopy(mout, patch_out);//��patchsize��С��ͼ��������ʱͼ���patch_out
			cvResetImageROI(mout); //�ͷ�mout

			//��������������cnMinMaxloc�ֱ��������ͨ���е���Сֵ
			double MinValue;
			double MaxValue;
			double B_Min, G_Min, R_Min;
			CvPoint MinLocation;
			CvPoint MaxLocation;
			cvSetImageCOI(patch_out, 1);
			cvMinMaxLoc(patch_out, &MinValue, &MaxValue, &MinLocation, &MaxLocation);
			B_Min = MinValue;
			cvSetImageCOI(patch_out, 2);
			cvMinMaxLoc(patch_out, &MinValue, &MaxValue, &MinLocation, &MaxLocation);
			G_Min = MinValue;
			cvSetImageCOI(patch_out, 3);
			cvMinMaxLoc(patch_out, &MinValue, &MaxValue, &MinLocation, &MaxLocation);
			R_Min = MinValue;
			int dark_point = (int)min(B_Min, G_Min, R_Min);
			//����ͨ������Сֵ���Ѿ����ֱ���ȡ������
			data2[i*step + j] = dark_point;//step ��jout��step���ǵ�ͨ����
			cvReleaseImage(&patch_out);
		};
	};
	double MinValue;
	double MaxValue;
	double B_Min, G_Min, R_Min;
	CvPoint MinLocation;
	CvPoint MaxLocation;
	cvSetImageCOI(jout, 1);
	cvMinMaxLoc(jout, &MinValue, &MaxValue, &MinLocation, &MaxLocation);
	cvReleaseImage(&mout);
	cout << "���㰵ͨ���������гɹ�" << "\n";
	return MaxValue;

};
//�ú����������൱��matlab��������ȡ����ͨ������Сֵ��Ȼ������Сֵ���һ���Ҷ�ͼ
IplImage* doMinChannel(IplImage* in)
{
	IplImage* b = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* g = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* r = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);//�����������ͼ������ͨ���ĵ��ڴ�����
	IplImage* w = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);//�����������ͼ����ڴ���������ͨ������Сֵ��ɵ�һ���Ҷ�ͼ��
	cvSetImageCOI(in, 1);
	cvCopy(in, b);
	cvSetImageCOI(in, 2);
	cvCopy(in, g);
	cvSetImageCOI(in, 3);
	cvCopy(in, r);//������ͨ���ĵ�ֵ�ֱ����r��g��b�����ڴ�������

	//cvSplit(src,dst1,dst2,dst3,NULL);

	int height = in->height;//��ȡ����ͼ��Ŀ�ߵ���Ϣ
	int width = in->width;
	int i, j, k;//����ѭ���ı���
	uchar *data_w;
	uchar *data_b;
	uchar *data_g;
	uchar *data_r;
	int step = b->widthStep / sizeof(uchar);
	data_w = (uchar *)w->imageData;//ָ�����ͼ�������ͷ
	data_b = (uchar *)b->imageData;//ָ�����ͼ�������ͷ
	data_g = (uchar *)g->imageData;//ָ�����ͼ�������ͷ
	data_r = (uchar *)r->imageData;//ָ�����ͼ�������ͷ
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			double b, g, r;
			int MIN;//b,g,r����ͨ������Сֵ
			b = data_b[i*step + j];
			g = data_g[i*step + j];
			r = data_r[i*step + j];
			MIN = (int)min(b, g, r);
			data_w[i*step + j] = MIN;
		};
	};
	cout << "��������ͨ����Сֵ�����һ���»Ҷ�ͼ�ĺ������гɹ�" << "\n";//��ʾ�ú������гɹ�
	return w;
};
IplImage* doCalculateV(IplImage* w, IplImage* diff, IplImage* smooth)
{
	IplImage* b = cvCreateImage(cvSize(w->width, w->height), w->depth, 1);
	IplImage* v = cvCreateImage(cvSize(w->width, w->height), w->depth, 1);
	int height = w->height;//��ȡ����ͼ��Ŀ�ߵ���Ϣ
	int width = w->width;
	int i, j, k;//����ѭ���ı���
	uchar *data_w;
	uchar *data_diff;
	uchar *data_v;
	uchar *data_b;
	uchar *data_smooth;
	int step = w->widthStep / sizeof(uchar);
	data_w = (uchar *)w->imageData;//ָ�����ͼ�������ͷ
	data_diff = (uchar *)diff->imageData;//ָ�����ͼ�������ͷ
	data_v = (uchar *)v->imageData;//ָ�����ͼ�������ͷ
	data_b = (uchar *)b->imageData;//ָ�����ͼ�������ͷ
	data_smooth = (uchar *)smooth->imageData;
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			double W;
			double DIFF;
			double B;
			double SMOOTH;
			double p = 0.78;//p = 0.78
			double MIN, MAX;
			W = data_w[i*step + j];
			DIFF = data_diff[i*step + j];
			SMOOTH = data_smooth[i*step + j];
			B = W - DIFF;
			MIN = min2(B, SMOOTH);
			MAX = max(MIN, 0);
			data_v[i*step + j] = p*MAX;
		};
	};
	cout << "����v�������гɹ�" << "\n";//��ʾ�ú������гɹ�
	return v;
};
//�������յ�ȥ��ͼ��ĺ���
IplImage* doFinally(IplImage* in, IplImage* v, double A)
{
	IplImage* b = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* g = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* r = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* result = cvCreateImage(cvSize(in->width, in->height), in->depth, 3);//�����洢���ͼ����ڴ�����
	int height = in->height;//��ȡ����ͼ��Ŀ�ߵ���Ϣ
	int width = in->width;
	int i, j;//����ѭ���ı���
	cvSetImageCOI(in, 1);
	cvCopy(in, b);
	cvSetImageCOI(in, 2);
	cvCopy(in, g);
	cvSetImageCOI(in, 3);
	cvCopy(in, r);//������ͨ���ĵ�ֵ�ֱ����r��g��b�����ڴ�������
	//cvSplit(in,b,g,r,NULL);//��ͼ����Ϊ����ͨ��
	uchar *data_b;
	uchar *data_g;
	uchar *data_r;
	uchar *data_v;
	int step = b->widthStep / sizeof(uchar);
	//data_w = (uchar *)w->imageData;//ָ�����ͼ�������ͷ
	data_b = (uchar *)b->imageData;//ָ����ɫͨ��������ͷ
	data_g = (uchar *)g->imageData;//ָ����ɫͨ��������ͷ
	data_r = (uchar *)r->imageData;//ָ���ɫͨ��������ͷ
	data_v = (uchar *)v->imageData;
	//������ɫͨ����ȥ����
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			double B, G, R, V, VAB, VAG, VAR;
			V = data_v[i*step + j];
			B = data_b[i*step + j];
			VAB = fabs(B - V) / (fabs(1 - V / A));   //����һЩֵ����256����Ҫ���й�һ��
			if (VAB>255)
				VAB = 255;
			else
				VAB = VAB;
			data_b[i*step + j] = VAB;
			G = data_g[i*step + j];
			VAG = fabs(G - V) / (fabs(1 - V / A));
			if (VAG>255)
				VAG = 255;
			else
				VAG = VAG;
			data_g[i*step + j] = VAG;
			R = data_r[i*step + j];
			VAR = fabs(R - V) / (fabs(1 - V / A));
			if (VAR>255)
				VAR = 255;
			else
				VAR = VAR;
			data_r[i*step + j] = VAR;
		};
	};
	cvMerge(b, g, r, NULL, result);//�����������Ҳ������~
	cout << "����ȥ���㷨���гɹ�" << "\n";//��ʾ�ú������гɹ�
	return result;

}

int main(int argc, char** argv)
{
	cvNamedWindow("Source Image");
	cvNamedWindow("Result Image");
	IplImage* image = cvLoadImage("dcpImage.jpg", 1);  //input a image��0��ʾ�ԻҶ�ͼ��ʽ����ͼ��-1��ʾ��ͼ��������ʵͨ��������ͼ��1��ʾ����ͨ������ͼ��
	//�˴��ɸĳ��Լ���ͼƬ·��
	cvShowImage("Source Image", image);//��ʾԴͼ��
	int patchsize = 20;
	//IplImage* out = doDarkChannel(image,patchsize);//����ֱ�ӽ����ص�ͼ�����ݸ���һ��δָ����С��ָ�룬
	IplImage* out = cvCreateImage(cvSize(image->width, image->height), image->depth, 3);//�����洢���ͼ����ڴ�����
	IplImage* w = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//�����洢���ͼ����ڴ�����
	//cvCopy(doDarkChannel(image,patchsize),out);//��patchsize��С��ͼ��������ʱͼ���patch_out
	IplImage* smooth = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//�����洢���ͼ����ڴ�����
	IplImage* diff = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//�洢w��I_smooth��ֵ����ֵ�ĵ��ڴ�����
	IplImage* v = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//�洢w��I_smooth��ֵ����ֵ�ĵ��ڴ�����
	int A_MAX = doDarkChannel(image, patchsize);//��ȡ��ͨ�������ֵ��A_MAX�൱��Matlab�е�A������doFinally
	cvCopy(doMinChannel(image), w);//��������ͨ������Сֵ������Сֵ���һ���Ҷ�ͼ��������һ����˹ƽ��
	//w����û����

	cvSaveImage("w.bmp", w);

	cvSmooth(w, smooth, CV_GAUSSIAN, 39, 39, 4.5, 4.5);//39x39;��ʹ����ض�ʹ�þ�����м��㣬���߽�㸴�Ƶõ���չ�߽�

	cvSaveImage("smooth.bmp", smooth);

	cvAbsDiff(smooth, w, diff);
	//diff�����⣬Ӧ��������smooth���µ�
	cvSaveImage("diff.bmp", diff);

	cvCopy(doCalculateV(w, diff, smooth), v);//����v��v�ĺ����matlab�����п��ҵ���v����doFinally�������յĽ������
	//v�����⣻����smooth�����⣬wû���⣬diff�����⣬����v������
	cvSaveImage("v.bmp", v);
	cvCopy(doFinally(image, v, A_MAX), out);//�������յ�ȥ�����ĺ����ĵ���
	//cvSaveImage("D://v.bmp",v);//�����ܷ�˳������ͼ��v�Ĵ���
	cout << "A_MAX=" << A_MAX << "\n";

	cvSaveImage("finally.bmp", out);

	cvShowImage("Result Image", out);//imshow the result
	cvWaitKey(0);
	cvReleaseImage(&image);//release the storage space
	cvReleaseImage(&out);//release the storage space
	cvReleaseImage(&w);//release the storage space
	cvReleaseImage(&smooth);//release the storage space
	cvReleaseImage(&diff);//release the storage space
	cvReleaseImage(&v);//release the storage space
	cvDestroyWindow("Source Image");
	cvDestroyWindow("Result Image");
	//system("pause"); //����һ������
	return 0;
}