#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define COLS (5)
#define ROWS (16)

extern double get_change(double *x,double *y,int n);
extern void relax(double *dest,double *srce, int cols, int rows);
extern void init_grid(double **, double **, int cols, int rows);
extern void init_boundaries(double *,int, int);
extern void printf_buffer(double *, int, int);

int main(int argc, char const *argv[])
{
	int size, rank;
	//MPI_Init(&argc, &argv);
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	int subROWS=ROWS/size;
	double *local,*local_new;
	double *p,*p_new;

	init_grid(&local,&local_new,COLS,subROWS+2);
	if (0==rank)
	{
		printf("Size: %d\nSubrow size is:%d\nThis is the unrelaxed data we have:\n",size,subROWS);
		init_grid(&p,&p_new,COLS,ROWS+2);
		init_boundaries(p,COLS,ROWS+2);
		memmove(p_new,p,COLS*(ROWS+2)*sizeof(double));
		printf_buffer(p_new,COLS,ROWS+2);
		printf("data ended\n");
	}
	MPI_Barrier(MPI_COMM_WORLD);
	/*free(local);
	free(local_new);
	free(p);
	free(p_new);*/
	//return 0;

	//MPI_Barrier(MPI_COMM_WORLD)


	if(0==rank)
		for(int j=0;j<size;j++)
			MPI_Send(p+j*subROWS*COLS,(subROWS+2)*COLS,MPI_DOUBLE,j,0,MPI_COMM_WORLD);
	MPI_Recv(local,(subROWS+2)*COLS,MPI_DOUBLE,0,0,MPI_COMM_WORLD,NULL);
	
	register int count=50;
	int up_nbr,dn_nbr;
	double *firstbuf, *lastbuf;
	init_grid(&firstbuf,&lastbuf,COLS,1);
	while(count>=0)
	{
		///*
		//printf("Rank:%d\n",rank);
		memmove(local_new,local,COLS*(subROWS+2)*sizeof(double));
		relax(local_new,local,COLS,subROWS+2);
		//printf("After relax\n");
		//printf_buffer(local_new,COLS,subROWS+2);

		memmove(lastbuf,local_new,COLS*sizeof(double));
		memmove(firstbuf,local_new+(subROWS+1)*COLS,COLS*sizeof(double));

		up_nbr=(rank==size-1) ? MPI_PROC_NULL : rank+1;
		dn_nbr=(rank==0) ? MPI_PROC_NULL : rank-1;
		//refresh these two buffers here
		MPI_Sendrecv(local_new+(1)*COLS,COLS,MPI_DOUBLE,dn_nbr,0,firstbuf,COLS,MPI_DOUBLE,up_nbr,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		MPI_Sendrecv(local_new+(subROWS)*COLS,COLS,MPI_DOUBLE,up_nbr,0,lastbuf,COLS,MPI_DOUBLE,dn_nbr,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		MPI_Barrier(MPI_COMM_WORLD);

		memmove(local_new,lastbuf,COLS*sizeof(double));
		memmove(local_new+(subROWS+1)*COLS,firstbuf,COLS*sizeof(double));
		//maybe things here
		memmove(local,local_new,COLS*(subROWS+2)*sizeof(double));
		//printf("After send receive\n");
		//printf_buffer(local_new,COLS,subROWS+2);
		//printf("Rank:%d over\n",rank);
		//
		count=count-1;
	}
	MPI_Send(local_new+1*COLS,(subROWS)*COLS,MPI_DOUBLE,0,(subROWS+2),MPI_COMM_WORLD);
	//receive relaxed data
	if (0==rank)
		for(int i=0;i<size;i++)
		{
			MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			//MPI_Recv(p_new+(status,MPI_SOURCE*subROWS+1)*COLS,(subROWS)*COLS,MPI_DOUBLE,status,MPI_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			MPI_Recv(p_new+(status.MPI_SOURCE*subROWS+1)*COLS,(subROWS)*COLS,MPI_DOUBLE,status.MPI_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		}
	if(0==rank)
	{
		printf("Final result:\n");
		printf_buffer(p_new,COLS,ROWS+2);
	}
	
	free(local);
	free(local_new);
	free(p);
	free(p_new);
	free(firstbuf);
	free(lastbuf);
	MPI_Finalize();
	return 0;
}



	void relax(double *pnew,double *pold, int cols, int rows)
	{
	for ( int j = 1 ; j < (rows)-1; j++) {
		for ( int i = 1 ; i < cols-1; i++) {
			pnew[i+j*cols] = 0.25*(pold[i-1+j*cols]+pold[i+1+j*cols]+pold[i+(j-1)*cols]+pold[i+(j+1)*cols]);
//			printf("  %d   \n",i+(j-1)*COLS);
//			printf("%d  %d  %d\n",i-1+j*COLS,j+i*COLS,j+1+i*COLS);
//			printf("  %d   \n",i+(j+1)*COLS);
		}
//		puts(" ");
//		puts(" ");
	}


}

void init_boundaries(double *l_p,int cols,int rows)
{
/* 
	for ( int i = 0 ; i < cols; i++) {
		l_p[i] = -1;
		l_p[i + cols*(rows -1)] = 1;
	}

	for ( int i = 0 ; i < rows; i++) {
		l_p[i*cols] = -1;
		l_p[(i+1)*cols -1] = 1; //column
		// l_p[i*(cols-1)+rows-1] = -1; //diagonal
	}
*/
	for (int i = 0 ; i < cols*rows; i++ )
		l_p[i] = 0;
	l_p[cols/2] = 1;
}


void init_grid(double **p, double **p_new,int cols, int rows)
{
	/*if (NULL == (*p = malloc(  cols*rows * sizeof(double) )  )  ) {
		puts("Allocation Error.");
		exit(99);
	}
	if (NULL == (*p_new = malloc(cols*rows * sizeof(double)))) {
		puts("Allocation Error.");
		exit(99);
	}*/
	*p = (double *)malloc(cols*rows * sizeof(double));
	*p_new = (double *)malloc(cols*rows * sizeof(double));
	for ( int i = 0 ; i < cols*rows; i++){

		(*p)[i] = 0. ;
		(*p_new)[i] = 0. ;
	}
}

void printf_buffer(double *p, int cols, int rows)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%f\t",p[i*cols+j]);
		}
		puts(" ");
	}
	printf("\n");


}

double get_change(double *x, double *y, int n)
{
	double result=0.;
	for (int i=0; i<n;i++)
		result+=x[i]*x[i]-y[i]*y[i];
	return result;
}

