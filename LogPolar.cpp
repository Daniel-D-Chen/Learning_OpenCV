/*#include <opencv2/opencv.hpp>
#include <iostream>
#define SRC "src"
#define LOG_POLAR "log_polar"
#define INVERSE_LOG_POLAR "inverse_logPolar"

using namespace std;

int M_value = 20;
void TrackbarOnMChange(int pos, void* userData);

int main(int argc, char** argv) {
    cv::Mat src = cv::imread("./Resources/lena.jpg", cv::IMREAD_COLOR);
    cv::imshow(SRC, src);

    if (src.empty()) { cout << "Can not load " << endl; return -1; }

    cv::Mat dst(src.size(), src.type()), src2(src.size(), src.type());

    cv::logPolar(
        src,
        dst,
        cv::Point2f(src.cols * 0.5f, src.rows * 0.5f),
        M_value,
        cv::INTER_LINEAR | cv::WARP_FILL_OUTLIERS
    );
    cv::logPolar(
        dst,
        src2,
        cv::Point2f(src.cols * 0.5f, src.rows * 0.5f),
        M_value,
        cv::INTER_LINEAR | cv::WARP_INVERSE_MAP
    );
    cv::namedWindow(LOG_POLAR,cv::WINDOW_AUTOSIZE);
    cv::namedWindow(INVERSE_LOG_POLAR, cv::WINDOW_AUTOSIZE);
    cv::imshow(LOG_POLAR, dst);
    cv::imshow(INVERSE_LOG_POLAR, src2);


    cv::createTrackbar("logPolar_Trackbar", LOG_POLAR, &M_value, 80, TrackbarOnMChange,(void*)&src);

    cv::waitKey();

    return 0;
}

void TrackbarOnMChange(int pos, void* userData) {
    cv::Mat src = *((cv::Mat*)userData);
    cv::Mat dst(src.size(), src.type()), src2(src.size(), src.type());
    cv::logPolar(
        src,
        dst,
        cv::Point2f(src.cols * 0.5f, src.rows * 0.5f),
        pos,
        cv::INTER_LINEAR | cv::WARP_FILL_OUTLIERS
    );
    cv::logPolar(
        dst,
        src2,
        cv::Point2f(src.cols * 0.5f, src.rows * 0.5f),
        pos,
        cv::INTER_LINEAR | cv::WARP_INVERSE_MAP
    );
    cv::imshow(LOG_POLAR, dst);
    cv::imshow(INVERSE_LOG_POLAR, src2);
}*/

#include <opencv2/opencv.hpp>
#include <iostream>

#define LOG_POLAR "log_polar"
#define INVERSE_LOG_POLAR "inverse_logPolar"

using namespace std;
using namespace cv;

int main_LogPolar(int argc, char** argv) {
    Mat src = Mat::zeros(Size(400,400),CV_8UC3);
    Point2f center = Point(src.cols * 0.5f, src.rows * 0.5f);
    Scalar Green = Scalar(0, 255, 0), Blue = Scalar(255, 0, 0), Red = Scalar(0, 0, 255), White = Scalar(255, 255, 255);
    //line(src, center, Point(src.cols * 0.5f,0), Green,3);//Green Line
    //line(src, center, Point(src.cols * 0.5f, src.rows), Blue , 3);//Blue Line
    rectangle(src,Point(src.cols*0.1, src.rows*0.1),Point(src.cols*0.9, src.rows*0.9), Green,5);
    rectangle(src, Point(src.cols * 0.2, src.rows * 0.2), Point(src.cols * 0.8, src.rows * 0.8), Blue, 5);
    circle(src, center, 50, Red, 4);// Red circle
    circle(src, center, 100, White, 4);// White circle
    namedWindow("SRC", cv::WINDOW_AUTOSIZE);
    imshow("SRC", src);

    Mat dst = Mat(src.size(), src.type());
    logPolar(src, dst, cv::Point2f(src.cols * 0.5f, src.rows * 0.5f),50, cv::INTER_LINEAR | cv::WARP_FILL_OUTLIERS);
    namedWindow(LOG_POLAR, cv::WINDOW_AUTOSIZE);
    imshow(LOG_POLAR, dst);

    Mat src2 = Mat(src.size(), src.type());
    logPolar(
        dst,
        src2,
        center,
        50,
        cv::INTER_LINEAR | cv::WARP_INVERSE_MAP
    );
    cv::namedWindow(INVERSE_LOG_POLAR, cv::WINDOW_AUTOSIZE);
    cv::imshow(INVERSE_LOG_POLAR, src2);
    waitKey();
    return 0;
}