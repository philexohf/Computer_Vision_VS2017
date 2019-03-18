#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	srcImage = imread("./image/test.jpg", 1);

	if (!srcImage.data){ 
		printf("��ȡͼƬ����.\n"); 
		return false; 
	}

	namedWindow("src", 0);
	namedWindow("equalizeHist", 0);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);  // תΪ�Ҷ�ͼ
	imshow("src", srcImage);

	equalizeHist(srcImage, dstImage);  // ֱ��ͼ����

	imshow("equalizeHist", dstImage);

	waitKey(0);
}