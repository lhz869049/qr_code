/**********************************************
* qr_rec.cpp
*  
*=====author====|====data====|===version===
*     luhz      | 2018-12-16 |   v1.0.2
*     luhz      | 2019-1-18  |   v1.0.3

*Abustract:  用来拼接提取出来的四个二维码小块
             使用zbar库来识别二维码
             
*  Note   :  最后传入识别部分的图片必须是灰度图
             或者是灰度图的二值图
***********************************************/
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "zbar.h"
using namespace std;
using namespace cv;
using namespace zbar;
//g++ xxx.cpp -o xxx `pkg-config opencv --cflags --libs` -lzbar

int main()
{
	//get picture
	Mat combine,combine1,combine2;
	Mat a=imread("codedede1.png",1);
	Mat b=imread("codedede2.png",1);
	Mat c=imread("codedede3.png",1);
	Mat d=imread("codedede4.png",1);
	

	threshold(a, a, 0, 255, THRESH_BINARY);
	threshold(b, b, 0, 255, THRESH_BINARY);
	threshold(c, c, 0, 255, THRESH_BINARY);
	threshold(d, d, 0, 255, THRESH_BINARY);

	cvtColor(a, a, CV_RGB2GRAY);
	cvtColor(b, b, CV_RGB2GRAY);
	cvtColor(c, c, CV_RGB2GRAY);
	cvtColor(d, d, CV_RGB2GRAY);

	//resize
 	resize(a,a,Size(200,200),0,0,INTER_LINEAR);
 	resize(b,b,Size(200,200),0,0,INTER_LINEAR);
 	resize(c,c,Size(200,200),0,0,INTER_LINEAR);
 	resize(d,d,Size(200,200),0,0,INTER_LINEAR);

 	//combine picture
	hconcat(a,b,combine1);//行排列   a+b=combine1
	hconcat(c,d,combine2);
	vconcat(combine1,combine2,combine);//列排列  combine1+combine2=combine
	namedWindow("Combine",CV_WINDOW_AUTOSIZE);
	imshow("Combine",combine);

	//adaptiveThreshold( combine, combine, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 21,0);
	//threshold(combine, combine, 30, 200.0, CV_THRESH_OTSU + CV_THRESH_BINARY_INV);
	//============ratation test===================//
	/*Point2f src_center(combine.rows / 2.0,combine.cols / 2.0);
	Mat warp_mat = getRotationMatrix2D(src_center,45,0.75);//得到旋转矩阵，逆时针旋转45度，尺度缩放为1，即保持原尺寸
	warpAffine(combine,combine,warp_mat,combine.size());*/

	//===============识别二维码=====================//
	ImageScanner scanner;      
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1); 
	int width1 = combine.cols;      
	int height1 = combine.rows;  //get cols and rows    
	uchar *raw = (uchar *)combine.data;         
	Image imageZbar(width1, height1, "Y800", raw, width1 * height1);        
	scanner.scan(imageZbar); //扫描条码    
	Image::SymbolIterator symbol = imageZbar.symbol_begin();  
	if(imageZbar.symbol_begin()==imageZbar.symbol_end())  
	{  
		cout<<"查询条码失败，请检查图片！"<<endl;  
	}  
	for(;symbol != imageZbar.symbol_end();++symbol)    
	{      
		cout<<"类型："<<endl<<symbol->get_type_name()<<endl<<endl;    
		cout<<"条码："<<endl<<symbol->get_data()<<endl<<endl;       
	}      
	namedWindow("Source Window",0);
	imshow("Source Window",combine);        
	waitKey();    
	imageZbar.set_data(NULL,0);  

	return 0;
}
