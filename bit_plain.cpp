#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void on_bp_change(int pos, void* userdata) {  // 트랙바 콜백함수 on_bp_change
	Mat src = *(Mat*)userdata;  // 사용자 데이터 대입
	Mat dst(src.rows, src.cols, src.type());  // 비트플레인 출력용 dst 생성
	int mask = 0x01;  // 비트 마스크 초기값 0x01 대입
	mask <<= pos - 1;  // 트랙바 위치에 맞게 비트 이동

	for (int i = 0; i < src.rows; i++) {  // 비트 마스크 적용 부분
		for (int j = 0; j < src.cols; j++) {
			if ((mask & src.at<uchar>(i, j)) == uchar(pow(2, pos - 1)))  // 비트 마스크한 결과가 해당 비트와 맞으면
				dst.at<uchar>(i, j) = 255;  // 화소값 255 대입
			else  // 그렇지 않으면
				dst.at<uchar>(i, j) = 0;  // 화소값 0 대입
		}
	}
	imshow("image", dst);  // 비트 플레인 출력
}

int main(void) {
	Mat src = imread("lenna.BMP", IMREAD_GRAYSCALE);  // 컬러 영상을 그레이 영상으로 변환하여 영상 불러오기
	if (src.empty()) { cerr << "img load failed!" << endl;  return -1; }  // 영상 불러오기 오류시 오류 메시지 출력
	
	namedWindow("image");  // image 윈도우 생성
	createTrackbar("bit-plain", "image", 0, 8, on_bp_change, (void*)&src);  // 트랙바 생성, 콜백 함수 on_bp_change
	imshow("image", src);  // 실행시 원본 영상 출력

	waitKey(0);  // 사용자의 키보드 입력 대기
	return 0;  // 프로그램 종료
}