#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
const int n=1000;
int BubbleSort(int);
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
}
void BubbleSort(int A[],int n)
{
	int i,j,t,T;
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
		printf(" M=%d,C=%d \n",M,C);
		T=M+C; printf("M+C=%d\n",T);
}
 void ShakerSort(int A[],int n)
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
	printf(" M=%d,C=%d \n",M,C);
	T=M+C; printf("M+C=%d\n",T);
} 
void FillInc(int A[],int n)
{
  int i;  
   for(i=0; i<n; i++) 
     A[i]=i+1; }
void FillDec(int A[],int n)
{
  int i;  
   for(i=0; i<n; i++)
     A[i]=n-i;
}
main()
{   int A[n],i,j; 
    float tM,tCmax,tCmin;
	srand(time(0));
	FillRand(A,n);
	printf("Massiv:\n");
	PrintMas(A,n);
	puts("\n");
	printf("BubbleSort:\n");
	BubbleSort(A,n);
	PrintMas(A,n);
	puts("\n");
	FillRand(A,n);
	printf("Massiv:\n");
	PrintMas(A,n);
	puts("\n");
	printf("ShakerSort:\n");
	ShakerSort(A,n);
	PrintMas(A,n);
	tM=(3*(n*n-n))/2; tCmax=(n*n-n)/2; tCmin=(n-1);
	printf("\n\nTeoreticheskie: Mmin=0, Mmax=%2.0f, Cmin=%2.0f, Cmax=%2.0f\n\n",tM,tCmin,tCmax);
	printf("Bubble sort:\n");
	printf("ubivaush: ");
	FillDec(A,n);
	BubbleSort(A,n);
	printf("vozrastaush: ");
	FillInc(A,n);
	BubbleSort(A,n);
	printf("\nShakerSort:\n");
	printf("ubivaush: ");
	FillDec(A,n); ShakerSort(A,n);
	printf("vozrastaush: ");
	FillInc(A,n); ShakerSort(A,n);
	
	system("PAUSE");
 	return 0;
	
}
