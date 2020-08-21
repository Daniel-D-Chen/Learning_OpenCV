#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

#define SRC_WIN "srcImg"
#define COL_WIN "colImg"

static void TrackbarOnChange(int pos, void* userData);
static String printColorMapTypeName(int);

int main_colorMap(int argc, char** argv) {
	Mat srcImg = imread("./Resources/mine/car7.jpg",cv::IMREAD_GRAYSCALE);
	if (srcImg.empty()) {
		cout << "Load Src Image Failure!!!" << endl;
		return EXIT_FAILURE;
	}
	namedWindow(SRC_WIN,WINDOW_AUTOSIZE);
	imshow(SRC_WIN, srcImg);

	int colormapType = cv::COLORMAP_AUTUMN;
	namedWindow(COL_WIN, WINDOW_AUTOSIZE);
	Mat colImg;//伪色彩图
	applyColorMap(srcImg, colImg, COLORMAP_JET);
	createTrackbar("伪彩色类型:", COL_WIN , &colormapType, 20, TrackbarOnChange, (void*)&srcImg);
	putText(colImg, "COLORMAP_AUTUMN", Point(5, colImg.rows - 20), cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
	imshow(COL_WIN, colImg);

	waitKey(0);
	return EXIT_SUCCESS;
}

static void TrackbarOnChange(int pos, void* userData) {
	Mat srcImg = *(Mat*)userData;
	Mat colImg;//伪色彩图
	applyColorMap(srcImg, colImg, pos);
	String colorMapTypeName = printColorMapTypeName(pos);
	putText(colImg, colorMapTypeName,Point(5,colImg.rows-20),cv::FONT_HERSHEY_SIMPLEX,1, Scalar(255,255,255));
	imshow(COL_WIN, colImg);
}

static String printColorMapTypeName(int pos) {
	String colorMapTypeName;
	switch (pos) {
		case COLORMAP_AUTUMN:
			colorMapTypeName = "COLORMAP_AUTUMN";
			break;
		case COLORMAP_BONE:
			colorMapTypeName = "COLORMAP_BONE";
			break;
		case COLORMAP_JET:
			colorMapTypeName = "COLORMAP_JET";
			break;
		case COLORMAP_WINTER:
			colorMapTypeName = "COLORMAP_WINTER";
			break;
		case COLORMAP_RAINBOW:
			colorMapTypeName = "COLORMAP_RAINBOW";
			break;
		case COLORMAP_OCEAN:
			colorMapTypeName = "COLORMAP_OCEAN";
			break;
		case COLORMAP_SUMMER:
			colorMapTypeName = "COLORMAP_SUMMER";
			break;
		case COLORMAP_SPRING:
			colorMapTypeName = "COLORMAP_SPRING";
			break;
		case COLORMAP_COOL:
			colorMapTypeName = "COLORMAP_COOL";
			break;
		case COLORMAP_HSV:
			colorMapTypeName = "COLORMAP_HSV";
			break;
		case COLORMAP_PINK:
			colorMapTypeName = "COLORMAP_PINK";
			break;
		case COLORMAP_HOT:
			colorMapTypeName = "COLORMAP_HOT";
			break;
		case COLORMAP_PARULA:
			colorMapTypeName = "COLORMAP_PARULA";
			break;
		case COLORMAP_MAGMA:
			colorMapTypeName = "COLORMAP_MAGMA";
			break;
		case COLORMAP_INFERNO:
			colorMapTypeName = "COLORMAP_INFERNO";
			break;
		case COLORMAP_PLASMA:
			colorMapTypeName = "COLORMAP_PLASMA";
			break;
		case COLORMAP_VIRIDIS:
			colorMapTypeName = "COLORMAP_VIRIDIS";
			break;
		case COLORMAP_CIVIDIS:
			colorMapTypeName = "COLORMAP_CIVIDIS";
			break;
		case COLORMAP_TWILIGHT:
			colorMapTypeName = "COLORMAP_TWILIGHT";
			break;
		case COLORMAP_TWILIGHT_SHIFTED:
			colorMapTypeName = "COLORMAP_TWILIGHT_SHIFTED";
			break;
		case COLORMAP_TURBO:
			colorMapTypeName = "COLORMAP_TURBO";
			break;
		default: colorMapTypeName = "COLORMAP_AUTUMN";
	}
	//std::cout << "伪彩色类型:" << colorMapTypeName << endl;
	return colorMapTypeName;
}