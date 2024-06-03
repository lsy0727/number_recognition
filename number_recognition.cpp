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

	imshow("img", img);
	waitKey();
	return 0;
}

void on_mouse(int event, int x, int y, int flags, void*) {
	imshow("img", img);
	Rect rect_area[] = {
		Rect(0, 0, 495, 495),	//입력창 영역
		Rect(501, 0, 199, 99),	//save 영역
		Rect(501, 500 / 5 + 1, 199, 99),	//load 영역
		Rect(501, 500 * 2 / 5 + 1, 199, 99),	//clear 영역
		Rect(501, 500 * 3 / 5 + 1, 199, 99),	//run 영역
		Rect(501, 500 * 4 / 5 + 1, 199, 99)	//exit 영역
	};
	switch (event) {
	case EVENT_LBUTTONDOWN:
		ptOld = Point(x, y);
		if (rect_area[1].contains(ptOld)) {	//save
			cout << "save press" << endl;
			cout << "저장할 파일명을 입력 : ";
			getline(cin, file_name);
			Mat save_img = img(Rect(2, 2, 497, 496));
			imwrite(file_name, save_img);
		}
		else if (rect_area[2].contains(ptOld)) {	//load
			cout << "load press" << endl;
			cout << "불러올 파일명을 입력 : ";
			getline(cin, file_name);
			Mat load_img = imread(file_name);
			load_img.copyTo(img(Rect(2, 2, 497, 496)));
			imshow("img", img);
		}
		else if (rect_area[3].contains(ptOld)) {	//clear
			cout << "clear press" << endl;
			rectangle(img, Rect(2, 2, 497, 496), Scalar(255, 255, 255), -1);
			imshow("img", img);
		}
		else if (rect_area[4].contains(ptOld)) {	//run
			cout << "run press" << endl;
			//미구현
		}
		else if (rect_area[5].contains(ptOld)) {	//exit
			cout << "exit press" << endl;
			cout << "프로그램 종료" << endl;
			exit(0);	//종료
		}
		break;
	case EVENT_MOUSEMOVE:
		if (rect_area[0].contains(Point(x, y))) {
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
		Size TextSize = getTextSize(text[i], fontface, fontscale, thickness, 0);	//글씨 크기
		Size imgsize = img_size.size();	//객체 사이즈
		Point org(500 + (imgsize.width - TextSize.width) / 2,
			500 * i / 5 + (imgsize.height + TextSize.height) / 2);
		putText(img, text[i], org, fontface, fontscale, Scalar(0, 0, 0), thickness);
	}
}
