#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

using namespace std;

#define SIZE 1000

int main(int argc, char **argv)
{
int size, rank;
MPI_Init(NULL,NULL);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

double *big_buf,*rec_buf;
double sum;

big_buf=(double*) malloc (sizeof(double) * SIZE * size);
rec_buf=(double*) malloc (sizeof(double) * SIZE);

for (int i=0; i<SIZE*size;i++)
	big_buf[i]=i;
MPI_Scatter(big_buf, SIZE, MPI_DOUBLE, rec_buf, SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);
double localsum=0;
for (int i=0; i<SIZE; i++)
{
	localsum +=rec_buf[i];
}
MPI_Reduce(&localsum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0,MPI_COMM_WORLD);

	if(0==rank);
	cout<<"\n>>THe sum of 0 thru" << SIZE*size-1<< "is"<<(long)sum<<endl;
	free(big_buf);
	free(rec_buf);
MPI_Finalize();

return 0;
}
