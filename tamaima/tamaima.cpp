#include<iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){

  int **ptr; int **auxi;
  int i,j,opc;
  long c=0;
  float n=0;

  Mat image = imread("../../tamaima/lena.jpg");

  if (image.empty())
  {
    printf("No image data \n");
    return -1;
  }
  char p=164;
  cout<<"1)Aumentar imagen"<<endl<<"2)Disminuir imagen"<<endl;
  cin>>opc;

  if(opc==1){
     cout<<"Para aumentar tama"<<p<<"o ingrese valores enteros mayores a 1 "<<endl;
     cout<<"ingrese escalado: ";
     cin>>n;
  }
  else{
     cout<<"Para disminuir su tama"<<p<<"o ingrese valores enteros mayores a 1: "<<endl;
     cout<<"Ingrese escalado: ";
     cin>>n;
     if(n==1);
     n=1/n;
  }

  cout<<endl<<"Imagen original"<<endl;
  printf("cols %d\n",image.cols);
  printf("rows %d\n",image.rows);
                                            //Reservar memoria
  ptr=(int**)calloc(image.rows,sizeof(int*));
  for (int i=0; i<image.rows; i++)
  ptr[i]=(int*)calloc(image.cols,sizeof(int*));

  auxi=(int**)calloc(image.rows*n,sizeof(int*));
  for (int i=0; i<image.rows*n; i++)
  auxi[i]=(int*)calloc(image.cols*n,sizeof(int*));
                                    //Pasar a escala de grises
  int v=0,m=0,f=0;
  int *R; int *G; int *B;
  R=(int*)calloc(image.cols*image.rows,sizeof(int));
  G=(int*)calloc(image.cols*image.rows,sizeof(int));
  B=(int*)calloc(image.cols*image.rows,sizeof(int));

 for(i=0;i<image.rows;i++){
    for(j=0;j<image.cols*3;j++){

    uchar pixel =image.at<uchar>(i,j);

    if(c==0){ R[v]=pixel; v++; }

    if(c==1){ G[m]=pixel; m++; }

    if(c==2){ B[f]=pixel; f++; }

    if(c==2) c=-1;
     c++;
    }
 } v=0; c=0;

 for(i=0;i<image.rows;i++){
    for(j=0;j<image.cols;j++){
        ptr[i][j]=(R[v]*0.3)+(G[v]*0.59)+(B[v]*0.11);
        v++;
        }
 }
  free(R); free(G); free(B);

  cout<<"Pixeles: "<<v<<endl;
                                        //Cambiar tamano
if(opc==1){
     for(int i=0 ; i<image.rows ; i++){
    for(int j=0 ; j<image.cols ; j++){

      for(int k=(n*i) ; k<((n*i)+n) ; k++){
        for(int l=(n*j) ; l<((n*j)+n) ; l++){
          auxi[k][l]=ptr[i][j];
                 }
                }
            }
		}
}
else{
      for(int i=0 ; i<image.rows ; i++){
    for(int j=0 ; j<image.cols ; j++){

      for(int k=(n*i) ; k<((n*i)+n) ; k++){
        for(int l=(n*j) ; l<((n*j)+n) ; l++){
            if(i==0 || j==0)
            auxi[k][l]=ptr[i][j];
                 else{
                if(i<image.rows-1  )
                auxi[k][l]=(ptr[i][j]+ptr[i-1][j]+ptr[i][j-1]+ptr[i+1][j])/4;
                 }
                }
            }
		}
      }
}

   for(int i = 0; i < image.rows; i++)delete [] ptr[i];
   delete [] ptr;
   ptr=NULL;

    int x,y;                        //casting
    x= image.cols*n; y=image.rows*n;

    cout<<endl<<"Nueva Imagen"<<endl;
    cout<<"cols "<<x<<endl<<"rows "<<y<<endl;
    v=v*n; cout<<"Pixeles "<<v;
                                       //Creacion archivo .pgm
    FILE *archivo;
    archivo=fopen("../../tamaima/Cambio.pgm","w");
    fprintf(archivo, "P2\n %d %d\n 255\n",x,y);

    for(i=0;i<y;i++){
      for(j=0;j<x;j++){
        fprintf(archivo,"%d ",auxi[i][j]);
      }
    }
 fclose(archivo);

  //for(int i = 0; i < image.rows; i++)delete [] auxi[i];
  //delete [] auxi;
  // auxi=NULL;

  Mat escalado = imread("../../tamaima/Cambio.pgm");
  imshow("cambio ", escalado);
  imshow("original",image);
  waitKey(0);

  return 0;
}
