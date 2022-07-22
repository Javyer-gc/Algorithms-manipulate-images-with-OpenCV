// OpenCV Code of rotating an image about its Centre
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
 const float pi=3.14;
 int x,y;
 Mat src1,src2;

 //Take the Input Image in src1
 src1 = imread("lobo.jpg",CV_LOAD_IMAGE_COLOR);
 if( !src1.data ) { printf("Error loading src1 \n"); return -1;}

 src2 = Mat::zeros(src1.rows,src1.cols, CV_8UC3);

 //Angle by which to rotate an Image
 //for (int a=0 ; a<360 ; a++)
 //{
 //Logic of Image Rotation
 int a=270;
 for (int i=0; i<src1.cols ; i++){
 for (int j=0 ; j<src1.rows ; j++)
 {
   //x'=(x-p)Cos(ϴ')-(y-q)Sin(ϴ')+p
   x=((i-src1.cols/2)*cos(a*pi/180)-(j-src1.rows/2)*sin(a*pi/180)+src1.cols/2);
   //y'=(y-q)Cos(ϴ')+(x-p)Sin(ϴ')+q
   y=((i-src1.cols/2)*sin(a*pi/180)+(j-src1.rows/2)*cos(a*pi/180)+src1.rows/2);

   if((x>=0 && x<src1.cols) && (y>=0 && y<src1.rows)){
  Vec3b color1 = src1.at<Vec3b>(Point(i,j));
  Vec3b color2 = src2.at<Vec3b>(Point(i,j));
  color2.val[0] = color1.val[0];
  color2.val[1] = color1.val[1];
  color2.val[2] = color1.val[2];
  src2.at<Vec3b>(Point(x,y)) = color2;
   }
    }
 }
waitKey(50);
namedWindow("Rotated Image",CV_WINDOW_AUTOSIZE);
imshow("Rotated Image", src2);
namedWindow("Original Image",CV_WINDOW_AUTOSIZE);
imshow("Original Image", src1);
string name="h";
imwrite("Neare" + name + ".jpg", src2);
 //}
 waitKey(0);
 return 0;
}
