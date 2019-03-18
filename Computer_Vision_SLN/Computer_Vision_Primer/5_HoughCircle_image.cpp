#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("./image/houghcircle1.jpg");
	Mat midImage, dstImage;  // 临时变量和目标图
	imshow("src", srcImage);

	cvtColor(srcImage, midImage, COLOR_BGR2GRAY);//转化灰度图
	GaussianBlur(midImage, midImage, Size(9, 9), 2, 2);  // 高斯平滑

	vector<Vec3f> circles;
	HoughCircles(midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);  // 霍夫圆变换

	for (size_t i = 0; i < circles.size(); i++){                      // 在图中绘制圆
		// 参数 
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// 绘制圆心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// 绘制圆轮廓
		circle(srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
 
	imshow("src", srcImage);

	waitKey(0);

}
