#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

int main_waterCoins(int argc, char** argv) {
	Mat_<Vec3b> imgSrc = imread("./Resources/mine/water_coins.jpg", IMREAD_COLOR);
	if (imgSrc.empty()) {
		cout << "Couldn't open image ";;
		return EXIT_FAILURE;
	}
	Mat_<Vec3b> imgHsv;
	vector<Mat> channels; //ԭͼתΪHSV���ͨ����ֵ
	cvtColor(imgSrc, imgHsv,COLOR_BGR2HSV);
	split(imgSrc, channels);
	Mat_<uchar> imgBI,sureBg,sureFg;//��ֵ����ԭͼ,ȷ���ı����㣬ȷ����ǰ����
	threshold(channels[0], imgBI, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3), Point(-1,-1));
	morphologyEx(imgBI, imgBI, MORPH_OPEN, kernel, Point(-1,-1), 2);//ȥ������
	dilate(imgBI, sureBg, kernel, Point(-1, -1), 2); //ȷ��������

	//ʹ�þ���任�ָ�ÿ��Ӳ��
	Mat dist_transform;//ͼ�����ľ���
	distanceTransform(imgBI, dist_transform , DIST_L2, DIST_MASK_5, 5);
	normalize(dist_transform, sureFg, 0, 255, NORM_MINMAX);
	double minVal,maxVal;//�����ͼ���е����ֵ
	minMaxLoc(sureFg, &minVal, &maxVal);
	threshold(sureFg, sureFg, 0.5 * maxVal, 255, cv::THRESH_BINARY);

	//ʹ����̬ѧ�仯��ֻ�ֱ�ǰ��
	//erode(imgBI, sureFg, kernel, Point(-1, -1), 2); //ȷ��ǰ����

	Mat_<uchar> unknown = sureBg - sureFg;
	Mat_<int> markers=Mat::zeros(Size(imgSrc.cols, imgSrc.rows),CV_32S);//ǰ��ͼ�е���ͨ�������
	connectedComponents(sureFg, markers, 8, CV_32S);//ͳ����ͨ������Ŀ��������markers
	markers = markers + 1;//�������ص���Ϊ1������Ҳ+1
	for (int x = 0; x < unknown.cols; x++) {
		for (int y = 0; y < unknown.rows; y++) {
			if (255==unknown(y,x)) {//��ȷ����Χ�����ص���Ϊ����û��Χ
				markers(y, x) = 0;
			}
		}
	}

	/*�ò�ͬ��ɫ��ǲ�ͬ��ͨ����
	Mat grayMap, colorMap;
	normalize(markers, grayMap, 0, 255, NORM_MINMAX, CV_8U);//ģ����һ��
	applyColorMap(grayMap, colorMap, COLORMAP_JET);*/

	watershed(imgSrc, markers);//ִ����ˮ�ָ
	for (int x = 0; x < imgSrc.cols; x++) {//��Ǳ߽�ˮ��Ϊ��ɫ
		for (int y = 0; y < imgSrc.rows; y++) {
			if (-1 == markers(y, x)) {
				imgSrc(y, x)[0] = 0;
				imgSrc(y, x)[1] = 0;
				imgSrc(y, x)[2] = 255;
			}
		}
	}

	namedWindow("imgSrc",WINDOW_AUTOSIZE);
	imshow("imgSrc", imgSrc);
	waitKey(0);
	destroyAllWindows();
	return EXIT_SUCCESS;
}