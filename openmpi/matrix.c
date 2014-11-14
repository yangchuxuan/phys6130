#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#define Array_SZ 256;

int main(void)
{
	int rank,size;
	srand(time(NULL));
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	double *A=(double*)malloc(256 * sizeof(double));
	if (0==rank)
		for (int i=0;i<256;i++)
		{
			A[i]=rand();
			printf("%f ",A[i]);	
		}
		
	


	MPI_Finalize();
	return 0;
}



