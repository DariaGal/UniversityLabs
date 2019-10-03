#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <math.h>
#include <vector>
using namespace std;
#define N 15
#define k 2
int main()
{
	int d[N];
	int c[N] = {0, 1, INT_MIN, 3, INT_MIN, INT_MIN, 2, 0, INT_MIN, 0, INT_MIN, INT_MIN, 1, 3, 0};
	int l[k] = {1,3};
	for(int i=0; i<N; i++)
	{
		d[i] = INT_MIN;	
	}
	d[0] = 0;

	for(int i = 1; i<N;i++)
	{
		int max = -INT_MAX;
		for(int j=0; j<k; j++)
		{
			if(l[j]<=i)
			if(d[i-l[j]]+c[i]>max)
			{
				max = d[i-l[j]]+c[i];
			}
		}
		d[i] = max;
	}
	for(int i =0;i<N;i++)
	{
		printf("%d ",d[i]);
	}
	return 0; 
}
