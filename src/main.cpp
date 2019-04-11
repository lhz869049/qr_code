/**@file main.cpp
 * @author luhz
 * @version 2.0.1
 * @date  2019-04-09
 * 
 * @brief
 * 这是主函数用来调用实现功能
 * 
*/
#include "detect_qrcode.h"

int main()
{
	//! picture的顺序无所谓
	Mat a = imread("../picture/th2.jpg");
	Mat b = imread("../picture/th4.jpg");
	Mat c = imread("../picture/th1.jpg");
	Mat d = imread("../picture/th3.jpg");

	imshow("a",a);
	imshow("b",b);
	imshow("c",c);
	imshow("d",d);

	//! detect_qrcode.h定义的类
    QR_detecter qr;
	qr.detect(a, b, c, d);

	waitKey();
	return 0;
}