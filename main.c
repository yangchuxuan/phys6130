#include <stdio.h>
#include <time.h>

int main(){

  srand(time(NULL));
  for (int i=0; i<10; i++){
	printf("%f \n", rand()/(double)RAND_MAX);
  }

  return 0;
}
