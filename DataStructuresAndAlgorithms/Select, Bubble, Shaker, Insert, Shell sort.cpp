#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
const int n=20;
void FillRand(int A[],int n)
{
  int i;  
   for(i=0; i<n; i++) 
    A[i]=rand()%50;
}
void PrintMas(int A[],int n)
{ 
  int i;
  for(int i=0; i<n; i++) 
   printf("%d ",A[i] );
   puts("\n");
}
void InsertSort(int A[],int n,int *iT)
{   int i, j, t,C=0,M=0;
	for(i=1;i<n;i++)
	{  M++;
		t=A[i]; j=i-1;
		C++;
		while(j>=0&&t<A[j])
		{   C++;
		 	A[j+1]=A[j];
		 	j=j-1;
		 	M++;
		}
		A[j+1]=t; 	
		M++;
	}
	*iT=C+M;
}
void SelectSort(int A[],int n, int *selT)
{ int i,j,k,t,C=0,M=0;	
	for(int i=0;i<(n-1);i++)
	{
    	k=i;
    	for(j=i+1;j<n;j++)
    	{   
			C=C+1;
    		if(A[j]<A[k]) k=j; 
		}
	  /* C=C+1;
		if(A[i]==A[k]) continue; */
		t=A[i];
    	A[i]=A[k];
    	A[k]=t;
    	M=M+3;
	
	}
	*selT=C+M;
} 
void BubbleSort(int A[],int n,int *bT)
{
	int i,j,t;
	int M=0,C=0;
	for(i=0;i<(n-1);i++)
		for(j=n-2;j>=i;j--)
		{   C++;
			if (A[j]>A[j+1]) {
				t=A[j];
				A[j]=A[j+1];
				A[j+1]=t;
				M=M+3;
			}
		}
		*bT=M+C; 
}
void ShakerSort(int A[],int n, int *shT)
{
	int j,t,L=0,R=(n-1),k=(n-1);
	int M=0,C=0,T;
	do{
		for(j=R;j>L;j--){
			C++;
			if(A[j]<A[j-1]) {
			
			t=A[j];
			A[j]=A[j-1];
			A[j-1]=t;
			k=j;
			M=M+3;}
		}
		L=k;
		for(j=L;j<R;j++)
		{   C++;
			if(A[j]>A[j+1]) {
			t=A[j];
			A[j]=A[j+1];
			A[j+1]=t;
			k=j;
			M=M+3;
			}
		}
		R=k;
	} while(L<R);
	*shT=M+C; 
} 
void ShellSort(int A[],int n, int *shelT)
{   int m, h[m],k;
	int t,i=0,j,C=0,M=0;
	m=(log2(n))-1;
	h[0]=1; 	
    for(i=1;i<=m;i++) 
	{
		h[i]=2*h[i-1]+1;
	} 	
	for(k;m>=0;m--)
	{
	k=h[m];
		for(i=k;i<n;i++)
		{
			M++;
			t=A[i]; j=i-k;
			C++;
			while(j>=0&&t<A[j])
			{
				C++;
			 	A[j+k]=A[j];
			 	j=j-k;
			 	M++;
			}
			A[j+k]=t; 	
			M++;
		}
    }
    	*shelT=M+C; 
}
main()
{
	int A[n],iT,selT,bT,shT,shelT,r,B[r];
	srand(time(0));
	FillRand(A,n);
	PrintMas(A,n);
	InsertSort(A,n,&iT); printf("\n InsertSort\n");
	PrintMas(A,n); puts("\n");
	FillRand(A,n);
	PrintMas(A,n);
	ShellSort(A,n,&shelT); printf("\n ShellSort\n");
	PrintMas(A,n); puts("\n");
	printf("   n \tSelect\t Bubble\t Shaker\t Insert\t Shell\n");
	for(r=100;r<=1000;r=r+100)
	{
		FillRand(B,r);InsertSort(B,r,&iT);
		FillRand(B,r);ShakerSort(B,r,&shT);
		FillRand(B,r);BubbleSort(B,r,&bT);
		FillRand(B,r);SelectSort(B,r,&selT);
		FillRand(B,r);ShellSort(B,r,&shelT);
		printf("%5d %7d %7d %7d %7d %7d",r,selT,bT,shT,iT,shelT);
		puts("\n");
	}
	
	
	system("PAUSE");
 	return 0;
	
}

