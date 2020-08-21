#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;
using namespace cv;

int main_EN2Pic(int argc, char** argv) {
	setlocale(LC_ALL, "chs");
	wchar_t wch = 0xFFFE;
	bitset<16> bitset_w(wch);
	wcout << L"中文字符：" << wch;
	cout << "  对应的编码：" << bitset_w << endl;

	/*
	unsigned char c = 0xEF;
	for (int i = 0; i < 8; i++) {
		cout << "第" << i << "位为：" << ((c >> i) & 0x01 )<< endl;
	}*/
	/*setlocale(LC_ALL, "chs");
	Mat_<Vec3b> srcImg = imread("./Resources/mine/squirrel_code.jpg", IMREAD_COLOR);
	vector<Mat> channels;//分离后图像的各通道
	cvtColor(srcImg, srcImg, COLOR_BGR2HSV);
	cv::split(srcImg, channels);
	wchar_t wch;
	unsigned char bytes[2];//每个unicode编码字符占据两个字节,修改类型为无符号字符型，方便后续进行左移位操作
	MatIterator_<uchar> it_begin = channels[1].begin<uchar>();
	MatIterator_<uchar> it_end = channels[1].end<uchar>();
	while (it_begin != it_end && (it_begin + 1) != it_end) {
		wch = *it_begin | (*(++it_begin) << 8) ;//第二个字节为中文的高位，第一个字节为中文的低位
		it_begin++;
		wcout << L"中文字符：" << wch<<endl ;
		cout << "首字节对应灰度:" << (unsigned short int)bytes[0] << "  次字节对应灰度:" << (unsigned short int)bytes[1] << endl;
	}*/

	/*fin.read((char*)(&wch), 2);*/
	/*char a = 'a';
	bitset<16> bitset1(a);
	bitset<16> bitset2(a<<8);
	bitset<16> bitset3(a>>4);
	cout << "整型表示：" << bitset1 << "  左移：" << bitset2 << "右移："<< bitset3 <<endl;*/
	return 0;
	/*bitset<8> bitset1(c[1]);
	bitset<8> bitset2(c[0]);
	cout << "分开字节对应比特：" << bitset1 << " " << bitset2 << endl; */
	/*unsigned char uchar1 = (unsigned char)(bytes[0]);//修改类型改为无符号字符型，方便后续进行左移位操作
	unsigned char uchar2 = (unsigned char)(bytes[1]);*/
	//cout << "分开字节对应比特：" << (int)c[0] << "    " << (int)c[1]<<endl;
	/*bitset<16> bitset3(wch);
	cout << "中文对应比特：" << bitset3 << endl;*/
	/*wcout << L"中文字符：" << wch << endl;
	bitset<16> bitset1(wch);
	cout << bitset1 << endl;
	fin.read((char*)(&wch), 2);*/

	/*bitset<8> bitset1(bytes[0]);
	bitset<8> bitset2(bytes[1]);
	cout << "低字节比特：" << bitset1 << "\t高字节比特： " << bitset2 << endl;*/
}