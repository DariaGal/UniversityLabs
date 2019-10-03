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

void Mass()
 {
 	int i;
 	for(i=0;i<n;i++)
 	{
 		A[i]=rand()%20;
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

void deleteVertex(int D)
{
	vertex **p,*q,*s,*r;
	p=&root1;
	while(*p!=NULL)
	{
		if(D<(*p)->data) p=&((*p)->left);
		else  if(D>(*p)->data) p=&((*p)->right);
					else break;
	}
	if(*p!=NULL)
	{
		q=*p;
		if(q->left==NULL) { *p=q->right; }
		 	 else
			  {  if(q->right==NULL) {*p=q->left;}
		 				else 
						 { r=q->left; s=q;
		 					if(r->right==NULL)
		 						{
		 							r->right=q->right;
		 							*p=r;
		 						}
		 					else 
							 {
		 							while(r->right!=NULL)
		 							{
		 								s=r;
		 								r=r->right;
		 							}
		 						s->right=r->right;
		 						r->left=q->left;
		 						r->right=q->right;
		 						*p=r;
		 	  				}
						}
			 } 
		free(q);	
	}
}
               
  main()             
 {                
 	int i,D;  
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
 	puts(" ");puts(" ");
 	i=0;
 	while(i!=9){
 	printf("Вершина:");
 	scanf("%d",&D);
 	deleteVertex(D);
 	obhod(root1);
 	puts(" ");
	i++;}
 /*	printf("\n| n=100 | Размер | Контр.сумма | Высота | Средн.высота |");
 	Sz=size(root2);
 	Sm=sum(root2);
 	H1=height(root2);
 	H2=SRheight(root2,1);
 	H=H2/Sz;
 	printf("\n|  СДП  | %5d  | %9d   | %4d   |%7d       |",Sz,Sm,H1,H);*/
 
 }
