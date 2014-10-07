#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv) {

	srand(atoi(argv));
	
	for (int i = 0; i < 10 ; i++) {
		printf("%d %f\n",i,rand()/(double) RAND_MAX);
	}
	
}
