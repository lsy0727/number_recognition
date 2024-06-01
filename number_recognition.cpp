#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat img(500, 700, CV_8UC3, Scalar(255, 255, 255));	//3채널 컬러영상
Mat copy_img;	//기존 영상 복사본
Mat img_size(500 / 5, 200, CV_8UC3, Scalar(255, 255, 255));
Point ptOld;
string file_name;

void on_mouse(int event, int x, int y, int flags, void*);	//마우스 이벤트
void img_UI(Mat& img);	//영상 UI 그리기 함수

int main() {
	img_UI(img);	//UI그리기 함수 호출

	namedWindow("img");
	setMouseCallback("img", on_mouse);	//마우스이벤트 함수 호출

	waitKey();
	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*) {
	imshow("img", img);
	Rect rectangle[] = {
		Rect(0, 0, 495, 495),	//입력창
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
			cout << "저장할 파일명을 입력 : ";
			getline(cin, file_name);
			imwrite(file_name, img);
		}
		else if (rectangle[2].contains(Point(x, y))) {	//load
			cout << "불러올 파일명을 입력 : ";
			getline(cin, file_name);
			img = imread(file_name);
			imshow("img", img);
		}
		else if (rectangle[3].contains(Point(x, y))) {	//clear
			img = copy_img.clone();
			imshow("img", img);
		}
		else if (rectangle[4].contains(Point(x, y))) {	//run
			//미구현
		}
		else if (rectangle[5].contains(Point(x, y))) {	//exit
			cout << "프로그램 종료" << endl;
			exit(0);	//종료
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
	//칸 나누기
	line(img, Point(500, 0), Point(500, 500), Scalar(0, 0, 0), 2);
	for (int i = 1; i < 5; i++) {
		line(img, Point(500, 500 * i / 5), Point(700, 500 * i / 5), Scalar(0, 0, 0), 2);
	}
	rectangle(img, Rect(0, 0, 700, 500), Scalar(0, 0, 0), 2);	//테두리

	//UI설계
	string text[] = { "Save", "Load", "Clear", "Run", "Exit" };
	int fontface = FONT_HERSHEY_SIMPLEX;	//폰트 종류
	double fontscale = 2.0;	//폰트 크기
	int thickness = 2;	//글씨 두께
	for (int i = 0; i < 5; i++) {
		Size sizeText = getTextSize(text[i], fontface, fontscale, thickness, 0);	//글씨 크기
		Size imgsize = img_size.size();	//객체 사이즈
		Point org(500 + (imgsize.width - sizeText.width) / 2,
			500 * i / 5 + (imgsize.height + sizeText.height) / 2);
		putText(img, text[i], org, fontface, fontscale, Scalar(0, 0, 0), thickness);
	}
	copy_img = img.clone();	//UI가 그려진 영상 복사
}