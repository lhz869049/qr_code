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
 * 2019/04/09 |2.0.1      |Lu Huaizhi |             *
 *                                                  *
 * *************************************************/


#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
/**@file detect_qrcode.h
 * @author luhz
 * @version 2.0.1
 * @date  2019-04-09
 * 
 * @brief
 * 定义各种函数
 * 
*/
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
    /**选取区域更加集中的区域
     * @param src : 输入的图片
    */
    Mat get_rect(Mat src);

    /**计算四点构成的两条直线的交点
     * @param A B ： 这两个点构成其中一条直线
     * @param C D ： 这两个点构成另外一条直线
     * @param return  两条直线的交点【point2f】
    */
    Point2f getCrossPoint(Point2f A, Point2f B, Point2f C, Point2f D);

    /**计算两点的距离
     * @param a b ：   两点
     * @param return  两点的距离【float】
    */
    float getDistance(Point2f a, Point2f b);

    /**三点围成的角度
     * @param cen ：  中心点，夹角点
     * @param first , second : 除去中点之外的点，顺序无所谓
     * @param return  ：  角度【float】
    */
    float angle(Point2f cen, Point2f first, Point2f second);

    /**寻找凸包
     * @param img ：  集中区域图片
     * @param return  ：  包含凸包的Mat
    */
    Mat get_hull(Mat img);

    /**寻找构成角度比较大的点
     * @param corner ：   角点检测出来的拐点
     * @param return  ：  构成角度比较大的点
    */
    vector<Point2f> find_bigger_corner(vector<Point2f> corner);

    /**寻找线的交点
     * @param big_corner ：   构成角度比较大的点
     * @param return  ：  返回这些点构的线的交点【有两个】
    */
    vector<Point2f> cacuate_cross_vector(vector<Point2f>big_corner);

    /**对corners按照方位进行排序
     * @param corners ：  交点集
     * @param return  ：  排序后的交点集
    */
    vector<Point2f> sort_point(vector<Point2f>corners);

    /**判断照片是否能识别
     * @param imageSource ： 输入的图片【灰度图或者二值图】
     * @param return  ：  能否识别
     * 需要用到zbar外部库
    */
    bool can_detect(Mat imageSource);

    /**判断照片是否能不相等
     * @param a,b,c,d ：  代表图片的下标
     * @param return  ：  是否相等
    */
    bool not_equal(int a, int b, int c, int d);

    /**组合四张图片并判断能否识别
     * @param src[4]  ：  处理后的图片四张
     * @param return  ：  组合后的图片
    */
    Mat combine_pic(Mat src[4]);

    /**识别的主要函数
     * @param a,b,c,d ：  输入的四张飞机拍摄图片
    */
    void detect(Mat a,Mat b,Mat c,Mat d);

};