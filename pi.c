#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	srand(time(NULL));
	printf("When count=100, Pi is %f\n", pi(100));
	printf("When count=1000, Pi is %f\n", pi(1000));
	printf("When count=10000, Pi is %f\n", pi(10000));
	printf("When count=100000, Pi is %f\n", pi(100000));
	printf("When count=1000000, Pi is %f\n", pi(1000000));
	printf("When count=10000000, Pi is %f\n", pi(10000000));
	return 0;
	return 0;
}
