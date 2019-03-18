#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{ 
	Mat srcImage = imread("./image/houghline1.jpg");
	Mat midImage, dstImage;  // ��ʱ������Ŀ��ͼ

	Canny(srcImage, midImage, 50, 200, 3);// canny��Ե���
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);//ת���Ҷ�ͼ

	vector<Vec2f> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);  // //�����߱任

	for (size_t i = 0; i < lines.size(); i++){         // ������ͼ�л��Ƴ�ÿ���߶�
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
