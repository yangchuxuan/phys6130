#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double pii=3.141592653;

double pi(int count)
{
	double tempx = 0;
	double tempy = 0;
	int truecount=0;
	for (int i = 0; i < count; i++)
	{
		tempx = (double)rand() / RAND_MAX;
		tempy = (double)rand() / RAND_MAX;
		if ((tempx*tempx + tempy*tempy) < 1.0)
		{
			truecount++;
		}
	}
	return (4 * ((double)truecount / count));
}

int main()
{
	double temp=0;
	srand(time(NULL));
	temp=pi(100);
	printf("When count=100, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	temp=pi(1000);
	printf("When count=1000, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	temp=pi(10000);
	printf("When count=10000, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	temp=pi(100000);
	printf("When count=100000, Pi is %f, and error is %f\n", temp,(temp-pii)/pii);
	return 0;
	return 0;
}

