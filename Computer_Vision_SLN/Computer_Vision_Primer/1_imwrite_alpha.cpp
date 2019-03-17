#include <vector>
#include <stdio.h>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat)  // 创建带alpha通道的Mat
{
	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec4b&rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float(mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
			rgba[2] = saturate_cast<uchar>((float(mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}

void ShowHelpText()
{
	printf("\n\n #############################################################\n");
	printf("\n\n\t\t\t程序功能：生成透明png图像.\n");
	printf("\n\n\t\t\t OpenCV版本：" CV_VERSION);
	printf("\n\n #############################################################\n");
}


int main()
{
	//创建带alpha通道的Mat
	Mat mat(720, 1080, CV_8UC4);
	createAlphaMat(mat);

	ShowHelpText();

	vector<int>compression_params;
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try {
		imwrite("透明Alpha值图.png", mat, compression_params);
		imshow("生成的png图", mat);
		printf("\n==================PNG图片已保存在项目目录下===================\n");
		waitKey(0);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "格式错误：%s\n", ex.what());
		return 1;
	}

	return 0;
}