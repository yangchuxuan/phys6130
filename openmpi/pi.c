#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

double pii=3.141592653;
double pi(int count,int rank)
{
	double tempx = 0;
	double tempy = 0;
	int truecount=0;
	double temppi=0;

	for (int i = 0; i < count; i++)
	{
		tempx = (double)rand() / RAND_MAX;
		//tempx = (double)rand() / RAND_MAX/10+0.1*rank;	
		tempy = (double)rand() / RAND_MAX;
		if ((tempx*tempx + tempy*tempy) < 1.0)
		{
			truecount++;
		}
	}
	//printf("%f\n",(4.0 * ((double)truecount / count)));
	//printf("%d\n",truecount);
	return truecount;
}

int main(void)
{
	int rank,size;
	int sum=0;
	int count=10000;
	double temp=0;
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int localsum=0;
	srand(rank);
	localsum=pi(count,rank);
	/*temp=pi(100);
	printf("When count=100, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	temp=pi(1000);
	printf("When count=1000, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	temp=pi(10000);
	printf("When count=10000, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	temp=pi(100000);
	printf("When count=100000, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);*/


	//Now need MPI_Reduce
	//printf("%d\n",localsum);
	MPI_Reduce(&localsum,&sum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	//printf("%d\n",localsum);
	if(0==rank)
	{
		temp=(4 * ((double)sum / (count*10)));
		printf("When count=10000, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	
	}
	MPI_Finalize();
	return 0;
}

