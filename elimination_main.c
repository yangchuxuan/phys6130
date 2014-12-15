#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


void swap(double* a, double* b)
{
    double c=*a;
    *a=*b;
    *b=c;
}

void swap_rows(double* m, int N, int r1, int r2)
{
	for(int c=0; c<N; c++)
		swap(m+r1*N+c, m+r2*N+c);
}

int find_pivot(double* m, int N, int r)
{
    int p=r;
    double val = fabs(m[r*N+r]);
    for (int rp=r+1; rp<N; rp++)
    if(fabs(m[rp*N+r])>val)
    {
        p=rp;
        val = fabs(m[rp*N+r]);
    }
return p;
}

void eliminate(double* m, int N, double* b)
{
    for(int r=0; r<N-1; r++)
    {
        int p = find_pivot(m, N, r);
        if(p != r)
    { 
        swap_rows(m, N, r, p);
        swap(b+r, b+p);
  }


  double piv = m[r*N+r];
//    if(fabs(piv)<1e-20) {printf("matrix nearly singular ...."); abort();}

  for(int rp = r+1; rp<N; rp++)
  {
      double fact = -m[rp*N+r]/piv;
      for(int c=r; c<N; c++) m[rp*N+c]+=fact*m[r*N+c];
          b[rp]+=fact*b[r];
  }
  }
}

void bks(double* m, int N, double* b, double* x)
{
  for(int r=N-1; r>-1; --r)
  {
      double temp = b[r];
      for (int c = r+1; c<N; ++c) temp -= m[r*N+c]*x[c];
          x[r] = temp/m[r*N+r];
  }
}

void solve_system (double* m, int N, double* b, double* x)
{
    eliminate (m, N, b);
    bks (m, N, b, x);
    
}

void print_matrix(double *p, int COLS,int ROWS)
{
	for (int i=0;i<ROWS;i++)
	{
		for (int j=0;j<COLS;j++)
		{
			printf("%7.3f",p[i*COLS+j]);
		}
		puts("  ");
	}
}
void init_matrix(double **p,int COLS,int ROWS)
{
	*p = (double *)malloc(COLS*ROWS * sizeof(double));
	for (int i=0;i<COLS*ROWS;i++)
	{
	(*p)[i] =(int)((double)rand()/RAND_MAX*10);
	}

}


int main(int argc, char** argv)

{
    int D=10;
    srand(time(0));
    double *A;
    double *B;
    init_matrix(&A,D,D);
    init_matrix(&B,D,1);
    printf("The first input matrix is:\n");
    print_matrix(A,D,D);
    printf("The Second input matrix is:\n");
    print_matrix(B,D,1);
    double *x = malloc(D*sizeof(double));
    solve_system(A, D, B, x);
    printf("The result is:\n");
    print_matrix(x,D,1);
    printf("\n");


    return 0;
}
