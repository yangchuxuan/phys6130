#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>
#include <time.h>
#define STRING_SZ 300


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
	//target=rand()%size;
	//printf("%d\n",target);
	
	if(rank==0)
	{
		//snprintf(string,sizeof(string),"%s",string_temp);
		target=rand()%size;
		printf("Game start, there are %d player, rank 0 will send it to %d\n",size,target);
		MPI_Send(&string,STRING_SZ,MPI_CHAR,target,1,MPI_COMM_WORLD);
	}
	
	MPI_Recv(&string,STRING_SZ,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,NULL);
	target=rank+1;;
	if(target>size-1)
		target=0;
	printf("%s, I'm rank %d, I will send it to %d \n",string,rank,target);
	MPI_Send(&string,STRING_SZ,MPI_CHAR,target,1,MPI_COMM_WORLD);
	MPI_Finalize();
	return 0;
	
}
