/****************************************************
 *  *
 *                                                  *
 * @file    detect_qrcode.hpp                       *
 * @brief   detect the qrcode                       *
 * @author  Lu Huaizhi                              *
 * @email   luhzh5@mail2.sysu.edu.cn                *
 * @date    2019-04-09                              *
 *                                                  *
 * -------------------------------------------------*
 * Remark   : Description                           *
 * -------------------------------------------------*
 * Change History :                                 *
 * <Date>     |<Version>  |<Author>   |<Description>*
 * 2019/04/09 |2.1.0      |Lu Huaizhi |             *
 *                                                  *
 * *************************************************/


#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>
#include <math.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <zbar.h>  

using namespace cv;
using namespace std;
using namespace zbar;

class QR_detecter{
public:
    Mat get_rect(Mat src);

    Point2f getCrossPoint(Point2f A, Point2f B, Point2f C, Point2f D);

    float getDistance(Point2f a, Point2f b);

    float angle(Point2f cen, Point2f first, Point2f second);

    Mat get_hull(Mat img);

    vector<Point2f> find_bigger_corner(vector<Point2f> corner);

    vector<Point2f> cacuate_cross_vector(vector<Point2f>big_corner);

    vector<Point2f> sort_point(vector<Point2f>corners);

    bool can_detect(Mat imageSource);

    bool not_equal(int a, int b, int c, int d);

    Mat combine_pic(Mat src[4]);

    void detect(Mat a,Mat b,Mat c,Mat d);

};