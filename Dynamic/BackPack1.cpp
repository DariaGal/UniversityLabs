/*рюкзак неограниченный*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <math.h>
#include <vector>
using namespace std;

#define N 5
#define W 15

int d[N+1][W+1] = {0};
int c[N] = {8,14,23,7,5};
int w[N] = {3,5,8,4,2};

void Print(int i, int j)
{
	if(d[i][j] == 0) return;
	if(d[i-1][j] == d[i][j]) Print(i-1,j);
	else 
	{
		Print(i,j-w[i-1]);
		printf("%d ",i);
	}
}

int main()
{
	
	for(int i=1; i<=N; i++)
	{
		for(int j=0; j<=W; j++)
		{
			d[i][j] = d[i-1][j];
			if(j>=w[i-1])
			{
				d[i][j] = max(d[i][j],d[i][j-w[i-1]]+c[i-1]);
			}
		}
	}
	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<=W; j++)
		{
			printf("%d\t",d[i][j]);
		}
		printf("\n");
	}
	
	Print(N, W);
	return 0; 
}
