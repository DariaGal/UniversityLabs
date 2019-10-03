#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <math.h>
const int n=1000;
void BSearch1(int A[], int n, int X, int *T,int *L1, int *R1)
{
     int i,C=0,t,h;
     long m,L=0,R=n;
     bool Found=false;
     *L1=0; *R1=-1;
     while(L<=R)
     {
           m=(L+R)/2; 
           C++;
           if(A[m]==X) {Found=true; t=m; h=m; C++;
           while(A[t]==X){C++;*L1=t; t--;}
           C++;
           while(A[h]==X){C++;*R1=h; h++;}}
           C++;
           if(A[m]<X) L=m+1;
           else R=m-1;
      }
      
      *T=C;
}      
void BSearch2(int A[], int n, int X, int *iT, int *L1, int *R1)
{
     int i,C=0,h;
     long m,L=0,R=n;
     bool Found=false;
     while(L<R)
     {
           m=(L+R)/2;
           C++;
           if(A[m]<X) L=m+1;
           else R=m;
      }
      C++;
      if(A[R]==X) {Found=true; h=m; *L1=m+1;C++; while(A[h]==X){C++;*R1=h; h++;}}
      else Found=false;
      *iT=C;
 }
void FillRand(int A[],int n)
      {
            int i;  
            for(i=0; i<n; i++) 
            A[i]=rand()%100;
      }
void PrintMas(int A[],int n)
      { 
        int i;
        for(int i=0; i<n; i++) 
        printf("%d ",A[i] );
        puts("\n");
       }
void ShellSort(int A[],int n)
{   int m, h[m],k;
	int t,i=0,j;
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
			t=A[i]; j=i-k;
			while(j>=0&&t<A[j])
			{
			 	A[j+k]=A[j];
			 	j=j-k;
			}
			A[j+k]=t; 	
		}
    }
    	
}
main()
{
      int A[n],X,r,T,iT,F,iF,L1,R1,x,y,k;
      bool Found;
      FillRand(A,n);
      ShellSort(A,n);
      PrintMas(A,n);
      printf("enter key: ");
      scanf("%d",&X);
      puts("\nBSearch1:\n");
      BSearch1(A,n,X,&T,&L1,&R1);
      if(R1<0) printf("NOT FOUND\n");
      else printf ("FOUND, from %d to %d elements of massiv\n",L1+1,R1+1);
      puts("\n\nBSearch2:\n");
      BSearch2(A,n,X,&iT,&L1,&R1);
      if(R1<0) printf("NOT FOUND\n");
      else printf ("FOUND, from %d to %d elements of massiv\n",L1+1,R1+1);
      printf("   n \tSearch 1   Search 2\n");
      	for(r=100;r<=1000;r=r+100)
	{
		FillRand(A,r);
		ShellSort(A,r);
	    BSearch1(A,r,X,&T,&L1,&R1);
	    BSearch2(A,r,X,&iT,&L1,&R1);
		printf("%5d %7d %9d",r,T,iT);
		puts("\n");
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
	outtextxy(100,100,"BSearchAll 1");
	for(r=0;r<=1000;r=r+10)
	{   moveto(x,y);
        x=x+10;
        FillRand(A,r);
        ShellSort(A,r);
        BSearch1(A,r,X,&T,&L1,&R1);
        BSearch2(A,r,X,&iT,&L1,&R1);
        y=550-(T*10);
        lineto(x,y);
        
    }
    	x=50;y=550;
    	setcolor(RED);
    	outtextxy(100,150,"BSearchAll 2");
    	for(r=0;r<=1000;r=r+10)
	{   moveto(x,y);
        x=x+10;
        FillRand(A,r);
        ShellSort(A,r);
        BSearch2(A,r,X,&iT,&L1,&R1);
        y=550-(iT*10);
        lineto(x,y);
        
    }
    
      getch();
}


