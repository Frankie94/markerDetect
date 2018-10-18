#include "undistortion.h"
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat undistortion(Mat frame){
    Mat frame1 = frame.clone();

    Mat camera_matrix = Mat(3, 3, CV_32FC1);
    Mat distortion_coefficients;

    FileStorage file_storage("out_camera_data.xml", FileStorage::READ);
    file_storage["camera_matrix"] >> camera_matrix;
    file_storage["distortion_coefficients"] >> distortion_coefficients;
    file_storage.release();

//    cout  << camera_matrix << endl;
//    cout  << distortion_coefficients << endl;
    undistort(frame, frame1, camera_matrix, distortion_coefficients);

    imshow("original", frame);
    imshow("distorted", frame1);
    imwrite("distorted.jpg",frame1);
//    waitKey(5000);
    return frame1;
}