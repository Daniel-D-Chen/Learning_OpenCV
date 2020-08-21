#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main_waterMark(int argc, char** argv) {
	String ext = ".png";//ʹ��png��ʽͼƬ������ѹ��
	Mat markImg = imread("./Resources/mine/black_white"+ ext, IMREAD_COLOR);//ˮӡͼ��
	Mat srcImg = imread("./Resources/mine/car5"+ ext, IMREAD_COLOR);//ԭͼ��
	if (markImg.empty() || srcImg.empty()) {
		cout << "Load Image Failure!!!" << endl;
		return EXIT_FAILURE;
	}
	cvtColor(markImg, markImg, COLOR_BGR2GRAY);//ˮӡͼ��Ϊ��ͨ���Ҷ�ͼ
	int pos = 0;//ˮӡͼ�ı�ʶ������uchar�ĵ�posλ
	if (pos < 0 || pos > 7) {//ucharֻ��0~7��8λ
		pos = 0;
	}
	int maxValue = pow(2,pos);//��ֵ����Ľϴ�ֵ,����ֵ�������޲�ֵ
	threshold(markImg, markImg,0, maxValue,THRESH_BINARY_INV| THRESH_OTSU);//��򷨽�ˮӡ��ֵ��
	//markImg += delta;//����ֵ�Ͻ����Ϊ255��ͬ��ֵ�����½�

	if (markImg.size() != srcImg.size()) {//���ˮӡ������ԭͼ��ߴ����
		int top = 0, bottom = srcImg.rows - markImg.rows, left = 0, right = srcImg.cols - markImg.cols;//�����ˮӡ�����ܵı߽�ߴ�
		copyMakeBorder(markImg, markImg, top, bottom, left,right, cv::BORDER_WRAP);//�Ա����
	}
	cvtColor(markImg, markImg, COLOR_GRAY2BGR);//ˮӡͼ������ͨ��������ԭͼ����ͬ
	int delta = 255 - pow(2, pos);
	Mat clearMat = Mat(Size(srcImg.cols, srcImg.rows),CV_8UC3,Scalar(delta, delta, delta));
	bitwise_and(srcImg, clearMat, srcImg);//��ԭͼ���ÿ�����صĵ�posλ���
	//bitwise_and(markImg, srcImg, srcImg);//ԭͼ����ˮӡ���Ӧ�����ر��أ���λ"��"����
	srcImg += markImg;//���ˮӡ�����صĵ�posλΪ1����Ҳ��ԭͼ��Ķ�Ӧ���صĵ�posλ��1
	imwrite("./Resources/mine/car5_waterMark" + ext, srcImg);//���������ˮӡ���ԭͼ��

	Mat srcMarkImg = imread("./Resources/mine/car5_waterMark" + ext, IMREAD_COLOR);
	Mat cmpMark;//���Ա���ǰ������ֵ�Ƿ�ı�
	compare(srcImg,srcMarkImg,cmpMark, CMP_EQ);

	Mat markExtImg;
	Mat extractMat = Mat(Size(srcMarkImg.cols, srcMarkImg.rows), CV_8UC3, Scalar(maxValue, maxValue, maxValue));//��ͼ��ÿ�����صĵ�posλ��ȡ
	bitwise_and(srcMarkImg, extractMat, markExtImg);
	//normalize(markExtImg, markExtImg,maxValue-1,255, NORM_MINMAX);//��׼����1תΪ255
	threshold(markExtImg, markExtImg, maxValue-1, 255, THRESH_BINARY);//��ֵ����1תΪ255
	imshow("markExtImg", markExtImg);

	waitKey(0);
	return EXIT_SUCCESS;
}