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
    QR_detecter qr;
	qr.detect(a, b, c, d);
	waitKey();
	return 0;
}