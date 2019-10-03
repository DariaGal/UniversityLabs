#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>
const int n=100;
int  A[n],B[n];
struct vertex
	{
		int data;
		vertex *left;
		vertex *right;
	};
vertex *root1=NULL;
void SDPrec(int A,vertex *&p)
{
	
	if(p==NULL)
	{
		p=new vertex;
		p->data=A;
		p->left=NULL;
		p->right=NULL;
	}
	else if(A<p->data)  SDPrec(A,p->left);
		else if(A>p->data)  SDPrec(A,p->right);
			else return;
	return;
}
void SDP(int A)
{
	vertex **p;
	p=&root1;
	while(*p!=NULL)
	{
		if(A<(*p)->data) p=&((*p)->left);
		else  if(A>(*p)->data) p=&((*p)->right);
					else return;
	}
	if(*p==NULL)
	{
		(*p)=new vertex;
		(*p)->data=A;
		(*p)->left=NULL;
		(*p)->right=NULL;
	}
	return;	
}
void QuickSort(int n, int L, int R)
{
	int x,i,j,t;
      i=L; j=R;/* x=A[(L+R)/2];*/ x=A[L];
	while(i<=j){
		while(A[i]<x)i++;
		while(A[j]>x)j--; 
		if(i<=j) 
		{
			t=A[i]; 
			A[i]=A[j];
			A[j]=t;
			i++; j--;
		}
		}
		if(L<j) QuickSort(n,L,j);
		if(i<R) QuickSort(n,i,R);
		
		
}

vertex *ISDP(int l, int r)
 {
 	vertex *p;
 	int m;  
 	if(l>r) return NULL;
 	else
 	{
 		m=(l+r)/2;
 		p=new vertex;
 		p->data=A[m];
 		p->left=ISDP(l,m-1);
 		p->right=ISDP(m+1,r);
 		return p;
 	}
 }
 
void Mass()
 {
 	int i;
 	for(i=0;i<n;i++)
 	{
 		A[i]=rand()%RAND_MAX;
 	}
 }     
 
void obhod(vertex *p)
{
	if(p!=NULL)
	{
		obhod(p->left);
		printf("%d ",p->data);
		obhod(p->right);
	}
}
							  
int size(vertex *p)
{

	if (p==NULL) return 0;
	else 
	{
		return(1+size(p->left)+size(p->right));
	}
	
}

int sum(vertex *p)
{
	if(p==NULL) return 0;
	else
	{
		return(p->data+sum(p->left)+sum(p->right));
	}
}
               
int height(vertex *p)             
{
	if(p==NULL) return 0;
	else
	{
		if(1+height(p->left)>1+height(p->right))
		return(1+height(p->left));
		else return(1+height(p->right));
	}
}

int SRheight(vertex *p,int L)
{
	if(p==NULL) return 0;
	else return(L+SRheight(p->left,L+1)+SRheight(p->right,L+1));
}
               
  main()             
 {                
 	int i;  
 	vertex *root,*root2=NULL;
 	vertex **p;
 	Mass();
 	int Sz,Sm,H1,H2,H,l=0,r=n-1;
 	for(i=0;i<n;i++)
 	{
 		SDP(A[i]);
 	}
 	obhod(root1);
 	puts(" ");
 	for(i=0;i<n;i++)
 	{
 		SDPrec(A[i],root2);
 	}
 /*	obhod(root2);*/
 	puts(" ");
 	QuickSort(n,0,n-1);
 	root=ISDP(l,r);
 	obhod(root);
 	printf("\n| n=100 | Размер | Контр.сумма | Высота | Средн.высота |\n");
 	Sz=size(root);
 	Sm=sum(root);
 	H1=height(root);
 	H2=SRheight(root,1);
 	H=H2/Sz;
 	printf("|  ИСДП | %5d  | %9d   | %4d   |%7d       |",Sz,Sm,H1,H);
 	Sz=size(root2);
 	Sm=sum(root2);
 	H1=height(root2);
 	H2=SRheight(root2,1);
 	H=H2/Sz;
 	printf("\n|  СДП  | %5d  | %9d   | %4d   |%7d       |",Sz,Sm,H1,H);
 
 }
