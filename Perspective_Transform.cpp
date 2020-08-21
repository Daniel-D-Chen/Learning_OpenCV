// Example 11-2. Code for perspective transformation
// Compute a perspective transformation between the 4 src control points
// in srcQuad to 4 dst control points in dstQuad and apply it the image.

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main_PerspectiveTransform(int argc, char** argv) {

    cv::Mat src = cv::imread("./Resources/opencv-logo.png", cv::IMREAD_COLOR);
    if (src.empty()) { cout << "Can not load " << endl; return -1; }

    cv::Point2f srcQuad[] = {
      cv::Point2f(0, 0),                   // src Top left
      cv::Point2f(src.cols - 1, 0),          // src Top right
      cv::Point2f(src.cols - 1, src.rows - 1), // src Bottom right
      cv::Point2f(0, src.rows - 1)           // src Bottom left
    };

    cv::Point2f dstQuad[] = {
      cv::Point2f(src.cols * 0.05f, src.rows * 0.33f),// 左上
      cv::Point2f(src.cols * 0.9f, src.rows * 0.25f),// 右上
      cv::Point2f(src.cols * 0.8f, src.rows * 0.9f),//右下
      cv::Point2f(src.cols * 0.2f, src.rows * 0.7f)//左下
    };

    // COMPUTE PERSPECTIVE MATRIX
    //
    cv::Mat warp_mat = cv::getPerspectiveTransform(srcQuad, dstQuad);
    cv::Mat dst;
    cv::warpPerspective(src, dst, warp_mat, src.size(), cv::INTER_LINEAR,
        cv::BORDER_CONSTANT, cv::Scalar());

    for (int i = 0; i < 4; i++)
        cv::circle(dst, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);

    cv::imshow("Perspective Transform Test", dst);
    cv::waitKey();
    return 0;
}