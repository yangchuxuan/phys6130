#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double bessel(int l,double x){
	if(l==10) return 3;
	if(l==9) return 2;
	return (((2*l+3)*bessel(l+1,x)-x*bessel(l+2,x))/x);
	}

int main(void){
  for (int l=10;l>=0;l--){
	printf("%f \n",bessel(l,2));
	}
  
  return 0;
}
