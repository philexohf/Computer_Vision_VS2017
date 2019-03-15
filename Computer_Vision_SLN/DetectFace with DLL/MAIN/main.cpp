#include "imageHist.h"
#pragma comment(lib,"imageHistDLL.lib")
#define SCALAR Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255))

using namespace cvih;

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
RNG rng;
void detectFace(Mat frame);

static void showCameraText(int width,int height) 
{
	printf("\n\n\n\n\n");
	printf("\t\t\t****************************\n");
	printf("\t\t\t**����ͷ�ķֱ���Ϊ:%dx%d**\n", width, height);
	printf("\t\t\t****************************\n");
	printf("\t\t\t*****��ESC���˳�����******\n");
	printf("\t\t\t****************************\n");
	printf("\n\n\n");
	printf("\t\t\t    by  ��ҶΪ�ζ���        \n");
	printf("\t\t\t    QQ:   81502787          \n");
}

int main()
{
	VideoCapture capture(0);
	Mat srcImage, xImage,yImage;
	if (!capture.isOpened()) {
		printf("**********************\n");
		printf("***����ͷ��ʧ�ܣ�***\n");
		printf("**********************\n");
		system("color 4F");
		system("pause");
		return -1;
	}
	system("color F5");
	const int width = capture.get(CAP_PROP_FRAME_WIDTH);           //��ȡ������ͷͼ��Ŀ��
	const int height = capture.get(CAP_PROP_FRAME_HEIGHT);         //��ȡ������ͷͼ��ĸ߶�
	showCameraText(width, height);
	if (!face_cascade.load(face_cascade_name)) {
		printf("����������������ʧ��:-()\n");
		return -1;
	}
	if (!eyes_cascade.load(eyes_cascade_name)) {
		printf("�۾�������������ʧ��:-()\n");
		return -1;
	}
	while (capture.isOpened()) {
		capture >> srcImage;
		flip(srcImage, xImage, 0);
		imshow("**��ֱ��ת** by ��ҶΪ�ζ��� #:-() ", xImage);
		flip(srcImage, yImage, 1);
		imshow("**ˮƽ��ת** by ��ҶΪ�ζ��� #:-() ", yImage);
		ImageHist::imageHist(srcImage);     //����ImageHist dll
		detectFace(srcImage);
		imshow("**�������** by ��ҶΪ�ζ��� #:-() ", srcImage);
		
		char c = (char)waitKey(40);
		if (c == 27)
			break;
	}
	return 0;
}

void detectFace(Mat frame)
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
		rectangle(frame, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), SCALAR, 2, 8, 0);

		Mat faceROI = frame_gray(faces[i]);
		eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
		for (size_t j = 0; j < eyes.size(); j++) {
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, eye_center, radius, SCALAR, 4, 8, 0);
		}
	}
}