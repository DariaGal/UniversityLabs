#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <math.h>
#include <vector>
#define N 3
#define M 4
using namespace std;

int m[N][M] = {{1, 2, 4, -3},
			   {3,-1, 2,-10},
			   {3,-2,-3, 3}};
int d[N][M] = {0};
void Print()
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			printf("%d ",d[i][j]);
		}
		printf("\n");
	}
}
void PrintPath(int i,int j)
{
	if(i==0 && j==0) return;
	if(i==0) 
	{
		PrintPath(i,j-1);
		printf("right ");
	}
	else if(j==0)
	{
		PrintPath(i-1,j);
		printf("down ");
	}
	else if(d[i][j-1]>d[i-1][j]) 
		{
			PrintPath(i,j-1);
			printf("right ");
		} else
		{
			PrintPath(i-1,j);
			printf("down ");
		}
}
int main()
{
	d[0][0] = m[0][0];
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			
			if(i==0 && j==0) continue;
			else if(i==0) d[i][j] = d[i][j-1]+m[i][j];
				else if(j==0) d[i][j] = d[i-1][j]+m[i][j];
					else
					d[i][j] = max(d[i-1][j],d[i][j-1])+m[i][j];
		}
	}
	Print();
	printf("%d\n",d[N-1][M-1]);
	PrintPath(N-1,M-1);
	return 0; 
}
