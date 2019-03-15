#include "imageHist.h"

namespace cvih {
	void ImageHist::imageHist(Mat srcImage)
	{
		int bins = 256;
		int hist_size[] = { bins };
		float range[] = { 0, 256 };
		const float* ranges[] = { range };
		MatND redHist, grayHist, blueHist;
		int channels_r[] = { 0 };

		//进行直方图的计算（红色分量）
		calcHist(&srcImage, 1, channels_r, Mat(), //不使用掩膜
			redHist, 1, hist_size, ranges,
			true, false);
		//进行直方图的计算（绿色分量）
		int channels_g[] = { 1 };
		calcHist(&srcImage, 1, channels_g, Mat(), // do not use mask
			grayHist, 1, hist_size, ranges,
			true, // the histogram is uniform
			false);
		//进行直方图的计算（蓝色分量）
		int channels_b[] = { 2 };
		calcHist(&srcImage, 1, channels_b, Mat(), // do not use mask
			blueHist, 1, hist_size, ranges,
			true, // the histogram is uniform
			false);

		//-----------------------绘制BGR直方图------------------------
		//参数准备
		double maxValue_red, maxValue_green, maxValue_blue;
		minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
		minMaxLoc(grayHist, 0, &maxValue_green, 0, 0);
		minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
		int scale = 1;
		int histHeight = 256;
		Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);
		//开始绘制
		for (int i = 0; i<bins; i++)
		{
			//参数准备
			float binValue_red = redHist.at<float>(i);
			float binValue_green = grayHist.at<float>(i);
			float binValue_blue = blueHist.at<float>(i);
			int intensity_red = cvRound(binValue_red*histHeight / maxValue_red);  //要绘制的高度
			int intensity_green = cvRound(binValue_green*histHeight / maxValue_green);  //要绘制的高度
			int intensity_blue = cvRound(binValue_blue*histHeight / maxValue_blue);  //要绘制的高度
																					 //绘制红色分量的直方图
			rectangle(histImage, Point(i*scale, histHeight - 1),
				Point((i + 1)*scale - 1, histHeight - intensity_red),
				Scalar(255, 0, 0));
			//绘制绿色分量的直方图
			rectangle(histImage, Point((i + bins)*scale, histHeight - 1),
				Point((i + bins + 1)*scale - 1, histHeight - intensity_green),
				Scalar(0, 255, 0));
			//绘制蓝色分量的直方图
			rectangle(histImage, Point((i + bins * 2)*scale, histHeight - 1),
				Point((i + bins * 2 + 1)*scale - 1, histHeight - intensity_blue),
				Scalar(0, 0, 255));
		}
		imshow("**图像直方图** by 秋叶为何而落 #:=()", histImage);
	}
}

