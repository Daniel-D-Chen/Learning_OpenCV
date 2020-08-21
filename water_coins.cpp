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
	vector<Mat> channels; //原图转为HSV后各通道数值
	cvtColor(imgSrc, imgHsv,COLOR_BGR2HSV);
	split(imgSrc, channels);
	Mat_<uchar> imgBI,sureBg,sureFg;//二值化的原图,确定的背景层，确定的前景层
	threshold(channels[0], imgBI, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3), Point(-1,-1));
	morphologyEx(imgBI, imgBI, MORPH_OPEN, kernel, Point(-1,-1), 2);//去除噪声
	dilate(imgBI, sureBg, kernel, Point(-1, -1), 2); //确定背景层

	//使用距离变换分割每个硬币
	Mat dist_transform;//图像中心距离
	distanceTransform(imgBI, dist_transform , DIST_L2, DIST_MASK_5, 5);
	normalize(dist_transform, sureFg, 0, 255, NORM_MINMAX);
	double minVal,maxVal;//距离的图像中的最大值
	minMaxLoc(sureFg, &minVal, &maxVal);
	threshold(sureFg, sureFg, 0.5 * maxVal, 255, cv::THRESH_BINARY);

	//使用形态学变化，只分辨前后景
	//erode(imgBI, sureFg, kernel, Point(-1, -1), 2); //确定前景层

	Mat_<uchar> unknown = sureBg - sureFg;
	Mat_<int> markers=Mat::zeros(Size(imgSrc.cols, imgSrc.rows),CV_32S);//前景图中的连通分量标记
	connectedComponents(sureFg, markers, 8, CV_32S);//统计连通分量数目，保存至markers
	markers = markers + 1;//背景像素点置为1，其他也+1
	for (int x = 0; x < unknown.cols; x++) {
		for (int y = 0; y < unknown.rows; y++) {
			if (255==unknown(y,x)) {//非确定范围的像素点置为可淹没范围
				markers(y, x) = 0;
			}
		}
	}

	/*用不同颜色标记不同连通分量
	Mat grayMap, colorMap;
	normalize(markers, grayMap, 0, 255, NORM_MINMAX, CV_8U);//模板层归一化
	applyColorMap(grayMap, colorMap, COLORMAP_JET);*/

	watershed(imgSrc, markers);//执行漫水分割法
	for (int x = 0; x < imgSrc.cols; x++) {//标记边界水坝为红色
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