#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <conio.h>
#define N 4	
/*int g[N][N] =  {   {0,2,4,9,1,3,7},
					 {4,0,9,7,6,INT_MAX,8},
					 {6,7,0,2,5,1,3},
					 {8,INT_MAX,1,0,2,4,9},
					 {1,6,INT_MAX,3,0,1,4},
					 {10,2,7,8,6,0,3},
					 {INT_MAX,5,3,6,8,1,0}};
	*/	
	int g[N][N] =  {   {0,1,6,INT_MAX},
					 {INT_MAX,0,4,1},
					 {INT_MAX,INT_MAX,0,INT_MAX},
					 {INT_MAX,INT_MAX,1,0}};			 
int p[N][N];


void FindPath(int i, int j)
{

 	if(i==j)
      printf("%d ",i);
    else if(p[i][j] == INT_MAX)
      printf("no path "); 
    else{
      FindPath( i, p[i][j]);
      printf("%d ",j);
    }
}
int main()
{
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
		{
			p[i][j] = i;
			if (g[i][j] == INT_MAX)
				p[i][j] = INT_MAX;
			
		}
	for (int k=0; k<N; k++)
		for (int i=0; i<N; i++)
			for (int j=0; j<N; j++)
			{
				if (g[i][k] < INT_MAX && g[k][j] < INT_MAX)
				{
					if(g[i][j]>g[i][k] + g[k][j])
					{
					g[i][j] = g[i][k] + g[k][j];
					p[i][j] = p[k][j];
					}
				}
			}
		
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
		if(g[i][j]==INT_MAX)
			printf(" oo ");
		else
			printf("%3d ",g[i][j]);
		}	
		printf("\n");
	}	printf("\n");

	FindPath(1,2);
	return 0;
	
}
