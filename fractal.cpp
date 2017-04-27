//! file fractal.cpp
//! \author Lebaz Lydia
//! version 1.0
//! date 24 avril 2017
//! breis Pour compiler avec N threads: g++ fractal.cpp -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core -DWITH_THREAD DNB_THREAD=n
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <complex> 
#include <time.h>
#include <thread>
#include <semaphore.h> 
#include <chrono>
#include <pthread.h>
#include <fstream>
#include<ctime>

//! namespace std
//! namespace cv
using namespace std;
using namespace cv;

Mat base;;  //declaration de notre base

//! def NB_THREAD 
#ifndef NB_THREAD
#define NB_THREAD thread::hardware_concurrency() //to get nof cores
#endif

#define N_max 4  
//! def iter_max
#define iter_max 150 

//! def WID
#ifndef WID
#define WID 600
#endif
//! def HEI
#ifndef HEI
#define HEI 600
#endif
//! def c 

double reel= -0.7927;  double img= 0.1609;
//double H =0, W=0;
std::complex<long double> c (reel,img );//la valeur de la constante complexe choisi
 
//! fn HSVtoRGB
void HSVtoRGB( unsigned char  *r, unsigned char  *g, unsigned char  *b, unsigned char  h, unsigned char  s, unsigned char  v );

// Creation de la fonction qui s'appelle "fractal" qui se charge du calcul des point de la fracatal du julia 

//! fn fractal 
//!breif cette fonction permit de dessiner la fractal
void *fractal(int k)
{
#ifdef WITH_THREAD
// calcul de i, n en fonction de l'identifiant du threads
  int i = ceil(k * (float)base.rows/NB_THREAD); 
  int n = ceil(k * (float)base.rows/NB_THREAD + (float)base.rows/NB_THREAD);
 
#else
  int i = 0, n = base.rows;
#endif  

for(; i < n; i++){
 for(int j(0); j < base.cols; j++){
       
//! breif calcul de la nouvelle valeur des pixels dans la bsse(-1;1)
	long double X1= ((long double)-1 +((long double)i *((long double)2/(long double) WID))); 
	long double Y1= ((long double)-1 +((long double)j *((long double)2/(long double) HEI)));
	std::complex<long double> ZC(Y1,X1);  
      
 int iteration=0;
 std::complex < long double > c (-0.7927,0.1609 );
        long double norm = std::norm(ZC);
        while(iteration<iter_max && norm<N_max){
          ZC=(ZC*ZC)+c;
          norm = std::norm(ZC);
          iteration++;
        }

        if(iteration==iter_max && norm<N_max){ // défintion de la couleur de la couleur de l'image 
          base.at<Vec3b>(i,j)[0]=0; 
          base.at<Vec3b>(i,j)[1]=0; 
          base.at<Vec3b>(i,j)[2]=0;
        }
       else{ 
          int couleur=(int)((float)iteration/(float)iter_max*360);// definitions des couleurs de la fractale
	  unsigned char brillance=150; 
          unsigned char saturation=150;
          unsigned char r,g,b;
	  HSVtoRGB( & r, & g, & b, couleur, brillance, saturation );
          base.at<Vec3b>(i,j)[0]=r;
          base.at<Vec3b>(i,j)[1]=g;
          base.at<Vec3b>(i,j)[2]=b;
      }
    }
  } 
return 0;
}

//!breif cette fonction permit la Conversion Hsv to RGB
void HSVtoRGB( unsigned char  *r, unsigned char  *g, unsigned char  *b, unsigned char  h, unsigned char  s, unsigned char  v )
{unsigned char m,f, p,q, t;

	if (s == 0)
	{
		*r = 0;
		*g = 0;
		*b = 0;
	}
	else
	{	 
    m = h / 43;
    f = (h - (m * 43)) * 3;
    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * f) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - f)) >> 8))) >> 8;
        
		switch (m)
		{
		case 0:
			*r = v;*g = t;*b = p;break;
		case 1:
			*r = q;*g = v;*b = p;break;
		case 2:
			*r = p;*g = v;*b = t;break;
		case 3:
			*r = p;*g = q;*b = v;break;
		case 4:
			*r = t;*g = p;*b = v;break;
		default:
			*r = v;*g = p;*b = q;break;
		}
	}
	return;
}
unsigned char randomVal(){
return (unsigned char)(rand()%360);
}

int main( int argc, char** argv )
{

//! breif déclaration des variables pour calcul du temps
	double temps_final, temps_cpu ,temps_initial;
//! breif déclaration de l'image 
	base=cv::Mat(WID, HEI, CV_8UC3);

//! breif lancer le chrono de temps
 	temps_initial = clock ();

 #ifdef WITH_THREAD
        thread * th = new thread[NB_THREAD];
        for(int k(0); k < NB_THREAD; k++) th[k] = thread(fractal, k);
        for(int k(0); k < NB_THREAD; k++) th[k].join();    
    #else
        fractal(0);
    #endif

//! breif calcul du temps de calcul de la fractal
temps_final = clock ();
temps_cpu = (temps_final - temps_initial) / CLOCKS_PER_SEC * 1000; // millisecondes
// Affichage du temps d'éxecution de la fractal
	cout<< " le temps d'execution est de : "<<temps_cpu<<" ms"<< " avec "<<NB_THREAD<<" threads "<< endl;
//! breif ecrire dans un fichier.txt

 ofstream fichier("test.txt", ios::app);
        if(fichier)
        {

          fichier << temps_cpu <<"  "<<NB_THREAD<<"  "<< endl;
          
          fichier.close();
        }
        else
              {
                cout << "Impossible d'ouvrir le fichier !" << endl;
              }

//affichage de la fractal
  while( true ) {	 
    imshow("picture julia", base ); 
    if(cvWaitKey(30) )  break;
    
  }
imwrite("image.jpg", base);    // sauve une copie de l'image
cvDestroyWindow("image");        //ferme la fenêtre
  return 0;
}

