
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef void (*vector_function)(double* y, double t, double* f);

//begin initial condition


/*
void F(double* y, double t, double* f)
{
    double d[3] = {y[6] - y[0], y[7] - y[1], y[8] - y[2]};
	double dcube = pow (d[0] * d[0] + d[1] * d[1] + d[2] * d[2], 1.5);
	for (int i = 0; i < 3; ++i)
	{
		//R_Earth
		f[i] = y[i+3];
        
		//V_Earth
        f[i + 3] = G * ms / dcube * d[i];
        
		//R_Sun
        f[i + 6] = y[i + 9];
        
        //V_Sun
        f[i + 9] = - G * me / dcube * d[i];
	}
    
}
*/
void F(double* y, double t, double* f)
{
double g=9.8,m1=0.000003,m2=1;
double r = y[0];
double vr = y[1];
double th = y[2];
double L=3;
f[0] = vr;
f[1] = (L*L/(m1*r*r*r)-m2*g)/(m1+m2);
f[2] = L/(m1*r*r);
}
//end initial condition


//Runge-Kutta Method Begin
void integrator(vector_function f, int n, double* y,
                double t, double dt, double* yn)
{
    
    double k1[n],k2[n],k3[n],k4[n],ytmp[n];
    double deriv[n]; 
    f(y,t,deriv);
    for(int i=0;i<n;++i)
    {
        k1[i]=deriv[i]*dt;
        ytmp[i]=y[i]+0.5*dt*deriv[i];
    }
    f(ytmp,t+0.5*dt,deriv);
    for(int i=0;i<n;++i)
    {
        k2[i]=dt*deriv[i];
        ytmp[i]=y[i]+0.5*dt*deriv[i];
    }
    f(ytmp,t+0.5*dt,deriv);
    for(int i=0;i<n;++i)
    {
        k3[i]=dt*deriv[i];
        ytmp[i]=y[i]+dt*deriv[i];
    }
    f(ytmp,t+dt,deriv);
    for(int i=0;i<n;++i) k4[i]=dt*deriv[i];
    
    for(int i=0;i<n;++i)
    {
        yn[i]=y[i]+(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6;
    }
}
//Runge-Kutta Method Over



//main function begin
int main(int argc, char ** argv)
{
	
	double g=9.8,m1=0.000003,m2=1;//initial condition harded coded, to change it just modify the golbal variables
	int tf,m;
	FILE *fp;
	fp=fopen("data.txt", "wt+");
	printf("Please input the final time of the iteration\n");
	scanf("%d",&tf);
	printf("please input the number of steps \n");
	scanf("%d",&m);
	double y[3],yn[3];//,sum[2];
	double t=0,i;

	double dt=( tf-t)/m;
	// the runge-kuta integrator starts from here
	t=0;
	y[0]=1;//r0=1
	y[1]=0;//vr0=0
	y[2]=0;//theta0=0
	for (int k=0; k<m;k++)
	{
	integrator(F, 3,  y, t, dt, yn);
	//printf("%.15e %.15e\n", y[0], y[2]);
	t=t+dt;
	for(int i=0; i<3; i++)y[i] = yn[i];
	//printf("{%.15e, %.15e}\n", y[2], y[0]);
	fprintf(fp,"{%.15f,%.15f},\n",y[2],y[0]);
	
	}
	fclose(fp);
	return 0;

}
//printf("the intigrated r is %lf\n",yn[0]);
//printf("the intigrated vr is %lf\n",yn[1]);
//printf("the intigrated theta is %lf\n",yn[2]);
//fprintf(fp,"{%.15e,%.15e},\n",y[2],y[0]);
