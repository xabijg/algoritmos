//Xabier Jimenez Gomez xabier.jimenez.gomez
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>


void inicializar_semilla(){

    srand(time(NULL));
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}


void ascendente(int v [], int n) {

    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}

void descendente(int v [], int n) {

    int i;
    int k=n;

    for (i=0; i<n; i++) {
        v[i] = k;
        k--;
    }
}


// void ord_ins(int v[],int n){

//     int x,j,i;
//     for(i=1;i<n;i++){

//         x=v[i];
//         j=i-1;

//         while(j>=0 && v[j]>x){

//             v[j+1]=v[j];
//             j=j-1;
//         }

//         v[j+1]=x;

//     }
// }


// void ord_shell(int v[],int n){

//     int j,i,tmp,incremento;
//     bool seguir;

//     incremento=n;

//     do{

//         incremento=incremento/2;

//         for(i=incremento;i<n;i++) {

//             tmp = v[i];
//             j = i;
//             seguir = true;

//             while ((j - incremento)>= 0 && seguir) {

//                 if (tmp < v[j - incremento]) {

//                     v[j] = v[j - incremento];
//                     j = j - incremento;

//                 }
//                 else seguir = false;
//             }
//             v[j] = tmp;
//         }
//     }
//     while (incremento>1);
// }

void valido(const int v[],int n){

    int k=0, i;
    int val=0;

    for(i=0;i<n;i++){

        if(v[i]<=v[i+1]) k++;

    }

    if(k==n-1)
        val=1;

    printf("Ordenado? %d \n",val);

}

void imprimirVector(int v[],int n){
    int i;

    for(i=0;i<n;i++){

        printf("%d ",v[i]);

    }
    printf("\n");
}

void ins_random(int v[]){

    printf("Inicialización aleatoria\n");
    aleatorio(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\nOrdenacion por Insercion\n");
    ord_ins(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\n");

}

void ins_ascendente(int v[]){

    printf("\nInicializacion ascendente\n");
    ascendente(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\nOrdenacion por Insercion\n");
    ord_ins(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\n");

}

void ins_descendente(int v[]){

    printf("\nInicializacion descendente\n");
    descendente(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\nOrdenacion por Insercion\n");
    ord_ins(v,10);
    imprimirVector(v,10);
    valido(v,10);

}

void shell_random(int v[]){

    printf("\nInicialización aleatoria\n");
    aleatorio(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\nOrdenacion por Shell\n");
    ord_shell(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\n");

}

void shell_ascendente(int v[]){

    printf("\nInicializacion ascendente\n");
    ascendente(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\nOrdenacion por Shell\n");
    ord_shell(v,10);
    imprimirVector(v,10);
    valido(v,10);

}

void shell_descendente(int v[]){

    printf("\nInicializacion descendente\n");
    descendente(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\nOrdenacion por Shell\n");
    ord_shell(v,10);
    imprimirVector(v,10);
    valido(v,10);

    printf("\n");

}

void test(int v[]){

    ins_random(v);
    ins_ascendente(v);
    ins_descendente(v);

    shell_random(v);
    shell_ascendente(v);
    shell_descendente(v);

}

double microsegundos() {

    struct timeval t;

    if (gettimeofday(&t, NULL) < 0 )

        return 0.0;

    return (t.tv_usec + t.tv_sec * 1000000.0);

}

void tiempoInsercionAleatorio(int n){

    int i,k=100;
    n=500;
    int v[32000];
    double tiempo, tInicio, tFinal, x, y, z;

    printf("Tiempos Insercion aleatoria: \n");
    printf("\n          n            t(n)          cti          cta            cts\n");
    for(n=n; n<=32000; n=n*2){
        aleatorio(v,n);
        tInicio = microsegundos();
        ord_ins(v,n);
        tFinal = microsegundos();
        tiempo= tFinal - tInicio;

        if(tiempo<500){
            printf("*");
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                aleatorio(v,n);
                ord_ins(v,n);
            }
            tFinal = microsegundos();
            tiempo = tFinal - tInicio;
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                aleatorio(v,n);
            }
            tFinal = microsegundos();
            tiempo = (tiempo-(tFinal-tInicio))/k;
        }
        x = tiempo/pow(n,1.8);
        y =tiempo/pow(n,2.0);
        z = tiempo/pow(n,2.2);
        printf("\n%12d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, x, y, z);
    }
}
void tiempoInsercionAscendente(int n){

    int i,k=100;
    n=500;
    int v[32000];
    double tiempo, tInicio, tFinal, x, y, z;

    printf("Tiempos Insercion ascendente: \n");
    printf("\n          n            t(n)          cti          cta            cts\n");
    for(n=n; n<=32000; n=n*2){
        ascendente(v,n);
        tInicio = microsegundos();
        ord_ins(v,n);
        tFinal = microsegundos();
        tiempo= tFinal - tInicio;

        if(tiempo<500){
            printf("*");
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                ascendente(v,n);
                ord_ins(v,n);
            }
            tFinal = microsegundos();
            tiempo = tFinal - tInicio;
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                ascendente(v,n);
            }
            tFinal = microsegundos();
            tiempo = (tiempo-(tFinal-tInicio))/k;
        }
        x = tiempo/pow(n,0.8);
        y =tiempo/n;
        z = tiempo/pow(n,1.2);
        printf("\n%12d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, x, y, z);
    }
}
void tiempoInsercionDescendente(int n){

    int i,k=100;
    n=500;
    int v[32000];
    double tiempo, tInicio, tFinal, x, y, z;

    printf("Tiempos Insercion descendente: \n");
    printf("\n          n            t(n)          cti          cta            cts\n");
    for(n=n; n<=32000; n=n*2){
        descendente(v,n);
        tInicio = microsegundos();
        ord_ins(v,n);
        tFinal = microsegundos();
        tiempo= tFinal - tInicio;

        if(tiempo<500){
            printf("*");
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                descendente(v,n);
                ord_ins(v,n);
            }
            tFinal = microsegundos();
            tiempo = tFinal - tInicio;
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                descendente(v,n);
            }
            tFinal = microsegundos();
            tiempo = (tiempo-(tFinal-tInicio))/k;
        }
        x = tiempo/pow(n,1.8);
        y =tiempo/pow(n,2.0);
        z = tiempo/pow(n,2.2);
        printf("\n%12d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, x, y, z);
    }
}
void tiempoShellAleatorio(int n){

    int i,k=100;
    n=500;
    int v[32000];
    double tiempo, tInicio, tFinal, x, y, z;

    printf("Tiempos shell aleatorio: \n");
    printf("\n          n            t(n)          cti          cta            cts\n");
    for(n=n; n<=32000; n=n*2){
        aleatorio(v,n);
        tInicio = microsegundos();
        ord_shell(v,n);
        tFinal = microsegundos();
        tiempo= tFinal - tInicio;

        if(tiempo<500){
            printf("*");
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                aleatorio(v,n);
                ord_shell(v,n);
            }
            tFinal = microsegundos();
            tiempo = tFinal - tInicio;
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                aleatorio(v,n);
            }
            tFinal = microsegundos();
            tiempo = (tiempo-(tFinal-tInicio))/k;
        }
        x = tiempo/(n*log(n));
        y = tiempo/pow(n,1.2);
        z = tiempo/pow(n,2.0);
        printf("\n%12d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, x, y, z);
    }
}
void tiempoShellAscendente(int n){

    int i,k=100;
    n=500;
    int v[32000];
    double tiempo, tInicio, tFinal, x, y, z;

    printf("Tiempos Shell ascendente: \n");
    printf("\n          n            t(n)          cti          cta            cts\n");
    for(n=n; n<=32000; n=n*2){
        ascendente(v,n);
        tInicio = microsegundos();
        ord_shell(v,n);
        tFinal = microsegundos();
        tiempo= tFinal - tInicio;

        if(tiempo<500){
            printf("*");
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                ascendente(v,n);
                ord_shell(v,n);
            }
            tFinal = microsegundos();
            tiempo = tFinal - tInicio;
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                ascendente(v,n);
            }
            tFinal = microsegundos();
            tiempo = (tiempo-(tFinal-tInicio))/k;
        }
        x = tiempo/n;
        y =tiempo/pow(n,1.15);
        z = tiempo/pow(n,1.30);
        printf("\n%12d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, x, y, z);
    }
}
void tiempoShellDescendente(int n){

    int i,k=100;
    n=500;
    int v[32000];
    double tiempo, tInicio, tFinal, x, y, z;

    printf("Tiempos Shell descendente: \n");
    printf("\n          n            t(n)          cti          cta            cts\n");
    for(n=n; n<=32000; n=n*2){
        descendente(v,n);
        tInicio = microsegundos();
        ord_shell(v,n);
        tFinal = microsegundos();
        tiempo= tFinal - tInicio;

        if(tiempo<500){
            printf("*");
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                descendente(v,n);
                ord_shell(v,n);
            }
            tFinal = microsegundos();
            tiempo = tFinal - tInicio;
            tInicio = microsegundos();
            for(i=0;i<k;i++){
                descendente(v,n);
            }
            tFinal = microsegundos();
            tiempo = (tiempo-(tFinal-tInicio))/k;
        }
        x = tiempo/n;
        y =tiempo/pow(n,1.15);
        z = tiempo/pow(n,1.30);
        printf("\n%12d%15.3f%15.6f%15.6f%15.6f\n", n, tiempo, x, y, z);
    }
}

void ejecutar(int n){

    int v[n];

    inicializar_semilla();
    test(v);
    tiempoShellAleatorio(n);
    tiempoShellAscendente(n);
    tiempoShellDescendente(n);
    tiempoInsercionAleatorio(n);
    tiempoInsercionAscendente(n);
    tiempoInsercionDescendente(n);

}

void calentar(int n) {

    int v[n];
    int i=0;

    while (i < 5){
        ord_ins(v, n);
    printf("EJECUCUIÓN PARA EL CALENTAMIENTO\n");
    printf("\n*************************\n");
    ejecutar(n);
    printf("\n*************************\n");

    printf("\n");
    i++;
}

}

int main() {

    int n = 2;

    calentar(n);
    printf("\nINICIO:\n");
    ejecutar(n);

}
