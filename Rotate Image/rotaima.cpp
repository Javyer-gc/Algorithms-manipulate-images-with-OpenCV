#include<iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int **gris(int**,Mat);

int main(){

  int **ptr; int **auxi;
  int i,j;
  double n=0,pi=3.141592654;

  Mat image = imread("../../rotarima/lena.jpg");

  if (image.empty())
  {
    printf("No se cargo la imagen \n");
    return -1;
  }

  cout<<"Ingresa angulo: ";
  cin>>n;
  cout<<n<<endl;
  n=(-1*n*pi)/180;

  ptr=(int**)calloc(image.rows,sizeof(int*));
  for (int i=0; i<image.rows; i++)
  ptr[i]=(int*)calloc(image.cols,sizeof(int*));
                                            //Pasar a escala de grises
  gris(ptr,image);

     //Valores maximos de la imagen

     //float valorx[2];  float valory[2];
     //valorx[0]=image.cols*cos(n);
     //valorx[1]=image.rows*cos(n);
     //valory[0]=image.cols*sin(n);
     //valory[1]=image.rows*sin(n);
     //int tamx=valorx[0]+valorx[1];
     //int tamy=valory[0]+valory[1];

   int tamx, tamy;
   if(image.cols>image.rows){
      tamx=image.cols;
      tamy=image.cols;
     }
   else{
        tamx=image.rows;
        tamy=image.rows;
        }

   auxi=(int**)calloc(tamy,sizeof(int*));
   for (int i=0; i<tamy; i++)
   auxi[i]=(int*)calloc(tamx,sizeof(int*));
                                                //ROTAR
   for(i=0; i< tamy; i++){
     for(j=0; j< tamx ; j++)
     {
      int  a=((i-tamx/2)*cos(n)-(j-tamy/2)*sin(n)+((tamx)/2));
      int  b=((i-tamx/2)*sin(n)+(j-tamy/2)*cos(n)+((tamy)/2));

      if (( a>=0 && a<image.rows) && (b>=0 && b<image.cols) )
             auxi[i][j] = ptr[a][b];
     }
  }


   for(int i = 0; i < image.rows; i++)delete [] ptr[i];
   delete [] ptr;
   ptr=NULL;
                                    //Creacion archivo .pgm
   FILE *archivo;
   archivo=fopen("../../rotarima/Rotada.pgm","wb");
   fprintf(archivo, "P2\n %d %d\n 255\n",tamx,tamy);

   for(i=0;i<tamy;i++){
      for(j=0;j<tamx;j++){
        fprintf(archivo," %d ",auxi[i][j]);
      }
   }
   fclose(archivo);

  //for(int i = 0; i < image.rows; i++)delete [] auxi[i];
  //delete [] auxi;
  // auxi=NULL;

  Mat nueva= imread("../../rotarima/Rotada.pgm");
  imshow("Rotada ", nueva);
  imshow("Original",image);
  waitKey(0);

  return 0;
}

int **gris(int** ptr, Mat image){
  int v=0,m=0,f=0,c=0;
  int *R; int *G; int *B;

  cout<<endl<<"Imagen "<<endl;
  printf("Ancho: %d Altura: %d  \n",image.cols,image.rows);

  R=(int*)calloc(image.cols*image.rows,sizeof(int));
  G=(int*)calloc(image.cols*image.rows,sizeof(int));
  B=(int*)calloc(image.cols*image.rows,sizeof(int));

 for(int i=0;i<image.rows;i++){
    for(int j=0;j<image.cols*3;j++){

    uchar pixel =image.at<uchar>(i,j);

    if(c==0){ R[v]=pixel; v++; }

    if(c==1){ G[m]=pixel; m++; }

    if(c==2){ B[f]=pixel; f++; }

    if(c==2) c=-1;
     c++;
    }
 } v=0;

  for(int i=0;i<image.rows;i++){
    for(int j=0;j<image.cols;j++){
        ptr[i][j]=(R[v]*0.3)+(G[v]*0.59)+(B[v]*0.11);
        v++;
       }
  }
  free(R); free(G); free(B);

  cout<<"Pixeles: "<<v<<endl;
  return ptr;
}
