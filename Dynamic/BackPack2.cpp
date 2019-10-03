/*рюкзак ограниченный*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <conio.h>
#include <math.h>
#include <vector>
using namespace std;
#define N 3
#define W 4

int d[N+1][W+1] = {0};
		//  1 2 3 4 5
int c[N] = {10,26,23};
int w[N] = {2,5,4};
int b[N] = {3,4,2};
void Print(int i, int j)
{
	if(d[i][j] == 0) return;
	if(d[i-1][j] == d[i][j]) Print(i-1,j);
	else 
	{
		Print(i-1,j-w[i-1]);
		printf("%d ",i);
	}
}
void print()
{
	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<=W; j++)
		{
			printf("%d ",d[i][j]);
		}
		printf("\n");
	}
}
struct p
{
	vector<int> list;	
};
int main()
{	
	printf("%d\n",W);
	printf("col\tm\tc\n");
	for(int i=0;i<N;i++)
	{
		printf("%d \t%d \t%d \n",b[i],w[i],c[i]);
	}
	printf("\n");
	p pb[N+1][W+1];
	for(int i=1; i<=N; i++)
	{
		for(int j=0; j<=W; j++)
		{
			d[i][j] = d[i-1][j];
			pb[i][j].list.insert(pb[i][j].list.end(), pb[i-1][j].list.begin(), pb[i-1][j].list.end());
			int k = min(b[i-1],j/w[i-1]);
			for(int l=k; l>0; l--)
			{
				if(j>=w[i-1])
				{
					d[i][j] = max(d[i][j],d[i-1][j-l*w[i-1]]+c[i-1]*l);
					if(d[i][j] == d[i-1][j-l*w[i-1]]+c[i-1]*l)
					{
						pb[i][j].list.clear();
						if(d[i-1][j-l*w[i-1]]!=0)
						{
							pb[i][j].list.insert(pb[i][j].list.end(), pb[i-1][j-l*w[i-1]].list.begin(), pb[i-1][j-l*w[i-1]].list.end());
						
						}
						for(int h=0;h<l;h++)
						{
							pb[i][j].list.push_back(i-1);
						}
					}
				}
			}
		}
	}
	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<=W; j++)
		{
			printf("%d \t",d[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<=N;i++)
	{
		for(int j=0; j<=W; j++)
		{
			for(int k=0;k<pb[i][j].list.size();k++)
			{
				printf("%d",pb[i][j].list[k]+1);
			}
			printf("\t");
		}
		printf("\n");
	}
	printf("sum=%d: ",d[N][W]);
	for(int k=0;k<pb[N][W].list.size();k++)
	{
		printf("%d ",pb[N][W].list[k]+1);
	}

	return 0; 
}
