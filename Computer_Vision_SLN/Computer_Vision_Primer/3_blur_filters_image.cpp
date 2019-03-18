#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6;  //方框滤波内核值
int g_nMeanBlurValue = 10;  //均值滤波内核值
int g_nGaussianBlurValue = 6;  //高斯滤波内核值
int g_nMedianBlurValue = 10;  //中值滤波参数值
int g_nBilateralFilterValue = 10;  //双边滤波参数值


//轨迹条回调函数
static void on_BoxFilter(int, void *);		//方框滤波
static void on_MeanBlur(int, void *);		//均值块滤波器
static void on_GaussianBlur(int, void *);			//高斯滤波器
static void on_MedianBlur(int, void *);			//中值滤波器
static void on_BilateralFilter(int, void *);			//双边滤波器

int main()
{
	g_srcImage = imread("./image/summer.png", 1);

	if (!g_srcImage.data){ 
		printf("读取图片错误.\n"); 
		return false; 
	}

	//克隆原图到四个Mat类型中
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	namedWindow("原图", 1);
	imshow("原图", g_srcImage);


	//=================方框滤波=========================
	namedWindow("方框滤波", 1);
	createTrackbar("内核值：", "方框滤波", &g_nBoxFilterValue, 50, on_BoxFilter);
	on_MeanBlur(g_nBoxFilterValue, 0);
	imshow("方框滤波", g_dstImage1);

	//=================均值滤波==========================
	namedWindow("均值滤波", 1);
	createTrackbar("内核值：", "均值滤波", &g_nMeanBlurValue, 50, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	//=================高斯滤波===========================
	namedWindow("高斯滤波", 1);
	createTrackbar("内核值：", "高斯滤波", &g_nGaussianBlurValue, 50, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	//=================中值滤波===========================
	namedWindow("中值滤波", 1);
	createTrackbar("参数值：", "中值滤波", &g_nMedianBlurValue, 50, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);

	//=================双边滤波===========================
	namedWindow("双边滤波", 1);
	createTrackbar("参数值：", "双边滤波", &g_nBilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);

	cout << endl << "\t调整滚动条可以改变滤波器尺寸；\n\n"
		<< "\t按“q”键退出程序。\n";
	while (char(waitKey(1)) != 'q') {}

	return 0;
}

static void on_BoxFilter(int, void *)  // 方框滤波回调函数
{
	//方框滤波操作
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	//显示窗口
	imshow("方框滤波", g_dstImage1);
}

static void on_MeanBlur(int, void *)  // 均值滤波回调函数
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("均值滤波", g_dstImage2);

}

static void on_GaussianBlur(int, void *)  // 高斯滤波回调函数
{
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
	imshow("高斯滤波", g_dstImage3);
}

static void on_MedianBlur(int, void *)  // 中值滤波回调函数
{
	medianBlur(g_srcImage, g_dstImage4, g_nMedianBlurValue * 2 + 1);
	imshow("中值滤波", g_dstImage4);
}

static void on_BilateralFilter(int, void *)  // 双边滤波回调函数
{
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue * 2, g_nBilateralFilterValue / 2);
	imshow("双边滤波", g_dstImage5);
}
