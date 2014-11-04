#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <time.h>
#define STRING_SZ 30
#define CORE_SZ 10


int main (void)
{
	int rank,size;
	char *string;
	int target;
	//int j=CORE_SZ;
	//string =malloc(STRING_SZ * sizeof(char));
	string="TAG! You're it!";
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	srand(time(NULL));
	target=(int)((double)rand()/RAND_MAX*CORE_SZ);
	printf("%d",target);

	if(rank==0)
	{
		//snprintf(string,sizeof(string),"%s",string_temp);
		//here we need to send the string, but the size of the string is unknow, it is a problem
		MPI_Send(string,STRING_SZ,MPI_CHAR,target,MPI_ANY_TAG,MPI_COMM_WORLD);
	}
	
	MPI_Recv(string,STRING_SZ,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,NULL);
	target++;
	if(target>size)
		target=0;
	printf("%s, I'm rank %d\n",string,rank);
	MPI_Send(string,STRING_SZ,MPI_CHAR,target,MPI_ANY_TAG,MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
	
}
