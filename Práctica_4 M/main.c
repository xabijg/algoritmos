#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define UMBRAL 1
#define intercambio(a,b,x) { x = a ; a= b; b = x; }

void OrdenarAux (int V[], int izq, int der);
void ord_ins (int v[], int n);
void aleatorio(int v [], int n);
void ord_rapida(int v [], int n);
void ascendente(int v [], int n);
void descendente(int v [], int n);
void test();
void cotas(double t, int n, int aleatorio);
void vectoras();
void vectordes();
void vectoral();

int main() {


    printf("Test\n");
    test();
    printf("\n\nAscendente\n");
    printf("\n%9s%15.6s%15.6s%15.6s%15.6s", "n", "t(n)", "t/sub", "t/ajus", "t/sob\n");
    printf("---------------------------------------------------------------------\n");
    vectoras();
    printf("\n\nDescendente\n");
    printf("\n%9s%15.6s%15.6s%15.6s%15.6s", "n", "t(n)", "t/sub", "t/ajus", "t/sob\n");
    printf("---------------------------------------------------------------------\n");
    vectordes();
    printf("\n\nAleatorio\n");
    printf("\n%9s%15.6s%15.6s%15.6s%15.6s", "n", "t(n)", "t/sub", "t/ajus", "t/sob\n");
    printf("---------------------------------------------------------------------\n");
    vectoral();


    return 0;
}

double microsegundos(){
    struct timeval t;
    if(gettimeofday(&t, NULL)<0)
        return 0.0;
    return(t.tv_usec + t.tv_sec *1000000.0);
}

void aleatorio(int v [], int n) {/* se generan números pseudoaleatorio entre -n y +n */
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}


void ascendente(int v [], int n) { //Genera un vector ordenado de forma ascendente
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}


void descendente(int v [], int n) { //Genera un vector ordenado de forma descendente
    int i;
    int k = 0;
    for (i = n - 1; i >= 0; i--) {
        v[k] = i;
        k++;
    }
}
void ord_ins (int v[], int n){ //Algoritmo de ordenacion por insercion
    int i, j, x;
    for(i=1; i<n; i++){
        x= v[i];
        j= i-1;
        while (j>=0 && v[j]>=x){
            v[j+1]=v[j];
            j=j-1;
        }
        v[j+1]=x;
    }
}
void ord_rapida(int v [], int n) {
    OrdenarAux(v, 0, n-1);
    if (UMBRAL > 1) {
        ord_ins(v, n);
    }
}

void OrdenarAux (int V[], int izq, int der){
    int i, j;
    int x;
    int pivote;
    int z=0;

    if (izq+UMBRAL <= der) {

        x = rand () % (der-izq+1) + izq;
        pivote=V[x];
        intercambio(V[izq],  V[x], z);
        i = izq + 1;
        j = der;

        while (i <= j) {
            while (i <= der && V[i] < pivote) {
                i = i + 1;
            }
            while (V[j] > pivote) {
                j = j - 1;
            }
            if (i <= j) {
                intercambio(V[i], V[j], z);
                i = i+1;
                j= j-1;
            }
        }
        intercambio(V[izq], V[j], z);
        OrdenarAux(V, izq, j - 1);
        OrdenarAux(V, j + 1, der);
    }
}
void test(){
    int n=25;
    int i;
    int V[n], W[n], Z[n];
    printf("Vector aleatorio\n");
    aleatorio(V, n);
    for (i=0; i<n; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
    ord_rapida(V, n);
    for (i=0; i<n; i++) {
        printf("%d ", V[i]);
    }
    printf("\nVector ascendente\n");
    ascendente(W, n);
    for (i=0; i<n; i++) {
        printf("%d ", W[i]);
    }
    printf("\n");
    ord_rapida(W, n);
    for (i=0; i<n; i++) {
        printf("%d ", W[i]);
    }
    printf("\nVector descendente\n");
    descendente(Z, n);
    for (i=0; i<n; i++) {
        printf("%d ", Z[i]);
    }
    printf("\n");
    ord_rapida(Z, n);
    for (i=0; i<n; i++) {
        printf("%d ", Z[i]);
    }
}

void cotas(double t, int n, int aleatorio) {
    double f1, f2, f3;
    if (UMBRAL == 1 || UMBRAL == 10 || aleatorio == 1) {
        f1 = t / (pow(n, 0.7) * log(n)); //cota subestimada
        f2 = t / (n * log(n)); //cota ajustada
        f3 = t / (pow(n, 1.2) * log(n)); //cota sobrestimada
    } else {
        f1 = t / (pow(n, 0.8) * log(n)); //cota subestimada
        f2 = t / (pow(n, 1.05) * log(n)); //cota ajustada
        f3 = t / (pow(n, 1.2) * log(n)); //cota sobrestimada
    }
    printf("%9d%15.6f%15.6f%15.6f%15.6f\n", n, t, f1, f2, f3);    
}
void vectoras(){
    int n , k;
    int r=256000;
    int v[r];
    int alea=0;
    double t, ta, tb, t1, t2;

    for(n=1000; n<=256000; n=n*2) {
        ascendente(v, n); //creamos el vector ordenado
        ta = microsegundos();
        ord_rapida(v, n);
        tb = microsegundos();
        t = tb - ta;

        if (t < 500) {

            ta=microsegundos();
            for(k=1; k<=10; k++){
                ascendente(v, n);
                ord_rapida(v, n);
            }
            tb=microsegundos();
            t1=tb-ta;
            ta=microsegundos();
            for(k=1; k<=10; k++){
                ascendente(v, n);
            }
            tb=microsegundos();
            t2=tb-ta;

            t=(t1-t2)/10;
        }

        cotas(t, n, alea);

    }
}

void vectordes(){
    int n , k;
    int r=256000;
    int v[r];
    int alea=0;
    double t, ta, tb, t1, t2;

    for(n=2000; n<=256000; n=n*2) {
        descendente(v, n); //creamos el vector ordenado en orden descendente
        ta = microsegundos();
        ord_rapida(v, n);
        tb = microsegundos();
        t = tb - ta;

        if (t < 500) {

            ta=microsegundos();
            for(k=1; k<=10; k++){
                descendente(v, n);
                ord_rapida(v, n);
            }
            tb=microsegundos();
            t1=tb-ta;
            ta=microsegundos();
            for(k=1; k<=10; k++){
                descendente(v, n);
            }
            tb=microsegundos();
            t2=tb-ta;
            t=(t1-t2)/10;
        }
        cotas(t, n, alea);


    }
}


void vectoral(){
    int n , k;
    int r=256000;
    int v[r];
    double t, ta, tb, t1, t2;
    int alea=1;

    for(n=2000; n<=256000; n=n*2) {
        aleatorio(v, n); //creamos el vector ordenado
        ta = microsegundos();
        ord_rapida(v, n);
        tb = microsegundos();
        t = tb - ta;

        if (t < 500) {

            ta=microsegundos();
            for(k=1; k<=10; k++){
                aleatorio(v, n);
                ord_rapida(v, n);
            }
            tb=microsegundos();
            t1=tb-ta;
            ta=microsegundos();
            for(k=1; k<=10; k++){
                aleatorio(v, n);
            }
            tb=microsegundos();
            t2=tb-ta;
            t=(t1-t2)/10;
        }

        cotas(t, n, alea);

    }
}
