#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
int FillInc(int);
int random (int N) { return rand()%N; }
const int n=1000;
void FillInc(int A[],int n)
{
  int i;  
   for(i=0; i<n; i++) 
     A[i]=i+1;
}
void FillDec(int A[],int n)
{
  int i;  
   for(i=0; i<n; i++)
     A[i]=n-i;
}
void FillRand(int A[],int n)
{
  int i;  
   for(i=0; i<n; i++) 
    A[i]=rand()%n;
}
void PrintMas(int A[],int n)
{ 
  int i;
  for(i=0; i<n; i++) 
   printf("%d ",A[i] );
}
void HeapSort(int A[],int n, int *T)
{
	int L,i,t,j,R,x,M=0,C=0;
	L=n/2; R=n;
	while(L>0)
	{
		x=A[L];i=L; M++;
		while(1)
		{
		j=2*i;
		if(j>n)break;
		C++;
		if((j<n)&&(A[j+1]<=A[j])) j=j+1;
		C++;
		if (x<=A[j])break;
		A[i]=A[j]; M++;
		i=j;
		}
		A[i]=x;M++;
		L=L-1;
	}
    R=n;
	while(R>1)
	{
		t=A[0]; M++;
		A[0]=A[R]; M++;
		A[R]=t; M++;
		R=R-1;
		x=A[0]; i=0; M++;
		while(1)
		{
		j=2*i;
		if(j>R)break;
		C++;
		if((j<R)&&(A[j+1]<=A[j])) j=j+1;
		C++;
		if (x<=A[j])break;
		A[i]=A[j]; M++;
		i=j;
		}
		A[i]=x; M++;
		
	}
	*T=C+M;
	
}
void QuickSort(int A[],int n, int L, int R, int &C, int &M)
{
	int x,i,j,t;
     M++; i=L; j=R;/* x=A[(L+R)/2];*/ x=A[L];
	while(i<=j){
		while(A[i]<x){i++; C++;}
		while(A[j]>x){j--; C++;}
		if(i<=j) 
		{
			t=A[i]; 
			A[i]=A[j];
			A[j]=t; M=M+3;
			i++; j--;
		}
		}
		if(L<j) QuickSort(A,n,L,j,C,M);
		if(i<R) QuickSort(A,n,i,R,C,M);
		
		
}
int main()
 {  int A[n],r,i,IT,DT,RT,C=0,M=0;
 	FillRand(A, n);
 	PrintMas(A,n);
 	QuickSort(A,n,0,n,C,M);
 	puts("\n");
 	PrintMas(A,n);
 	
 	
 	
 	
 	
 	
 	
 /*	HeapSort(A,n,&T);
 	puts("\n");
 	PrintMas(A,n);*/
 	printf("\n\n\n\n n \tinc\t  dec\t    rand \n" );
 	for(r=100;r<=700;r=r+100)
 	{
 		M=0;C=0;
 		printf("%4d",r);
 		FillInc(A,r);
 		QuickSort(A,r,0,r,C,M);
 		IT=C+M;
 		M=0;C=0;
 		printf("%8d",IT);
 		FillDec(A,r);
 		QuickSort(A,r,0,r,C,M);
 		DT=C+M;
 		M=0;C=0;
 		printf("%10d",DT);
 		FillRand(A,r);
 		QuickSort(A,r,0,r,C,M);
 		RT=C+M;
 		M=0;C=0;
 		printf("%10d\n",RT);
 	}
 system("PAUSE");
 return 0;
 }
