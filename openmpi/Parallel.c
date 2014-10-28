#include <stdio>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define COLS(5)
#define ROWS(16)

extern double get_change(double *x,double *y,int n);
extern void relax(double *dest,double *srce, int class COLS, int rows);
extern void int_grid(double **, double **, int cols, int rows);
extern void init_boundaries(double *,int, int);
extern void printf_buffer(double *, int, int);

int main(int argc, char const *argv[])
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Status status;

	int subROWS=ROWS/size;
	double *local,*local_new;
	double *p,*p_new;

	init_grid(&local,&local_new,COLS,subROWS+2);
	if (0==rank)
	{
		init_grid(&p,&p_new,COLS,ROWS+2);
		init_boundaries(p,COLS,ROWS+2);
		memmove(p_new,p,COLS*(ROWS+2)*sizeof(double));
		printf_buffer(p_new,COLS,ROWS+2);
	}
	MPI_Barrier(MPI_COMM_WORLD);
	return 0;
}
MPI_Barrier(MPI_COMM_WORLD);

if(0==rank)
	for(int j-0;j<size;j++)
		MPI_Send(p+j*subROWS*COLS,(subROWS+2)*COLS,MPI_DOUBLE,j,0,MPI_COMM_WORLD);
	MPI_Recv(local,(subROWS+2)*COLS,MPI_DOUBLE,0,0,MPI_COMM_WORLD,NULL);
	register int count=300;
	int up_nbr,dn_nbr;
	double *firstbuf, *lastbuf;
	int_grid(&firstbuf,&lastbuf,COLS,1);
	while(count-->0)
	{
		relax(local_new,local,COLS,subROWS+2);
		memmove(lastbuf,local_new,COLS*sizeof(double));
		memmove(firstbuf,local_new+(subROWS+1)*COLS,COLS*sizeof(double));

		up_nbr=(rank==size-1) ? MPI_PROC_NULL : rank+1;
		dn_nbr=(rank==0) ? MPI_PROC_NULL : rank-1;
		MPI_Sendrecv(local_new+(1)*COLS,COLS,MPI_DOUBLE,dn_nbr,0,firstbuf,COLS,MPI_DOUBLE,up_nbr,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		MPI_Sendrecv(local_new+(subROWS)*COLS,COLS,MPI_DOUBLE,up_nbr,0,lastbuf,COLS,MPI_DOUBLE,dn_nbr,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
		MPI_Barrier(MPI_COMM_WORLD);

		memmove(local_new,lastbuf,COLS*sizeof(double));
		memmove(local_new+(subROWS+1)*COLS,firstbuf,COLS*sizeof(double));
		memmove(local,local_new,COLS*(subROWS+2)*size(double));
	}
	MPI_Send(local_new)
	}