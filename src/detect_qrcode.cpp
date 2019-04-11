/**@file detect_qrcode.cpp
 * @author luhz
 * @version 2.0.1
 * @date  2019-04-09
 * 
 * @brief
 * 实现detect_qrcoded的函数
 * 
*/
#include "detect_qrcode.h"

double these = 0.03;
/**选取区域更加集中的区域
 * @param src : 输入的图片
*/
Mat QR_detecter::get_rect(Mat src) {
	Mat graysrc, thessrc;
	cvtColor(src, graysrc, CV_BGR2GRAY);
	//此处阈值的选取很重要，可以弄个滑块  80-255   
	threshold(graysrc, thessrc, 80, 255.0, CV_THRESH_BINARY);
	GaussianBlur(thessrc, thessrc, Size(5, 5), 0, 0);  //高斯滤波

	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3)); //第一个参数MORPH_RECT表示矩形的卷积核
	//膨胀操作
	dilate(thessrc, thessrc, element);   //膨胀

	Canny(thessrc, thessrc, 30, 200, 3);

	//==========找最大面积的边界
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(thessrc, contours, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE);
	double contour_area_temp = 0, contour_area_max = 0;
	int max_size = 0;
	for (int i = 0; i < contours.size(); i++) {
		contour_area_temp = fabs(contourArea(contours[i]));
		if (contour_area_max < contour_area_temp) {
			contour_area_max = contour_area_temp;
			max_size = i;
		}
	}

	//=============最大边界的最小外接矩形
	RotatedRect box = minAreaRect(contours[max_size]);
	Point2f four_cornor[4];
	box.points(four_cornor);
	//for (int i = 0; i < 4; i++)  //把RotatedRect画出来
	//{
	//	cout << four_cornor[i] << endl;
	//	line(src, four_cornor[i], four_cornor[(1 + i) % 4], Scalar(255, 255, 255), 2, 8, 0);
	//}

	Rect rect(four_cornor[1].x, four_cornor[1].y,
		four_cornor[3].x - four_cornor[1].x, four_cornor[0].y - four_cornor[1].y);
	Mat maskk = src(rect);
	resize(maskk, maskk, Size(200, 200));
	return maskk;
}

/**计算四点构成的两条直线的交点
 * @param A B ： 这两个点构成其中一条直线
 * @param C D ： 这两个点构成另外一条直线
 * @param return  两条直线的交点【point2f】
*/
Point2f QR_detecter::getCrossPoint(Point2f A, Point2f B, Point2f C, Point2f D){
	if (A == B || A == C || A == D || B == C || B == D || C == D)
		return Point2f(0, 0);
	else {
		double ka, kb;
		ka = (double)(A.y - B.y) / (double)(A.x - B.x);
		kb = (double)(C.y - D.y) / (double)(C.x - D.x);
		
		Point2f crossPoint;
		crossPoint.x = float(int((ka*B.x - B.y - kb * D.x + D.y) / (ka - kb)));
		crossPoint.y = float(int((ka*kb*(B.x - D.x) + ka * D.y - kb * B.y) / (ka - kb)));
		if (crossPoint.x < 0 || crossPoint.y < 0)
			return Point2f(0, 0);
		else
			return crossPoint;
	}
}

/**计算两点的距离
 * @param a b ：   两点
 * @param return  两点的距离【float】
*/
float QR_detecter::getDistance(Point2f a, Point2f b) {
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

/**三点围成的角度
 * @param cen ：  中心点，夹角点
 * @param first , second : 除去中点之外的点，顺序无所谓
 * @param return  ：  角度【float】
*/
float QR_detecter::angle(Point2f cen, Point2f first, Point2f second){
	const float My_PI = 3.1415926535897;

	float ma_x = first.x - cen.x;
	float ma_y = first.y - cen.y;
	float mb_x = second.x - cen.x;
	float mb_y = second.y - cen.y;
	float v1 = (ma_x * mb_x) + (ma_y * mb_y);
	float ma_val = sqrt(ma_x * ma_x + ma_y * ma_y);
	float mb_val = sqrt(mb_x * mb_x + mb_y * mb_y);
	float cosM = v1 / (ma_val * mb_val);
	float angleAMB = acos(cosM) * 180 / My_PI;

	return angleAMB;
}

/**寻找凸包
 * @param img ：  集中区域图片
 * @param return  ：  包含凸包的Mat
*/
Mat QR_detecter::get_hull(Mat img){
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat gray, the;
	cvtColor(img, gray, CV_BGR2GRAY);
	threshold(gray, the, 50, 255, CV_THRESH_BINARY);
	Mat mid;
	Canny(the, mid, 30, 255, 3);
	findContours(the, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	double contour_area_temp = 0, contour_area_max = 0;
	int max_size = 0;
	vector<vector<Point> >hull(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		convexHull(Mat(contours[i]), hull[i]);
	}
	//！ 计算面积最大的凸包
	Mat b = Mat::zeros(the.size(), CV_8UC3);
	for (int i = 0; i < contours.size(); i++) {
		contour_area_temp = fabs(contourArea(hull[i]));
		if (contour_area_max < contour_area_temp) {
			contour_area_max = contour_area_temp;
			max_size = i;
		}
	}
	drawContours(b, hull, max_size, Scalar(255, 255, 255), 1, 8, vector<Vec4i>(), 0);
	return b;
}

/**寻找构成角度比较大的点
 * @param corner ：   角点检测出来的拐点
 * @param return  ：  构成角度比较大的点
*/
vector<Point2f> QR_detecter::find_bigger_corner(vector<Point2f> corner) {
	vector<Point2f> big_corner;
	vector<Point2f>::iterator at1, at2;
	//！ big_angle从107开始，可以适当改变
	float big_angle = 107;
	do{
		//判断角度大于110
		for (int i = 0; i < corner.size(); i++)
		{
			for (int j = i + 1; j < corner.size(); j++)
			{
				for (int k = j + 1; k < corner.size(); k++)
				{
					if (angle(corner[i], corner[j], corner[k]) > big_angle)
					{
						big_corner.push_back(corner[k]);
						big_corner.push_back(corner[j]);
						big_corner.push_back(corner[i]);
					}
					if (angle(corner[j], corner[i], corner[k]) > big_angle)
					{
						big_corner.push_back(corner[k]);
						big_corner.push_back(corner[j]);
						big_corner.push_back(corner[i]);
					}
					if (angle(corner[k], corner[j], corner[i]) > big_angle)
					{
						big_corner.push_back(corner[k]);
						big_corner.push_back(corner[j]);
						big_corner.push_back(corner[i]);
					}
				}
			}
		}
		//剔除重复元素
		for (at1 = ++big_corner.begin(); at1 != big_corner.end();)
		{
			at2 = find(big_corner.begin(), at1, *at1);
			if (at2 != at1)
				at1 = big_corner.erase(at1);
			else
				at1++;
		}
		big_angle = big_angle + 1;
	}while(big_corner.size()!=4);

	return big_corner;
}

/**寻找线的交点
 * @param big_corner ：   构成角度比较大的点
 * @param return  ：  返回这些点构的线的交点【有两个】
*/
vector<Point2f> QR_detecter::cacuate_cross_vector(vector<Point2f>big_corner) {
	vector<Point2f>::iterator it, it1;
	vector<Point2f> tmp;
	Point2f tp;
	//计算交点存在tmp中
	for (int i = 0; i < big_corner.size(); i++) {
		for (int j = 0; j < big_corner.size(); j++) {
			for (int k = 0; k < big_corner.size(); k++) {
				for (int l = 0; l < big_corner.size(); l++) {
					tp = getCrossPoint(big_corner[i], big_corner[j], big_corner[k], big_corner[l]);
					if (tp != big_corner[i] && tp != big_corner[j] && tp != big_corner[k] && 
						tp != big_corner[l] && tp != Point2f(0, 0) && tp.x<230&&tp.y<230) 
						//！tp.x<230和图片的size挂钩，为了防止计算的点超出图片范围
					{
						tmp.push_back(tp);
					}
				}
			}
		}
	}
	//去除重复的元素
	for (it = ++tmp.begin(); it != tmp.end();)
	{
		it1 = find(tmp.begin(), it, *it);
		if (it1 != it)
			it = tmp.erase(it);
		else
			it++;
	}
	return tmp;
}

/**对corners按照方位进行排序
 * @param corners ：  交点集
 * @param return  ：  排序后的交点集
*/
vector<Point2f> QR_detecter::sort_point(vector<Point2f>corners) {
	//！计算四点的中心点
	Point2f center = Point(100,100);
	vector<Point2f> sort_corners(4);
	for (int i = 0; i < corners.size(); i++)
	{
		center.x += corners[i].x;
		center.y += corners[i].y;
	}
	center.x = center.x / corners.size();
	center.y = center.y / corners.size();
	//！根据点的位置来确定顺序
	for (int i = 0; i < corners.size(); i++) {
		if (corners[i].x > center.x&&corners[i].y < center.y)
			sort_corners.insert(sort_corners.begin(), corners[i]);
		else if (corners[i].x < center.x&&corners[i].y > center.y)
			sort_corners.insert(sort_corners.begin() + 1, corners[i]);
		else if (corners[i].x < center.x&&corners[i].y < center.y)
			sort_corners.insert(sort_corners.begin() + 2, corners[i]);
		else
			sort_corners.insert(sort_corners.begin() + 3, corners[i]);


		vector<Point2f>::iterator it;
		for (it = ++sort_corners.begin(); it != sort_corners.end();)
		{
			if (*it == Point2f(0, 0)) {
				it = sort_corners.erase(it);
				if (sort_corners.size() == 4)
					break;
			}
			else
				it++;
		}
	}
	return sort_corners;
}

/**判断照片是否能识别
 * @param imageSource ： 输入的图片【灰度图或者二值图】
 * @param return  ：  能否识别
 * 需要用到zbar外部库
*/
bool QR_detecter::can_detect(Mat imageSource){
	ImageScanner scanner;      
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1); 
	int width1 = imageSource.cols;      
	int height1 = imageSource.rows;      
	uchar *raw = (uchar *)imageSource.data;         
	Image imageZbar(width1, height1, "Y800", raw, width1 * height1);        
	scanner.scan(imageZbar); //扫描条码    
	Image::SymbolIterator symbol = imageZbar.symbol_begin();
	if(imageZbar.symbol_begin()==imageZbar.symbol_end())  
	{  
		return false;
	}  
	for(;symbol != imageZbar.symbol_end();++symbol)    
	{ 
		cout<<"类型："<<endl<<symbol->get_type_name()<<endl<<endl;    
		cout<<"条码："<<endl<<symbol->get_data()<<endl<<endl;       
		return true;
	}            
	imageZbar.set_data(NULL,0);   
	return true;
}

/**判断照片是否能不相等
 * @param a,b,c,d ：  代表图片的下标
 * @param return  ：  是否相等
*/
bool QR_detecter::not_equal(int a, int b, int c, int d){
	if((a-b!=0)&&(a-c!=0)&&(a-d!=0)&&(b-c!=0)&&(b-d!=0)&&(c-d!=0))
		return true;
	else
		return false;
}

/**组合四张图片并判断能否识别
 * @param src[4]  ：  处理后的图片四张
 * @param return  ：  组合后的图片
*/
Mat QR_detecter::combine_pic(Mat src[4]){
	Rect rec1(0, 0, 210, 210), rec2(10, 0, 210, 210), rec3(0, 10, 210, 210), rec4(10, 10, 210, 210);
	Mat imageSource,combine1,combine2;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				for(int l=0;l<4;l++){
					if(not_equal(i,j,k,l)){
						//！ 剪切图片并合并
						Mat a = src[i];
						Mat b = src[j];
						Mat c = src[k];
						Mat d = src[l];
						a = a(rec1);
						b = b(rec2);
						c = c(rec3);
						d = d(rec4);
						hconcat(a,b,combine1);//行排列   a+b=combine1
						hconcat(c,d,combine2);
						vconcat(combine1,combine2,imageSource);//列排列  combine1+combine2=combine
						cvtColor(imageSource,imageSource,CV_BGR2GRAY);
						threshold(imageSource, imageSource, 100, 255, CV_THRESH_BINARY);
						if(can_detect(imageSource))
							return imageSource;
					}
				}
			}
		}
	}
	return imageSource;

}

/**识别的主要函数
 * @param a,b,c,d ：  输入的四张飞机拍摄图片
*/
void QR_detecter::detect(Mat a,Mat b,Mat c,Mat d) {
	Mat src[4],out_put[4];
	src[0] = a;
	src[1] = b;
	src[2] = c;
	src[3] = d;
	
	for (int kk = 0; kk < 4; kk++) {
		//!这个size需要具体测试
		resize(src[kk], src[kk], Size(src[kk].cols / 2, src[kk].cols / 2));

		Mat rough_pic, accurate_pic;
		rough_pic = get_rect(src[kk]);

		//扩充图片
		Mat img2 = Mat::zeros(220, 220, rough_pic.type());
		//bitwise_not(img2, img2); //白背景
		Mat roi_img = img2(Rect(10, 10, 200, 200));
		Mat mask;
		cvtColor(rough_pic, mask, CV_BGR2GRAY);

		rough_pic.copyTo(roi_img, mask);

		Mat b = get_hull(img2);
		//imshow("sah", b);

		//====判断是否符合交点要求

		GaussianBlur(b, b, Size(9, 11), 0, 0);
		//blur(b, b, Size(5, 5));
		vector<Point2f>corners;
		Mat graypic;
		cvtColor(b, graypic, CV_BGR2GRAY);
		Mat dst = b.clone();
		goodFeaturesToTrack(graypic, corners, 5, 0.005, 15);
		// while(corners.size()!=5){
		// 	these = these + 0.05;
		// 	goodFeaturesToTrack(graypic, corners, 6, these, 15);
		// 	cout<<these<<endl;
		// }
		for (int i = 0; i < corners.size(); i++) {
			circle(dst, corners[i], 2, Scalar(255, 0, 233), 2);
		}
		//imshow("dst",dst);
		vector<Point2f> big_corner = find_bigger_corner(corners);
		vector<Point2f>::iterator it, it1;
		Point2f another_po;

		//find diff
		for (it = corners.begin(); it != corners.end(); it++)
		{
			if (find(big_corner.begin(), big_corner.end(), *it) == big_corner.end())
				another_po = *it;
		}
		vector<Point2f> tmp = cacuate_cross_vector(big_corner);
		//找到边界点
		float dis_max = 0;
		Point2f real_cross;
		for (int i = 0; i < tmp.size(); i++)
		{
			if (dis_max < getDistance(another_po, tmp[i]))
			{
				dis_max = getDistance(another_po, tmp[i]);
				real_cross = tmp[i];
			}
		}
		//! 删掉非角落的点
		int r = 0;
		dis_max = 10000;
		for (int i = 0; i < corners.size(); i++)
		{
			if (dis_max > getDistance(real_cross, corners[i]))
			{
				dis_max = getDistance(real_cross, corners[i]);
				r = i;
			}
		}
		corners.erase(corners.begin() + r);

		dis_max = 10000;
		for (int i = 0; i < corners.size(); i++)
		{
			if (dis_max > getDistance(real_cross, corners[i]))
			{
				dis_max = getDistance(real_cross, corners[i]);
				r = i;
			}
		}
		corners.erase(corners.begin() + r);

		//! 把计算出的交点push进去
		corners.push_back(real_cross);

		//! 对点进行方位上的排序
		vector<Point2f> sort_corners = sort_point(corners);

		//! 透视变换
		Mat warp_img = Mat::zeros(img2.rows, img2.cols, img2.type());
		Point2f srcTri[4], dstTri[4];
		for (int i = 0; i < sort_corners.size(); i++) {
			srcTri[i] = sort_corners[i];
			circle(b, sort_corners[i], 2, Scalar(255, 0, 233), 2);
		}
		dstTri[2] = Point(0, 0);
		dstTri[0] = Point(warp_img.cols, 0);
		dstTri[3] = Point(warp_img.cols, warp_img.rows);
		dstTri[1] = Point(0, warp_img.rows);

		Mat warp_mat(2, 3, CV_32FC1);

		warp_mat = getPerspectiveTransform(srcTri, dstTri);
		warpPerspective(img2, warp_img, warp_mat, warp_img.size());

		out_put[kk] = warp_img;
	}

	Mat combine = combine_pic(out_put);
	imshow("combine",combine);
	// imshow("src[0]", src[0]);
	// imshow("src[1]", src[1]);
	// imshow("src[2]", src[2]);
	// imshow("src[3]", src[3]);
	// imshow("out_put[0]", out_put[0]);
	// imshow("out_put[1]", out_put[1]);
	// imshow("out_put[2]", out_put[2]);
	// imshow("out_put[3]", out_put[3]);
	waitKey();
}