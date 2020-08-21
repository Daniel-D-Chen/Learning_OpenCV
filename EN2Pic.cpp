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
	wcout << L"�����ַ���" << wch;
	cout << "  ��Ӧ�ı��룺" << bitset_w << endl;

	/*
	unsigned char c = 0xEF;
	for (int i = 0; i < 8; i++) {
		cout << "��" << i << "λΪ��" << ((c >> i) & 0x01 )<< endl;
	}*/
	/*setlocale(LC_ALL, "chs");
	Mat_<Vec3b> srcImg = imread("./Resources/mine/squirrel_code.jpg", IMREAD_COLOR);
	vector<Mat> channels;//�����ͼ��ĸ�ͨ��
	cvtColor(srcImg, srcImg, COLOR_BGR2HSV);
	cv::split(srcImg, channels);
	wchar_t wch;
	unsigned char bytes[2];//ÿ��unicode�����ַ�ռ�������ֽ�,�޸�����Ϊ�޷����ַ��ͣ����������������λ����
	MatIterator_<uchar> it_begin = channels[1].begin<uchar>();
	MatIterator_<uchar> it_end = channels[1].end<uchar>();
	while (it_begin != it_end && (it_begin + 1) != it_end) {
		wch = *it_begin | (*(++it_begin) << 8) ;//�ڶ����ֽ�Ϊ���ĵĸ�λ����һ���ֽ�Ϊ���ĵĵ�λ
		it_begin++;
		wcout << L"�����ַ���" << wch<<endl ;
		cout << "���ֽڶ�Ӧ�Ҷ�:" << (unsigned short int)bytes[0] << "  ���ֽڶ�Ӧ�Ҷ�:" << (unsigned short int)bytes[1] << endl;
	}*/

	/*fin.read((char*)(&wch), 2);*/
	/*char a = 'a';
	bitset<16> bitset1(a);
	bitset<16> bitset2(a<<8);
	bitset<16> bitset3(a>>4);
	cout << "���ͱ�ʾ��" << bitset1 << "  ���ƣ�" << bitset2 << "���ƣ�"<< bitset3 <<endl;*/
	return 0;
	/*bitset<8> bitset1(c[1]);
	bitset<8> bitset2(c[0]);
	cout << "�ֿ��ֽڶ�Ӧ���أ�" << bitset1 << " " << bitset2 << endl; */
	/*unsigned char uchar1 = (unsigned char)(bytes[0]);//�޸����͸�Ϊ�޷����ַ��ͣ����������������λ����
	unsigned char uchar2 = (unsigned char)(bytes[1]);*/
	//cout << "�ֿ��ֽڶ�Ӧ���أ�" << (int)c[0] << "    " << (int)c[1]<<endl;
	/*bitset<16> bitset3(wch);
	cout << "���Ķ�Ӧ���أ�" << bitset3 << endl;*/
	/*wcout << L"�����ַ���" << wch << endl;
	bitset<16> bitset1(wch);
	cout << bitset1 << endl;
	fin.read((char*)(&wch), 2);*/

	/*bitset<8> bitset1(bytes[0]);
	bitset<8> bitset2(bytes[1]);
	cout << "���ֽڱ��أ�" << bitset1 << "\t���ֽڱ��أ� " << bitset2 << endl;*/
}