#include <stdio.h>
#include <math.h>
#include <stdlib.h>


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
			printf("%f\t",p[i*COLS+j]);
		}
		puts("  ");
	}
}


int main(int argc, char** argv)

{

    int NN=0;
    FILE* fileA = fopen("arrayA.dat", "r");
    FILE* fileB = fopen("arrayB.dat", "r");
   
    while (fscanf(fileA, "%*f")!=EOF)
	NN++;
    rewind(fileA);
    
    int N=sqrt((double)NN);
    double  *dataA = malloc(NN*sizeof(double));
    double  *dataB = malloc(N*sizeof(double));

    for (int i=0; i<N*N; i++) 
        fscanf(fileA, "%lf", &dataA[i]);
    for (int i=0; i<N; i++) 
        fscanf(fileB, "%lf", &dataB[i]);

    fclose(fileA);
    fclose(fileB);
    printf("The first input matrix is:\n");
    print_matrix(dataA,N,N);
    printf("The Second input matrix is:\n");
    print_matrix(dataB,N,1);
    double *x = malloc(N*sizeof(double));
    solve_system(dataA, N, dataB, x);
    printf("The result is:\n");
    print_matrix(x,N,1);
    printf("\n");


    return 0;
}
