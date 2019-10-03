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
int T1=0,T2=0;
struct vertex
{
	int v1;
	int v2;
	int r;
	 bool operator< (const vertex& a) const{
	 	if(r < a.r)
          return true ;
        if(r == a.r && v1<a.v1)
        return true;
        return false;
        }
};
int main()
{
	
	setlocale( LC_ALL,"Russian" );
	int graf[N][N] = {   {0,2,4,9,1,3,7},
						 {4,0,9,7,6,INT_MAX,8},
						 {6,7,0,2,5,1,3},
						 {8,INT_MAX,1,0,2,4,9},
						 {1,6,INT_MAX,3,0,1,4},
						 {10,2,7,8,6,0,3},
						 {INT_MAX,5,3,6,8,1,0}};
	int cor[N];
	int weight = 0;
	for(int i = 0; i<N;i++)	
		cor[i] = i;
	int s = 1;		
	vector<vertex> v;
	vector<vertex> newgraf;
	for(int i = 0; i<N;i++)
	{
		for(int j = s; j<N;j++){
			vertex t;
			t.v1 = i;
			t.v2 = j;
			t.r = graf[i][j];
			v.push_back(t);
	}
		s++;
	}
	std::sort(v.begin(),v.end()); 
	for(int i = 0; i<v.size();i++)
	{
		cout<<"("<<v[i].v1<<","<<v[i].v2<<")="<<v[i].r<<", ";
	}
	cout<<"\n\n";
		for(int n = 0; n<N;n++)	
			{
				cout<<" "<<n<<" ";
			}
			cout<<endl;
	for(int n = 0; n<N;n++)	
			{
				cout<<" "<<cor[n]<<" ";
			}
			cout<<endl;
	for(int i = 0; i<v.size();i++)
	{
		int c1 = v[i].v1, c2 = v[i].v2;
		cout<<"вершины: "<<c1<<","<<c2<<endl;
		if(cor[c1] != cor[c2])
		{
			T1++;
			cout<<"Результативный этап. \n";
			int change = cor[c2];
			for(int k = 0; k<N;k++)
			{
				if(cor[k]==change)
				{
					cor[k] = cor[c1];				
				}
			}
			newgraf.push_back(v[i]);
			weight+=v[i].r;
			for(int n = 0; n<N;n++)	
			{
				cout<<" "<<n<<" ";
			}
			cout<<endl;
			for(int n = 0; n<N;n++)	
			{
				cout<<" "<<cor[n]<<" ";
			}
			cout<<endl;
		}else {
			cout<<"Нерезультативный этап. "<<endl;
		T2++;}
		cout<<"____________________\n";
		if(newgraf.size()==(N-1))break;
	}
	cout<<"\n\n";
	for(int i = 0; i<newgraf.size();i++)
	{
		cout<<"("<<newgraf[i].v1<<","<<newgraf[i].v2<<")="<<newgraf[i].r<<", ";
	}
	cout<<"\n"<<"weight="<<weight<<endl;
//	cout<<"Результативные этапы: "<<T1<<"*n = "<<T1*N<<"\nНерезультативные: "<<T2;
	return 0;
	
}
