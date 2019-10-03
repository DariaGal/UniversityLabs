#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits.h>

using namespace std;
#define N 7
int T=0;

int p[N][N];


int main()
{
/*	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			p[i][j] = INT_MAX;
		}
	}*/

	setlocale( LC_ALL,"Russian" );
	int C[N][N] = {   {0,2,4,9,1,3,7},
						 {4,0,9,7,6,INT_MAX,8},
						 {6,7,0,2,5,1,3},
						 {8,INT_MAX,1,0,2,4,9},
						 {1,6,INT_MAX,3,0,1,4},
						 {10,2,7,8,6,0,3},
						 {INT_MAX,5,3,6,8,1,0}};
 /*	int C[N][N] =  {   {0,1,6,INT_MAX},
					{INT_MAX,0,4,1},
					{INT_MAX,INT_MAX,0,INT_MAX},
					{INT_MAX,INT_MAX,1,0}};	*/
	for (int i=0; i<N; i++)
	for (int j=0; j<N; j++)
		{
			p[i][j] = i;
			if (C[i][j] == INT_MAX)
				p[i][j] = INT_MAX;
			
		}

	int start = 0;
	vector<int> S;
	int D[N][N];
	int W[N],Dw[N];
	bool visited[N];
	for(int i = 0;i<N;i++)
	{
		visited[i] = false;
	}
	visited[start] = true;
	S.push_back(start);
	for(int i = 0;i<N;i++)
	{
		for(int j = 0;j<N;j++)
		{
			if(i==0 && j!=start)
			D[i][j] = C[start][j];
			else D[i][j] = -1;
		}
	}
	W[0] = -1;
    Dw[0] = -1;
	int i = 0, w;
	for (int i=0;i<N-1;i++)
	{
		int min = INT_MAX;
		cout<<"S=";
		for(int s = 0;s<S.size();s++)
		{
			cout<<S[s]<<" ";
		}
		cout<<"\nD[W]=min(";
       	for(int j = 0;j<N;j++)
       	{
       		if(!visited[j] && D[i][j]<min)
       		{
       			min = D[i][j];
       			w = j;
       		}
       		if(!visited[j])
       		{
       			 if(D[i][j]==INT_MAX) cout<<" oo,"; else cout<<" "<<D[i][j]<<",";
       		}
       	}
       	cout<<")="<<min<<endl;
       	cout<<"W="<<w<<endl;
      	visited[w] = true;
       	W[i+1] = w;
       	Dw[i+1] = min;
		S.push_back(w);
       	for(int j = 0;j<N;j++)
       	{
       		if(!visited[j])
       		{
       			T++;
	       		if(min!= INT_MAX && C[w][j]!= INT_MAX && w!=j)
	       		{
	       			cout<<"D["<<j<<"] = min("<<"D[V"<<j<<"]"<<", "<<min<<"+"<<"C("<<w<<","<<j<<")) = min(";
					   if(D[i][j]==INT_MAX) cout<<"oo"; else cout<<D[i][j];
					   cout<<","<<min + C[w][j]<<") = ";
	       		   	D[i+1][j] = (D[i][j]<min+C[w][j]) ? D[i][j] : min+C[w][j];
	       		   	cout<<D[i+1][j]<<endl;
	       		   	
	       		   
	       		} else
				   {
				   		D[i+1][j] = D[i][j];
				  	 	cout<<"D["<<j<<"]="<<D[i][j]<<endl;
					}
       		}
       	}
       	cout<<"_______________________________________________\n";
	}
	
	
	cout<<"\n\n|   W  |  D[W] |";
	for(int i = 0;i<N;i++)
	{
		if(i!=start)
		cout<<" D["<<i<<"] |";
	}
	cout<<endl;
	cout<<"_________________________________________________________________"<<endl;
	for(int i = 0;i<N;i++)
	{
		if(W[i]==-1)
				 printf("|  --  |");
				 else
		printf("| %4d |",W[i]);
		if(Dw[i]==-1)
				 printf("   --  |");
				 else
		printf("  %4d |",Dw[i]);
		for(int j = 0;j<N;j++)
		{
			if(j!=start)
			{
				if(D[i][j]==-1)
				 printf("  --  |");
				else if(D[i][j]==INT_MAX)
				printf("  oo  |");
				else
				printf(" %4d |",D[i][j]);
			}
			
		}
		cout<<endl;
	}
	
	cout<<"\n"<<T<<endl;

	return 0;
	
}
