#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("./image/test.jpg");
	Mat tmpImage, dstImage1, dstImage2;
	tmpImage = srcImage;
 
	imshow("src", srcImage);

	//进行尺寸调整操作
	resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0, 0), (0, 0), 3);
	resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0, 0), (0, 0), 3);

	//显示效果图  
	imshow("resize: *1/2", dstImage1);
	imshow("resize: *2", dstImage2);

	waitKey(0);
	return 0;
}
