#include <opencv2/opencv.hpp>

#define ALPHA (width - logoImage.cols)       //LOGO�ڿ���ϵ��ƶ�����
#define BETA (height - logoImage.rows)       //LOGO�ڸ߶��ϵ��ƶ�����
#define TIMER 0                              //��ʱ֡������

using namespace cv;

int main()
{
	Mat srcImage, grayImage;
	VideoCapture camera(0);
	if (!camera.isOpened()){
		printf("**********************\n");
		printf("***����ͷ��ʧ�ܣ�***\n");
		printf("**********************\n");
		system("color 4F");
		system("pause");
		return -1;
	}
	system("color F4");

	const int width = camera.get(CAP_PROP_FRAME_WIDTH);
	const int height = camera.get(CAP_PROP_FRAME_HEIGHT);
//	VideoWriter video("��Ƶ.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(width, height));  //¼����Ƶ.
	Mat logoImage = imread("./image/logo.png");
	Mat logoMask = imread("./image/logo.png", 0);
	Mat dstImage(width, height, CV_8UC3);
	printf("����ͷ�ķֱ���Ϊ��%dx%d\n", width, height);
	printf("ͼ��ĳߴ�Ϊ��%dx%d\n", logoImage.cols, logoImage.rows);
	int t = 0, i = 0, j = 0;                                      //(i,j)��ʾLOGO��λ��,t��ʾLOGO��λ��ʱ��֡��.
	//while�ڲ���if�������Բ�Ҫ.
	while (camera.isOpened()){
		//LOGO�ɣ�0,0�����ƶ�����ALPHA,0����.
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
				imshow("����ͷ", dstImage);
//				video << dstImage;         //¼����Ƶ.
				waitKey(40);
			}
//		}
		//LOGO�ɣ�ALPHA,0�����ƶ�����ALPHA,BETA����.
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
				imshow("����ͷ", dstImage);
//				video << dstImage;           //¼����Ƶ.
				waitKey(40);
			}
//		}
		//LOGO�ɣ�ALPHA,BETA�����ƶ�����0,BETA����.
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
				imshow("����ͷ", dstImage);
//				video << dstImage;           //¼����Ƶ.
				waitKey(40);
			}
//		}
		//LOGO�ɣ�0,BETA�����ƶ�����0,0����.
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
				imshow("����ͷ", dstImage);
//				video << dstImage;           //¼����Ƶ.
				waitKey(40);
			}
//		}
	}

	return 0;
}