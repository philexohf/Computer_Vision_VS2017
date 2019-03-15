#include <opencv2/opencv.hpp>

#define ALPHA (width - logoImage.cols)       //LOGO�ڿ���ϵ��ƶ�����
#define BETA  (height - logoImage.rows)       //LOGO�ڸ߶��ϵ��ƶ�����              

using namespace cv;

int main()
{	
	VideoCapture camera(0);
	Mat srcImage;

	if (!camera.isOpened()){
		printf("**********************\n");
		printf("***����ͷ��ʧ�ܣ�***\n");
		printf("**********************\n");
		system("color 4F");
		system("pause");
		return -1;
	}
	system("color F4");

	const int width = camera.get(CAP_PROP_FRAME_WIDTH);           //��ȡ������ͷͼ��Ŀ��
	const int height = camera.get(CAP_PROP_FRAME_HEIGHT);         //��ȡ������ͷͼ��ĸ߶�
	VideoWriter video("��Ƶ.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(width, height));  //¼����Ƶ.
	Mat logoImage = imread("logo.png");
	Mat logoMask = imread("logo.png", 0);
	printf("����ͷ�ķֱ���Ϊ��%dx%d\n", width, height);
	printf("ͼ��ĳߴ�Ϊ��%dx%d\n", logoImage.cols, logoImage.rows);
	int i = 0, j = 0;                                      //(i,j)��ʾLOGO��λ��,t��ʾLOGO��λ��ʱ��֡��.

	while (camera.isOpened()){

		//LOGO�ɣ�0,0�����ƶ�����ALPHA,0����.
		for (i = 0; i != ALPHA; ++i){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, 0, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("����ͷ", srcImage);
//			video << srcImage;         //¼����Ƶ.
			waitKey(40);
		}

		//LOGO�ɣ�ALPHA,0�����ƶ�����ALPHA,BETA����.
		for (j = 0; j != BETA; ++j){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(ALPHA, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("����ͷ", srcImage);
//			video << srcImage;         //¼����Ƶ.
			waitKey(40);
		}
		//LOGO�ɣ�ALPHA,BETA�����ƶ�����0,BETA����.
		for (; i >0; --i){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, BETA, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("����ͷ", srcImage);
//			video << srcImage;         //¼����Ƶ.
			waitKey(40);
		}
		//LOGO�ɣ�0,BETA�����ƶ�����0,0����.
		for (; j >0; --j){
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(0, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("����ͷ", srcImage);
//			video << srcImage;         //¼����Ƶ.
			waitKey(40);
		}
		//LOGO�ɣ�0,0�����ƶ�����ALPHA,BETA����.
		for (i = 0; i != ALPHA; ++i){
			j = i*BETA / ALPHA*1.0;
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("����ͷ", srcImage);
//			video << srcImage;         //¼����Ƶ.
			waitKey(40);
		}
		//LOGO�ɣ�ALPHA,BETA�����ƶ�����0,0����.
		for (; i > 0; --i){
			j = i*BETA / ALPHA*1.0;
			printf("i=%d,j=%d\n", i, j);
			camera >> srcImage;
			Mat ImageROI = srcImage(Rect(i, j, logoImage.cols, logoImage.rows));
			logoImage.copyTo(ImageROI, logoMask);
			imshow("����ͷ", srcImage);
//			video << srcImage;         //¼����Ƶ.
			waitKey(40);
		}
	}
	return 0;
}