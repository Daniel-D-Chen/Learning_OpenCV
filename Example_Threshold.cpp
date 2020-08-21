#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

static int threshold1 = 100;
static String fileName = "ticket3.jpg";

static void TrackbarOnChange(int pos, void* userData);

int main_threshold(int argc, char** argv) {
	Mat img,img2;
	img = imread("./Resources/mine/"+ fileName, IMREAD_COLOR);
	if (img.empty()) {
		cout << "invaild image!!!";
		return 0;
	}
	namedWindow(fileName, WINDOW_AUTOSIZE);
	imshow(fileName, img);

	/*Mat_<int> kernel = (Mat_<int>(3, 3) <<  0,  -1, 0,
											-1,  4, -1,
											0,  -1, 0);
	cvtColor(img,img2, COLOR_BGR2GRAY);
	imshow(fileName, img2);*/

	/*filter2D(img, dst, img.depth(), kernel,Point2i(-1,-1));
	imwrite("./Resources/mine/ticket1_拉普拉斯边缘检测.jpg", dst);
	namedWindow("filter_"+fileName, WINDOW_AUTOSIZE);
	imshow("filter_" + fileName, dst);*/

	/*GaussianBlur(img, img, Size(3,3), 0, 0);
	cv::threshold(img, dst, 100, 255, cv::THRESH_BINARY_INV);
	namedWindow("filter_" + fileName, WINDOW_AUTOSIZE);
	createTrackbar("阈值:", "filter_" + fileName, &threshold1, 255, TrackbarOnChange,(void *)&img);
	imshow("filter_" + fileName, dst);*/

	cvtColor(img, img2, CV_BGR2HSV);
	vector<Mat> channels_HSV;
	split(img2, channels_HSV);
	namedWindow("V_channel_" + fileName, WINDOW_AUTOSIZE);
	imshow("V_channel_" + fileName, channels_HSV[2]);
	Mat_<uchar> dst;
	//cv::threshold(channels_HSV[2], dst, 180, 255, cv::THRESH_BINARY_INV);
	cv::threshold(channels_HSV[2], dst, 180, 255, cv::THRESH_BINARY_INV| cv::THRESH_OTSU);
	//Mat element = getStructuringElement(MORPH_CROSS, Size(3,3), Point(-1,-1));
	//morphologyEx(dst, dst, MORPH_OPEN , element);
	/*for (int x = 1; x < dst.cols-1; x++) {
		for (int y = 1; y < dst.rows-1; y++) {//中间白点，左右上下四点为黑色
			if ((int)dst.at<uchar>(y,x) == 255 && (int)dst.at<uchar>(y-1, x) == 0 && (int)dst.at<uchar>(y , x - 1) == 0 && (int)dst.at<uchar>(y, x + 1) == 0 && (int)dst.at<uchar>(y+1, x+1) == 0) {
				dst.at<uchar>(y, x) = 0;
			}
		}
	}*/
	medianBlur(dst, dst, 3);
	namedWindow("V_threshold_" + fileName, WINDOW_AUTOSIZE);
	imshow("V_threshold_" + fileName, dst);
	waitKey(0);
}

static void TrackbarOnChange(int pos, void* userData) {
	Mat img = *((Mat*)userData);
	Mat dst;
	cv::threshold(img, dst, pos, 255, cv::THRESH_BINARY_INV);
	imshow("filter_" + fileName, dst);
}