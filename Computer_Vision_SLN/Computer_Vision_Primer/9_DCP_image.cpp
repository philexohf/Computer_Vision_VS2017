#include <opencv2\opencv.hpp> 
#include "cv.h"
#include <cxcore.h>
#include "highgui.h"
#include <math.h>
using namespace cv;
using namespace std;

//求三个通道中最小值的最小值时调用的函数
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
double min2(double a, double b)//比较两个数值中的最小值并返回
{
	double MIN;
	if (a<b)
		MIN = a;
	else
		MIN = b;
	return MIN;
};
//这个函数相当于darkchannel的功能，但在padarray时。使用的是将边缘像素复制的方法，不是matlab的将边缘处镜像复制,计算出darkchannel后有计算了最大值A
double doDarkChannel(IplImage* in, int patchsize)
{

	int height, width, step, channels;//图像的宽，高，等信息，height，width是输入图像的尺寸，也是输出图像的尺寸，step是输出图像jout的（j对应matlab代码中的darkchannel的输出图像J）
	int i, j, k;//用于循环的变量
	uchar *data2;//输出的结果图像的指针
	height = in->height;//获取输入图像的宽高等信息
	width = in->width;
	int patch = patchsize / 2;//图像要延拓的边缘的宽度
	IplImage* mout = cvCreateImage(cvSize(in->width + patchsize, in->height + patchsize), in->depth, in->nChannels);   //存放图像被镜像延拓后图像的空图像
	cvCopyMakeBorder(in, mout, cvPoint(patch, patch), IPL_BORDER_REPLICATE);//这个函数相当于padarray，mout中存放padarrry后的图像
	IplImage* jout = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);//darkchannel 的输出结果，J

	step = jout->widthStep / sizeof(uchar);//step是单通道输出图像jout的widthstep
	data2 = (uchar *)jout->imageData;//指向输出图像的数据头

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			cvSetImageROI(mout, cvRect(j, i, patchsize, patchsize));//操作输入图像的（i，j）点处patchsize大小的图像块
			IplImage*  patch_out = cvCreateImage(cvSize(patchsize, patchsize), in->depth, in->nChannels);//存储三通道图像块的临时内存区，循环体里用到的内存区域再循环体里申请，在循环体里释放
			cvCopy(mout, patch_out);//将patchsize大小的图像块存入临时图像块patch_out
			cvResetImageROI(mout); //释放mout

			//以下内容是利用cnMinMaxloc分别计算三个通道中的最小值
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
			//三个通道的最小值都已经被分别提取出来了
			data2[i*step + j] = dark_point;//step 是jout的step，是单通道的
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
	cout << "计算暗通道函数运行成功" << "\n";
	return MaxValue;

};
//该函数的作用相当于matlab代码中求取三个通道中最小值，然后以最小值组成一幅灰度图
IplImage* doMinChannel(IplImage* in)
{
	IplImage* b = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* g = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* r = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);//创建保存读入图像三个通道的的内存区域
	IplImage* w = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);//创建保存输出图像的内存区域（三个通道中最小值组成的一幅灰度图）
	cvSetImageCOI(in, 1);
	cvCopy(in, b);
	cvSetImageCOI(in, 2);
	cvCopy(in, g);
	cvSetImageCOI(in, 3);
	cvCopy(in, r);//将三个通道的的值分别存入r，g，b三块内存区域中

	//cvSplit(src,dst1,dst2,dst3,NULL);

	int height = in->height;//获取输入图像的宽高等信息
	int width = in->width;
	int i, j, k;//用于循环的变量
	uchar *data_w;
	uchar *data_b;
	uchar *data_g;
	uchar *data_r;
	int step = b->widthStep / sizeof(uchar);
	data_w = (uchar *)w->imageData;//指向输出图像的数据头
	data_b = (uchar *)b->imageData;//指向输出图像的数据头
	data_g = (uchar *)g->imageData;//指向输出图像的数据头
	data_r = (uchar *)r->imageData;//指向输出图像的数据头
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			double b, g, r;
			int MIN;//b,g,r三个通道的最小值
			b = data_b[i*step + j];
			g = data_g[i*step + j];
			r = data_r[i*step + j];
			MIN = (int)min(b, g, r);
			data_w[i*step + j] = MIN;
		};
	};
	cout << "计算三个通道最小值并组成一幅新灰度图的函数运行成功" << "\n";//表示该函数运行成功
	return w;
};
IplImage* doCalculateV(IplImage* w, IplImage* diff, IplImage* smooth)
{
	IplImage* b = cvCreateImage(cvSize(w->width, w->height), w->depth, 1);
	IplImage* v = cvCreateImage(cvSize(w->width, w->height), w->depth, 1);
	int height = w->height;//获取输入图像的宽高等信息
	int width = w->width;
	int i, j, k;//用于循环的变量
	uchar *data_w;
	uchar *data_diff;
	uchar *data_v;
	uchar *data_b;
	uchar *data_smooth;
	int step = w->widthStep / sizeof(uchar);
	data_w = (uchar *)w->imageData;//指向输出图像的数据头
	data_diff = (uchar *)diff->imageData;//指向输出图像的数据头
	data_v = (uchar *)v->imageData;//指向输出图像的数据头
	data_b = (uchar *)b->imageData;//指向输出图像的数据头
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
	cout << "计算v函数运行成功" << "\n";//表示该函数运行成功
	return v;
};
//计算最终的去雾图像的函数
IplImage* doFinally(IplImage* in, IplImage* v, double A)
{
	IplImage* b = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* g = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* r = cvCreateImage(cvSize(in->width, in->height), in->depth, 1);
	IplImage* result = cvCreateImage(cvSize(in->width, in->height), in->depth, 3);//创建存储输出图像的内存区域
	int height = in->height;//获取输入图像的宽高等信息
	int width = in->width;
	int i, j;//用于循环的变量
	cvSetImageCOI(in, 1);
	cvCopy(in, b);
	cvSetImageCOI(in, 2);
	cvCopy(in, g);
	cvSetImageCOI(in, 3);
	cvCopy(in, r);//将三个通道的的值分别存入r，g，b三块内存区域中
	//cvSplit(in,b,g,r,NULL);//将图像拆分为三个通道
	uchar *data_b;
	uchar *data_g;
	uchar *data_r;
	uchar *data_v;
	int step = b->widthStep / sizeof(uchar);
	//data_w = (uchar *)w->imageData;//指向输出图像的数据头
	data_b = (uchar *)b->imageData;//指向蓝色通道的数据头
	data_g = (uchar *)g->imageData;//指向绿色通道的数据头
	data_r = (uchar *)r->imageData;//指向红色通道的数据头
	data_v = (uchar *)v->imageData;
	//计算蓝色通道的去雾结果
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			double B, G, R, V, VAB, VAG, VAR;
			V = data_v[i*step + j];
			B = data_b[i*step + j];
			VAB = fabs(B - V) / (fabs(1 - V / A));   //会有一些值大于256，需要进行归一化
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
	cvMerge(b, g, r, NULL, result);//这个函数可能也有问题~
	cout << "最终去雾算法运行成功" << "\n";//表示该函数运行成功
	return result;

}

int main(int argc, char** argv)
{
	cvNamedWindow("Source Image");
	cvNamedWindow("Result Image");
	IplImage* image = cvLoadImage("dcpImage.jpg", 1);  //input a image，0表示以灰度图形式读入图像，-1表示以图像自身真实通道数读入图像，1表示以三通道读入图像
	//此处可改成自己的图片路径
	cvShowImage("Source Image", image);//显示源图像
	int patchsize = 20;
	//IplImage* out = doDarkChannel(image,patchsize);//不能直接将返回的图像数据赋给一个未指定大小的指针，
	IplImage* out = cvCreateImage(cvSize(image->width, image->height), image->depth, 3);//创建存储输出图像的内存区域
	IplImage* w = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//创建存储输出图像的内存区域
	//cvCopy(doDarkChannel(image,patchsize),out);//将patchsize大小的图像块存入临时图像块patch_out
	IplImage* smooth = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//创建存储输出图像的内存区域
	IplImage* diff = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//存储w与I_smooth差值绝对值的的内存区域
	IplImage* v = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);//存储w与I_smooth差值绝对值的的内存区域
	int A_MAX = doDarkChannel(image, patchsize);//求取暗通道的最大值，A_MAX相当于Matlab中的A，传入doFinally
	cvCopy(doMinChannel(image), w);//计算三个通道的最小值并以最小值组成一副灰度图，进行下一步高斯平滑
	//w计算没问题

	cvSaveImage("w.bmp", w);

	cvSmooth(w, smooth, CV_GAUSSIAN, 39, 39, 4.5, 4.5);//39x39;不使用相关而使用卷积进行计算，将边界点复制得到拓展边界

	cvSaveImage("smooth.bmp", smooth);

	cvAbsDiff(smooth, w, diff);
	//diff有问题，应该是由于smooth导致的
	cvSaveImage("diff.bmp", diff);

	cvCopy(doCalculateV(w, diff, smooth), v);//计算v，v的含义从matlab代码中可找到，v传入doFinally进行最终的结果计算
	//v有问题；由于smooth有问题，w没问题，diff有问题，导致v有问题
	cvSaveImage("v.bmp", v);
	cvCopy(doFinally(image, v, A_MAX), out);//计算最终的去雾结果的函数的调用
	//cvSaveImage("D://v.bmp",v);//测试能否顺利产生图像v的代码
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
	//system("pause"); //避免一闪而过
	return 0;
}