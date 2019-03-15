#include <opencv2/opencv.hpp>

using namespace cv;

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
RNG rng(12345);

void detectAndDisplay(Mat frame);
void detectHist(Mat srcImage);

int main()
{
	printf("OpenCV Version: %s\n", CV_VERSION);
	system("color F5");

	VideoCapture camera(0);
	Mat srcImage;
//	const int32_t width = camera.get(CV_CAP_PROP_FRAME_WIDTH);
//	const int32_t height = camera.get(CV_CAP_PROP_FRAME_HEIGHT);
//	VideoWriter video("faceDetection.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(width, height));
	face_cascade.load(face_cascade_name);
	eyes_cascade.load(eyes_cascade_name);
	while (camera.isOpened()) {
		camera >> srcImage;
		detectHist(srcImage);
		detectAndDisplay(srcImage);
//		video << srcImage;
		imshow("人脸&眼睛检测:-D", srcImage);
		waitKey(40);
	}
	return 0;
}

void detectAndDisplay(Mat frame)
{
	std::vector<Rect> faces;
	std::vector<Rect> eyes;
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	for (size_t i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
//		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 1, 8, 0);
		rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 1, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t j = 0; j < eyes.size(); j++) {
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, eye_center, radius, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 4, 8, 0);
		}
	}
}

void detectHist(Mat srcImage)
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
	imshow("BGR直方图", histImage);
}
