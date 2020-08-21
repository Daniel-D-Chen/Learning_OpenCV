#include <opencv2/core/core.hpp>              
#include <opencv2/highgui/highgui.hpp>              
#include <opencv2/imgproc/imgproc.hpp>             
#include <iostream>            
using namespace std;
using namespace cv;

void TrackbarOnChange(int pos, void* userData);
void TrackbarOnChange2(int pos, void* userData);

int main_ostu(int argc, char* argv[]) {
    Mat img = imread("./Resources/pic2.png", cv::IMREAD_GRAYSCALE);
    //Mat img = imread("./Resources/mine/ticket1.jpg", IMREAD_GRAYSCALE);
    if (img.empty()) {
        cout << "invaild image!!!";
        return 0;
    }
    Mat dst1;
    Mat dst2;
    Mat dst3;
    threshold(img, dst1, 127, 255, THRESH_BINARY);
    threshold(img, dst2, 0, 255, THRESH_OTSU);//最大类间方差法分割 Otsu algorithm to choose the optimal threshold value
    Mat img2 = img.clone();
    medianBlur(img2, img2, 3);
    //GaussianBlur(img2, img2, Size(3, 3), 0);//高斯滤波去除小噪点
    threshold(img2, dst3, 0, 255, THRESH_OTSU);

    Mat element = getStructuringElement(cv::MORPH_RECT, Size(3, 3), Point(-1, -1)),dst_MORPH;
    cv::morphologyEx(dst3, dst_MORPH, cv::MORPH_OPEN, element);//形态学开操作
    imshow("GaussianBlur OTSU dst_MORPH", dst_MORPH);


    imshow("BINARY dst1", dst1);
    imshow("OTSU dst2", dst2);
    imshow("GaussianBlur", img2);
    imshow("GaussianBlur OTSU dst3", dst3);
    imshow("original img", img);
    waitKey(0);
}