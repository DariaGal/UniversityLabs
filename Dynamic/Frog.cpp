#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <algorithm>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define N 6
#define M N/2+1
int stones[N] = {0, 1 , 3, 6 , 7, 8};
//int stones[N] = {0, 1, 2, 3, 6, 8, 10, 11, 13, 15, 18, 20};
//int stones[N] = {0, 1, 2, 3, 5, 8, 9, 10, 14, 18, 21, 22, 24, 26};
//int stones[N] = {0, 1, 2, 3,4,5,6,7,8,9,10};
int d[M][N];

void print()
{
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(d[i][j]!=INT_MAX)
			printf("%d\t ",d[i][j]);
			else
			printf("+oo\t ");
		}
		printf("\n");
	}
}
int findStoneIndex(int x, int currentIndex)
{
	for(int i = currentIndex; i >=0; i--)
	{
		if(x == stones[i])
		{
			return i;
		}
	}
	return -1;
}

int findMinIndex(int j)
{
	int min = INT_MAX;
	int IndexMin = -1;
	for(int i=0; i<M; i++)
	{
		if(min>d[i][j])
		{
			min = d[i][j];
			IndexMin = i;
		}
	}
	return IndexMin;
}

int main()
{
	for(int i=0;i<N;i++) 
	{ 
		for(int j=0;j<N;j++) 
		{ 
			d[i][j] = INT_MAX; 	
			d[0][j] = stones[j];
		} 
	} 
	int min = INT_MAX;
	int startIndex = -1;
	for(int j=1;j<N;j++) 
	{
		for(int i=1;i<M;i++) 
		{ 
			if((stones[j]-i)>=0)
			{
				for (int k=0; k<j; k++)
				{
					if ((stones[j]-i) == stones[k])
					{
						if(i==1 && j>1)
						{
							min = MIN(d[i][k], d[i+1][k]);
						}
						else
							min = MIN(MIN(d[i][k],d[i-1][k]), d[i+1][k]);
							
						if (min<INT_MAX)
						{
							min++;
							d[i][j]=min;
							startIndex = i;													
						}	
					} 
				}
			}
		}
	}
	print();
	int stepsCount = d[startIndex][N-1];
	printf("\nstartIndex = %d \nstepsCount = %d\n", startIndex, stepsCount);
	int stoneIndex = N-1;
	int index = startIndex;
	if(stepsCount == INT_MAX || startIndex == -1)
	{
		printf("no path");
	}
	else
	while(stepsCount>0)
	{
		printf("%d ",stones[stoneIndex]);
		int stoneNumber = stones[stoneIndex] - index;
	//	printf("stone %d \n",stoneNumber);
		
		stoneIndex = findStoneIndex(stoneNumber,stoneIndex);
	//	printf("index stone %d \n",stoneIndex);
		
		index = findMinIndex(stoneIndex);
	//	printf("index %d \n\n",index);
		stepsCount--;
	}
	return 0; 
}
