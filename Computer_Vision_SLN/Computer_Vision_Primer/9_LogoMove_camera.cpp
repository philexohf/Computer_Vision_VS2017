#include <opencv2/opencv.hpp>

#define ALPHA (width - logoImage.cols)       //LOGO在宽度上的移动上限
#define BETA  (height - logoImage.rows)       //LOGO在高度上的移动上限              

using namespace cv;

int main()
{	
	VideoCapture camera(0);
	Mat srcImage;

	if (!camera.isOpened()){
		printf("**********************\n");
		printf("***摄像头打开失败！***\n");
		printf("**********************\n");
		system("color 4F");
		system("pause");
		return -1;
	}
	system("color F4");

	const int width = camera.get(CAP_PROP_FRAME_WIDTH);           //获取的摄像头图像的宽度
	const int height = camera.get(CAP_PROP_FRAME_HEIGHT);         //获取的摄像头图像的高度
//	VideoWriter video("视频.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(width, height));  //录制视频.
	Mat logoImage = imread("./image/logo.png");
	Mat logoMask = imread("./image/logo.png", 0);
	printf("摄像头的分辨率为：%dx%d\n", width, height);
	printf("图标的尺寸为：%dx%d\n", logoImage.cols, logoImage.rows);
	int i = 0, j = 0;                                      //(i,j)表示LOGO的位置,t表示LOGO移位延时的帧数.

	while (camera.isOpened()){

		//LOGO由（0,0）点移动到（ALPHA,0）点.
		for (i = 0; i != ALPHA; ++i){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, 0, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("摄像头", srcImage);
//			video << srcImage;         //录制视频.
			waitKey(40);
		}

		//LOGO由（ALPHA,0）点移动到（ALPHA,BETA）点.
		for (j = 0; j != BETA; ++j){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(ALPHA, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("摄像头", srcImage);
//			video << srcImage;         //录制视频.
			waitKey(40);
		}
		//LOGO由（ALPHA,BETA）点移动到（0,BETA）点.
		for (; i >0; --i){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, BETA, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("摄像头", srcImage);
//			video << srcImage;         //录制视频.
			waitKey(40);
		}
		//LOGO由（0,BETA）点移动到（0,0）点.
		for (; j >0; --j){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(0, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("摄像头", srcImage);
//			video << srcImage;         //录制视频.
			waitKey(40);
		}
		//LOGO由（0,0）点移动到（ALPHA,BETA）点.
		for (i = 0; i != ALPHA; ++i){
			j = i*BETA / ALPHA*1.0;
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("摄像头", srcImage);
//			video << srcImage;         //录制视频.
			waitKey(40);
		}
		//LOGO由（ALPHA,BETA）点移动到（0,0）点.
		for (; i > 0; --i){
			j = i*BETA / ALPHA*1.0;
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("摄像头", srcImage);
//			video << srcImage;         //录制视频.
			waitKey(40);
		}
	}
	return 0;
}