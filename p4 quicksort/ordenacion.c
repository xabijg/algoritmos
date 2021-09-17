//XABIER JIMENEZ GOMEZ xabier.jimenez.gomez

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define swap(x, y, aux) aux = x; x = y; y = aux;

void inicializar_semilla()
{
	srand(time(NULL));
}

double microsegundos() 
{
	struct timeval t;
	if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v[],int n)
{
	int i=0,m=2*n+i;
	for (i = 0; i < n; i++)
	{
		v[i]=(rand()%m)-n;
	}
}

void ascendente(int v[],int n)
{
   	int i;
   	for(i=0;i<n;i++)
   		v[i]=i;
}


void descendente(int v[],int n)
{
	int i;
	for(i=0;i<n;i++)
		v[i]=n-i;
}

void auxord(int v[], int izq, int der){
        int j=0,i=0,aux=0;

    	if(izq<der)
    	{
        	j=der;
        	for (i = der-1; i >= izq; i--)
        	{
            		if(v[i]>v[der]){
                		j=j-1;
                	aux=v[i];
                	v[i]=v[j];
                	v[j]=aux;
            		}  
        	}
       	 aux =v[j];
        	v[j]=v[der];
        	v[der]=aux;

        	auxord(v,izq,j-1);
        		auxord(v,j+1,der);
    	}
}

void ordenar(int v [], int n,int umbral) {
    	auxord(v,0,n-1);
}
bool ordenado(int v[],int n){
	bool ord = 1;
	int i;
	for (i = 0; i < n-1; i++)
	{
		if (v[i] > v[i+1])
		{
			ord = 0;
		}
	}
	return ord;
}

struct INIC {
	int umbral;
	char* nombre;
	void(*pfuncion)(int v[], int n);
};

struct INIC inics[] = {
	{1,"ascendente" ,ascendente},
	{1, "descendente",descendente},
	{1, "aleatorio" ,aleatorio},
	{10, "ascendente" ,ascendente},
	{10, "descendente",descendente},
	{10, "aleatorio" ,aleatorio},
	{100, "ascendente" ,ascendente},
	{100, "descendente",descendente},
	{100, "aleatorio" ,aleatorio},
	{4, NULL}
};

 void testInsAsc(int n,int v[])
 {
	int j,i;
 	for (i=0; i<9; i++){
		//int umbral = inics[i].umbral;
		//Insercion Ascendente descendente aleatoria
		inics[i].pfuncion(v,n);
		printf("Test Inserción con inicialización %s y umbral %d:\n",inics[i].nombre,inics[i].umbral);
		for ( j = 0; j < n; j++)
			printf("%d,",v[j]);
		
		printf("\n");
		printf("¿Ordenado?: %d\n",ordenado(v,n));
		ordenar(v,n,inics[i].umbral);
		printf("Ordenacion por insercion:\n");
		for ( j = 0; j < n; j++)
			printf("%d,",v[j]);
		
		printf("\n");
		printf("¿Ordenado?: %d\n",ordenado(v,n));
		printf("\n");
	}
}

void medirTiempo(int n, int v[])
 {
 	double t,t1,t2;
 	int i,l,j,x,k=1000;
	for(l = 1; l <= 3; l++){
		printf("\nEjecución numero %d del algoritmo  ***************\n\n",l);
		for ( j=0; j<9; j++){//cada inicializacion y umbral
			
			printf("\nOrdenacion con inicializacion %s y umbral %d\n", inics[j].nombre,inics[j].umbral);
			printf("           N           t(n)       t(n)/n^1,01      t(n)/n^1,15 t(n)/n^1,22 \n");
			printf("                                  c.subestimada   c.ajustada     c.sobrestimada \n");
			n = 500;
			for (i = 0; i < 7; i++)//cada valor de m
			{
				//inicializar v
				inics[j].pfuncion(v,n);
				t1=microsegundos();
				ordenar(v,n,inics[j].umbral);
				t2=microsegundos();
				t=t2-t1;
				if(t<500){
					t1=microsegundos();
					for( x=0;x<k;x++){
						//inicializar v
						inics[j].pfuncion(v,n);
						ordenar(v,n,inics[j].umbral);
					}
					t2=microsegundos();
					t = (t2-t1)/k;
					printf("*");
				}
				else{
					printf(" ");
				}
				printf("%12d%15.3f  %15.9f%15.9f%15.9f\n",n,t,t/pow(n,1.01),t/(pow(n, 1.15)),t/pow(n, 1.22));
				n = n*2;
			}
		}
	}
 }

int main(int argc, char const *argv[])
{
	int n=20;
	int m=500;
	int v[32000];

	inicializar_semilla();
	testInsAsc(n,v);
	medirTiempo(m,v);
}
	
	return 0;
}
