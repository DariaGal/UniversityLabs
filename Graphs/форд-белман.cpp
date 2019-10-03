#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <math.h>
#include <vector>

#include <limits.h>
#include <algorithm>
using namespace std;
#define N 7
int T=0;
bool equal(int *D1,int *D2)
{
	for(int i = 0;i<N;i++)
	{
		if(D1[i]!=D2[i])
		{
			return true;
		}
	}
	return false;
}

int main()
{
	
	setlocale( LC_ALL,"Russian" );
	int C[N][N] =  {   {0,2,4,9,1,3,7},
						 {4,0,9,7,6,INT_MAX,8},
						 {6,7,0,2,5,1,3},
						 {8,INT_MAX,1,0,2,4,9},
						 {1,6,INT_MAX,3,0,1,4},
						 {10,2,7,8,6,0,3},
						 {INT_MAX,5,3,6,8,1,0}};

	int Dold[N],Dnew[N];
	int start = 3;
	for(int i=0; i < N;i++)
	{
		if(i==start)
			Dnew[i]=0;
		else
			Dnew[i] = INT_MAX;
	}
	for(int i=0; i < N;i++)
	{
		if(Dnew[i]==INT_MAX)
		cout<<"oo"<<", ";
		else cout<<Dnew[i]<<", ";
	}
	cout<<endl;
	int step = 1;
	while(equal(Dold,Dnew))
	{
		cout<<"шаг "<<step<<endl;
		memcpy(Dold,Dnew,sizeof(Dnew));
		for(int i = 0; i < N; i++)
		{
			int min = INT_MAX;
			cout<<"D("<<i<<")=min(";
			for(int j = 0; j < N; j++)
			{
				int t = INT_MAX;
				if(Dold[j]!=INT_MAX && C[j][i]!=INT_MAX)
					t = Dold[j] + C[j][i];
				if(t<min) min = t;
				if(t==INT_MAX)
				cout<<" oo"<<",";
				else cout<<" "<<t<<",";
				T++;
			}
			if(min==INT_MAX)
			cout<<")=oo;"<<endl;
			else cout<<")="<<min<<";";
			Dnew[i] = min;
			if(Dnew[i]==Dold[i]) cout<<"\t -стабилизация.";
			cout<<endl;
			
		}
		
			cout<<endl;
		for(int i=0; i < N;i++)
			{
				if(Dnew[i]==INT_MAX)
				cout<<"oo"<<", ";
				else cout<<Dnew[i]<<", ";
			}
			cout<<endl;
			
			cout<<endl;
		step++;
	}
	cout<<endl;
	for(int i = 0; i < N; i++)
	{
		cout<<"D("<<i<<")="<<Dnew[i]<<", ";
	}
	cout<<"\n"<<T;
	return 0;
	
}
