#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat img(500, 700, CV_8UC3, Scalar(255, 255, 255));	//3ä�� �÷�����
Mat copy_img;	//���� ���� ���纻
Mat img_size(500 / 5, 200, CV_8UC3, Scalar(255, 255, 255));
Point ptOld;
string file_name;

void on_mouse(int event, int x, int y, int flags, void*);	//���콺 �̺�Ʈ
void img_UI(Mat& img);	//���� UI �׸��� �Լ�

int main() {
	img_UI(img);	//UI�׸��� �Լ� ȣ��

	namedWindow("img");
	setMouseCallback("img", on_mouse);	//���콺�̺�Ʈ �Լ� ȣ��

	waitKey();
	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*) {
	imshow("img", img);
	Rect rectangle[] = {
		Rect(0, 0, 495, 495),	//�Է�â
		Rect(501, 0, 199, 99),	//save
		Rect(501, 500 / 5 + 1, 199, 99),	//load
		Rect(501, 500 * 2 / 5 + 1, 199, 99),	//clear
		Rect(501, 500 * 3 / 5 + 1, 199, 99),	//run
		Rect(501, 500 * 4 / 5 + 1, 199, 99)	//exit
	};
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		if (rectangle[1].contains(Point(x, y))) {	//save
			cout << "������ ���ϸ��� �Է� : ";
			getline(cin, file_name);
			imwrite(file_name, img);
		}
		else if (rectangle[2].contains(Point(x, y))) {	//load
			cout << "�ҷ��� ���ϸ��� �Է� : ";
			getline(cin, file_name);
			img = imread(file_name);
			imshow("img", img);
		}
		else if (rectangle[3].contains(Point(x, y))) {	//clear
			img = copy_img.clone();
			imshow("img", img);
		}
		else if (rectangle[4].contains(Point(x, y))) {	//run
			//�̱���
		}
		else if (rectangle[5].contains(Point(x, y))) {	//exit
			cout << "���α׷� ����" << endl;
			exit(0);	//����
		}
		break;
	case EVENT_MOUSEMOVE:
		if (rectangle[0].contains(Point(x, y))) {
			if (flags & EVENT_FLAG_LBUTTON) {
				line(img, ptOld, Point(x, y), Scalar(0, 0, 0), 10);
				imshow("img", img);
				ptOld = Point(x, y);
			}
		}
		break;
	}
}
void img_UI(Mat& img) {
	//ĭ ������
	line(img, Point(500, 0), Point(500, 500), Scalar(0, 0, 0), 2);
	for (int i = 1; i < 5; i++) {
		line(img, Point(500, 500 * i / 5), Point(700, 500 * i / 5), Scalar(0, 0, 0), 2);
	}
	rectangle(img, Rect(0, 0, 700, 500), Scalar(0, 0, 0), 2);	//�׵θ�

	//UI����
	string text[] = { "Save", "Load", "Clear", "Run", "Exit" };
	int fontface = FONT_HERSHEY_SIMPLEX;	//��Ʈ ����
	double fontscale = 2.0;	//��Ʈ ũ��
	int thickness = 2;	//�۾� �β�
	for (int i = 0; i < 5; i++) {
		Size sizeText = getTextSize(text[i], fontface, fontscale, thickness, 0);	//�۾� ũ��
		Size imgsize = img_size.size();	//��ü ������
		Point org(500 + (imgsize.width - sizeText.width) / 2,
			500 * i / 5 + (imgsize.height + sizeText.height) / 2);
		putText(img, text[i], org, fontface, fontscale, Scalar(0, 0, 0), thickness);
	}
	copy_img = img.clone();	//UI�� �׷��� ���� ����
}