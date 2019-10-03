#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <math.h>
#include <vector>
#define N 5
using namespace std;

//int r[]={10,10,10,10,10,10,10,10};
int r[]={10,20,50,1,100};

int s[N+1][N+1];

void Print(int m[N+1][N+1])
{
	for(int t=1; t<=N;t++)
	{
		for(int k=t; k<=N;k++)
		{
			printf("f(%d,%d) = %d\t",t,k,m[t][k]);
		}
		printf("\n");
	}
	printf("\n");
}
void PrintSolution(int t, int k)
{
	if(t==k) 
		printf("M%d", t);
	else
	{
		printf("(");
		PrintSolution(t,s[t][k]);
		printf("*");
		PrintSolution(s[t][k]+1,k);
		printf(")");
	}
}
int main()
{
	int M[N+1][N+1];
	for(int i=0; i<=N;i++)
	{
		M[i][i]=0;
	}
	for(int t=1; t<N;t++)
	{
		for(int k=1; k<N;k++)
		{
			int min = INT_MAX;
			for(int j = k; j<=k+t-1; j++)
			{
				int m = M[k][j]+M[j+1][k+t]+r[k-1]*r[j]*r[k+t];
				if(m<min)
				{
					min = m;
					M[k][k+t] = min;
					s[k][k+t] = j;
				}
			}
		}
	}
	Print(M);
//	Print(s);
	PrintSolution(1,N);
	return 0; 
}
