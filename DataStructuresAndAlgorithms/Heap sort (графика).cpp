#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
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
void ShellSort(int A[],int n, int *T)
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
			t=A[i]; j=i-k; M++; C++;
			while(j>=0&&t<A[j])
			{
                C++;
			 	A[j+k]=A[j]; M++;
			 	j=j-k;
			}
			A[j+k]=t; 	M++;
		}
    }
    *T=C+M;	
}
int main()
 {  int A[n],r,i,T,y,x,k;
 	FillRand(A, n);
 	PrintMas(A,n);
 	HeapSort(A,n,&T);
 	puts("\n");
 	PrintMas(A,n);
 	printf("\n\n\n\n n \tinc\t  dec\t    rand \n" );
 	for(r=100;r<=500;r=r+100)
 	{
 		printf("%4d",r);
 		FillInc(A,r);
 		HeapSort(A,r,&T);
 		printf("%8d",T);
 		FillDec(A,r);
 		HeapSort(A,r,&T);
 		printf("%10d",T);
 		FillRand(A,r);
 		HeapSort(A,r,&T);
 		printf("%10d\n",T);
 	}
 	
 	initwindow(1000,600);
	moveto(50,550);
	lineto(50,50);
	moveto(50,550);
	lineto(950,550);
	moveto(50,550);
	x=50;y=550;k=550;
	for(r=50;r<=1000;r=r+100){moveto(r,555);lineto(r,545); moveto(45,k);lineto(55,k);k=k-100;}
	setcolor(GREEN);
	outtextxy(100,100,"Shell");
	for(r=0;r<=1000;r=r+10)
	{   moveto(x,y);
        x=x+10;
        FillRand(A,r);
        ShellSort(A,r,&T);
        y=550-T*0.01;
        lineto(x,y);
        
    }
    	x=50;y=550;
    	setcolor(RED);
    	outtextxy(100,150,"Heap");
    	for(r=0;r<=1000;r=r+1)
	{   moveto(x,y);
        x=x+1;
        FillRand(A,r);
        HeapSort(A,r,&T);
        y=550-T*0.01;
        lineto(x,y);
        
    }
 system("PAUSE");
 return 0;
 }
