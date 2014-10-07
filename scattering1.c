#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define pi 3.141592653

struct position
{
	double x;
	double y;	
};


int Z=0;
double E=0;
int A=0;

double irand()
{
	return (double)rand()/RAND_MAX;
}

double energy(double Ec)
{
	E=Ec*(1+0.01*pow(-2*log(irand()),1/2)*cos(2*pi*irand()));
	return 0;
}
double alpha()
{
	return (3.4*pow(10,-3)*pow(Z,0.67)/E);
}

double step()
{
	//double alpha=3.4*pow(10,-3)*pow(Z,0.67)/E;
	double sigmaE=5.21*pow(10,-21)*Z*Z/E/E*4*pi/(alpha()*(alpha()+1))*pow((E+511)/(E+1024),2);
	double lambda=A/(6.022*pow(10,23)*196.9665*sigmaE);
	return (-lambda*log(irand())*pow(10,8));
	//in unit of 10*e-10
}

double phi()
{
	//double alpha=3.4*pow(10,-3)*pow(Z,0.67)/E;
	//return 1-(2*alpha()*irand())/(1+alpha()-irand());
	return 2*pi*irand();
}
double cospsi()
{
	return 1-(2*alpha()*irand())/(1+alpha()+irand());
}

double sinpsi()
{
	return Pow(1-cospsi(),1/2);
}

double perenergyloss()
{
	double J=(9.76*79+58.5/(Z^(0.19)))*pow(10,-3);
	return -78500*196.9665*Z/A/E*log(1.166*E/J+1);
}

double totalenergyloss()
{
	
	double totald=step()+R/sinphi();
	return totald*perenergyloss();
}

int main()
{
	double totald=0;
	position *p=(position*) malloc(10 * sizeof(position));
	Z=79;
	double Ec=10000;
	A=117;
	srand(time(NULL));
	for (int i=0;i<10;i++)
	{
		energy(Ec);
		//printf("%f\n",E);
		//now for the interaction point
		//printf("%f\n",step());
		//printf("%f",phi());
		printf("step here is %f\n",step());
		printf("scattering angle here is %f\n",arccos(cosphi()));
		printf("energy loss is %f\n",totalenergyloss());
	}
	
	return 0;
}
