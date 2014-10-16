
//#define CV_NO_BACKWARD_COMPATIBILITY

// jmmossi

#include "cv.h"
#include "cxmisc.h"
#include "highgui.h"
//#include "cvaux.h"
#include <stdio.h>
#include <sys/time.h>

#include <string>
#include <iostream>
//#include <midemonio.h>

//#define cimg_plugin "cimg_gpiv.h"
#define cimg_plugin2 "cimgIPL.h"
#define cimg_plugin1 "cimgcvMat.h"
#include "CImg.h"

using namespace std;
using namespace cimg_library;

//#include <midemonio.h>

/*************************************************
 
 Generar LookUpTable
 
 *************************************************/
CvMat* GenerarLut()
{
	CvMat* LutVisual = cvCreateMat( 1, 256, CV_8UC3 ); 
	
	uchar *pp;
	int cc;
	pp=(uchar*) LutVisual->data.ptr;
	for (cc=0; cc<64; cc++) {    // de rojo a amarillo
		*pp++ = 0;  
		*pp++ = cc*4;   
		*pp++ = 255; 
	}
	for (cc=0; cc<64; cc++) {    // de amarillo a verde
		*pp++ = 0;  
		*pp++ = 255;   
		*pp++ = 255-cc*4; 
	}
	for (cc=0; cc<64; cc++) {    // de verde a cyan
		*pp++ = cc*4;  
		*pp++ = 255;   
		*pp++ = 0; 
	}
	for (cc=0; cc<64; cc++) {    // de cyan a azul
		*pp++ = 255;  
		*pp++ = 255-cc*4;   
		*pp++ = 0; 
	}
	
	return LutVisual;
	
}//void GenerarLut()


/************************************************
 De momento aqui todas las imagenes son de unsigned char,
 imGris y depth de un canal y imColor de 3
 
 
 POR DEBAJO DE min_val no se colore
 por encima de max_val se satura a max_val
 
 HAY OTRA funcion con el mismo nombre sobrecargada para mostrar solo disp sin depth
 
 ************************************************/


void Img2ColorGrade(CvMat *imGris,   // imagen monocanal de entrada
					CvMat* disp,     // imagen necesaria para saber en que pixels se ha podido calcular disparidad y cuales no
					float min_disp,  // valor necesario para saber donde no hay disparidad (min_disp - 1)
					CvMat* depth,    // imagen   matriz con la coordenada Z
					float min_depth, float max_depth,   // valor minimo y maximo para ajustar la escala de colores
					CvMat* LutVisual,        // paleta a utilizar        
					CvMat *imColor)       // imagen resultante. CV_8UC3 
{
	int cc;
	int rr;
	float *pDepth, *pDisp;
	uchar *pColor, *pLut, *pGris;
	
	pLut= (uchar*)(LutVisual->data.ptr);
	
	float v_depth, v_disp;
	unsigned int indice;
	int jj3;
	float rango = max_depth - min_depth;
	float escalado = (float) 255 / rango;
	
	for (rr=0; rr<imGris->rows; rr++) {
		pColor  = (uchar *) (imColor->data.ptr + rr * imColor->step);
		pDepth = (float*)(depth->data.ptr + rr * depth->step);
		pDisp = (float*)(disp->data.ptr + rr * disp->step);
		pGris = (uchar *) (imGris->data.ptr + rr * imGris->step);
		
		for (cc=0; cc<imGris->cols; cc++) {
			v_disp = (float)*pDisp;								
			if (v_disp >= min_disp)
			{ // si hay disparidad se colorea
				v_depth = *pDepth;
				// normalizacion
				v_depth = (v_depth -min_depth)*escalado;
				if (v_depth < 0 ) indice = 0;
				else if (v_depth>255.0) indice = 255;
				else indice = (unsigned char) v_depth;
				indice *= 3; // hay que avanzar de 3 en 3 porque la paleta es de color.
				
				jj3= 2*(int)pLut[indice] + *pGris;
				*pColor++ = (uchar) (jj3/3);
				jj3= 2*(int)pLut[indice+1] + *pGris;
				*pColor++ = (uchar) (jj3/3);
				jj3= 2*(int)pLut[indice+2] + *pGris;
				*pColor++ = (uchar) (jj3/3);
				
				
			}
			else
			{  // si no hay disparidad se deja en gris
				
				*pColor++ = *pGris;
				*pColor++ = *pGris;
				*pColor++ = *pGris;	
				
			}
			
			pGris++;
			pDepth++;
			pDisp++;
		}
	}
	
}//void Img2ColorGrade(CvMat *imGris, CvMat *imColor, CvMat* Lut






/************************************************
 De momento aqui todas las imagenes son de unsigned char,
 imGris y depth de un canal y imColor de 3
 
 
 POR DEBAJO DE min_val no se colore
 por encima de max_val se satura a max_val
 
 
 FUNCION SOBRECARGADA DE LA ANTERIOR PARA MOSTRAR SOLO LA DISPARIDAD Y NO EL DEPTH
 
 ************************************************/


void Img2ColorGrade(CvMat *imGris,   // imagen monocanal de entrada
					CvMat* disp,     // imagen necesaria para saber en que pixels se ha podido calcular disparidad y cuales no
					float min_disp,  // valor necesario para saber donde no hay disparidad (min_disp - 1)
					float max_disp,  // valor para ajustar el maximo al color mas alto
					CvMat* LutVisual,        // paleta a utilizar        
					CvMat *imColor)       // imagen resultante.
{
	int cc;
	int rr;
	float *pDisp;
	uchar *pColor, *pLut, *pGris;
	
	pLut= (uchar*)(LutVisual->data.ptr);
	unsigned int indice;
	int jj3;
	float rango = (max_disp - min_disp);
	float escalado = (float) 255 / rango;
	float v_disp;
	
	for (rr=0; rr<imGris->rows; rr++) {
		pColor  = (uchar *) (imColor->data.ptr + rr * imColor->step);
		//pDepth = (float*)(depth->data.ptr + rr * depth->step);
		pDisp = (float*)(disp->data.ptr + rr * disp->step);
		pGris = (uchar *) (imGris->data.ptr + rr * imGris->step);
		
		for (cc=0; cc<imGris->cols; cc++) {
			v_disp = (float)*pDisp;								
			if (v_disp >= min_disp)
			{ // si hay disparidad se colorea
				
				// normalizacion
				v_disp = (v_disp -min_disp)*escalado;
				if (v_disp < 0 ) indice = 0;
				else if (v_disp>255.0) indice = 255;
				else indice = (unsigned char) v_disp;
				indice *= 3; // hay que avanzar de 3 en 3 porque la paleta es de color.
				
				jj3= 2*(int)pLut[indice] + *pGris;  //mezclamos 2/3 el color y 1/3 el nivel de gris original
				*pColor++ = (uchar) (jj3/3);
				jj3= 2*(int)pLut[indice+1] + *pGris;
				*pColor++ = (uchar) (jj3/3);
				jj3= 2*(int)pLut[indice+2] + *pGris;
				*pColor++ = (uchar) (jj3/3);
				
			}
			else
			{  // si no hay disparidad se deja en gris
				*pColor++ = *pGris;
				*pColor++ = *pGris;
				*pColor++ = *pGris;	
			}
			
			pGris++;
			pDisp++;
		}
	}
	
}//void Img2ColorGrade(CvMat *imGris,CvMat* disp,float min_disp,
//float max_disp, CvMat* LutVisual, CvMat *imColor) 


/*****************************************
 
 Distancia a la camara
 en src tiene que ser de 3 canales, el primero la coordenada X,
 el segundo canal la Y y el tercero la Z.
 
 En la imagen dst se pone el valor de sqrt(X^2+Y^2+Z^2)
 
 ****************************************/
void DistFromCam(CvMat *src, CvMat *dst)
{
   // FALTA COMPROBAR DIMENSIONES Y TIPOS
	
	float *ps, *pd;
	int rr, cc;
	float t1, t2;
	for (rr=0; rr<src->rows; rr++) {
		ps= (float*) (src->data.ptr + rr * src->step);
		pd= (float*) (dst->data.ptr + rr * dst->step);
		
		for (cc=0; cc<src->cols; cc++) {
			t1 = *ps++;
			t2 = t1 * t1;
			t1 = *ps++;
			t2 += t1 * t1;
			t1 = *ps++;
			t2 += t1 * t1;
			
			*pd++ = sqrt((double)t2);
		}
	}
}//void DistFromCam(CvMat *src, CvMat *dst)



int timeval_subtract (timeval *x, timeval *y, timeval *result)
{
	/* Perform the carry for the later subtraction by updating y. */ 
	if (x->tv_usec < y->tv_usec) {
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1; 
		y->tv_usec -= 1000000 * nsec; 
		y->tv_sec += nsec;
	} if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec; 
		y->tv_sec -= nsec;
	}
	/* Compute the time remaining to wait. tv_usec is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec; 
	result->tv_usec = x->tv_usec - y->tv_usec;
	/* Return 1 if result is negative. */ 
	return x->tv_sec < y->tv_sec;
}



void ayuda()
{
  printf("stereo_display -d #\n"
	 " muestra la imagen de las camaras, salvo que se especifique \n"
         " la opcion -f o -l en cuyo caso toma como entrada un avi o ficheros\n\n"
	 "  -d #:  diezmado. De momento solo acepta 1, 2, 4. Defecto 1\n"
	 "  -f:    toma como entrada los ficjeros avi camL.avi y camR.avi \n"
	 "  -t token:   toma com entrada el demonio de memoria compartida\n"
	 "  -m:   distancia minima (rojo) para el coloreado de la profundidad\n"
	 "  -M:   distancia maxima (azul) para el coloreado de la profuncidad\n"
	 "  -v:  nivel de verbosidad\n"
	 "  -L:  numero dispositivo camara izquierda (Ejemplo 0)\n"
	 "  -R:  numero dispositivo camara izquierda (Ejemplo 1)\n"
	 "\n"
	 );
}

/****************************************************************
 
 
 ****************************************************************/
int main(int argc, char *argv[]) {
	
	CvFont font = cvFont( 1, 1 );
	
	const unsigned char black[] = { 0,0,0 }, white[] = { 255,255,255 }; 
	
	IplImage  *imA_tmp, *imB_tmp;
	CvMat *img1r_tmp, *img2r_tmp;
	CvMat *img1r_d2, *img2r_d2;

	int verbose_level=0;

	char bbuf[1000]; 

	CvSize imageSize = {0,0};
	CvSize imageSize2 = {0,0};

	int primera_vez = 1;
	int ii;
	int modo_pausa=1;
	
	int ancho, alto;
	int  nframes;
	int FromSource=0;  // 0:por defecto de las camaras,
	                 // 1: de los ficheros camL.avi y camR.avi
	                 // 2: de lista de ficheros.
	                 // 3: de memoria compartida.
	char *imageList;

	
	CvMat *img1, *img2;
	CvMat *img1r, *img2r;
	CvMat *disp, *depth;
	CvMat *depth_X,*depth_Y,*depth_Z, *depth_R;
	CvMat *dispColor, *depthColor;
	
	//CvMat *par_rectified;
	
	CImgDisplay display_1;
	CImgDisplay display_2;
	
	FILE *f;
	vector<string> imageNames[2];
	int diezmado = 1;
	float display_dist_min=500.0;   //500 milimetros
	float display_dist_max=4500.0;  // 4.5 m, 5500mm 
	
	timeval tiempo1, tiempo2, tiempo3, tiempo4, tiempo5,tiempo6;
	timeval time_dif1,time_dif2,time_dif3,time_dif4;

	int opt;

	void *handlein= 0;//token videoserver
 	std::string tokenfilein;
	//char shared_mem_text[SHARED_TEXT_LENGTH+1];
	int leftcamdevice = -1;
	int rightcamdevice = -1;
//	while((opt=getopt(argc,argv,"hd:fl:m:M:t:v:L:R:"))!=-1) //  
  	while((opt=getopt(argc,argv,"hd:fl:m:M:v:L:R:"))!=-1) //  
    {
		switch(opt)
		{
			case 'h':
				ayuda();
				exit(0);
				break;
			case 'd':
				diezmado=atoi(optarg);
				if (diezmado != 1 && diezmado != 2 && diezmado != 4) {
					fprintf(stderr, "diezmado erroneo\n");
					exit(-1);
				}
				break;	
			case 'f':
				FromSource=1; // de los ficheros camL.avi y camR.avi  
				break;
			case 'l':
				FromSource=2;
				imageList=optarg;
				break;

/*			case 't':
			  FromSource=3;  // del demonio
				tokenfilein = optarg;
				break;
*/
			case 'm':
				display_dist_min=atof(optarg);
				if (display_dist_min <0.0 ) {
					fprintf(stderr, "distancia minima erronea\n");
					exit(-1);
				}
				break;	
			case 'M':
				display_dist_max=atof(optarg);
				if (display_dist_max <0.0 ) {
					fprintf(stderr, "distancia maxima erronea\n");
					exit(-1);
				}
				break;	
		case 'L':
		  leftcamdevice = atoi(optarg);
		  break;

		case 'R':
		  rightcamdevice = atoi(optarg);
		  break;
		}
    }//while((opt=getopt(argc,argv,"hm:c:d:"))!=-1)

	if((0==FromSource) && (leftcamdevice < 0 || rightcamdevice <0))
	  {
	    std::cerr << "Option -L and -R should be provided\n";
	    exit(0);
	  }
	CvCapture* captureA=NULL;
	CvCapture* captureB=NULL;
	
	switch (FromSource) {
		case 0:   
			captureA = cvCaptureFromCAM( leftcamdevice );
			captureB = cvCaptureFromCAM( rightcamdevice );
			
			if( !captureA ) {
				fprintf( stderr, "ERROR: capture A is NULL \n" ); 
				exit( -1);
			} 
			else {
				fprintf(stderr, "Capture A open\n");
			}
			
			
			if( !captureB ) {
				fprintf( stderr, "ERROR: capture B is NULL \n" ); 
				exit( -1);
			} 
			else {
				fprintf(stderr, "Capture B open\n");
			}
			std::cout << "Check point\n";	
			break;
		case 1:
			captureA = cvCreateFileCapture("camL.avi");		
			captureB = cvCreateFileCapture("camR.avi");
			if( !captureA ) {
				fprintf( stderr, "ERROR: capture A is NULL \n" ); 
				exit( -1);
			} 
			else {
				fprintf(stderr, "Capture A open\n");
			}
			
			if( !captureB ) {
				fprintf( stderr, "ERROR: capture B is NULL \n" ); 
				exit( -1);
			} 
			else {
				fprintf(stderr, "Capture B open\n");
			}
			
			break;
		case 2:
			
			f = fopen(imageList, "rt");
			int i, lr;
			
			
			nframes=0;
			for(i=0;;i++)
			{
				char buf[1024];
				lr = i % 2;
				if( !fgets( buf, sizeof(buf)-3, f ))
					break;
				size_t len = strlen(buf);
				while( len > 0 && isspace(buf[len-1]))
					buf[--len] = '\0';
				if( buf[0] == '#')
					continue;
				imageNames[lr].push_back(buf);
				if (0==nframes) { //only with the first GetSize
					IplImage* img = cvLoadImage( buf, 0 );
					if( !img )
					{
						fprintf(stderr, "error al cargar imagenes\n");
						exit(-1);
					}
					imageSize = cvGetSize(img);
					cvReleaseImage(&img);
				}
				nframes++;
			}		
			nframes = nframes/2;
			break;
/*
	case 3:
	  if(tokenfilein.size())
	    {
	      std::cout << "Starting Input  Daemon " << tokenfilein << "\n";
    
	      handlein = initDemonio(tokenfilein.c_str(),MODE_CLIENTE);
    
	      if(NULL == handlein)
		{
		  std::cerr << "Error abriendo token de demonio de entrada:" << tokenfilein << std::endl;
		  exit(0);
		}
	    }

	  else
	    {
		  std::cerr << "token no especificado" << std::endl;
		  exit(0);
	    }
	  break;
	  */
	}// end switch FromSource
	
	if(verbose_level >= 1)	std::cout<<"Importing mat_cam1.xml \n";
	CvMat *_M1= (CvMat*) cvLoad("mat_cam1.xml"); 
	if(! _M1) { std::cerr<<"error loading matrix\n"; exit(-1);}
	
	if(verbose_level >= 1) std::cout<<"Importing mat_cam2.xml\n";
	CvMat *_M2= (CvMat*) cvLoad("mat_cam2.xml"); 
	if( ! _M2) {std::cerr<<"error loading matrix\n";  exit(-1);}
	
	if(verbose_level >= 1) std::cout<<"Importing mat_distortion1.xml\n";
	CvMat *_D1= (CvMat*) cvLoad("mat_distortion1.xml"); 
	if( ! _D1) {std::cerr<<"error loading matrix\n";  exit(-1);}
	
	if(verbose_level >= 1) std::cout<<"Importing mat_distortion2.xml\n";
	CvMat *_D2= (CvMat*) cvLoad("mat_distortion2.xml"); 
	if( ! _D2){	std::cerr<<"error loading matrix\n";  exit(-1);}
	
	if(verbose_level >= 1) std::cout<<"Importing mat_R.xml\n";
	CvMat *_R= (CvMat*) cvLoad("mat_R.xml");
	if( !_R ){ std::cerr<<"error loading matrix\n";  exit(-1);}

	if(verbose_level >= 1) std::cout<<"Importing mat_T.xml\n";	
	CvMat *_T= (CvMat*) cvLoad("mat_T.xml");
	if( ! _T ){ std::cerr<<"error loading matrix\n";  exit(-1);}

	if(verbose_level >= 1) std::cout<<"Importing mat_imagesize\n";	
	CvMat *_mat_imagesize= (CvMat*) cvLoad("mat_imagesize.xml");
	if( ! _mat_imagesize )	{std::cerr<<"error loading matrix\n";  exit(-1);}
	imageSize.width = (int) CV_MAT_ELEM(*_mat_imagesize, double,0,0);
	imageSize.height = (int) CV_MAT_ELEM(*_mat_imagesize, double,0,1); 
	
	if(verbose_level >= 1) fprintf(stderr, "imageSize: %d %d\n", imageSize.width, imageSize.height);
       	
	double R1[3][3], R2[3][3], P1[3][4], P2[3][4],pQ[4][4];
	
	CvMat _R1 = cvMat(3, 3, CV_64F, R1);
	CvMat _R2 = cvMat(3, 3, CV_64F, R2);	
	CvMat _P1 = cvMat(3, 4, CV_64F, P1);
	CvMat _P2 = cvMat(3, 4, CV_64F, P2);
	CvMat _Q = cvMat(4, 4, CV_64F, pQ); 
	CvMat *Q  = &_Q;
	
	if(verbose_level >= 1) printf("Getting  cvStereo Rectify\n");
	cvStereoRectify( _M1, _M2, _D1, _D2, imageSize,
	 				_R, _T,
	 				&_R1, &_R2, &_P1, &_P2, Q,
	 				0/*CV_CALIB_ZERO_DISPARITY*/ );
	
	if(verbose_level >= 1) 	printf("stereo rectify......done\nGetting maps \n" );
	CvMat* mx1 = cvCreateMat( imageSize.height, imageSize.width, CV_32F );
	CvMat* my1 = cvCreateMat( imageSize.height, imageSize.width, CV_32F );
	CvMat* mx2 = cvCreateMat( imageSize.height, imageSize.width, CV_32F );
	CvMat* my2 = cvCreateMat( imageSize.height, imageSize.width, CV_32F );
	
	cvInitUndistortRectifyMap(_M1,_D1,&_R1,&_P1,mx1,my1);
	cvInitUndistortRectifyMap(_M2,_D2,&_R2,&_P2,mx2,my2);
	if(verbose_level >= 1) 	printf("maps..............done\n");	
	
	*((double*)CV_MAT_ELEM_PTR(*Q,3,2)) = abs( CV_MAT_ELEM(*Q, double,3,2));
	
	CvMat *Lut;
	Lut = GenerarLut();
	
	// ++++++ BEGIN RECTIFICAR IMAGENES, ENCONTRAR DISPARIDAD Y MOSTRAR
	// RECTIFY THE IMAGES AND FIND DISPARITY MAPS
	
	//Setup for finding stereo corrrespondences
	CvStereoBMState *BMState = cvCreateStereoBMState();
	assert(BMState != 0);
	
	//BMState->preFilterSize=41; //original
	//BMState->preFilterCap=31;  //original
	//BMState->SADWindowSize=41; //original
	//BMState->minDisparity=-64;
	//BMState->numberOfDisparities=128; // original
	//BMState->textureThreshold=10;  //original
	//BMState->uniquenessRatio=15;   //original
	
	if(1==diezmado)
	{
		BMState->preFilterSize=21;
		BMState->preFilterCap=33;
		BMState->SADWindowSize=41;
		BMState->minDisparity=0;
		BMState->numberOfDisparities= 96;//96;//192;//80; //192;    //tiene que ser divisible por 16
		BMState->textureThreshold=10;  //original 15
		BMState->uniquenessRatio=15;    //original 15
	}
	else if(2==diezmado)
	{
		BMState->preFilterSize=21;
		BMState->preFilterCap=15;
		BMState->SADWindowSize=21;
		BMState->minDisparity=0;  //original 0
		BMState->numberOfDisparities=80;   //48 //tiene que ser divisible por 16
		BMState->textureThreshold=15;
		BMState->uniquenessRatio=15;
	}
	else if(4==diezmado)
	{
		BMState->preFilterSize=11;
		BMState->preFilterCap=9;
		BMState->SADWindowSize=11;
		BMState->minDisparity=0;
		BMState->numberOfDisparities=32;    //tiene que ser divisible por 16
		BMState->textureThreshold=15;
		BMState->uniquenessRatio=15;
	}
	
	int minDisp_diezmado =BMState->minDisparity * diezmado; //para las funciones de visualizacion
	

	gettimeofday(&tiempo6, NULL);
	// Show the image captured from the camera in the window and repeat 
	ii=-1;
	while( 1 ) {  
		// Get one frame 
		ii++;
		if (2==FromSource && ii == nframes) 
			ii=nframes-1;

		switch (FromSource) {
			case 0:  // from camera
			case 1:  // from avifile
				
				gettimeofday (&tiempo1, NULL);		
				cvGrabFrame( captureA ); 
				gettimeofday (&tiempo2, NULL);		
				cvGrabFrame( captureB ); 
				gettimeofday (&tiempo3, NULL);		
				
				imA_tmp = cvRetrieveFrame( captureA ); 
				imB_tmp = cvRetrieveFrame( captureB ); 

				gettimeofday (&tiempo4, NULL);		
				std::cout << "check point 2\n";
				break;
			case 2:   //from image file list
				imA_tmp=cvLoadImage(imageNames[0][ii].c_str());
				imB_tmp=cvLoadImage(imageNames[1][ii].c_str());
				break;
/*
		case 3:
		  {  //case 3:   llave para que cree variables y las destruya al cerrar la llave
		    int rr;
		    CImg<unsigned char>img_c;
		    img_c.assign( handlein, shared_mem_text, &rr );	//Read Image
		    if(rr == A_TERMINAR)
		      {
			goto terminar;
		      }
		    CImg<unsigned char> CimA = img_c.get_crop(0,0,img_c.width()-1, img_c.height()/2-1);
		    CImg<unsigned char> CimB = img_c.get_crop(0, img_c.height()/2,img_c.width()-1, img_c.height()-1);
		    
		    imA_tmp = CimA.get_IPL();
		    imB_tmp = CimB.get_IPL();

		  }//case 3:   la "llave" para que cree variables y las destruya al cerrar la llave

		  break;
		  */
		  }//end	switch (FromSource) 
	
		
		if( !imA_tmp ) {
			fprintf( stderr, "ERROR: frame A is null...\n" ); 
			break;   
		}    
		
		if( !imB_tmp ) {
			fprintf( stderr, "ERROR: frame B is null...\n" ); 
			break;   
		}   
		timeval_subtract(&tiempo2,&tiempo1,&time_dif1);
		timeval_subtract(&tiempo3,&tiempo2,&time_dif2);
		timeval_subtract(&tiempo4,&tiempo3,&time_dif3);
		timeval_subtract(&tiempo1,&tiempo5,&time_dif4);
	
		if(verbose_level >= 4)
		  { 
		    fprintf(stderr, "tiempos en microsegundos\n");
		    fprintf(stderr, "ii %d,t1 %1.0f, t2 %1.0f, tiempo grab_L: %1.0f\n", ii,
			    (float)(tiempo1.tv_usec),(float)(tiempo2.tv_usec),(float)(time_dif1.tv_usec));
		    fprintf(stderr, "      t2 %1.0f, t3 %1.0f, tiempo grab_R: %1.0f\n", 
			    (float)(tiempo2.tv_usec),(float)(tiempo3.tv_usec),(float)(time_dif2.tv_usec));
		    fprintf(stderr, "      t4 %1.0f, t1 %1.0f, tiempo Retrieve L + R: %1.0f\n", 
			    (float)(tiempo3.tv_usec),(float)(tiempo4.tv_usec),(float)(time_dif3.tv_usec));
		    fprintf(stderr, "      t5 %1.0f, t1 %1.0f, tiempo iteracion completa: %1.0f\n", 
			    (float)(tiempo4.tv_usec),(float)(tiempo1.tv_usec),(float)(time_dif4.tv_usec));
		  }
		tiempo5=tiempo1;
		
		if(1==primera_vez)
		{
			imageSize = cvGetSize(imA_tmp);
			imageSize2 = cvGetSize(imB_tmp);
						
			if(imageSize.height != imageSize2.height || imageSize.width != imageSize2.width
			   || imA_tmp->depth != imB_tmp->depth || imA_tmp->nChannels != imB_tmp->nChannels)
			{
				fprintf(stderr, "el tamanyo de las imagenes es diferente\n");
				exit(-1);
			}
			
			// BEGIN si el diezmado se hace DESPUES de rectificar y la calibracion con imgs SIN diezmar
			img1r_tmp=cvCreateMat( imageSize.height, imageSize.width, CV_8U );
			img2r_tmp=cvCreateMat( imageSize.height, imageSize.width, CV_8U );
			
			if (diezmado > 2) 
			{
				img1r_d2=cvCreateMat( imageSize.height/2, imageSize.width/2, CV_8U ); //diezmado temporal por 2
				img2r_d2=cvCreateMat( imageSize.height/2, imageSize.width/2, CV_8U );
			}
			ancho = imageSize.width/diezmado;
			alto = imageSize.height/diezmado;
			
			img1 = cvCreateMat( imageSize.height, imageSize.width, CV_8U );
			img2 = cvCreateMat( imageSize.height, imageSize.width, CV_8U );
			
			img1r = cvCreateMat( alto, ancho, CV_8U );
			img2r = cvCreateMat( alto, ancho, CV_8U );
			
			// END si el diezmado se hace DESPUES de rectificar y la calibracion con imgs SIN diezmar
			
			disp= cvCreateMat(alto, ancho, CV_32FC1);
			depth= cvCreateMat(alto, ancho, CV_32FC3);
			depth_X= cvCreateMat(alto, ancho, CV_32FC1);
			depth_Y= cvCreateMat(alto, ancho, CV_32FC1);
			depth_Z= cvCreateMat(alto, ancho, CV_32FC1);
			depth_R= cvCreateMat(alto, ancho, CV_32FC1);
			dispColor= cvCreateMat(alto, ancho, CV_8UC3);
			depthColor= cvCreateMat(alto, ancho, CV_8UC3);
			
			primera_vez=0;
		}
		
		// BEGIN si el diezmado se hace DESPUES de rectificar y la calibracion con imgs SIN diezmar
		
		cvCvtColor(imA_tmp, img1, CV_RGB2GRAY);
		cvCvtColor(imB_tmp, img2, CV_RGB2GRAY);
		
		if(2==FromSource || 3==FromSource)
		  { //si es de fichero imagen o de demonio liberamos, si es de avi o de camara no
		    cvReleaseImage(&imA_tmp);
		    cvReleaseImage(&imB_tmp);
		  }
		
		if( !img1 || !img2 ) break;
		
		cvRemap( img1, img1r_tmp, mx1, my1 );
		cvRemap( img2, img2r_tmp, mx2, my2 );
		
		if (1==diezmado)
		{
			cvCopy(img1r_tmp, img1r);
			cvCopy(img2r_tmp, img2r);
		}
		else if (2==diezmado)
		{
			cvPyrDown(img1r_tmp, img1r);
			cvPyrDown(img2r_tmp, img2r);
		}
		else if(4==diezmado)
		{
			cvPyrDown(img1r_tmp, img1r_d2);
			cvPyrDown(img2r_tmp, img2r_d2);
			cvPyrDown(img1r_d2, img1r);
			cvPyrDown(img2r_d2, img2r);
		} 
		//END
		
		cvFindStereoCorrespondenceBM(img1r, img2r, disp, BMState);
		
		// BEGIN si el diezmado se hace DESPUES de rectificar y la calibracion con imgs SIN diezmar
		if (diezmado > 1) {
			cvConvertScale(disp, disp, (double) diezmado);
		}
		
		double disp_min, disp_max, depth_min, depth_max;
		
		cvMinMaxLoc(disp, &disp_min, &disp_max);
		
		if(verbose_level >= 2) fprintf(stderr, "ii:%d;  disparity min: %f,  max %f\n", ii,disp_min, disp_max);
		
		cvReprojectImageTo3D( disp , depth, Q); 
		
		cvSplit(depth, depth_X, depth_Y, depth_Z, NULL);
		DistFromCam(depth, depth_R);
		
		cvMinMaxLoc(depth_Z, &depth_min, &depth_max);
		if(verbose_level >= 2) fprintf(stderr, "depth Z min: %f,  max %f\n", depth_min, depth_max);
	
				
		Img2ColorGrade(img1r, disp,minDisp_diezmado,
					   depth_R,
					   display_dist_min,   //500 milimetros
					   display_dist_max,  // 4.5 m, 5500mm 
					   Lut,
					   dispColor);
		
		CImg<unsigned char>c_im1(img1r);
		CImg<unsigned char>c_im2(img2r);
		
		for (int ff=16; ff<alto; ff+=16) {
			c_im1.draw_line(0,ff, ancho-1,ff, black, 0.7);
		}
		for (int ff=16; ff<alto; ff+=16) {
			c_im2.draw_line(0,ff, ancho-1,ff,black, 0.7);
		}
	
		CImgList<unsigned char> c_rectif=(c_im1,c_im2);
		display_2.display(c_rectif);
	
		CImg<float>c_disp(disp);
		CImg<float>c_depth_X(depth_X);
		CImg<float>c_depth_Y(depth_Y);
		CImg<float>c_depth_Z(depth_Z);
		CImg<float>c_depth_R(depth_R);
		
		CImg<unsigned char>c_dispColor(dispColor);
		CImg<unsigned char>c_dispColor2(dispColor);
		
		if(display_1.mouse_y()>=0 && display_1.mouse_x()>=0 )
		{
			int yy = (float) display_1.mouse_y();
			int xx = (float) display_1.mouse_x();
			sprintf(bbuf,"(%d,%d)", xx, yy);
			c_dispColor2.draw_text(3,3,bbuf,white,black,0.8f,14+10/diezmado);
			
			if (c_disp(xx,yy,0,0)>=minDisp_diezmado) {
				sprintf(bbuf,"D:%1.2f", c_disp(xx,yy,0,0));
				c_dispColor2.draw_text(3,18+12/diezmado,bbuf,white,black,0.8f,14+10/diezmado);
				sprintf(bbuf,"R:%1.0f", c_depth_R(xx,yy,0,0));
				c_dispColor2.draw_text(3,2*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
				sprintf(bbuf,"X:%1.0f", c_depth_X(xx,yy,0,0));
				c_dispColor2.draw_text(3,3*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
				sprintf(bbuf,"Y:%1.0f", c_depth_Y(xx,yy,0,0));
				c_dispColor2.draw_text(3,4*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
				sprintf(bbuf,"Z:%1.0f", c_depth_Z(xx,yy,0,0));
				c_dispColor2.draw_text(3,5*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
				
				CImg<unsigned char> c_im1_c=c_im1;
				CImg<unsigned char> c_im2_c=c_im2;
				
				c_im1_c.draw_circle(xx,yy,3,black,1,1).draw_circle(xx,yy,4,white,1,1);
				int xxt = xx-(int)(c_disp(xx,yy,0,0)/diezmado);
				c_im2_c.draw_circle(xxt,yy,3,black,1,1).draw_circle(xxt,yy,4,white,1,1);
				
				c_rectif=(c_im1_c,c_im2_c);
			}
			else{
				sprintf(bbuf,"D:");
				c_dispColor2.draw_text(3,18+12/diezmado,bbuf,white,black,0.8f,14+10/diezmado);
				sprintf(bbuf,"Z:");
				c_dispColor2.draw_text(3,2*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);

				c_rectif=(c_im1,c_im2);
			}
		}	
		display_2.display(c_rectif);
		
		switch (FromSource) {
			case 0:
				display_1.display(c_dispColor2);
				break;
			case 1:
				sprintf(bbuf, "cam_%d", ii);
				display_1.display(c_dispColor2).set_title(bbuf);
				break;
			case 2:
				display_1.display(c_dispColor2).set_title(imageNames[0][ii].c_str());
				break;
	//		case 3:
	//		  display_1.display(c_dispColor2).set_title(shared_mem_text);
	//			break;

			default:
				break;
		}
		display_1.wait(1);  // de momento solo manejo eventos en display_1.
		
		if (display_1.is_keySPACE()) {
		  modo_pausa=1;
		}
		else if (display_1.is_keyQ() || display_1.is_keyESC())
		  {
		    break;
		  }
		else if (display_1.is_keyN())
		  {
		    if (modo_pausa) continue;
		  }
		else if (display_1.is_keyENTER())
		  {
		    modo_pausa=0;
		  }
		if (modo_pausa){
			while(1){
				display_1.wait();
				
				if(display_1.is_keyN()) {
					if (FromSource>1 && ii == nframes-1)
					{
						// para que si esta en modo pausa y 
						//FromSource ==2 (imagenes sueltas) si se pulsa N en la ultima imagen no se salga
						// se puede salir con la tecla Q
						ii = nframes - 2;  // al volver al inicio del bucle se incrementa y se vuelve a quedar en nframes-1
					}
					else {
						break;
					}
				}
				
				else if(display_1.is_keyP()) {
					ii = ii - 2;   
					if (ii < -1) ii=-1;
					break;
				}
				else if(display_1.is_keyB()) {
					ii = ii - 2;   
					if (ii < -1) ii=-1;
					break;
				}
				else if (display_1.is_keyESC() || display_1.is_keyQ()) {
					goto terminar;
				}
				else if (display_1.is_keyENTER())
				{
					fprintf(stderr, "en modo pausa pulsado ENTER\n");
					modo_pausa=0;
					break;
				}
				
				if(display_1.mouse_y()>=0 && display_1.mouse_x()>=0 )
				{
					int yy = (float) display_1.mouse_y();
					int xx = (float) display_1.mouse_x();
					c_dispColor2=c_dispColor;
					sprintf(bbuf,"(%d,%d)", xx, yy);
					c_dispColor2.draw_text(3,3,bbuf,white,black,0.8f,14+10/diezmado);
					
					if (c_disp(xx,yy,0,0)>=minDisp_diezmado) {
						sprintf(bbuf,"D:%1.2f", c_disp(xx,yy,0,0));
						c_dispColor2.draw_text(3,18+12/diezmado,bbuf,white,black,0.8f,14+10/diezmado);
						sprintf(bbuf,"R:%1.0f", c_depth_R(xx,yy,0,0));
						c_dispColor2.draw_text(3,2*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
						sprintf(bbuf,"X:%1.0f", c_depth_X(xx,yy,0,0));
						c_dispColor2.draw_text(3,3*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
						sprintf(bbuf,"Y:%1.0f", c_depth_Y(xx,yy,0,0));
						c_dispColor2.draw_text(3,4*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
						sprintf(bbuf,"Z:%1.0f", c_depth_Z(xx,yy,0,0));
						c_dispColor2.draw_text(3,5*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);
						
						CImg<unsigned char> c_im1_c=c_im1;
						CImg<unsigned char> c_im2_c=c_im2;
						c_im1_c.draw_circle(xx,yy,3,black,1,1).draw_circle(xx,yy,4,white,1,1);
						int xxt = xx-(int)(c_disp(xx,yy,0,0)/diezmado);
						c_im2_c.draw_circle(xxt,yy,3,black,1,1).draw_circle(xxt,yy,4,white,1,1);
						
						c_rectif=(c_im1_c,c_im2_c);
						
					}
					else{
						sprintf(bbuf,"D:");
						c_dispColor2.draw_text(3,18+12/diezmado,bbuf,white,black,0.8f,14+10/diezmado);
						sprintf(bbuf,"Z:");
						c_dispColor2.draw_text(3,2*(18+12/diezmado),bbuf,white,black,0.8f,14+10/diezmado);

						c_rectif=(c_im1,c_im2);
						
					}
				}
				display_2.display(c_rectif);
				display_1.display(c_dispColor2);
			}//while(1)
			
		}//if (modo_pausa) 
		
	} //while 1
	
	terminar:	
	gettimeofday(&tiempo1, NULL);
	timeval_subtract(&tiempo1,&tiempo6,&time_dif1);
	fprintf(stderr, "t1_s %d, t1_us %d\nt6_s %d, t6_us %d\ndf_s %d, df_us %d\n",
			          (int)tiempo1.tv_sec,(int)tiempo1.tv_usec,
					  (int)tiempo6.tv_sec,(int)tiempo6.tv_usec,
			          (int)time_dif1.tv_sec,(int)time_dif1.tv_usec);
	float ttt= time_dif1.tv_sec + (float)time_dif1.tv_usec / 1000000 ;
	fprintf(stderr, "ips: %f\n", (float)ii/ttt);
	// Release the capture device housekeeping
	if(captureA) cvReleaseCapture( &captureA ); 
	if(captureB) cvReleaseCapture( &captureB ); 

	return 0; 
}   
