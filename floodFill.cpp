#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

static String fileName = "ticket3.jpg";

int main_floodFill(int argc, char** argv) {
	Mat_<uchar> srcImg = imread("./Resources/mine/" + fileName, IMREAD_GRAYSCALE);
	/*Mat_<uchar> srcImg = Mat::zeros(400,512,CV_8UC1);
	for (int x = 0; x < srcImg.cols; x++) {
		for (int y = 0; y < srcImg.rows; y++) {
			srcImg(y, x) = saturate_cast<uchar>(x/2);
		}
	}*/
	Point seed = Point(100,100);
	cout << "seed(" << seed.x << "," << seed.y << ")=" <<(int) srcImg(seed.y, seed.x) << endl;

	Scalar LowDifference = Scalar(10);
	Scalar UpDifference = Scalar(10);
	Scalar newVal = Scalar(255);
	int flags = 4 | FLOODFILL_FIXED_RANGE;
	//circle(srcImg, seed, 20, Scalar(0));
	floodFill(srcImg,  seed, newVal, 0, LowDifference, UpDifference, flags);

	namedWindow("Flood_Win",CV_WINDOW_AUTOSIZE);
	imshow("Flood_Win", srcImg);
	waitKey(0);
	return EXIT_SUCCESS;
}