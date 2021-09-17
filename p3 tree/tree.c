//XABIER JIMENEZ GOMEZ xabier.jimenez.gomez
//PABLO GONZALEZ RODRIGUEZ 
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

struct nodo {
	int elem;
	int num_repeticiones;
	struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

static struct nodo *crearnodo(int e) {
	struct nodo *p = malloc(sizeof(struct nodo));
	if (p == NULL) {
		printf("memoria agotada\n");exit(EXIT_FAILURE);
	}
	p->elem = e;
	p->num_repeticiones = 1;
	p->izq = NULL;p->der = NULL;
	return p;
}

/////////////////////////////////////////////////////////////////////////////////////////////FUNCIONES////////////////////////////////////////////
arbol creararbol();
int esarbolvacio(arbol);
posicion buscar(int,arbol);
arbol eliminararbol(arbol);
arbol insertar(int,arbol);

posicion hijoizquierdo(arbol);
posicion hijoderecho(arbol);
int elemento(posicion);
int numerorepeticiones(posicion);

int altura(arbol);
void visualizar(arbol);

arbol creararbol()
{
	return NULL;
}

int esarbolvacio(arbol tree)
{
	return tree == NULL;
}

arbol eliminararbol(arbol tree)
{
    arbol tmp;
    if(esarbolvacio(tree))
        return tree;
    if(!esarbolvacio(tree->izq))
        tree = eliminararbol(tree->izq);
    else if(!esarbolvacio(tree->der))
    	tree = eliminararbol(tree->der);
    else{
    	tmp=tree;
        tree=tree->der;
        free(tmp);
    }
    
    return tree;
}

arbol insertar(int e, arbol a){
	if (a == NULL)
		return crearnodo(e);
	else if (e < a->elem)
		a->izq = insertar(e, a->izq);
	else if (e > a->elem)
		a->der = insertar(e, a->der);
	else
		a->num_repeticiones++;
	return a;
}

posicion hijoizquierdo(arbol tree){
	return tree->izq;
}

posicion hijoderecho(arbol tree){
	return tree->der;
}

int elemento(posicion pos){
	return pos->elem;
}

int numerorepeticiones(posicion pos){
	return pos->num_repeticiones;
}

void visualizar(arbol tree)
{
	if(tree != NULL){
		if(tree->izq != NULL){
			printf("(");
			visualizar(tree->izq);
			printf(")");
		}
		printf("%d",tree->elem);
		if(tree->der != NULL){
			printf("(");
			visualizar(tree->der);
			printf(")");
		}
	} 
	else{
		printf("()");
	}
}

int max(int num1, int num2) 
{
 	int result;
 	if (num1 > num2)
 		result = num1;
 	else
 		result = num2;
 	return result;
}

int altura(arbol tree)
{
	if (tree==NULL)
		return -1;
	else
		return 1+max(altura(tree->izq),altura(tree->der));
	

}

posicion buscar(int x,arbol tree)
{
	posicion pos;
	pos = creararbol();
	
	if(x==tree->elem)
		pos = tree;
	else if(x<tree->elem && tree->izq != NULL)
		pos = buscar(x,tree->izq);
	else if(x>tree->elem && tree->der != NULL)
		pos = buscar(x,tree->der);
	
	return pos;

}
////////////////////////////////////////////////////////////////////////////////////////////////////TEST//////////////////////////////////////////////////////
arbol testInsercion(arbol tree)
{
	printf("arbol vacio : ");
	visualizar(tree);
	printf(".\n");
	printf("altura del arbol : %d\n",altura(tree));
	
	printf("inserto un 3\n");
	tree = insertar(3,tree);
	
	printf("inserto un 1\n");
	tree = insertar(1,tree);

	printf("inserto un 2\n");
	tree = insertar(2,tree);

	printf("inserto un 5\n");
	tree = insertar(5,tree);

	printf("inserto un 4\n");
	tree = insertar(4,tree);

	printf("inserto un 5\n");
	tree = insertar(5,tree);

	printf("arbol : ");visualizar(tree);printf("\n");
	printf("altura del arbol : %d\n",altura(tree));
	
	return tree;
}

arbol testBusqueda(arbol tree){
	arbol pos;
	int x=1;
	pos = buscar(x,tree);
	if (pos!=NULL)
		printf("busco %d y encuentro %d repetido: %d veces\n",x,pos->elem,pos->num_repeticiones);
	else 
		printf("busco %d y no encuentro nada\n",x);
	x=2;
	pos = buscar(x,tree);
	if (pos!=NULL)
		printf("busco %d y encuentro %d repetido: %d veces\n",x,pos->elem,pos->num_repeticiones);
	else 
		printf("busco %d y no encuentro nada\n",x);	
	x=3;
	pos = buscar(x,tree);
	if (pos!=NULL)
		printf("busco %d y encuentro %d repetido: %d veces\n",x,pos->elem,pos->num_repeticiones);
	else 
		printf("busco %d y no encuentro nada\n",x);
	x=4;
	pos = buscar(x,tree);
	if (pos!=NULL)
		printf("busco %d y encuentro %d repetido: %d veces\n",x,pos->elem,pos->num_repeticiones);
	else 
		printf("busco %d y no encuentro nada\n",x);
	x=5;
	pos = buscar(x,tree);
	if (pos!=NULL)
		printf("busco %d y encuentro %d repetido: %d veces\n",x,pos->elem,pos->num_repeticiones);
	else 
		printf("busco %d y no encuentro nada\n",x);
	x=6;
	pos = buscar(x,tree);
	if (pos!=NULL)
		printf("busco %d y encuentro %d repetido: %d veces\n",x,pos->elem,pos->num_repeticiones);
	else 
		printf("busco %d y no encuentro nada\n",x);
	return tree;
}


arbol testBorrado(arbol tree){
	printf("borro todos los nodos liberando la memoria:\n");
	tree = eliminararbol(tree);
	printf("arbol vacio : ");
	visualizar(tree);
	printf(".\n");
	printf("altura del arbol : %d\n",altura(tree));
	
	return tree;
}

void totalTests(){

	arbol tree;
	tree = creararbol();
	
	tree = testInsercion(tree);
	tree = testBusqueda(tree);
	tree = testBorrado(tree);
}

void medirTInsertar(){
	int i,n;
	double t,t1,t2,x,y,z;
	arbol tree;
	int *v = malloc(256000 * sizeof(int));
	for(n=8000;n<=256000;n=n*2){
		tree=creararbol();
		aleatorio(v,n);
		t1=microsegundos();

		for(i=0;i<n;i++)
			tree=insertar(v[i],tree);

		t2=microsegundos();
		t=t2-t1;
		
		x=t/n;
		y=t/pow(n,1.25);
		z=t/pow(n,1.5);
		printf("%12d%15.2f%15.6f%15.6f%15.6f\n",n,t,x,y,z);
		tree = eliminararbol(tree);
	}
	free(v);
}

void medirTBuscar(){
	int i,n=0;
	double t,t1,t2,x,y,z;
	arbol tree;
	int k=1000;
	int *v = malloc(256000 * sizeof(int));
	for(n=8000;n<=256000;n=n*2){
		tree=creararbol();
		aleatorio(v,n);

		for(i=0;i<n;i++)
		 	tree=insertar(v[i],tree);

		t1=microsegundos();
		for(i=0;i<n;i++)
			buscar(v[i],tree);

		t2=microsegundos();
		t=t2-t1;
		if(t<500){
			t1=microsegundos();
			for (int i =0; i <k ;i++)
				buscar(v[i],tree);
			
			t2=microsegundos();
			tree=eliminararbol(tree);
			t=(t2-t1)/k;
			printf("*");
		}
		else
			printf(" ");
		x=t/n;
		y=t/pow(n,1.25);
		z=t/pow(n,1.5);
		printf("%12d%15.2f%15.6f%15.6f%15.6f\n",n,t,x,y,z);
		tree = eliminararbol(tree);
	}
	free(v);
}

void tablaInsercion(){
 	printf("Insercion de n elementos\n");
 	printf("           N           t(n)       t(n)/f(n)      t(n)/g(n)       t(n)/h(n) \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n\n");
 	medirTInsertar();
 	printf("\n");

 }

 void tablaBusqueda(){
 	printf("Busqueda de n elementos\n");
 	printf("           N           t(n)       t(n)/f(n)      t(n)/g(n)       t(n)/h(n) \n");
 	printf("                                  c.subestimada   c.ajustada     c.sobreestimada \n\n");
 	medirTBuscar();
 	printf("\n");
 }

  void totalTablas(){
  	int i;
	for (i = 1; i < 4; i++)
	{
		printf("Ejecución %d del algoritmo:\n\n",i);
		tablaInsercion();
		tablaBusqueda();
		printf("\n");
	} 
}



int main(int argc, char const *argv[])
{
	inicializar_semilla();
	totalTests();
	totalTablas();
	
	return 0;
}
