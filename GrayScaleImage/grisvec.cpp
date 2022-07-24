#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main( )
{
  char* salida="gris.pgm";
  FILE *gris;
  int i,j,aux;
  int **ptr;

  // load the image
  Mat image = imread("../../grisesvec/lena.jpg"); // add route to Read the file

  // check if the image is loaded successful
  if (image.empty())
  {
    printf("No image data \n");
    return -1;
  }

   ptr=(int**)calloc(image.rows,sizeof(int*));
    for (int i=0; i<image.rows; i++)
        ptr[i]=(int*)calloc(image.cols,sizeof(int*));

    printf("cols %d\n",image.cols);
    printf("rows %d",image.rows);

  //access to RGB the color image
  for(i=0;i<image.rows;i++){
    for(j=0;j<image.cols;j++){
      Vec3b pixel=image.at<Vec3b>(i,j);

            int R = pixel[0];
            int G = pixel[1];
            int B = pixel[2];
      *(*(ptr+i)+j)=(R*0.3)+(G*0.59)+(B*0.11);
    }
  }

    gris=fopen(salida,"w");
    fprintf(gris, "P2\n");
	fprintf(gris, "%d %d\n",image.cols,image.rows);
	fprintf(gris, "255\n");

    for(i=0;i<image.rows;i++){
      for(j=0;j<image.cols;j++){
        aux=*(*(ptr+i)+j);
        fprintf(gris,"%d ",aux);
     }
    }
      fclose(gris);

     for (int i=0; i<image.rows; i++)
        free(ptr[i]);

     Mat griss = imread("../../grisesvec/gris.pgm");
      imshow("Gris ", griss);
      imshow("color",image);
      waitKey(0);

    return 0;
}
