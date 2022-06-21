#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void on_bp_change(int pos, void* userdata) {  // Ʈ���� �ݹ��Լ� on_bp_change
	Mat src = *(Mat*)userdata;  // ����� ������ ����
	Mat dst(src.rows, src.cols, src.type());  // ��Ʈ�÷��� ��¿� dst ����
	int mask = 0x01;  // ��Ʈ ����ũ �ʱⰪ 0x01 ����
	mask <<= pos - 1;  // Ʈ���� ��ġ�� �°� ��Ʈ �̵�

	for (int i = 0; i < src.rows; i++) {  // ��Ʈ ����ũ ���� �κ�
		for (int j = 0; j < src.cols; j++) {
			if ((mask & src.at<uchar>(i, j)) == uchar(pow(2, pos - 1)))  // ��Ʈ ����ũ�� ����� �ش� ��Ʈ�� ������
				dst.at<uchar>(i, j) = 255;  // ȭ�Ұ� 255 ����
			else  // �׷��� ������
				dst.at<uchar>(i, j) = 0;  // ȭ�Ұ� 0 ����
		}
	}
	imshow("image", dst);  // ��Ʈ �÷��� ���
}

int main(void) {
	Mat src = imread("lenna.BMP", IMREAD_GRAYSCALE);  // �÷� ������ �׷��� �������� ��ȯ�Ͽ� ���� �ҷ�����
	if (src.empty()) { cerr << "img load failed!" << endl;  return -1; }  // ���� �ҷ����� ������ ���� �޽��� ���
	
	namedWindow("image");  // image ������ ����
	createTrackbar("bit-plain", "image", 0, 8, on_bp_change, (void*)&src);  // Ʈ���� ����, �ݹ� �Լ� on_bp_change
	imshow("image", src);  // ����� ���� ���� ���

	waitKey(0);  // ������� Ű���� �Է� ���
	return 0;  // ���α׷� ����
}