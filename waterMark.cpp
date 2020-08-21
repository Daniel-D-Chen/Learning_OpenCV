#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main_waterMark(int argc, char** argv) {
	String ext = ".png";//使用png格式图片，无损压缩
	Mat markImg = imread("./Resources/mine/black_white"+ ext, IMREAD_COLOR);//水印图层
	Mat srcImg = imread("./Resources/mine/car5"+ ext, IMREAD_COLOR);//原图像
	if (markImg.empty() || srcImg.empty()) {
		cout << "Load Image Failure!!!" << endl;
		return EXIT_FAILURE;
	}
	cvtColor(markImg, markImg, COLOR_BGR2GRAY);//水印图变为单通道灰度图
	int pos = 0;//水印图的标识保存于uchar的第pos位
	if (pos < 0 || pos > 7) {//uchar只有0~7共8位
		pos = 0;
	}
	int maxValue = pow(2,pos);//二值化后的较大值,即阈值的上下限差值
	threshold(markImg, markImg,0, maxValue,THRESH_BINARY_INV| THRESH_OTSU);//大津法将水印二值化
	//markImg += delta;//将阈值上界调整为255，同增值调整下界

	if (markImg.size() != srcImg.size()) {//填充水印层至与原图像尺寸相等
		int top = 0, bottom = srcImg.rows - markImg.rows, left = 0, right = srcImg.cols - markImg.cols;//填充在水印层四周的边界尺寸
		copyMakeBorder(markImg, markImg, top, bottom, left,right, cv::BORDER_WRAP);//对边填充
	}
	cvtColor(markImg, markImg, COLOR_GRAY2BGR);//水印图层扩充通道，至与原图像相同
	int delta = 255 - pow(2, pos);
	Mat clearMat = Mat(Size(srcImg.cols, srcImg.rows),CV_8UC3,Scalar(delta, delta, delta));
	bitwise_and(srcImg, clearMat, srcImg);//将原图像的每个像素的第pos位清空
	//bitwise_and(markImg, srcImg, srcImg);//原图像与水印层对应的像素比特，按位"与"操作
	srcImg += markImg;//如果水印层像素的第pos位为1，则也将原图像的对应像素的第pos位变1
	imwrite("./Resources/mine/car5_waterMark" + ext, srcImg);//保存输出加水印后的原图像

	Mat srcMarkImg = imread("./Resources/mine/car5_waterMark" + ext, IMREAD_COLOR);
	Mat cmpMark;//测试保存前后像素值是否改变
	compare(srcImg,srcMarkImg,cmpMark, CMP_EQ);

	Mat markExtImg;
	Mat extractMat = Mat(Size(srcMarkImg.cols, srcMarkImg.rows), CV_8UC3, Scalar(maxValue, maxValue, maxValue));//将图像每个像素的第pos位提取
	bitwise_and(srcMarkImg, extractMat, markExtImg);
	//normalize(markExtImg, markExtImg,maxValue-1,255, NORM_MINMAX);//标准化将1转为255
	threshold(markExtImg, markExtImg, maxValue-1, 255, THRESH_BINARY);//阈值化将1转为255
	imshow("markExtImg", markExtImg);

	waitKey(0);
	return EXIT_SUCCESS;
}