#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{ 
	Mat srcImage = imread("./image/houghline1.jpg");
	Mat midImage, dstImage;  // 临时变量和目标图

	Canny(srcImage, midImage, 50, 200, 3);// canny边缘检测
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);//转化灰度图

	vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);  // //霍夫线变换

	for (size_t i = 0; i < lines.size(); i++){         // 依次在图中绘制出每条线段
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
	}

	imshow("src", srcImage);
	imshow("canny", midImage); 
	imshow("dst", dstImage);

	waitKey(0);
	destroyAllWindows();

}
