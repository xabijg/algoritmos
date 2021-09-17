#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


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



bool ordenado(int v[],int n){
    bool ord = 1;
    int i;
    for ( i = 0; i < n-1; i++)
    {
        if (v[i] > v[i+1])
        {
            ord = 0;
        }
    }
    return ord;
}


void ord_ins (int v[],int n)
{
	int x,j,i;

	for (i = 1; i < n; i++)
	{
		x=v[i];
		j=i-1;
		while((j>=0)&&(v[j]>x))
		{
			v[j+1]=v[j];
			j--;
		}
		v[j+1]=x;
	}
}

void ord_shell(int v[],int n)
{
	int incremento=n,tmp,j,i,seguir;
	while(incremento!=1)
	{
		incremento=incremento/2;
		for (i=incremento; i < n;i++)
		{
			tmp=v[i];
			j=i;
			seguir=1;
			while(((j-incremento)>=0)&&(seguir==1))
			{
				if(tmp<v[j-incremento])
				{
					v[j]=v[j-incremento];
					j=j-incremento;
				}
				else seguir=0;
			}
			v[j]=tmp;
		}
	}

}

void cotas(int n,double t,int x){
    switch (x){
    case 1: printf("%12d%15.3f  %15.9f%15.9f%15.9f\n",n,t,t/pow(n,1.7),t/pow(n, 2),t/pow(n, 2.3));
      break;
    case 2: printf("%12d%15.3f  %15.9f%15.9f%15.9f\n",n,t,t/pow(n,0.87),t/(n*1.85),t/pow(n, 1.35));
      break;
    case 3: printf("%12d%15.3f  %15.9f%15.9f%15.9f\n",n,t,t/pow(n,1.8),t/pow(n, 2),t/pow(n, 2.3));
      break;
    case 4: printf("%12d%15.3f  %15.9f%15.9f%15.9f\n",n,t,t/pow(n,1.05),t/pow(n,1.2),t/pow(n, 1.8));
      break;
    case 5: printf("%12d%15.3f  %15.9f%15.9f%15.9f\n",n,t,t/pow(n,0.9),t/pow(n,1.131),t/pow(n,1.6));
      break;
    case 6: printf("%12d%15.3f  %15.9f%15.9f%15.9f\n",n,t,t/pow(n,0.9),t/pow(n,1.12),t/pow(n, 1.7));
      break;
    default:break;
     }
 }


void medirTiempo1(int n, int * v,int m)
 {
 	double t,t1,t2;
 	int i,k=1000;

 	for (i = 0; i < 5; i++)
	{
		t1=microsegundos();
		ord_ins(v,n);
		t2=microsegundos();
		t=t2-t1;
		if(t<500){
			t1=microsegundos();
			for(int x=0;x<k;x++){
				ord_ins(v,n);
			}
			t2=microsegundos();
			t = (t2-t1)/k;
			printf("*");
		}
		else{
			printf(" ");
		}
		cotas(n,t,m);
		n = n*2;
	 }
 }

 void medirTiempo2(int n,int *v,int m)
 {
 	double t,t1,t2;
 	int i,k=1000;
 	
 	
	for ( i = 0; i < 5; i++)
	{
		t1=microsegundos();
		ord_shell(v,n);
		t2=microsegundos();
		t=t2-t1;
		if(t<500){
			t1=microsegundos();
			for(int x=0;x<k;x++){
				ord_shell(v,n);
			}
			t2=microsegundos();
			t = (t2-t1)/k;
			printf("*");
		}
		else{
			printf(" ");
		}
		cotas(n,t,m);
		n = n*2;
	 }
 }

void tablaInsercionDescendente(int n,int *v){
	//Insercion descendente
	descendente(v,n);

 	printf("Ordenacion por insercion con inicializacion descendente\n");
 	printf("           N           t(n)       t(n)/n^1.8      t(n)/n^2       t(n)/n^2.3 \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n");
 	medirTiempo1(n,v,3);
 	printf("\n");
}
 void tablaInsercionAscendente(int n,int *v){
	//Insercion ascendente
	ascendente(v,n);

 	printf("Ordenacion por insercion con inicializacion ascendente\n");
 	printf("           N           t(n)       t(n)/n^0.87     t(n)/n^1.85    t(n)/n^1.35 \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n");
 	medirTiempo1(n,v,2);
 	printf("\n");
}

void tablaInsercionAleatoria(int n,int *v){
	//Insercion aleatorio
	aleatorio(v,n);

 	printf("Ordenacion por insercion con inicializacion aleatoria\n");
 	printf("           N           t(n)       t(n)/n^1.7      t(n)/n^2       t(n)/n^2.3 \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n");
 	medirTiempo1(n,v,1);
 	printf("\n");
}

  void tablaShellAscendente(int n,int *v){
	//Insercion ascendente
	ascendente(v,n);  

 	printf("Ordenacion por shell con inicializacion ascendente\n");
 	printf("           N           t(n)       t(n)/n^1.05     t(n)/n^1.2     t(n)/n^1.8 \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n");
 	medirTiempo2(n,v,4);
 	printf("\n");
 }
 void tablaShellDescendente(int n,int *v){
	//Insercion descendente
	descendente(v,n);

 	printf("Ordenacion por shell con inicializacion descendente\n");
 	printf("           N           t(n)       t(n)/n^0.9      t(n)/n^1.2     t(n)/n^1.7 \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n");
 	medirTiempo2(n,v,5);
 	printf("\n");
 }
  void tablaShellAleatoria(int n,int *v){
	//Insercion aleatorio
	aleatorio(v,n);

 	printf("Ordenacion por shell con inicializacion aleatoria\n");
 	printf("           N           t(n)       t(n)/n^0.9      t(n)/n^1.2     t(n)/n^1.7 \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n");
 	medirTiempo2(n,v,6);
 	printf("\n");
 }

 void totalTablas(){
	int n=500;
	int *v = (int *)malloc(n*sizeof(int));
	for (int i = 1; i < 4; i++)
	{
		printf("Ejecución %d del algoritmo:\n\n",i);
		
		tablaInsercionDescendente(n,v);
		tablaInsercionAscendente(n,v);
		tablaInsercionAleatoria(n,v);
	
		tablaShellDescendente(n,v);
		tablaShellAscendente(n,v);
		tablaShellAleatoria(n,v);
		
		printf("\n");
	} 
	
}


void testInsAle(int n,int *v)
{
 	int i=0;
 	
	//Insercion aleatorio
	aleatorio(v,n);
	
	printf("Test Inserción con inicialización Aleatoria:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	
	ord_ins(v,n);
	
	printf("Ordenacion por insercion:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	printf("\n");
 }
 
 void testInsAsc(int n,int *v)
 {
 	int i=0;
 	
	//Insercion Ascendente
	ascendente(v,n);
	
	printf("Test Inserción con inicialización Ascendente:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	
	ord_ins(v,n);
	
	printf("Ordenacion por insercion:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	printf("\n");
}

void testInsDes(int n,int *v)
{
 	int i=0;
 	
	//Insercion descendente
	descendente(v,n);
	
	printf("Test Inserción con inicialización Descendente:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	
	ord_ins(v,n);
	
	printf("Ordenacion por insercion:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n)); 
	printf("\n");
}

void testShellAle(int n,int *v)
{
 	int i=0;
 	
	//Insercion aleatorio
	aleatorio(v,n);
	
	printf("Test Shell con inicialización Aleatoria:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	
	ord_shell(v,n);
	
	printf("Ordenacion por shell:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	printf("\n");
 }
 
void testShellDes(int n,int *v)
{
 	int i=0;
 	
	//Insercion aleatorio
	descendente(v,n);
	
	printf("Test Shell con inicialización Descendente:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	
	ord_shell(v,n);
	
	printf("Ordenacion por shell:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	printf("\n");
 }

void testShellAsc(int n,int *v)
{
 	int i=0;
 	
	//Insercion aleatorio
	ascendente(v,n);
	
	printf("Test Shell con inicialización Ascendente:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	
	ord_shell(v,n);
	
	printf("Ordenacion por shell:\n");
	for ( i = 0; i < n; i++)
		printf("%d,",v[i]);
	
	printf("\n");
	printf("¿Ordenado?: %d\n",ordenado(v,n));
	printf("\n");
 }

 void totalTest(){
	int n=10;
	int *v = (int *)malloc(n*sizeof(int));
	 
	 //testsIns
	testInsAle(n,v);
	testInsDes(n,v);
	testInsAsc(n,v);
	
	//testsShell
	testShellAle(n,v);
	testShellDes(n,v);
	testShellAsc(n,v);
	
	free(v);
}

int main(){
	inicializar_semilla();
	
	//tests
	totalTest();
	
	//tablas:
	totalTablas();
}
