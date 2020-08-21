#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <bitset>
#include <math.h>
using namespace std;
using namespace cv;

static String ext = ".png";//使用png格式图片，无损压缩
static String path = "./Resources/mine/";//文件路径

/*int main() {
	vector<Mat> channels;
	cv::split(srcImg, channels);
	channels[2] = Mat(channels[2].rows, channels[2].cols,CV_8UC1,Scalar(0));
	wchar_t wch;
	unsigned char bytes[2];//每个unicode编码字符占据两个字节,修改类型为无符号字符型，方便后续进行左移位操作
	fin.read((char*)bytes, 2);
	MatIterator_<uchar> it_begin = channels[1].begin<uchar>();
	MatIterator_<uchar> it_end = channels[1].end<uchar>();
	while (!fin.eof() && it_begin!= it_end && (it_begin+1)!= it_end) {
		(*it_begin++) = bytes[0];//使用迭代器顺序保存字节
		(*it_begin++) = bytes[1];
		wch = (bytes[1] << 8) | bytes[0];//第二个字节为中文的高位，第一个字节为中文的低位
		wcout << L"中文字符：" << wch << endl;
		cout << "首字节对应灰度:" << (unsigned short int)bytes[0] << "  次字节对应灰度:" << (unsigned short int)bytes[1] << endl;
		fin.read((char*)bytes, 2);
	}
	merge(channels, srcImg_HSV);
	cvtColor(srcImg_HSV, srcImg_HSV2BGR, COLOR_HSV2BGR);
	Mat imgChangeCmp;//颜色类型由BGR转HSV后，再转回BGR对比
	compare(srcImg, srcImg_HSV2BGR, imgChangeCmp, CMP_EQ);

	/*std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);    // 无压缩png.
	compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
	compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);

	imwrite("./Resources/mine/squirrel_code.jpg", srcImg);
	fin.close();
	//namedWindow("srcImg", WINDOW_AUTOSIZE);
	//imshow("srcImg", srcImg);

	Mat_<Vec3b> codeImg = imread("./Resources/mine/squirrel_code.jpg", IMREAD_COLOR);
	/*cvtColor(codeImg, codeImg, COLOR_BGR2HSV);
	vector<Mat> channels_code;//分离后图像的各通道
	cv::split(codeImg, channels_code);
	Mat imgSaveCmp;//保存前后对比
	compare(srcImg,codeImg, imgSaveCmp, CMP_EQ);
}*/

//将文本对应的unicode编码逐一比特保存至图像每个像素的最后一位，在文本末尾添加停止符0xFFFE
bool CN2Pic(String txtName,String picName) {
	ifstream fin;
	fin.open(path+txtName, ios::binary | ios::in);
	if (!fin.is_open()) {
		cout << "open file failed" << endl;
		return false;
	}else {
		fin.seekg(2, ios::beg);// 跳过unicode文本开头有两个字节0xFFFE（称作BOM，用于标识unicode编码）
		if (fin.peek() == EOF) {
			cout << "file is empty." << endl;
			return false;
		}else {
			Mat_<Vec3b> srcImg = imread(path + picName + ext, IMREAD_COLOR);//加载原图像
			long int num = 0;//保存字符数
			int delta = 255 - 1;
			Mat clearMat = Mat(Size(srcImg.cols, srcImg.rows), CV_8UC3, Scalar(delta, delta, delta));
			bitwise_and(srcImg, clearMat, srcImg);//将原图像的每个像素的第0位清空
			wchar_t wch;
			fin.read((char*)&wch, 2); //读取文本的一个字
			int bitSize = sizeof(wchar_t) * 8;//每个文字所占位数
			int pixSize = ceil((float)bitSize / srcImg.channels());//计算每个文字所占的像素数量
			MatIterator_<Vec3b> it_begin = srcImg.begin();
			MatIterator_<Vec3b> it_end = srcImg.end();
			while (!fin.eof() && it_begin != it_end) {//读取全部文本或保存直至最后一像素
				num++;
				wcout << wch;
				/*bitset<16> bitset_w(wch);
				wcout << L"中文字符：" << wch;
				cout << "  对应的编码：" << bitset_w << endl;*/
				for (int i = 0; i < pixSize && it_begin != it_end; i++, it_begin++) {//遍历文字的每一位
					for (int j = 0; j < srcImg.channels(); j++) {//按序修改像素的每个通道
						int bitNum = i * srcImg.channels() + j;//当前遍历的是文字的第几位比特
						if (bitNum >= bitSize) {
							break;
						}
						/*bitset<8> bitset_uBf((*it_begin)[j]);
						cout << "第" << bitNum << "位修改前对应编码: " << bitset_uBf;*/
						(*it_begin)[j] += ((wch >> bitNum) & 0x0001);
						/*bitset<8> bitset_uAf((*it_begin)[j]);
						cout << " 修改后对应编码: " << bitset_uAf << endl;*/
					}
				}
				fin.read((char*)&wch, 2); //读取文本的一个字
			}
			if (it_begin != it_end) {//在文本末尾添加停止符0xFFFE
				wch = 0xFFFE;
				for (int i = 0; i < pixSize && it_begin != it_end; i++, it_begin++) {//遍历文字的每一位
					for (int j = 0; j < srcImg.channels(); j++) {//按序修改像素的每个通道
						int bitNum = i * srcImg.channels() + j;//当前遍历的是文字的第几位比特
						if (bitNum >= bitSize) {
							cout << endl << "末尾添加停止符0xFFFE" << endl;
							break;
						}
						(*it_begin)[j] += ((wch >> bitNum) & 0x0001);
					}
				}
			}else {
				cout << endl << "图像容量已经满！" << endl;
			}
			cout << "保存字数:"<< num << endl;
			fin.close();

			vector<int> compression_params;//压缩参数
			/*compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //选择JPEG
			compression_params.push_back(100);//从0到100（数值越高质量越好），默认值为95 */
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);  //选择png
			compression_params.push_back(9);//从0到9,数值越高，文件大小越小，压缩时间越长。默认值为3
			imwrite(path + picName + "_code" + ext, srcImg, compression_params);
			cout << endl << "保存完毕" << endl;
			waitKey(0);
			return true;
		}
	}
}

//图像每个像素的最后一位拼凑成文本，并输出
bool Pic2CN(String picName) {
	Mat_<Vec3b> codeImg = imread(path + picName + "_code" + ext, IMREAD_COLOR);
	if (codeImg.empty()) {
		cout << "Load Image Failure!!!" << endl;
		return false;
	}
	int bitSize = sizeof(wchar_t) * 8;//每个文字所占位数
	int pixSize = ceil((float)bitSize / codeImg.channels());//计算每个文字所占的像素数量
	MatIterator_<Vec3b> it_code_begin = codeImg.begin();
	MatIterator_<Vec3b> it_code_end = codeImg.end();
	while (it_code_begin != it_code_end) {//读取全部文本或直至最后一像素
		wchar_t wch = 0x0000;
		for (int i = 0; i < pixSize && it_code_begin != it_code_end; i++, it_code_begin++) {//遍历文字的每一位
			for (int j = 0; j < codeImg.channels(); j++) {//按序修改像素的每个通道
				int bitNum = i * codeImg.channels() + j;//当前遍历的是文字的第几位比特
				if (bitNum >= bitSize) {//只取前16位
					break;
				}
				wch |= ((*it_code_begin)[j] & 0x0001) << bitNum; //将数据放入对应的比特位
			}
		}
		if (wch == 0xFFFE) {//读取到设定的停止符
			cout << endl << "读取到停止符0xFFFE！" << endl;
			break;
		}else if(it_code_begin == it_code_end){
			cout << endl << "已读取到图像末尾！" << endl;
		}else {
			wcout << wch;
			/*bitset<16> bitset_w(wch);
			wcout << L"中文字符：" << wch;
			cout << "  对应的编码：" << bitset_w << endl;*/
		}
	}
}

int main/*_CN2Pic*/(int argc, char** argv){
			setlocale(LC_ALL, "chs");
			CN2Pic("CN-Test.txt", "squirrel");
			cout<<"----------------------------文字存入图片完毕，重新加载图片并读出文字！！-------------------"<<endl;
			Pic2CN("squirrel");
			return EXIT_SUCCESS;
}
