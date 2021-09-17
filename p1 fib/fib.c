#include <stdio.h>
#include <math.h>
#include <sys/time.h>

 int fib1(int n)
 {
	if(n<2)
		return n;
	else
		return fib1(n-1)+fib1(n-2);
 }
 
 int fib2(int n)
 {
	int i=1,j=0;
	for(int k=1;k<=n;k++)
	{
	 j=i+j;
	 i=j-i;
	}
	return j;
 }


 int fib3(int n)
 {
	int i=1,j=0,k=0,h=1,t=0;
	while(n>0)
	{
		if (n%2 != 0)
		{
			t=j*h;
			j=i*h + j*k + t;
			i=i*k + t;
		}
		t=h*h;
		h=2*k*h + t;
		k=k*k + t;
		n=n/2;
	}
	return j;
 }
 
 /* obtiene la hora actual en microsegundos */
 double microsegundos() {
	 struct timeval t;
	 if (gettimeofday(&t, NULL) < 0 )
		return 0.0;
	return (t.tv_usec + t.tv_sec * 1000000.0);
}
 
 void test()
 {
	for(int n=1;n<10;n++)
	 { 
		printf("%3d  %3d  %3d  %3d\n",n,fib1(n),fib2(n),fib3(n));
	 } 
 }
 
 void medirTiempoFib1()
 {
 	double t,t1,t2,x, y, z;
 	int n = 2,k=100;
 	
	for (int i = 0; i < 5; i++)
	{
		t1=microsegundos();
		fib1(n);
		t2=microsegundos();
		t=t2-t1;
		if(t<500){
			t1=microsegundos();
			for(int j=0;j<100;j++){
				fib1(n);
			}
	    		t2=microsegundos();
	        	t=(t2-t1)/k;
		}
		x = t / pow(1.1,n); //cota subestimada
		y = t / pow((1+sqrt(5))/2,n);
		z = t / pow(2,n);  //cota sobreestimada
		printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		n = n*2;
	 }  
 }
 
 void medirTiempoFib2()
 {
 	double t,t1,t2,x, y, z;
 	int n = 1000, k=100;
 	
	for (int i = 0; i < 5; i++)
	{
		t1=microsegundos();
		fib2(n);
		t2=microsegundos();
		t=t2-t1;
		if(t<500){
			t1=microsegundos();
			for(int x=0;x<k;x++){
				fib2(n);
	    		}
	    		t2=microsegundos();
	        	t=(t2-t1)/k;
		}
		x = t / pow(n,0.8); //cota subestimada
		y = t / n;
		z = t / (n*log(n));  //cota sobreestimada
		printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		n = n*10;
	 }	 
 }
 
 void medirTiempoFib3()
 {
 	double t,t1,t2,x, y, z;
 	int n = 1000, k=100;
 	
	for (int i = 0; i < 5; i++)
	{
		t1=microsegundos();
		fib3(n);
		t2=microsegundos();
		t=t2-t1;
		if(t<500){
			t1=microsegundos();
			for(int x=0;x<k;x++){
				fib3(n);
	    	}
	        	t2=microsegundos();
	        	t = (t2-t1)/k;
		}
		x = t / sqrt(log(n)); //cota subestimada
		y = t / log(n);
		z = t / pow(n, 0.5);  //cota sobreestimada
		printf("%12d%15.3f%15.6f%15.6f%15.6f\n", n, t, x, y, z);
		n = n*10;
	 }
 }
 
 int main(){
	 test();
	 printf("\n");
	 
	 printf("Fib1:      N               T       Cota Sub              Y     Cota Sobre\n");
	 
	 medirTiempoFib1();
	 
	 printf("Fib2:      N               T       Cota Sub              Y     Cota Sobre\n");
	 
	 medirTiempoFib2();
	 
	 printf("Fib3:      N               T       Cota Sub              Y     Cota Sobre\n");
	 
	 medirTiempoFib3();
 }
