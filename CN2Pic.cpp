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

static String ext = ".png";//ʹ��png��ʽͼƬ������ѹ��
static String path = "./Resources/mine/";//�ļ�·��

/*int main() {
	vector<Mat> channels;
	cv::split(srcImg, channels);
	channels[2] = Mat(channels[2].rows, channels[2].cols,CV_8UC1,Scalar(0));
	wchar_t wch;
	unsigned char bytes[2];//ÿ��unicode�����ַ�ռ�������ֽ�,�޸�����Ϊ�޷����ַ��ͣ����������������λ����
	fin.read((char*)bytes, 2);
	MatIterator_<uchar> it_begin = channels[1].begin<uchar>();
	MatIterator_<uchar> it_end = channels[1].end<uchar>();
	while (!fin.eof() && it_begin!= it_end && (it_begin+1)!= it_end) {
		(*it_begin++) = bytes[0];//ʹ�õ�����˳�򱣴��ֽ�
		(*it_begin++) = bytes[1];
		wch = (bytes[1] << 8) | bytes[0];//�ڶ����ֽ�Ϊ���ĵĸ�λ����һ���ֽ�Ϊ���ĵĵ�λ
		wcout << L"�����ַ���" << wch << endl;
		cout << "���ֽڶ�Ӧ�Ҷ�:" << (unsigned short int)bytes[0] << "  ���ֽڶ�Ӧ�Ҷ�:" << (unsigned short int)bytes[1] << endl;
		fin.read((char*)bytes, 2);
	}
	merge(channels, srcImg_HSV);
	cvtColor(srcImg_HSV, srcImg_HSV2BGR, COLOR_HSV2BGR);
	Mat imgChangeCmp;//��ɫ������BGRתHSV����ת��BGR�Ա�
	compare(srcImg, srcImg_HSV2BGR, imgChangeCmp, CMP_EQ);

	/*std::vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(0);    // ��ѹ��png.
	compression_params.push_back(cv::IMWRITE_PNG_STRATEGY);
	compression_params.push_back(cv::IMWRITE_PNG_STRATEGY_DEFAULT);

	imwrite("./Resources/mine/squirrel_code.jpg", srcImg);
	fin.close();
	//namedWindow("srcImg", WINDOW_AUTOSIZE);
	//imshow("srcImg", srcImg);

	Mat_<Vec3b> codeImg = imread("./Resources/mine/squirrel_code.jpg", IMREAD_COLOR);
	/*cvtColor(codeImg, codeImg, COLOR_BGR2HSV);
	vector<Mat> channels_code;//�����ͼ��ĸ�ͨ��
	cv::split(codeImg, channels_code);
	Mat imgSaveCmp;//����ǰ��Ա�
	compare(srcImg,codeImg, imgSaveCmp, CMP_EQ);
}*/

//���ı���Ӧ��unicode������һ���ر�����ͼ��ÿ�����ص����һλ�����ı�ĩβ���ֹͣ��0xFFFE
bool CN2Pic(String txtName,String picName) {
	ifstream fin;
	fin.open(path+txtName, ios::binary | ios::in);
	if (!fin.is_open()) {
		cout << "open file failed" << endl;
		return false;
	}else {
		fin.seekg(2, ios::beg);// ����unicode�ı���ͷ�������ֽ�0xFFFE������BOM�����ڱ�ʶunicode���룩
		if (fin.peek() == EOF) {
			cout << "file is empty." << endl;
			return false;
		}else {
			Mat_<Vec3b> srcImg = imread(path + picName + ext, IMREAD_COLOR);//����ԭͼ��
			long int num = 0;//�����ַ���
			int delta = 255 - 1;
			Mat clearMat = Mat(Size(srcImg.cols, srcImg.rows), CV_8UC3, Scalar(delta, delta, delta));
			bitwise_and(srcImg, clearMat, srcImg);//��ԭͼ���ÿ�����صĵ�0λ���
			wchar_t wch;
			fin.read((char*)&wch, 2); //��ȡ�ı���һ����
			int bitSize = sizeof(wchar_t) * 8;//ÿ��������ռλ��
			int pixSize = ceil((float)bitSize / srcImg.channels());//����ÿ��������ռ����������
			MatIterator_<Vec3b> it_begin = srcImg.begin();
			MatIterator_<Vec3b> it_end = srcImg.end();
			while (!fin.eof() && it_begin != it_end) {//��ȡȫ���ı��򱣴�ֱ�����һ����
				num++;
				wcout << wch;
				/*bitset<16> bitset_w(wch);
				wcout << L"�����ַ���" << wch;
				cout << "  ��Ӧ�ı��룺" << bitset_w << endl;*/
				for (int i = 0; i < pixSize && it_begin != it_end; i++, it_begin++) {//�������ֵ�ÿһλ
					for (int j = 0; j < srcImg.channels(); j++) {//�����޸����ص�ÿ��ͨ��
						int bitNum = i * srcImg.channels() + j;//��ǰ�����������ֵĵڼ�λ����
						if (bitNum >= bitSize) {
							break;
						}
						/*bitset<8> bitset_uBf((*it_begin)[j]);
						cout << "��" << bitNum << "λ�޸�ǰ��Ӧ����: " << bitset_uBf;*/
						(*it_begin)[j] += ((wch >> bitNum) & 0x0001);
						/*bitset<8> bitset_uAf((*it_begin)[j]);
						cout << " �޸ĺ��Ӧ����: " << bitset_uAf << endl;*/
					}
				}
				fin.read((char*)&wch, 2); //��ȡ�ı���һ����
			}
			if (it_begin != it_end) {//���ı�ĩβ���ֹͣ��0xFFFE
				wch = 0xFFFE;
				for (int i = 0; i < pixSize && it_begin != it_end; i++, it_begin++) {//�������ֵ�ÿһλ
					for (int j = 0; j < srcImg.channels(); j++) {//�����޸����ص�ÿ��ͨ��
						int bitNum = i * srcImg.channels() + j;//��ǰ�����������ֵĵڼ�λ����
						if (bitNum >= bitSize) {
							cout << endl << "ĩβ���ֹͣ��0xFFFE" << endl;
							break;
						}
						(*it_begin)[j] += ((wch >> bitNum) & 0x0001);
					}
				}
			}else {
				cout << endl << "ͼ�������Ѿ�����" << endl;
			}
			cout << "��������:"<< num << endl;
			fin.close();

			vector<int> compression_params;//ѹ������
			/*compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);  //ѡ��JPEG
			compression_params.push_back(100);//��0��100����ֵԽ������Խ�ã���Ĭ��ֵΪ95 */
			compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);  //ѡ��png
			compression_params.push_back(9);//��0��9,��ֵԽ�ߣ��ļ���СԽС��ѹ��ʱ��Խ����Ĭ��ֵΪ3
			imwrite(path + picName + "_code" + ext, srcImg, compression_params);
			cout << endl << "�������" << endl;
			waitKey(0);
			return true;
		}
	}
}

//ͼ��ÿ�����ص����һλƴ�ճ��ı��������
bool Pic2CN(String picName) {
	Mat_<Vec3b> codeImg = imread(path + picName + "_code" + ext, IMREAD_COLOR);
	if (codeImg.empty()) {
		cout << "Load Image Failure!!!" << endl;
		return false;
	}
	int bitSize = sizeof(wchar_t) * 8;//ÿ��������ռλ��
	int pixSize = ceil((float)bitSize / codeImg.channels());//����ÿ��������ռ����������
	MatIterator_<Vec3b> it_code_begin = codeImg.begin();
	MatIterator_<Vec3b> it_code_end = codeImg.end();
	while (it_code_begin != it_code_end) {//��ȡȫ���ı���ֱ�����һ����
		wchar_t wch = 0x0000;
		for (int i = 0; i < pixSize && it_code_begin != it_code_end; i++, it_code_begin++) {//�������ֵ�ÿһλ
			for (int j = 0; j < codeImg.channels(); j++) {//�����޸����ص�ÿ��ͨ��
				int bitNum = i * codeImg.channels() + j;//��ǰ�����������ֵĵڼ�λ����
				if (bitNum >= bitSize) {//ֻȡǰ16λ
					break;
				}
				wch |= ((*it_code_begin)[j] & 0x0001) << bitNum; //�����ݷ����Ӧ�ı���λ
			}
		}
		if (wch == 0xFFFE) {//��ȡ���趨��ֹͣ��
			cout << endl << "��ȡ��ֹͣ��0xFFFE��" << endl;
			break;
		}else if(it_code_begin == it_code_end){
			cout << endl << "�Ѷ�ȡ��ͼ��ĩβ��" << endl;
		}else {
			wcout << wch;
			/*bitset<16> bitset_w(wch);
			wcout << L"�����ַ���" << wch;
			cout << "  ��Ӧ�ı��룺" << bitset_w << endl;*/
		}
	}
}

int main/*_CN2Pic*/(int argc, char** argv){
			setlocale(LC_ALL, "chs");
			CN2Pic("CN-Test.txt", "squirrel");
			cout<<"----------------------------���ִ���ͼƬ��ϣ����¼���ͼƬ���������֣���-------------------"<<endl;
			Pic2CN("squirrel");
			return EXIT_SUCCESS;
}
