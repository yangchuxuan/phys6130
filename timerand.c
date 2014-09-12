#include <stdio.h>
#include <time.h>

int main(){

  srand(time(NULL));
  for (int i=0; i<10; i++){
	printf("%f \n", rand());
  }

  return 0;
}
