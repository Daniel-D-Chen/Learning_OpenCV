#include <opencv2/core/core.hpp>              
#include <opencv2/highgui/highgui.hpp>              
#include <opencv2/imgproc/imgproc.hpp>             
#include <iostream>            
using namespace std;
using namespace cv;

void TrackbarOnChange(int pos, void* userData);
void TrackbarOnChange2(int pos, void* userData);

static int blockSize = 5;
static int subtracted_C = 4;
static String dst1_win = "ȫ����ֵ";
static String dst2_win = "����Ӧ��ֵ";

int main_adaptive(int argc, char* argv[]) {
    //Mat img = imread("./Resources/sudoku.png",cv::IMREAD_GRAYSCALE);
    Mat img = imread("./Resources/mine/ticket1.jpg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "invaild image!!!";
        return 0;
    }
    //cv::cvtColor(img, img, COLOR_RGB2GRAY);//���У��Ҷȴ���
    //medianBlur(img, img, 5);//��ֵ�˲�
    Mat dst1,dst2;
    namedWindow("ԭͼ��", cv::WINDOW_AUTOSIZE);
    imshow("ԭͼ��", img);

    int threshold1 = 100;
    namedWindow(dst1_win, cv::WINDOW_AUTOSIZE);
    createTrackbar("��ֵ:", dst1_win, &threshold1, 255, TrackbarOnChange, (void*)&img);
    threshold(img, dst1, threshold1, 255, THRESH_BINARY);//��ֵ�ָ�
    imshow(dst1_win, dst1);

    int adaptiveMethod = 0;//�Զ���ֵ�ָ�����ֵ��
    namedWindow(dst2_win, cv::WINDOW_AUTOSIZE);
    createTrackbar("�Զ���ֵ����:", dst2_win, &adaptiveMethod, 1, TrackbarOnChange2, (void*)&img);
    GaussianBlur(img, dst2, Size(blockSize + 2, blockSize + 2), 0, 0);
    adaptiveThreshold(dst2, dst2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, subtracted_C);//�Զ���ֵ�ָ�,�����ֵ
    imshow(dst2_win, dst2);

    waitKey(0);
}

void TrackbarOnChange(int pos, void* userData) {
    Mat img = *((Mat*)userData);
    Mat dst1;
    cv::threshold(img, dst1, pos, 255, cv::THRESH_BINARY);
    imshow(dst1_win, dst1);
}

void TrackbarOnChange2(int pos, void* userData) {
    Mat img = *((Mat*)userData);
    Mat dst2;
    switch (pos)
    {
    case cv::ADAPTIVE_THRESH_MEAN_C: 
        adaptiveThreshold(img, dst2, 255, pos, THRESH_BINARY, blockSize, subtracted_C);//�Զ���ֵ�ָ�,�����ֵ
        break;
    case cv::ADAPTIVE_THRESH_GAUSSIAN_C:
        adaptiveThreshold(img, dst2, 255, pos, THRESH_BINARY, blockSize, subtracted_C); // �Զ���ֵ�ָ��˹����
        break;
    default:
        break;
    }
    imshow(dst2_win, dst2);
}