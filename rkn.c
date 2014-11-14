/* Runge Kutta Nystrom, Order 4-- Integrates second order differential equation. 
 * f(x(t),v(t),t)=d2x/dt2=func, v=dx/dt.
 *
 * Arguments to main: None 
 *	Returns int.
 * 
 * Arguments to rkn4: function pointer, array of x, initial value of x
 * 		      array of v, initial value of v, step size, number of steps.
 *	Returns nothing but fills columns of x and v.
 *	Called from main
 *
 * Arguments to function: x and v as computed in rkn as well as t.
 *		This is the function to be integrated.
 *	Returns value of f.
 * 	Called from rkn
 * 
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double ms,me,a,e,G;

double functionx(double x, double y, double vx, double vy, double t);
double functiony(double x, double y, double vx, double vy, double t);

double (*funcx)(double x, double y, double vx, double vy, double t);
double (*funcy)(double x, double y, double vx, double vy, double t);

double rkn4(double (*funcx)(double x, double y, double vx, double vy, double t),double (*funcy)(double x, double y, double vx, double vy, double t),
	double x[], double y[], double x0, double y0, double vx[], double vy[], double vx0, double vy0, double t, double h, long steps);

double functionx(double x, double y, double vx, double vy, double t)
{
	double temp=0;
	temp=-G*me*x*(1+ms/me)/pow((x*x+y*y),3);
    return temp; //Change this value to change integrand.
}

double functiony(double x, double y, double vx, double vy, double t)
{
	double temp=0;
	temp=-G*me*x*(1+ms/me)/pow((x*x+y*y),3);
    return temp; //Change this value to change integrand.
}


int main (){
	long steps = 1000; 	//Number of steps.
	ms=1.989*pow(10,30);
	me=5.974*pow(10,24);
	a=1.495*pow(10,8);
	e=1.671*pow(10,-2);
	G=6.674*pow(10,-11);
	double KE=G*ms*me/a*(1/(1+e)-1/2);	
	double x0=a*(1+e)*ms/(me+ms);
	double y0=0;
	double vx0=0;
	double vy0=sqrt(2*KE/(me*(1+me/ms)));
	double t;
	double h=0.001; 			//Initial position, initial velocity, time, step size.
	double *x = (double*)malloc(steps * sizeof(double)); 
	double *y = (double*)malloc(steps * sizeof(double)); 	//Position array
    double *vx = (double*)malloc(steps * sizeof(double)); 	//Position array
    double *vy = (double*)malloc(steps * sizeof(double)); 	//Velocity array

/* Set pointer to point at the function to integrate. */
	funcx = functionx;
	funcy = functiony;

/* Do integration. */
	rkn4(funcx,funcy,x,y,x0,y0,vx,vy,vx0,vy0,t,h,steps);
	
/* Print results to STDOUT */
	long int i;
        for ( i=0; i<steps; ++i){
		printf(" %ld %e %e %e %e\n",i,x[i],y[i],vx[i],vy[i]);
        }


	return 0;
}

double rkn4(double (*funcx)(double x, double y, double vx, double vy, double t),double (*funcy)(double x, double y, double vx, double vy, double t), double x[], double y[], double x0, double y0, double vx[], double vy[], double vx0, double vy0, double t, double h, long steps)
{
	double k1,k2,k3,k4;
	
	x[0] = x0;
	y[0] = y0; //Initial position
	vx[0] = vx0;
	vy[0] = vy0; //Initial velocity
	
	long i;
	for ( i=1; i<steps; ++i){
		//x part
		k1 = funcx(x[i-1],y[i],vx[i-1],vy[i],t);	
		k2 = funcx(x[i-1]+h*vx[i-1]/2.+h*h*k1/8.,y[i],vx[i-1]+h*k1/2.,vy[i],t+h/2.);
        k3 = funcx(x[i-1]+h*vx[i-1]/2.+h*h*k1/8.,y[i],vx[i-1]+h*k2/2.,vy[i],t+h/2.);
		k4 = funcx(x[i-1]+h*vx[i-1]+h*h*k3/2.,y[i],vx[i-1]+h*k3,vy[i],t+h);
		
		x[i] = x[i-1] + h*vx[i-1] + h*h*(k1+k2+k3)/6.;
		vx[i] = vx[i-1] + h*(k1 + 2.*k2 + 2.*k3 + k4)/6.;

		//y part
		k1 = funcy(x[i],y[i-1],vx[i],vy[i-1],t);	
		k2 = funcy(x[i],y[i-1]+h*vy[i-1]/2.+h*h*k1/8.,vx[i],vy[i-1]+h*k1/2.,t+h/2.);
        k3 = funcy(x[i],y[i-1]+h*vy[i-1]/2.+h*h*k1/8.,vx[i],vy[i-1]+h*k2/2.,t+h/2.);
		k4 = funcy(x[i],y[i-1]+h*vy[i-1]+h*h*k3/2.,vx[i],vy[i-1]+h*k3,t+h);
		y[i] = y[i-1] + h*vy[i-1] + h*h*(k1+k2+k3)/6.;
		vy[i] = vy[i-1] + h*(k1 + 2.*k2 + 2.*k3 + k4)/6.;



		t+=h;
	}
	
	return 0;
}