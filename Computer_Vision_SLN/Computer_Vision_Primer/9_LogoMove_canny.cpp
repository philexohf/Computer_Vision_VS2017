#include <opencv2/opencv.hpp>

#define ALPHA (width - logoImage.cols)       //LOGO在宽度上的移动上限
#define BETA (height - logoImage.rows)       //LOGO在高度上的移动上限
#define TIMER 0                              //延时帧率上限

using namespace cv;

int main()
{
	Mat srcImage, grayImage;
	VideoCapture camera(0);
	if (!camera.isOpened()){
		printf("**********************\n");
		printf("***摄像头打开失败！***\n");
		printf("**********************\n");
		system("color 4F");
		system("pause");
		return -1;
	}
	system("color F4");

	const int width = camera.get(CAP_PROP_FRAME_WIDTH);
	const int height = camera.get(CAP_PROP_FRAME_HEIGHT);
//	VideoWriter video("视频.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(width, height));  //录制视频.
	Mat logoImage = imread("./image/logo.png");
	Mat logoMask = imread("./image/logo.png", 0);
	Mat dstImage(width, height, CV_8UC3);
	printf("摄像头的分辨率为：%dx%d\n", width, height);
	printf("图标的尺寸为：%dx%d\n", logoImage.cols, logoImage.rows);
	int t = 0, i = 0, j = 0;                                      //(i,j)表示LOGO的位置,t表示LOGO移位延时的帧数.
	//while内部的if条件可以不要.
	while (camera.isOpened()){
		//LOGO由（0,0）点移动到（ALPHA,0）点.
//		if ((i == 0) && (j == 0)){
			for (i = 0; i != ALPHA;++i)
			for (t = 0; t <= TIMER; ++t){
				printf("i=%d,j=%d\n", i, j);
				camera >> srcImage;
				cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
				GaussianBlur(grayImage, grayImage, Size(7, 7), 1.5, 1.5);
				Canny(grayImage, grayImage, 10, 30, 3);
				cvtColor(grayImage, dstImage, COLOR_GRAY2BGR);
				Mat ImageROI = dstImage(Rect(i, 0, logoImage.cols, logoImage.rows));
				logoImage.copyTo(ImageROI, logoMask);
				imshow("摄像头", dstImage);
//				video << dstImage;         //录制视频.
				waitKey(40);
			}
//		}
		//LOGO由（ALPHA,0）点移动到（ALPHA,BETA）点.
//		if ((i == ALPHA) && (j == 0)){
			for (j = 0; j != BETA; ++j)
			for (t = 0; t <= TIMER; ++t){
				printf("i=%d,j=%d\n", i, j);
				camera >> srcImage;
				cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
				GaussianBlur(grayImage, grayImage, Size(7, 7), 1.5, 1.5);
				Canny(grayImage, grayImage, 10, 30, 3);
				cvtColor(grayImage, dstImage, COLOR_GRAY2BGR);
				Mat ImageROI = dstImage(Rect(ALPHA, j, logoImage.cols, logoImage.rows));
				logoImage.copyTo(ImageROI, logoMask);
				imshow("摄像头", dstImage);
//				video << dstImage;           //录制视频.
				waitKey(40);
			}
//		}
		//LOGO由（ALPHA,BETA）点移动到（0,BETA）点.
//		if ((i == ALPHA) && (j == BETA)){
			for (; i >0; --i)
			for (t = 0; t <= TIMER; ++t){
				printf("i=%d,j=%d\n", i, j);
				camera >> srcImage;
				cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
				GaussianBlur(grayImage, grayImage, Size(7, 7), 1.5, 1.5);
				Canny(grayImage, grayImage, 10, 30, 3);
				cvtColor(grayImage, dstImage, COLOR_GRAY2BGR);
				Mat ImageROI = dstImage(Rect(i, BETA, logoImage.cols, logoImage.rows));
				logoImage.copyTo(ImageROI, logoMask);
				imshow("摄像头", dstImage);
//				video << dstImage;           //录制视频.
				waitKey(40);
			}
//		}
		//LOGO由（0,BETA）点移动到（0,0）点.
//		if ((i == 0) && (j == BETA)){
			for (; j >0; --j)
			for (t = 0; t <= TIMER; ++t){
				printf("i=%d,j=%d\n", i, j);
				camera >> srcImage;
				cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
				GaussianBlur(grayImage, grayImage, Size(7, 7), 1.5, 1.5);
				Canny(grayImage, grayImage, 10, 30, 3);
				cvtColor(grayImage, dstImage, COLOR_GRAY2BGR);
				Mat ImageROI = dstImage(Rect(0, j, logoImage.cols, logoImage.rows));
				logoImage.copyTo(ImageROI, logoMask);
				imshow("摄像头", dstImage);
//				video << dstImage;           //录制视频.
				waitKey(40);
			}
//		}
	}

	return 0;
}