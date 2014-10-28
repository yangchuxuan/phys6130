/*
 * Test this example with 
 * 	mpirun -n $X ./scatter_gather
 * where for X in {2,4,8,16}
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS (5)
#define ROWS (8)

extern double get_change(double *x, double *y, int n);
extern void relax(double *dest,double *srce, int cols, int rows);
extern void init_grid(double **,double **,int cols, int rows);
extern void init_boundaries(double *,int,int rows);
extern void print_buffer(double *,int cols,int rows);

int main(int argc, char **argv) {

	double  *p,*p_new;
	init_grid(&p,&p_new,COLS,ROWS+2);

	init_boundaries(p,COLS,ROWS+2); 
	memmove(p_new,p, COLS*(ROWS+2) * sizeof(double) );




	// Do some calculations.
	int count = 0;
	while (count++ < 300) {
		relax(p_new,p,COLS,ROWS+2);
		if (0.000001< get_change(p_new,p,COLS*(ROWS+2)))
			printf("Change/Iteration %f/%d\n",get_change(p_new,p,COLS*(ROWS+2)),count);
		memmove(p,p_new, COLS*(ROWS+2) * sizeof(double) );
	}





	// Print out the results.
		print_buffer(p,COLS,ROWS+2);
	free(p_new); 
	free(p); 
	return 0; 
}

void relax(double *pnew,double *pold, int cols, int rows){
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

void init_boundaries(double *l_p,int cols,int rows){
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


void init_grid(double **p, double **p_new,int cols, int rows){
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

void print_buffer(double *p, int cols, int rows){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%f\t",p[i*cols+j]);
		}
		puts(" ");
	}


}

double get_change(double *x, double *y, int n){
	double result=0.;
	for (int i=0; i<n;i++)
		result+=x[i]*x[i]-y[i]*y[i];
	return result;
}

