#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("./image/houghcircle1.jpg");
	Mat midImage, dstImage;  // ��ʱ������Ŀ��ͼ
	imshow("src", srcImage);

	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);//ת���Ҷ�ͼ
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);  // ��˹ƽ��

	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);  // ����Բ�任

	for (size_t i = 0; i < circles.size(); i++){                      // ��ͼ�л���Բ
		// ���� 
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// ����Բ��
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// ����Բ����
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
 
	imshow("src", srcImage);

	waitKey(0);

}
