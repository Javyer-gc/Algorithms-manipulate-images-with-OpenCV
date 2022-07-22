#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>
# define PI           3.14159265358979323846
using namespace cv;
using namespace std;

int **CrearMatriz(unsigned int nFilas, unsigned int nCol);
float **CrearMatrizfloat(unsigned int nFilas, unsigned int nCol);
void LiberarMemoriafloat(float **Puntero_Matriz, unsigned int nFilas, unsigned int nCol);
void LiberarMemoria(int **Puntero_Matriz, unsigned int nFilas, unsigned int nCol);
int ProcesarImagen();
void Imagen_A_Escala_De_Grises(int **MatrizImagen, int filas, int columnas);
void EscalarImagen(int **MatrizImagen,int filas,int columnas);
void ReducirImagen(int **MatrizImagen,int filas,int columnas);
void RotarImagen(int **MatrizImagen,int filas,int columnas);
float **GetRGB(int filas,int columnas,int RGBopc,Mat ImagenColor);


int main( )
{
	int opc;
	cout << "************************PROGRAMA EN C++ PARA MANEJO DE IMAGENES******************" << endl;
    ProcesarImagen();

    return 0;
}

int **CrearMatriz(unsigned int nFilas, unsigned int nCol){
	int **Puntero_Matriz=0;
	Puntero_Matriz=new int*[nFilas]; //reservando memoria para las filas

	for(int i=0 ; i<nFilas ; i++)
		Puntero_Matriz[i]=new int[nCol];//reservar memoria para las columnas

	return Puntero_Matriz;
}

void LiberarMemoria(int **Puntero_Matriz, unsigned int nFilas, unsigned int nCol){


	for(int i=0 ; i<nFilas ; i++)
		delete[] Puntero_Matriz[i];//reservar memoria para las columnas

	delete Puntero_Matriz;
}

int ProcesarImagen()//tiene que ser int para el return -1
{
	int **MatrizImagen;
	int filas = 0, columnas = 0;
    // carga la imagen a color
	Mat ImagenColor = imread("lena.jpg");
	//obtencion de valores para filas y columnas
	filas = ImagenColor.rows;
	columnas = ImagenColor.cols;

    // verificar si la imagen ha sida cargada correctamente
    if (ImagenColor.empty())
    {
        printf("No se ha cargado la imagen \n");
		return -1;
    }
	else
	{
		cout << "La imagen es de " << columnas << " x " << filas << endl;
		float **R,**G,**B,MTemp = 0.0;
		MatrizImagen=CrearMatriz(filas,columnas);
		R=CrearMatrizfloat(filas,columnas); R=GetRGB(filas,columnas,2,ImagenColor);
		G=CrearMatrizfloat(filas,columnas);	G=GetRGB(filas,columnas,1,ImagenColor);
		B=CrearMatrizfloat(filas,columnas);	B=GetRGB(filas,columnas,0,ImagenColor);

		for (int i = 0; i < filas; i++){
				for (int j = 0; j < columnas; j++){
						MTemp = (R[i][j] * 0.3) + (G[i][j] * 0.59) + (B[i][j] * 0.11);
						//MTemp = (R+G+B)/3;
						*(*(MatrizImagen+i)+j) = int(MTemp);
					}
			}
	Imagen_A_Escala_De_Grises(MatrizImagen,filas,columnas);
	int opc1;
	cout << "La imagen fue pasada a escala de grises" << endl;
	cout << "Que desea hacer?" << endl;
	cout << "  1.-Agrandar imagen  \n  2.-Achicar imagen \n  3.-Rotar imagen"<< endl;
	cin >> opc1;
	if(opc1==1){
		EscalarImagen(MatrizImagen,filas,columnas);
	}
	else if(opc1==2){
		ReducirImagen(MatrizImagen,filas,columnas);
	}
	else if(opc1==3){
        RotarImagen(MatrizImagen,filas,columnas);
	}
	LiberarMemoria(MatrizImagen,filas,columnas);
	LiberarMemoriafloat(R,filas,columnas);
	LiberarMemoriafloat(G,filas,columnas);
	LiberarMemoriafloat(B,filas,columnas);
    waitKey(0);
	}
	return 0;
}

float **GetRGB(int filas,int columnas,int RGBopc, Mat ImagenColor){
	float **RGB;
	RGB=CrearMatrizfloat(filas,columnas);

	for (int i = 0; i < filas; i++)
		for (int j = 0; j < columnas; j++)
            RGB[i][j]=ImagenColor.data[ImagenColor.channels()*(ImagenColor.cols*i + j) + RGBopc];

	return RGB;
	LiberarMemoriafloat(RGB,filas,columnas);
}

void Imagen_A_Escala_De_Grises(int **MatrizImagen,int filas,int columnas)
{
	FILE* EscalaGrises;
	/*char Imagen[50];
	cout << "Que nombre desea que tenga la imagen en escala de grises? ";
	cin >> Imagen;*/
	EscalaGrises = fopen("Imagen_escala_grises.pgm", "wb");
	fprintf(EscalaGrises, "P2\n");
	fprintf(EscalaGrises, "%d %d\n", columnas, filas);
	fprintf(EscalaGrises, "255\n");
	int temp = 0;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			temp = *(*(MatrizImagen+i)+j);
			// escala de grises del arreglo al archivo
			fprintf(EscalaGrises, "%d ", temp);
		}
		fprintf(EscalaGrises, "\n");
	}
	fclose(EscalaGrises);
}

void EscalarImagen(int **MatrizImagen,int filas,int columnas){
    int **MESCALADA;
    int n,nFilas,nColumnas;
    cout << "ingrese escalado" << endl;
    cin  >> n;
    nFilas=filas*n;
    nColumnas=columnas*n;
	MESCALADA=CrearMatriz(nFilas,nColumnas);
    for(int i=0 ; i<filas ; i++){
		for(int j=0 ; j<columnas ; j++){
			//2 for internos para la matriz copia
			for(int k=(n*i) ; k<((n*i)+n) ; k++){
					for(int l=(n*j) ; l<((n*j)+n) ; l++){
						*(*(MESCALADA+k)+l)=*(*(MatrizImagen+i)+j);
					}
				}
		}
	}
    cout << nFilas << " x " << nColumnas << endl;
	FILE* Escala;
	Escala = fopen("Imagen_escalada.pgm", "wb");
	fprintf(Escala, "P2\n");
	fprintf(Escala, "%d %d\n", nColumnas, nFilas);
	fprintf(Escala, "255\n");
	int temp = 0;
	for (int i = 0; i < (nFilas); i++) {
		for (int j = 0; j < (nColumnas); j++) {
			//temp = MatrizImagen[i][j];
			temp = *(*(MESCALADA+i)+j);
			// escala de grises del arreglo al archivo
			fprintf(Escala, "%d ", temp);
		}
		fprintf(Escala, "\n");
	}
	fclose(Escala);
}

void ReducirImagen(int **MatrizImagen,int filas,int columnas){
    int **MESCALADA;
    int n,nFilas,nColumnas;
    cout << "ingrese el numero a reducir" << endl;
    cin  >> n;
    nFilas=int(float(filas)/float(n));
    nColumnas=int(float(columnas)/float(n));
    cout << nFilas << " x " << nColumnas << endl;
	MESCALADA=CrearMatriz(nFilas,nColumnas);
    for(int i=0 ; i<nFilas ; i++){
		for(int j=0 ; j<nColumnas ; j++){
			//2 for internos para la matriz copia
			int sum=0;
			float prom=0.0;
			for(int k=(n*i) ; k<((n*i)+n) ; k++){
					for(int l=(n*j) ; l<((n*j)+n) ; l++){
						sum+=*(*(MatrizImagen+k)+l);
						//cout << "suma= " <<sum << endl;
					}
				}
            prom=float(sum)/(float(n*n));
           // cout << "promedio= " << prom << endl;
            *(*(MESCALADA+i)+j)=int(prom);
		}
	}
	FILE* Escala;
	Escala = fopen("Imagen_reducida.pgm", "wb");
	fprintf(Escala, "P2\n");
	fprintf(Escala, "%d %d\n", nColumnas, nFilas);
	fprintf(Escala, "255\n");
	int temp = 0;
	for (int i = 0; i < (nFilas); i++) {
		for (int j = 0; j < (nColumnas); j++) {
			//temp = MatrizImagen[i][j];
			temp = *(*(MESCALADA+i)+j);
			// escala de grises del arreglo al archivo
			fprintf(Escala, "%d ", temp);
		}
		fprintf(Escala, "\n");
	}
	fclose(Escala);
}

void RotarImagen(int **MatrizImagen,int filas,int columnas)
{
    float angulo;
    int x,y;
    int **MROTADA;
    int MNFilas,MNColumnas;
    cout << "A cuantos grados desea rotar la imagen? ";
    cin >>angulo;
    //angulo=angulo-30;
   // if(angulo!=90 || angulo!=180 || angulo!=270 || angulo!=360){
     //   MNFilas=filas*columnas;
       // MNColumnas=filas*columnas;
    //}
    //else{
        MNFilas=filas;
        MNColumnas=columnas;
    //}
    MROTADA=CrearMatriz(MNFilas,MNColumnas);

    for(int i=0; i<MNFilas ; i++){
        for(int j=0 ; j<MNColumnas ; j++){
            int nfilas = MNFilas / 2;
			int ncolumnas = MNColumnas / 2;
			int xt = i - nfilas;
			int yt = j - ncolumnas;
			float seno=sin(-angulo*PI/180);
			float coseno=cos(-angulo*PI/180);
			x=int(float(xt)*coseno-float(yt)*seno)+nfilas;
			y=int(float(xt)*seno+float(yt)*coseno)+ncolumnas;

            if((x>=0) && (y>=0) &&(x<MNFilas)&&(y<MNColumnas))
                *(*(MROTADA+i)+j)=*(*(MatrizImagen+x)+y);
            else
                *(*(MROTADA+i)+j)=255;
        }
    }

    FILE* Rotada;
	Rotada = fopen("Imagen_rotada.pgm", "wb");
	fprintf(Rotada, "P2\n");
	fprintf(Rotada, "%d %d\n", MNColumnas,MNFilas);
	fprintf(Rotada, "255\n");
	int temp = 0;
	for (int i = 0; i < (MNFilas); i++) {
		for (int j = 0; j < (MNColumnas); j++) {
			//temp = MatrizImagen[i][j];
			temp = *(*(MROTADA+i)+j);
			// escala de grises del arreglo al archivo
			fprintf(Rotada, "%d ", temp);
		}
		fprintf(Rotada, "\n");
	}
	fclose(Rotada);
}

float **CrearMatrizfloat(unsigned int nFilas, unsigned int nCol){
	float **Puntero_Matriz=0;
	Puntero_Matriz=new float*[nFilas]; //reservando memoria para las filas

	for(int i=0 ; i<nFilas ; i++)
		Puntero_Matriz[i]=new float[nCol];//reservar memoria para las columnas

	return Puntero_Matriz;
}

void LiberarMemoriafloat(float **Puntero_Matriz, unsigned int nFilas, unsigned int nCol){


	for(int i=0 ; i<nFilas ; i++)
		delete[] Puntero_Matriz[i];//reservar memoria para las columnas

	delete Puntero_Matriz;
}

