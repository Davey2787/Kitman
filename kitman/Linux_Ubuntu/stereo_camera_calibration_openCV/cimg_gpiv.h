/******************************************************************************/
/*                                                                            */
/* Copyright (C) 1995-2007   	      		      		              */
/* Universidad Politecnica de Valencia (UPV) - Valencia - Spain             */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* CREATED BY :  Antonio -- 15-Oct-09                                     */
/******************************************************************************/



/******************************************************************************/
#ifndef D_CIMG_GPIV_H
#define D_CIMG_GPIV_H

#ifndef cimg_version
#error cimg_gpiv.h requires that CImg.h is included!
#endif

#include <math.h>
#if cimg_version >= 151
   CImg<T>  get_shared_plane (const unsigned int z0, const unsigned int c0=0) const {
		return get_shared_slice(z0, c0); }

   CImg<T> get_shared_line (const unsigned int y0, const unsigned int z0=0, const unsigned int c0=0) const {
		return get_shared_row (y0, z0, c0) ; }


   CImg<T> get_shared_lines(const unsigned int y0, const unsigned int y1,
                                const unsigned int z0=0, const unsigned int c0=0) const {
	   return get_shared_rows(y0,y1,z0,c0); }
       
   CImg<T> line (const unsigned int y0, const unsigned int z0=0, const unsigned int c0=0) const {
       return row (y0, z0, c0) ; }
       
       
    CImg<T> get_lines(const unsigned int y0, const unsigned int y1,
                                const unsigned int z0=0, const unsigned int c0=0) const {
        return get_rows(y0,y1,z0,c0); }
       
    CImg<T> lines(const unsigned int y0, const unsigned int y1,
                          const unsigned int z0=0, const unsigned int c0=0) const {
        return rows(y0,y1,z0,c0); }   

#endif


#if cimg_version >= 132
int dimx(void) const//__attribute__ ((deprecated))
{
	return width();
}
int dimy(void) const //__attribute__ ((deprecated))
{
	return height();
}
int dimz(void) const //__attribute__ ((deprecated))
{
	return depth();
}
int dimv(void) const //__attribute__ ((deprecated))
{
	return spectrum();
}


int dimx(void) //__attribute__ ((deprecated))
{
	return width();
}
int dimy(void)  //__attribute__ ((deprecated))
{
	return height();
}
int dimz(void)  //__attribute__ ((deprecated))
{
	return depth();
}
int dimv(void)  //__attribute__ ((deprecated))
{
	return spectrum();
}
T * ptr()
{
	return _data;
}

const T* ptr() const {
	return _data;
}

CImg<T>& transfer_to(CImg<T> & img) {
	/*     img.assign(*this); */
	/*       assign(); */
	/*       return img; */
	return move_to(img);
}

#endif
/********************************************************

 Para leer una img del demonio
 CImg(void *handle,char *texto) : is_shared(false) 

 ********************************************************/
//#include "cimg_morpho_plugin.h"

public:
/* int resultado_demonio; */
/* char texto_demonio[SHARED_TEXT_LENGTH]; */
/** 
 * 
 * 
 * @param handle: a un demonio inicializado 
 * @param texto : el texto recibido con la imagen
 * 
 * @return Constructor CImg Devuelve la siguiente imagen leida del demonio
 */


#if cimg_version >= 132
CImg(void *handle,char *texto,int *rcode_demonio) : _is_shared(false) 
#else
CImg(void *handle,char *texto,int *rcode_demonio) : is_shared(false) 
#endif
{

#if cimg_version >= 132
	_width=_height=_depth=_spectrum=0;
	_data=NULL;
#else
	width=height=depth=dim=0;
	data=NULL;
#endif


	memoriacompartida *mem;
	struct imagencompartida *shared_image;
	// int anch,alt,bits;

	// union semun sem_semctl;
	struct mimensaje mensaje;
	int terminar_de_esperar;



	mem=(memoriacompartida *)handle;
	if(mem==NULL)
	{
		fprintf(stderr,"Handle nulo en escribe_imagen_en_memoria_compartida\n");
		*rcode_demonio = NULL_HANDLE;


		return;
	}


	shared_image=mem->shared_image;

	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		*rcode_demonio = A_TERMINAR;
#if cimg_version >= 132
		_width=_height=_depth=_spectrum=0;
		_data=NULL;
#else
		width=height=depth=dim=0;
		data=NULL;
#endif


		return;
	}



	terminar_de_esperar=0;
	do
	{
		//Espero a que me llegue el mensaje de que puedo leer
		if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),PUEDES_LEER,0)==-1)
		{
			if(errno!= EINTR ) //El error se soluciona volviendo a repetir la llamada. si errno==EINTR
			{
				//	      perror(strerror(errno));
				*rcode_demonio = ERROR_DE_MENSAJES;
			}
		}
		else //No se ha producido error en msgrcv
			terminar_de_esperar=1;
	}while(!terminar_de_esperar);



	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		*rcode_demonio = A_TERMINAR;
#if cimg_version >= 132
		_width=_height=_depth=_spectrum=0;
		_data=NULL;
#else
		width=height=depth=dim=0;
		data=NULL;
#endif


		return;

		//      exit(0);
	}



	if(shared_image->width<0) //Son datos jpeg de tamaño shared_image->height
	{

#ifdef cimg_use_jpeg
#if cimg_version >= 132
		_load_jpeg_mem(shared_image->data, shared_image->height);
		if (width() > 0 && height() >0 )
			*rcode_demonio = 0;
		else
			*rcode_demonio = -1;
#else
		fprintf(stderr,"Reading jpeg from daemon not supported, compile with cimg_use_jpeg\n");
		*rcode_demonio = -1;
#endif
#else
		fprintf(stderr,"Reading jpeg from daemon not supported, compile with cimg_use_jpeg\n");
		*rcode_demonio = -1;
#endif
	}



	//Bueno, aqui tras esperar tengo una imagen
	else
	{

#if cimg_version >= 132
		_width = (unsigned int) shared_image->width;
		_height= (unsigned int) shared_image->height;
		_depth=1;

		if (shared_image->bpp==8)
			_spectrum=1;
		else
			_spectrum=3;
		_data = new T[size()];
		if(NULL==_data)
#else
	width = (unsigned int) shared_image->width;
		height= (unsigned int) shared_image->height;
		depth=1;


		if (shared_image->bpp==8)
			dim=1;
		else
			dim=3;
		data = new T[size()];
		if(NULL==data)
#endif




{
			fprintf(stderr,"Error  allocando imagen de lectura\n");
			*rcode_demonio = ERROR_DE_MENSAJES_3;
}


		//Copio los pixels

		//   memcpy(imagen->ibuff,shared_image->data,shared_image->width*shared_image->height*shared_image->bpp/8);
		/*     if (0==strcmp(pixel_type(),"unsigned char")) */
		/*       { */
		unsigned int kk;
		unsigned int ccc;

		if(8==shared_image->bpp) //grises:hay que invertir para dejar primera fila arriba
		{
			if (0==strcmp(pixel_type(),"unsigned char"))
			{
#if cimg_version >= 132
				for(kk=0;kk<_height;kk++)
					memcpy(_data+(_height-1-kk)*_width,shared_image->data+kk*_width,_width);
#else	
				for(kk=0;kk<height;kk++)
					memcpy(data+(height-1-kk)*width,shared_image->data+kk*width,width);
#endif
			}
			else
			{
				unsigned char *psrc;
				T *pdest;
#if cimg_version >= 132
				for(kk=0;kk<_height;kk++)
				{
					psrc=shared_image->data+kk*_width;
					pdest=_data+(_height-1-kk)*_width;
					for (ccc=0;ccc<_width;ccc++)
					{
						pdest[ccc]=(T)psrc[ccc];
					}
				}
#else
	for(kk=0;kk<height;kk++)
	{
		psrc=shared_image->data+kk*width;
		pdest=data+(height-1-kk)*width;
		for (ccc=0;ccc<width;ccc++)
		{
			pdest[ccc]=(T)psrc[ccc];
		}
	}
#endif

			}
		}
		else //color
		{
			T *projo,*pverde,*pazul;
			int plane_size;

			int width3;
			unsigned char *psrc;
#if cimg_version >= 132
			width3=3*_width;
			plane_size=_width*_height;

			for(kk=0;kk<_height;kk++)
			{
				projo=_data+(_height-1-kk)*_width;
				pverde=projo+plane_size;
				pazul=pverde+plane_size;
				psrc=shared_image->data+kk*width3;
				for(ccc=0;ccc<_width;ccc++)
				{
					pazul[ccc]=*psrc;
					psrc++;
					pverde[ccc]=*psrc;
					psrc++;
					projo[ccc]=*psrc;
					psrc++;

				}

			}
#else

	width3=3*width;
plane_size=width*height;

for(kk=0;kk<height;kk++)
{
	projo=data+(height-1-kk)*width;
	pverde=projo+plane_size;
	pazul=pverde+plane_size;
	psrc=shared_image->data+kk*width3;
	for(ccc=0;ccc<width;ccc++)
	{
		pazul[ccc]=*psrc;
		psrc++;
		pverde[ccc]=*psrc;
		psrc++;
		projo[ccc]=*psrc;
		psrc++;

	}

}
#endif
		}

		/*       }// if (0==strcmp(pixel_type(),"unsigned char")) */
		/*     else */
		/*       { */
		/* 	//Para completar */
		/*       } */


	}


	strncpy(texto,shared_image->text,SHARED_TEXT_LENGTH-1);

	//LE DIGO Ahora al servidor que puede escribir (si es que estaba esperando)
	mensaje.message_type=PUEDES_ESCRIBIR;

	if(msgsnd(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),0)==-1)
	{
		fprintf(stderr,"No se ha podido dar permiso para leer\n");
		*rcode_demonio = ERROR_DE_MENSAJES_3;
	}
	*rcode_demonio = 0;



}




#if cimg_version >= 132
CImg(void *handle, CImg<unsigned short> & depth, char *texto,int *rcode_demonio) : _is_shared(false)

{

	memoriacompartida *mem;
	struct imagencompartida *shared_image;
	// int anch,alt,bits;

	// union semun sem_semctl;
	struct mimensaje mensaje;
	int terminar_de_esperar;



	mem=(memoriacompartida *)handle;
	if(mem==NULL)
	{
		fprintf(stderr,"Handle nulo en escribe_imagen_en_memoria_compartida\n");
		*rcode_demonio = NULL_HANDLE;
		_width=_height=_depth=_spectrum=0;
		_data=NULL;
		depth.assign();
		return;
	}


	shared_image=mem->shared_image;

	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		*rcode_demonio = A_TERMINAR;
		_width=_height=_depth=_spectrum=0;
		_data=NULL;
		depth.assign();
		return;
	}



	terminar_de_esperar=0;
	do
	{
		//Espero a que me llegue el mensaje de que puedo leer
		if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),PUEDES_LEER,0)==-1)
		{
			if(errno!= EINTR ) //El error se soluciona volviendo a repetir la llamada. si errno==EINTR
			{
				//	      perror(strerror(errno));
				*rcode_demonio = ERROR_DE_MENSAJES;
			}
		}
		else //No se ha producido error en msgrcv
			terminar_de_esperar=1;
	}while(!terminar_de_esperar);



	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		*rcode_demonio = A_TERMINAR;
		_width=_height=_depth=_spectrum=0;
		_data=NULL;
		depth.assign();
		return;
	}



	if(shared_image->width<0) //Son datos jpeg de tamaño shared_image->height
	{


		*rcode_demonio = -1;
		fprintf(stderr,"Error: JPEG data not supported from daemon with depth\n");
		_width=_height=_depth=_spectrum=0;
		_data=NULL;
		depth.assign();


		return;
	}



	//Bueno, aqui tras esperar tengo una imagen


	_width = (unsigned int) shared_image->width;
	_height= (unsigned int) shared_image->height;
	_depth=1;

	if (shared_image->bpp==8)
		_spectrum=1;
	else
		_spectrum=3;

	if(_width * _height * _depth * _spectrum + _width * _height * sizeof(unsigned short) > NUM_SHARED_PIXELS)
	{
		*rcode_demonio = -1;
		fprintf(stderr,"Error: Depth Image does not fit in shared memory. Width =%d Height =%d, Spectrum=%d SharedMemSize=%d\n",
				_width, _height, _spectrum, NUM_SHARED_PIXELS );
		_width=_height=_depth=_spectrum=0;
		_data=NULL;
		depth.assign();
		return;
	}
	_data = new T[size()];
	if(NULL==_data)
	{
		fprintf(stderr,"Error  allocando imagen de lectura\n");
		*rcode_demonio = ERROR_DE_MENSAJES_3;
		depth.assign();
		return;
	}


	//Copio los pixels

	//   memcpy(imagen->ibuff,shared_image->data,shared_image->width*shared_image->height*shared_image->bpp/8);
	/*     if (0==strcmp(pixel_type(),"unsigned char")) */
	/*       { */
	unsigned int kk;
	unsigned int ccc;

	if(8==shared_image->bpp) //grises:hay que invertir para dejar primera fila arriba
	{
		if (0==strcmp(pixel_type(),"unsigned char"))
		{
			for(kk=0;kk<_height;kk++)
				memcpy(_data+(_height-1-kk)*_width,shared_image->data+kk*_width,_width);
		}
		else
		{
			unsigned char *psrc;
			T *pdest;
			for(kk=0;kk<_height;kk++)
			{
				psrc=shared_image->data+kk*_width;
				pdest=_data+(_height-1-kk)*_width;
				for (ccc=0;ccc<_width;ccc++)
				{
					pdest[ccc]=(T)psrc[ccc];
				}
			}


		}
	}
	else //color
	{
		T *projo,*pverde,*pazul;
		int plane_size;

		int width3;
		unsigned char *psrc;

		width3=3*_width;
		plane_size=_width*_height;

		for(kk=0;kk<_height;kk++)
		{
			projo=_data+(_height-1-kk)*_width;
			pverde=projo+plane_size;
			pazul=pverde+plane_size;
			psrc=shared_image->data+kk*width3;
			for(ccc=0;ccc<_width;ccc++)
			{
				pazul[ccc]=*psrc;
				psrc++;
				pverde[ccc]=*psrc;
				psrc++;
				projo[ccc]=*psrc;
				psrc++;

			}

		}

	}

	// Get Depth

	int total_size = size();
	unsigned char * init =  shared_image->data + total_size;
	depth.assign( width() , height() );
	memcpy( depth.data() , init, width() * height() * sizeof(unsigned short));







	strncpy(texto,shared_image->text,SHARED_TEXT_LENGTH-1);

	//LE DIGO Ahora al servidor que puede escribir (si es que estaba esperando)
	mensaje.message_type=PUEDES_ESCRIBIR;

	if(msgsnd(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),0)==-1)
	{
		fprintf(stderr,"No se ha podido dar permiso para leer\n");
		*rcode_demonio = ERROR_DE_MENSAJES_3;
	}
	*rcode_demonio = 0;



}//CImg<float> & depth


#endif



CImg<T> &assign(void *handle,char *texto,int *resultado_demonio)
		{

	CImg<T> result(handle,texto,resultado_demonio);
	return result.transfer_to(*this);
		}



CImg<T> &assign(void *handle, CImg<unsigned short> & depth, char *texto,int *resultado_demonio)
		{

	CImg<T> result(handle,  depth, texto, resultado_demonio);
	return result.transfer_to(*this);
		}


CImg<T>& tocolor(void)
		{


#if cimg_version >= 132
	if(spectrum()==3) //No hacer nada
		return *this;
	CImg<T> result(width(),height(),depth(),3);

#else
	if(dimv()==3) //No hacer nada
		return *this;
	CImg<T> result(dimx(),dimy(),dimz(),3);
#endif


	CImg<T> R=result.get_shared_channel(0);
	CImg<T> G=result.get_shared_channel(1);
	CImg<T> B=result.get_shared_channel(2);

	R=(*this);
	G=(*this);
	B=(*this);
	return result.transfer_to(*this);
		}

//--------------------------------------------

// Version no inplace que llama a la inplace
CImg<T> get_tocolor() const {

	return CImg<T>(*this,false).tocolor();
}


//-----------------------------------------------------------
CImg<T> get_togray(void) const
		{

	unsigned int d;
	unsigned  int plane_size;
	T *tmp;
	CImg <T> resultado;

#if cimg_version >= 132
	if(1==_spectrum)
	{
		resultado=(*this);
		return resultado;
	}

#else
	if(1==dimv())
	{
		resultado=(*this);
		return resultado;
	}
#endif


#if cimg_version >= 132
	resultado.assign(_width,_height,_depth,1);
#else
	resultado.assign(dimx(),dimy(),dimz(),1);
#endif




	T dos,cuatro;



#if cimg_version >= 132
	plane_size=_width*_height*_depth;
#else
	plane_size=dimx()*dimy()*dimz();
#endif


	T *R,*G,*B;

#if cimg_version >= 132
	R=_data;
#else
	R=data;
#endif

	G=R+plane_size;
	B=G+plane_size;

	dos=(T) 2;
	cuatro=(T) 4;

#if cimg_version >= 132
	tmp=  resultado._data;
#else
	tmp=  resultado.data;
#endif

	for(d=0;d<plane_size;d++)//Para cada plano de color
	{
		tmp[d]=(R[d]+dos*G[d]+B[d])/4;
	}

	//Ahora libero data (imag original) y lo apunto a tmp;
	return resultado;

		}
/*****************************************************/


/*********************************************************+
 Si es de grises no hace nada
 Si es de color la convierte a grises "inplace"

 ********************************************************/

CImg<T>& togray(void)
		{
	//Reservo memoria para resultado

	T *tmp;

	unsigned int d;
	unsigned int plane_size;

	T dos,cuatro;
#if cimg_version >= 132
	if(_spectrum==1) //No hacer nada
		return *this;

#else
	if(dimv()==1) //No hacer nada
		return *this;

#endif

#if cimg_version >= 132
	plane_size=width()*height()*depth();
#else
	plane_size=dimx()*dimy()*dimz();
#endif


	tmp=  new T [plane_size];
	T *R,*G,*B;
#if cimg_version >= 132
	R=_data;
#else
	R=data;
#endif
	G=R+plane_size;
	B=G+plane_size;

	dos=(T) 2;
	cuatro=(T) 4;

	for(d=0;d<plane_size;d++)//Para cada plano de color
	{
		tmp[d]=(R[d]+dos*G[d]+B[d])/cuatro;
	}

	//Ahora libero data (imag original) y lo apunto a tmp;

#if cimg_version >= 132
	_spectrum=1;
	delete [] _data ;
	_data=tmp;

#else
	dim=1;
	delete [] data ;
	data=tmp;

#endif

	return *this;

		}


#if cimg_version >= 132
/*------------------------------------------------------------------------
 * to_daemon(void *handle, const CImg<float> & depth, const char *texto,int *resultado_demonio)

 * escribe una imagen cimg en memoria compartida. 
 y su profundidad (Kinect)
 * Lo que hace es que detrás de los pixels mete la matriz de float
 *------------------------------------------------------------------------*/

void to_daemon(void *handle, const CImg<unsigned short> & depth, const char *texto,int *resultado_demonio)
{
	memoriacompartida *mem;
	struct imagencompartida *shared_image;
	int anch,alt,bits;
	int tam;
	//  union semun sem_semctl;
	struct mimensaje mensaje;
	int terminar_de_esperar;

	mem=(memoriacompartida *)handle;
	if(mem==NULL)
	{
		fprintf(stderr,"Handle nulo en escribe_imagen_en_memoria_compartida\n");
		*resultado_demonio= NULL_HANDLE;
		return;
	}

	anch=dimx();
	alt=dimy();
	bits=dimv()*8;

	if(! (this->is_sameXY(depth)) || depth.depth()> 1 || depth.spectrum() >1)
	{
		fprintf(stderr,"Image-Depth Size mismatch\n");
		*resultado_demonio= ERROR_DE_MENSAJES_3;
		return;
	}
	if(anch<=0 || alt <= 0 || (bits!=8 && bits!=24) || this->dimz()>1)
	{
		fprintf(stderr,"Imagen CImg a compartir invalida \n");
		*resultado_demonio=INVALID_IMAGE_TO_SHARE;
		return ;
	}

	shared_image=mem->shared_image;

	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA_SERVER,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		//      printf("Recibido A terminar\n");
		*resultado_demonio=A_TERMINAR;
		return;
	}


	terminar_de_esperar=0;
	do
	{

		//Espero a que me llegue el mensaje de que puedo leer
		if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),PUEDES_ESCRIBIR,0)==-1)
		{
			if(errno!= EINTR ) //El error se soluciona volviendo a repetir la llamada. si errno==EINTR
			{
				perror(strerror(errno));
				*resultado_demonio= ERROR_DE_MENSAJES;
				return;
			}
		}
		else //No se ha producido error en msgrcv
			terminar_de_esperar=1;
		if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA_SERVER,IPC_NOWAIT)!=-1)//Me dicen que termine
		{
			*resultado_demonio= A_TERMINAR;
			return;
		}


	}while(!terminar_de_esperar);






	//Por si mientras esperaba ha llegado el momento de terminar
	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA_SERVER,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		// printf("Recibido A terminar 2\n");
		*resultado_demonio= A_TERMINAR;
		return;
	}



	//Aqui se que puedo leer
	//  printf("Escribiendo imagen compartida\n");
	tam=anch*alt*bits/8;
	int anch4=anch*bits/8;
	T *src, *R,*G,*B;
	int planesize;
	unsigned char *dest;
	planesize=anch*alt;
	if(tam + planesize * sizeof(unsigned short) < NUM_SHARED_PIXELS)
	{

		if(8==bits)
		{
			for(int f=0;f<alt;f++)
			{
				src=data()+f*dimx();
				dest=shared_image->data+(alt-1-f)*anch4;
				for(int c=0;c<anch;c++)
				{
					dest[c]=src[c];
				}
			}
		}
		else//bits==24
				{
			src=data();
			for(int f=0;f<alt;f++)
			{
				R=data()+f*dimx();
				G=R+planesize;
				B=G+planesize;
				dest=shared_image->data+(alt-1-f)*anch4;
				for(int c=0;c<anch;c++)
				{
					int c3=3*c;
					dest[c3]=B[c];
					dest[c3+1]=G[c];
					dest[c3+2]=R[c];
				}
			}
				}//else bits=24


		//Copy Depth
		int total_size = size();
		unsigned char *init = shared_image->data + total_size;
		memcpy(init,depth.data(),planesize *sizeof(unsigned short));


	}
	else
	{
		fprintf(stderr,"Muchos pixels\n");
		*resultado_demonio= ERROR_DE_MENSAJES_3;
		return;
	}

	shared_image->width=anch;
	shared_image->height=alt;
	shared_image->bpp=bits;


	if(strlen(texto)<SHARED_TEXT_LENGTH)
		strcpy(shared_image->text,texto);
	else
		strcpy(shared_image->text,"");

	//Ahora le digo al cliente que ya puede leer

	mensaje.message_type=PUEDES_LEER;

	if(msgsnd(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),0)==-1)
	{
		fprintf(stderr,"No se ha podido dar permiso para leer\n");
		*resultado_demonio= ERROR_DE_MENSAJES_3;
		return;
	}
	*resultado_demonio= 0;
	return;
}//to_daemon(void *handle, const CImg<float> & depth, const char *texto,int *resultado_demonio)




/*------------------------------------------------------------------------
 * to_daemon(void *handle, const char *texto,int *resultado_demonio)

 * escribe una imagen cimg en memoria compartida. 
 y su profundidad (Kinect)
 * Lo que hace es que detrás de los pixels mete la matriz de float
 *------------------------------------------------------------------------*/

void to_daemon(void *handle, const char *texto,int *resultado_demonio)
{
	memoriacompartida *mem;
	struct imagencompartida *shared_image;
	int anch,alt,bits;
	int tam;
	//  union semun sem_semctl;
	struct mimensaje mensaje;
	int terminar_de_esperar;

	mem=(memoriacompartida *)handle;
	if(mem==NULL)
	{
		fprintf(stderr,"Handle nulo en escribe_imagen_en_memoria_compartida\n");
		*resultado_demonio= NULL_HANDLE;
		return;
	}

	anch=dimx();
	alt=dimy();
	bits=dimv()*8;


	if(anch<=0 || alt <= 0 || (bits!=8 && bits!=24) || this->dimz()>1)
	{
		fprintf(stderr,"Imagen CImg a compartir invalida \n");
		*resultado_demonio=INVALID_IMAGE_TO_SHARE;
		return ;
	}

	shared_image=mem->shared_image;

	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA_SERVER,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		//      printf("Recibido A terminar\n");
		*resultado_demonio=A_TERMINAR;
		return;
	}


	terminar_de_esperar=0;
	do
	{

		//Espero a que me llegue el mensaje de que puedo leer
		if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),PUEDES_ESCRIBIR,0)==-1)
		{
			if(errno!= EINTR ) //El error se soluciona volviendo a repetir la llamada. si errno==EINTR
			{
				perror(strerror(errno));
				*resultado_demonio= ERROR_DE_MENSAJES;
				return;
			}
		}
		else //No se ha producido error en msgrcv
			terminar_de_esperar=1;
		if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA_SERVER,IPC_NOWAIT)!=-1)//Me dicen que termine
		{
			*resultado_demonio= A_TERMINAR;
			return;
		}


	}while(!terminar_de_esperar);






	//Por si mientras esperaba ha llegado el momento de terminar
	if(msgrcv(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),TERMINA_YA_SERVER,IPC_NOWAIT)!=-1)//Me dicen que termine
	{
		// printf("Recibido A terminar 2\n");
		*resultado_demonio= A_TERMINAR;
		return;
	}



	//Aqui se que puedo leer
	//  printf("Escribiendo imagen compartida\n");
	tam=anch*alt*bits/8;
	int anch4=anch*bits/8;
	T *src, *R,*G,*B;
	int planesize;
	unsigned char *dest;
	planesize=dimx()*dimy();
	if(tam< NUM_SHARED_PIXELS)
	{

		if(8==bits)
		{
			for(int f=0;f<alt;f++)
			{
				src=data()+f*dimx();
				dest=shared_image->data+(alt-1-f)*anch4;
				for(int c=0;c<anch;c++)
				{
					dest[c]=src[c];
				}
			}
		}
		else//bits==24
				{
			src=data();
			for(int f=0;f<alt;f++)
			{
				R=data()+f*dimx();
				G=R+planesize;
				B=G+planesize;
				dest=shared_image->data+(alt-1-f)*anch4;
				for(int c=0;c<anch;c++)
				{
					int c3=3*c;
					dest[c3]=B[c];
					dest[c3+1]=G[c];
					dest[c3+2]=R[c];
				}
			}
				}//else bits=24

	}
	else
	{
		fprintf(stderr,"Muchos pixels\n");
		*resultado_demonio= ERROR_DE_MENSAJES_3;
		return;
	}

	shared_image->width=anch;
	shared_image->height=alt;
	shared_image->bpp=bits;


	if(strlen(texto)<SHARED_TEXT_LENGTH)
		strcpy(shared_image->text,texto);
	else
		strcpy(shared_image->text,"");

	//Ahora le digo al cliente que ya puede leer

	mensaje.message_type=PUEDES_LEER;

	if(msgsnd(mem->msgid,&mensaje,sizeof(struct mimensaje)- sizeof(long int),0)==-1)
	{
		fprintf(stderr,"No se ha podido dar permiso para leer\n");
		*resultado_demonio= ERROR_DE_MENSAJES_3;
		return;
	}
	*resultado_demonio= 0;
	return;
}//to_daemon(void *handle, char *texto)
#endif







/***********************************************
 CImg<T> get_filtvarx(double  sigmabottom,double sigmatop=0.0)
 ************************************************/

CImg<T> get_filtvarx(double  sigmabottom,double sigmatop=0.0)
		{
	CImg<T> resultado(*this);

#if cimg_version >= 132

	CImg<double>taus(height(),1);
	CImg<double>as(height(),1);
	CImg<double>bs(height(),1);

	int tamy=height();
#else

	CImg<double>taus(dimy(),1);
	CImg<double>as(dimy(),1);
	CImg<double>bs(dimy(),1);

	int tamy=dimy();
#endif

	double tamyf=tamy;
	//Calculo parametros variantes

	cimg_forX(taus,x)
	{
		taus[x]=fabs(((sigmabottom-sigmatop)*x)/tamyf+1.0e-8+sigmatop);
		as[x]=std::exp(-1/taus[x]);
		bs[x]=1.0-as[x];
	}
#if cimg_version >= 132
	cimg_forZC(*this,z,v)
#else
	cimg_forZV(*this,z,v)
#endif
	{
		CImg<T> input=get_shared_plane(z,v);
		CImg<T> result=resultado.get_shared_plane(z,v);

		//Filtrado horizontal

		cimg_forY(*this,y)
		{
			double sigmax;
#if cimg_version >= 132 
			sigmax=fabs((sigmabottom-sigmatop)*y/(*this).height()+sigmatop+1.0e-8);
#else
			sigmax=fabs((sigmabottom-sigmatop)*y/(*this).dimy()+sigmatop+1.0e-8);
#endif
			CImg<T> linea=input.get_shared_line(y);
			CImg<T> lineas=result.get_shared_line(y);

			lineas=linea.get_deriche(sigmax,0,'X');

		}


	}
	return resultado;
		}






/***********************************************
 CImg<T> & filtvarx(double sigmabottom,double sigmatop=0.0)
 ************************************************/
CImg<T> & filtvarx(double sigmabottom,double sigmatop=0.0)
		{
	return get_filtvarx(sigmabottom,sigmatop).transfer_to(*this);
		}




/***********************************************
 CImg<T> get_filtvary(double  sigmabottom,double sigmatop=0.0)
 ************************************************/

CImg<T> get_filtvary(double  sigmabottom,double sigmatop=0.0)
		{
	CImg<T> resultado(*this);
	int dx,dy;
#if cimg_version >= 132
	dx=width();
	dy=height();
#else
	dx=dimx();
	dy=dimy();
#endif

	CImg<double>taus(dy,1);
	CImg<double>as(dy,1);
	CImg<double>bs(dy,1);

	double *tausp,*asp,*bsp;
	double tamyf=double(dy);
	//Calculo parametros variantes

#if cimg_version >= 132
	tausp=taus.data();
	asp=as.data();
	bsp=bs.data();
#else
	tausp=taus.data;
	asp=as.data;
	bsp=bs.data;
#endif

	for(int x=0;x<dy;x++)
	{
		tausp[x]=fabs(((sigmabottom-sigmatop)*x)/tamyf+1.0e-15+sigmatop);
		asp[x]=std::exp(-1/tausp[x]);
		bsp[x]=1.0-asp[x];
	}

#if cimg_version >= 132
	cimg_forZC(*this,z,v)
#else
	cimg_forZV(*this,z,v)
#endif
	{
		CImg<T> inputi=get_shared_plane(z,v);
		CImg<T> resulti=resultado.get_shared_plane(z,v);

		T *input;
		T *result;

#if cimg_version >= 132
		input=inputi.data();
		result=resulti.data();
#else
		input=inputi.data;
		result=resulti.data;
#endif    

		//Filtrado vertical


		for(int x=0;x<dx;x++)
			result[x]=input[x];

		T *filainput;
		T *filaresult;
		T *filaresultanterior;
		T *filaresultsiguiente;

		for(int y=1;y<dy;y++)
		{
			filainput=input+y*dx;
			filaresult=result+y*dx;
			filaresultanterior=result+(y-1)*dx;

			double a,b;
			a=as[y];
			b=bs[y];

			for(int x=0;x<dx;x++)
			{
				filaresult[x]=b*filainput[x]+a*filaresultanterior[x];
			}


		}

		for(int y=dy-2;y>=0;y--)
		{
			double a,b;
			a=as[y];
			b=bs[y];
			filainput=input+y*dx;
			filaresult=result+y*dx;
			filaresultsiguiente=result+(y+1)*dx;


			for(int x=0;x<dx;x++)
			{
				filaresult[x]=b*filainput[x]+a*filaresultsiguiente[x];
			}





		}
	}
	return resultado;
		}


CImg<T> & filtvary(double sigmabottom,double sigmatop=0.0)
		{
	return get_filtvary(sigmabottom,sigmatop).transfer_to(*this);
		}




/**************************** filtvar ************************************
 Calcula un filtrado variable dependiendo de la posición vertical.
 Arriba realiza un blur de sigma =0 mientras que abajo implementa 
 un blur de valor sigma.

 En sentido horizontal, realiza un blur gaussiano, mientras que en vertical la respuesta impulsiva es exponencial bilateral

 Antonio, enero 2009
 *****************************************************************************/

CImg<T> get_filtvar(double  sigmabottom,double sigmatop=0.0)
		{
	CImg<T> resultado;
	resultado = this->get_filtvarx(sigmabottom,sigmatop).filtvary(sigmabottom,sigmatop);
	return resultado;
		}







CImg<T> & filtvar(double sigmabottom,double sigmatop=0.0)
		{
	return get_filtvar(sigmabottom,sigmatop).transfer_to(*this);
		}

public:
/******************************************************************
 CImg<double> get_integral_image()
 Computes the integral image for each color channel.
 If the input has dimz()>1 it also integrates along the z direction.

 The output at x,y,z is the sum for all x', y',z' such that 0<=x'<=x, 0<=y'<=y 0<=z'<=z

 If same_size = true integral and original are same size if not integral is of size (dimx+1, dimy+1,Z,C)

 Auxiliary function for moving average filters.
 ***********************************************************************/
CImg<double> get_integral_image(bool same_size = true) const
{
	int dx,dy,dz,dv;

	dx=dimx();
	dy=dimy();
	dz=dimz();
	dv=dimv();

	if (same_size) // same size
	{
		CImg<double>res(dx,dy,dz,dv);
#if cimg_version >= 132
		cimg_forZC(res,z,v)
#else
		cimg_forZV(res,z,v)
#endif
		{
			CImg<T> in=this->get_shared_plane(z,v);
			CImg<double> out=res.get_shared_plane(z,v);
			int x,y;
			y=0;
			float sumrow;
			out(0,y,z) = in(0,y);
			for(x=1;x<dx;x++){
				out(x,y) = out( x-1 , y) +  in(x,y);
			}

			for(y=1;y<dy;y++)
			{
				sumrow = in(0,y);
				out(0,y)=out(0,y-1)+in(0,y);
				for(x=1;x<dx;x++)
				{
					sumrow += in(x,y);
					out(x,y) = out(x,y-1) + sumrow;
				}
			}
		}
		return res;
	}
	else
	{
		CImg<double>res(dx+1,dy+1,dz,dv);
#if cimg_version >= 132
		cimg_forZC(res,z,v)
#else
		cimg_forZV(res,z,v)
#endif
		{
			CImg<T> in=this->get_shared_plane(z,v);
			CImg<double> out=res.get_shared_plane(z,v);
			int x,y;
			y=0;
			float sumrow;
			//		  out(0,y,z) = in(0,y);
			for(x=0;x<dx+1;x++)
				out(x,0)=0;

			out(0,y+1,z) = 0;
			out(1,y+1,z) = in(0,y);

			for(x=1;x<dx;x++){
				//			  out(x,y) = out( x-1 , y) +  in(x,y);
				out(x+1,y+1) = out( x , y+1) +  in(x,y);
			}

			for(y=1;y<dy;y++)
			{
				sumrow = in(0,y);
				//			  out(0,y)=out(0,y-1)+in(0,y);
				out(1,y)=out(1,y-1)+in(0,y);

				for(x=1;x<dx;x++)
				{
					sumrow += in(x,y);
					//				  out(x,y) = out(x,y-1) + sumrow;
					out(x+1,y+1) = out(x+1,y) + sumrow;

				}
			}
		}
		return res;
	}
}


/**************************************************************************
 CImg<T>& meanfilter(const unsigned int size) {//square in place
 CImg<T> get_meanfilter(const int size){ //square
 CImg<T>& meanfilter(const unsigned int nx,const unsigned int ny) {//rectangle in place
 CImg<T> get_meanfilter(const int nx,const int ny)//rectangle

 No filtering in the z dimension.  cimg_forZV: the same for each plane/channel

 Moving average filter
 ***************************************************************************/

CImg<T>& meanfilter(const unsigned int size) {//square in place
	if (size<2) return *this;
	return get_meanfilter(size,size).transfer_to(*this);
}
//-----------------------------------------------------------
CImg<T> get_meanfilter(const int size)const { //square
	return get_meanfilter(size,size);
}
//-----------------------------------------------------------
CImg<T>& meanfilter(const unsigned int nx,const unsigned int ny) {//rectangle in place
	if (nx<2 && ny <2) return *this;
	return get_meanfilter(nx,ny).transfer_to(*this);
}
//-----------------------------------------------------------

//----- Main function
CImg<T> get_meanfilter(const int nx,const int ny) const //rectangle
		{
	CImg<T> res;
	if(1==nx && 1==ny)
	{
		res=*this;
		return res;
	}
	res.assign(this->dimx(),this->dimy(),this->dimz(),this->dimv());
	CImg<double> ones;
	ones.assign(this->dimx(),this->dimy()).fill(1.0);


	CImg<double> sumImage = this->get_sumfilter(nx,ny);
	CImg<double> npix = ones.get_sumfilter(nx,ny);


	int z,c,o;

	for( z= 0; z< res.depth(); z++)
		for(  c = 0; c< res.spectrum(); c++)
		{
			CImg<T>resp = res.get_shared_plane(z,c);
			CImg<double>sump = sumImage.get_shared_plane(z,c);

			for(  o = 0; o < resp.size() ; o++)
				resp[o] = sump[o] / npix[o];
		}
	return res;
		}



/***************************************************************************
 get_sumfilter
 It computes the sum of the pixels in a rectangular neighborhood centered at each pixel.
 IMPORTANT: ALWAYS returns a DOUBLE image
 ***************************************************************************/

CImg<double> get_sumfilter(const int size)const {
	return get_sumfilter(size,size);
}


CImg<double> get_sumfilter(int nx,int ny)const
		{
	CImg<double> res;

	if(1==nx && 1==ny)
	{
		res=*this;
		return res;
	}

	if(nx > dimx())
		nx = dimx();

	if(ny > dimy())
		ny = dimy();


	int nxf,nxb,nyf,nyb;
	nxf=(nx-1)/2;
	nxb=nxf-nx;//negative
	nyf=(ny-1)/2;
	nyb=nyf-ny;//negative
	res.assign(dimx(),dimy(),dimz(),dimv());
	res.fill(0);
	int x,lx1,lx2;
	int y,ly1,ly2;
	lx1=-nxb;
	lx2=dimx()-nxf;
	ly1=-nyb;
	ly2=dimy()-nyf;

#if cimg_version >= 132
	cimg_forZC(*this,z,v)
#else
	cimg_forZV(*this,z,v)
#endif
	{

		CImg<double> inte = this -> get_shared_plane(z,v).get_integral_image();
		CImg<double> out=res.get_shared_plane(z,v);

		for(x=0;x<lx1;x++)//Left side
		{
			for(y=0;y<ly1;y++)
				out(x,y)=inte(x+nxf,y+nyf);
			for(;y<ly2;y++)
			{
				out(x,y)=inte(x+nxf,y+nyf)-inte(x+nxf,y+nyb);

			}
			for(;y<dimy();y++)
				out(x,y)=inte(x+nxf,dimy()-1)-inte(x+nxf,y+nyb);
		}

		for(;x<lx2;x++)//Hor. central size
		{
			for(y=0;y<ly1;y++) //top
			{
				out(x,y)=inte(x+nxf,y+nyf)-inte(x+nxb,y+nyf);
			}
			for(y=ly1;y<ly2;y++) //vert. center
			{
				out(x,y)=inte(x+nxf,y+nyf)+inte(x+nxb,y+nyb)-inte(x+nxb,y+nyf)-inte(x+nxf,y+nyb);

			}
			for(y=ly2;y<dimy();y++) //bottom
			{
				out(x,y)=inte(x+nxf,dimy()-1)+inte(x+nxb,y+nyb)-
						inte(x+nxb,dimy()-1)-inte(x+nxf,y+nyb);

			}
		}



		for(;x<dimx();x++) //Rigth side
		{
			for(y=0;y<ly1;y++)
				out(x,y)=inte(dimx()-1,y+nyf)-inte(x+nxb,y+nyf);
			for(y=ly1;y<ly2;y++)
			{
				out(x,y)=inte(dimx()-1,y+nyf)-inte(dimx()-1,y+nyb)-inte(x+nxb,y+nyf)+inte(x+nxb,y+nyb);

			}
			for(;y<dimy();y++)
				out(x,y)=inte(dimx()-1,dimy()-1)-inte(dimx()-1,y+nyb)-inte(x+nxb,dimy()-1)+inte(x+nxb,y+nyb);
		}




	}
	return res;
		}


//! Devuelve el máximo de una imagen CImg (maxvalue) y sus coordenadas (xmax,ymax,zmax,vmax)
/**
 \param img Imagen de entrada para calcular su máximo
 \param posimax Vector con las coordenadas del máximo
 \param maxvalue Valor del máximo
 **/
void find_posmax(CImg<int> & posimax,T & maxvalue)
{
	T *p;
	T maximo;
	if(0==size())
	{
		posimax.assign(4).fill(-1);//Valor imposible: error
		maxvalue=0;
	}

#if cimg_version >= 132
	p=data();
#else
	p=ptr();
#endif


	maximo=*p;
	int xmax=0,ymax=0,zmax=0,cmax=0;

#if cimg_version >= 132
	cimg_forXYZC(*this,x,y,z,v)

#else
	cimg_forXYZV(*this,x,y,z,v)
#endif
	{
		if( !std::isnan(*p) )
		{
			if( (*p>maximo) || std::isnan(maximo) )
			{
				xmax=x;
				ymax=y;
				zmax=z;
				cmax=v;
				maximo=*p;
			}
		}
		p++;
	}

	posimax.assign(4);
	posimax[0]=xmax;
	posimax[1]=ymax;
	posimax[2]=zmax;
	posimax[3]=cmax;
	maxvalue=maximo;
}// find_posmax(CImg<int> & posimax,T & maxvalue)


//! Devuelve el maximo de una imagen CImg (maxvalue) y su offset respecto del primer elemento
/**

 \param posimax Vector con las coordenadas del máximo
 \param maxvalue Valor del máximo
 **/
T find_posmax(int &ind)
{
	T *p = data();
	T max = *p;
	ind = 0;
	cimg_foroff(*this, off)
	{
		if( !std::isnan(*p) )
		{
			if( (*p>max) || std::isnan(max) )
			{
				max = *p;
				ind = off;
			}
		}
		p++;
	}
	return max;
}


//! Devuelve el minimo de una imagen CImg (maxvalue) y sus coordenadas (xmin,ymin,zmin,vmin)
/**
 \param img Imagen de entrada para calcular su minimo
 \param posimax Vector con las coordenadas del minimo
 \param maxvalue Valor del máximo
 **/
void find_posmin(CImg<int> & posimin,T & minvalue)
{
	T *p;
	T minimo;
	if(0==size())
	{
		posimin.assign(4).fill(-1);//Valor imposible: error
		minvalue=0;
	}

#if cimg_version >= 132
	p=data();
#else
	p=ptr();
#endif


	minimo=*p;
	int xmax=0,ymax=0,zmax=0,cmax=0;

#if cimg_version >= 132
	cimg_forXYZC(*this,x,y,z,v)

#else
	cimg_forXYZV(*this,x,y,z,v)
#endif
	{
		if( !std::isnan(*p) )
		{
			if( (*p<minimo) || std::isnan(minimo) )
			{
				xmax=x;
				ymax=y;
				zmax=z;
				cmax=v;
				minimo=*p;
			}
		}
		p++;
	}

	posimin.assign(4);
	posimin[0]=xmax;
	posimin[1]=ymax;
	posimin[2]=zmax;
	posimin[3]=cmax;
	minvalue=minimo;
}// find_posmin(CImg<int> & posimin,T & minvalue)


//! Devuelve el minimo de una imagen CImg (minvalue) y su offset respecto del primer elemento
/**

 \param posimin Vector con las coordenadas del mínimo
 \param minvalue Valor del mínimo
 **/
T find_posmin(int &ind)
{
	T *p = data();
	T min = *p;
	ind = 0;
	cimg_foroff(*this, off)
	{
		if( !std::isnan(*p) )
		{
			if( (*p<min) || std::isnan(min) )
			{
				min = *p;
				ind = off;
			}
		}
		p++;
	}
	return min;
}



//! Reduces image size by factor 2
CImg<T> get_UPVhalfXY() //Reduces image size by factor 2
		{
	CImg<T> res;
	int anch = width();
	int alt = height();

	int anch2 = anch/2;
	int alt2 = alt/2;
#if cimg_version >= 132    
	res.assign( anch2 , alt2 , depth() , spectrum() );
#else  
	res.assign( anch2 , alt2 , dimz() , dimv() );
#endif

	int posifilaA = 0;
	int posifilaB = 0;

#if cimg_version >= 132  
	cimg_forZC(*this,z,c)
#else
	cimg_forZV(*this,z,c)
#endif  
	{
		T * srcA = get_shared_plane(z,c).data();
		T * srcB = res.get_shared_plane(z,c).data();


		if( (!cimg::strcasecmp(pixel_type(),"float")) ||  (!cimg::strcasecmp(pixel_type(),"double")) )
		{ //Floating point case
			double divisor = 4.0;
			for(int f=0;f<alt2;f++)
			{
				posifilaA=2*f*anch;    // Inicio de cada fila imagen A
				posifilaB=f*anch2;
				for(int c=0;c<anch2;c++)
				{
					int posiA=posifilaA+2*c;
					int posiB=posifilaB+c;
					//calcular la media de los cuatro puntos
					double media=srcA[posiA];
					posiA++;
					media=media+srcA[posiA];
					posiA=posiA+anch;
					media=media+srcA[posiA];
					posiA--;
					media=(media+srcA[posiA]) / divisor;
					//escribir el resultado en destino
					srcB[posiB]=media;
				}
			}
		}//if( (!cimg::strcasecmp(pixel_typ


		else
		{
			//Integer case
			int divisor = 4;
			for(int f=0;f<alt2;f++)
			{
				posifilaA=2*f*anch;    // Inicio de cada fila imagen A
				posifilaB=f*anch2;
				for(int c=0;c<anch2;c++)
				{
					int posiA=posifilaA+2*c;
					int posiB=posifilaB+c;
					//calcular la media de los cuatro puntos
					int media=srcA[posiA];
					posiA++;
					media=media+srcA[posiA];
					posiA=posiA+anch;
					media=media+srcA[posiA];
					posiA--;
					media=(media+srcA[posiA]) /divisor;
					//escribir el resultado en destino
					srcB[posiB]=media;
				}
			}
		}
	}
	return res;
		}


//! Reduces image size by factor 2
CImg<T>& UPVhalfXY() {//Reduces image size by factor 2 In-place

	return get_UPVhalfXY().transfer_to(*this);
}


//! Downsamples image by factor  without filtering
CImg<T> get_UPVhalfXYNN(int factor=2) //Reduces image size by factor 
		{
	CImg<T> res;
	int anch = width();
	int alt = height();

	int anch2 = anch/factor;
	int alt2 = alt/factor;
#if cimg_version >= 132    
	res.assign( anch2 , alt2 , depth() , spectrum() );
#else  
	res.assign( anch2 , alt2 , dimz() , dimv() );  
#endif


#if cimg_version >= 132  
	cimg_forZC(*this,z,c)
#else
	cimg_forZV(*this,z,c)
#endif  
	{
		T * srcA = get_shared_plane(z,c).data();
		T * srcB = res.get_shared_plane(z,c).data();


		//Integer case
		for(int f=0;f<alt2;f++)
		{
			int posiA=factor*f*anch;    // Inicio de cada fila imagen A
			int posiB=f*anch2;
			for(int c=0;c<anch2;c++)
			{

				//escribir el resultado en destino
				srcB[posiB]=srcA[posiA];
				posiA += factor;
				posiB++;
			}
		}

	}
	return res;
		}

CImg<T>& UPVhalfXYNN(int factor=2) {//Downsamples image by factor  without filtering In-place

	return get_UPVhalfXYNN(factor).transfer_to(*this);
}


//!Dowscales the image by factor. Prior to downscaling the image is blurred to avoid aliasing using integral image
/**
 * \param integer factor to downsample
 *
 */


CImg<T> get_UPVDownscale(int factor) const//Reduces image size by factor
		{

	CImg<double> integral = get_integral_image(false);

	CImg<T> res;


	int anch = width();
	int alt = height();
#if cimg_version >= 132
        int anchi = integral.width();
#else
        int anchi = integral.dimx();
#endif
	int anch2 = anch/factor;

	int alt2 = alt/factor;
#if cimg_version >= 132
	res.assign( anch2 , alt2 , depth() , spectrum() );
#else
	res.assign( anch2 , alt2 , dimz() , dimv() );
#endif

	int posifilaA = 0;
	int posifilaB = 0;

#if cimg_version >= 132
	cimg_forZC(*this,z,c)
#else
	cimg_forZV(*this,z,c)
#endif
	{
#if cimg_version >= 132
		double * srcA = integral.get_shared_plane(z,c).data();
		T * srcB = res.get_shared_plane(z,c).data();
#else
		double * srcA = integral.get_shared_plane(z,c).ptr();
		T * srcB = res.get_shared_plane(z,c).ptr();
#endif
		//	    if( (!cimg::strcasecmp(pixel_type(),"float")) ||  (!cimg::strcasecmp(pixel_type(),"double")) )
		//	    { //Floating point case
		double divisor = factor * factor;
		for(int f=0;f<alt2;f++)
		{
			posifilaA=factor*f*anchi;    // Inicio de cada fila imagen A
			posifilaB=f*anch2;
			for(int c=0;c<anch2;c++)
			{
				int posiA=posifilaA+factor*c;
				int posiB=posifilaB+c;
				//calcular la media de los cuatro puntos
				double media=(srcA[posiA+factor*anchi+factor]-srcA[posiA+factor*anchi]-srcA[posiA+factor]+srcA[posiA])/divisor;

				//escribir el resultado en destino
				if( (!cimg::strcasecmp(pixel_type(),"float")) ||  (!cimg::strcasecmp(pixel_type(),"double")) )
					srcB[posiB]=media;
				else
					srcB[posiB]=floor(media+0.5);
			}
		}
		//	    }//if( (!cimg::strcasecmp(pixel_typ
		//	    else
		//	    {
		//	    	//Integer case
		//	    	int divisor = factor*factor;
		//	    	for(int f=0;f<alt2;f++)
		//	    	{
		//	    		posifilaA=factor*f*anchi;    // Inicio de cada fila imagen A
		//	    		posifilaB=f*anch2;
		//	    		for(int c=0;c<anch2;c++)
		//	    		{
		//	    			int posiA=posifilaA+factor*c;
		//	    			int posiB=posifilaB+c;
		//	    			//calcular la media de los cuatro puntos
		//	    			double media=(srcA[posiA+factor*anchi+factor]-srcA[posiA+factor*anchi]-srcA[posiA+factor]+srcA[posiA])/divisor;
		//
		//	    			srcB[posiB]=floor(media+0.5);
		//	    		}
		//	    	}
		//	    }
	}
	return res;


	//	if (sigma < 0)
	//	{
	//		int k = 1;
	//		while (factor >= 2*k)
	//			k = k*2;
	//		sigma = k;
	//	}
	//
	//	return  get_blur(sigma).UPVhalfXYNN(factor);



		}

CImg<T>& UPVDownscale(int factor) {

	return get_UPVDownscale(factor).transfer_to(*this);
}



#if cimg_version >= 132

#ifdef cimg_use_jpeg
CImg<T>& _load_jpeg_mem(const unsigned char *data, int ndata) {

	struct jpeg_decompress_struct cinfo;
	struct _cimg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr.original);
	jerr.original.error_exit = _cimg_jpeg_error_exit;

	if (setjmp(jerr.setjmp_buffer)) { // JPEG error
		cimg::warn(_cimg_instance
				"load_jpeg() : Error message returned by libjpeg : %s.",
				cimg_instance,jerr.message);
		assign((unsigned int) 0,(unsigned int)0,(unsigned int)0,(unsigned int)0);
		return *this ;
	}

	//  std::FILE *const nfile = file?file:cimg::fopen(filename,"rb");
	jpeg_create_decompress(&cinfo);
	//  jpeg_stdio_src(&cinfo,nfile);
	local_jpeg_mem_src(&cinfo,(JOCTET*) data,ndata);
	jpeg_read_header(&cinfo,TRUE);
	jpeg_start_decompress(&cinfo);

	if (cinfo.output_components!=1 && cinfo.output_components!=3 && cinfo.output_components!=4) {
		cimg::warn(_cimg_instance
				"_load_jpeg_mem() : Failed to load JPEG data from memory");
		assign((unsigned int) 0,(unsigned int)0,(unsigned int)0,(unsigned int)0);
		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);
		return *this;
	}
	CImg<ucharT> buffer(cinfo.output_width*cinfo.output_components);
	JSAMPROW row_pointer[1];
	assign(cinfo.output_width,cinfo.output_height,1,cinfo.output_components);
	T *ptr_r = _data, *ptr_g = _data + _width*_height, *ptr_b = _data + 2*_width*_height, *ptr_a = _data + 3*_width*_height;
	while (cinfo.output_scanline<cinfo.output_height) {
		*row_pointer = buffer._data;
		if (jpeg_read_scanlines(&cinfo,row_pointer,1)!=1) {
			cimg::warn(_cimg_instance
					"load_jpeg_mem() : Incomplete data in memory'.");
			break;
		}
		const unsigned char *ptrs = buffer._data;
		switch (_spectrum) {
		case 1 : {
			cimg_forX(*this,x) *(ptr_r++) = (T)*(ptrs++);
		} break;
		case 3 : {
			cimg_forX(*this,x) {
				*(ptr_r++) = (T)*(ptrs++);
				*(ptr_g++) = (T)*(ptrs++);
				*(ptr_b++) = (T)*(ptrs++);
			}
		} break;
		case 4 : {
			cimg_forX(*this,x) {
				*(ptr_r++) = (T)*(ptrs++);
				*(ptr_g++) = (T)*(ptrs++);
				*(ptr_b++) = (T)*(ptrs++);
				*(ptr_a++) = (T)*(ptrs++);
			}
		} break;
		}
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	return *this;
}
#endif //cimg_use_jpeg
#endif //cimg > 132

#endif /* D_CIMG_GPIV_H */
