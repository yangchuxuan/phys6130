#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double bessel(int l,double x){
	//printf("%f",sin(x)/x);
	if (l == 0)  return (sin(x)/x);
	if (l == 1)  return (sin(x)/(x*x)-cos(x)/x);
	return (((2*l-1)*bessel(l-1,x)-x*bessel(l-2,x))/x);
	}

int main(void){
  //printf("%f\n",sin(2.0)/2.0);
  for (int l=0;l<10;l++){
	printf("%f \n",bessel(l,2.0));
	}
  return 0;
}
