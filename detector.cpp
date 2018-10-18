#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "undistortion.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

bool SortByX(const Point &v1, const Point &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致
{
    return v1.x < v2.x;//升序排列
}

int main() {
    int r = 15;
    vector<Point2f> pts;
    Mat origin = imread("origin.jpg");
    Mat img = undistortion(origin);

    //找到蓝色标识点,并用红圈圈出
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {

            int B_value = img.at<Vec3b>(i, j)[0];
            int G_value = img.at<Vec3b>(i, j)[1];
            int R_value = img.at<Vec3b>(i, j)[2];

            if (120 < B_value && B_value < 140 && 60 < G_value && G_value < 80 && 15 < R_value && R_value < 35) {
                Point center = Point(j, i);//注意圆心点定义应当是反的
                Point keyPT = Point(i, j);
                pts.push_back(keyPT);
                circle(img, center, r, Scalar(0, 0, 250));
                cout << i << "," << j << "," << B_value << "," << G_value << "," << R_value << endl;
            }

        }
    }

    //按y值大小排序
    sort(pts.begin(), pts.end(), SortByX);
    cout << pts << endl;

    //依据y方向差异，分离各点堆
    vector<Point2f> muPts;
    float temp_x = pts[0].x;
    int n = 0;
    float sum_x = 0;
    float sum_y = 0;
    for (int m = 0; m < pts.size(); m++) {
        if (pts[m].x - temp_x > 15) {
            cout << m - 1 << "号为本点堆边界:" << temp_x << "->" << pts[m].x << endl;
            double mu_X = sum_x / (m - n);
            double mu_Y = sum_y / (m - n);
            cout << "mu_X" << "=" << mu_X << "," << "mu_Y" << "=" << mu_Y << endl;
            CvPoint2D32f muPT = cvPoint2D32f(mu_X, mu_Y);
            muPts.push_back(muPT);
            n = m;
            sum_x = pts[m].x;
            sum_y = pts[m].y;
            temp_x = pts[m].x;
            continue;
        }
        sum_x = sum_x + pts[m].x;
        sum_y = sum_y + pts[m].y;
        temp_x = pts[m].x;
    }
    cout << pts.size() - 1 << "号为末点堆边界:" << temp_x << "->" << "END" << endl;
    float mu_X = sum_x / (pts.size() - n);
    float mu_Y = sum_y / (pts.size() - n);
    cout << "mu_X" << "=" << mu_X << "," << "mu_Y" << "=" << mu_Y << endl;
    CvPoint2D32f muPT = CvPoint2D32f(mu_X, mu_Y);
    muPts.push_back(muPT);
    cout << muPts << endl;

    //计算角度,单位：度
    double lineP1P2 = sqrt((double) ((muPts[0].x - muPts[1].x) * (muPts[0].x - muPts[1].x) +
                                     (muPts[0].y - muPts[1].y) * (muPts[0].y - muPts[1].y)));
    double lineP1P3 = sqrt((double) ((muPts[0].x - muPts[2].x) * (muPts[0].x - muPts[2].x) +
                                     (muPts[0].y - muPts[2].y) * (muPts[0].y - muPts[2].y)));
    double lineP2P3 = sqrt((double) ((muPts[1].x - muPts[2].x) * (muPts[1].x - muPts[2].x) +
                                     (muPts[1].y - muPts[2].y) * (muPts[1].y - muPts[2].y)));
    double angleP2 =
            acos((lineP1P2 * lineP1P2 + lineP2P3 * lineP2P3 - lineP1P3 * lineP1P3) / (2 * lineP1P2 * lineP2P3)) *
            180.0 / 3.1415926;
    cout << "三点的中间点角度为：" << angleP2 << endl;


    imshow("Blue_pts.jpg", img);
    imwrite("Blue_pts.jpg", img);
    waitKey(1000);
    return 0;
}