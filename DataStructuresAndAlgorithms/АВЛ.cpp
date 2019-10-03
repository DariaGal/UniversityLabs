#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>
int const n=100;
int A[n];
struct vertex
	{
		int data;
		int Bal;
		vertex *left;
		vertex *right;
	};
void Mass()
 {
 	int i;
 	for(i=0;i<n;i++)
 	{
 		A[i]=rand()%100;
 	}
 }     
void LL(vertex *&p)	
{
	vertex *q;
	q=p->left;
	p->Bal=0;
	q->Bal=0;
	p->left=q->right;
	q->right=p;
	p=q;
}
void RR(vertex *&p)	
{
	vertex *q;
	q=p->right;
	q->Bal=0;
	p->Bal=0;
	p->right=q->left;
	q->left=p;
	p=q;
}
void LR(vertex *&p)	
{
	vertex *q,*r;
	q=p->left;
	r=q->right;
	if(r->Bal<0) {p->Bal=1;}
		else {p->Bal=0;}
	if(r->Bal>0) {q->Bal=-1;}
		else {q->Bal=0;}
	r->Bal=0;
	p->left=r->right;
	q->right=r->left;
	r->left=q;
	r->right=p;
	p=r;
}
void RL(vertex *&p)	
{
	vertex *q,*r;
	q=p->right;
	r=q->left;
	if(r->Bal>0){ p->Bal=-1;}
		else{p->Bal=0;}
	if(r->Bal<0) {q->Bal=1;}
		else {q->Bal=0;}
	r->Bal=0;
	p->right=r->left;
	q->left=r->right;
	r->right=q;
	r->left=p;
	p=r;
}
void AVL(int D,vertex *&p)
{
	bool Rost;
	if(p==NULL){ p=new vertex;
				p->data=D;
				p->left=NULL;
				p->right=NULL;
				p->Bal=0;
				printf("%d ",p->data);
				Rost=true;}
			else 
			{
				if(p->data>D) { AVL(D,p->left);
					if(Rost==true)
					{
						if(p->Bal>0){p->Bal=0;}
							else
							{ 
								if(p->Bal==0){p->Bal=-1;}
									else 
									{
										if((p->left->Bal)<=0){ LL(p); Rost=false;}
											else{ LR(p); Rost=false;}
									}
					    	}
					}
				}
				else
				{
					if(p->data<D) { AVL(D,p->right);
						if(Rost==true)
						{
							if(p->Bal<0){p->Bal=0; Rost=false;}
								else
								{
									if(p->Bal==0){p->Bal=1;}
										else
										{
											if(p->right->Bal>=0) {RR(p); Rost=false;}
												else{ RL(p); Rost=false;}
										}
								}
						}
					}
					else return;
				}
			}
			
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
 
void obhod(vertex *p)
{
	int i=0;
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
	int i,Sz,Sm,H1,H2;
	float H;
	vertex *root2,*root1=NULL;
	srand(time(NULL));
	vertex *root=NULL;
	Mass();
	for(i=0;i<n;i++)
 	{
 		AVL(A[i],root);
 	}
 	obhod(root);
 	puts(" ");
 	for(i=0;i<n;i++)
 	{
 		SDPrec(A[i],root1);
 	}
 	QuickSort(n,0,n-1);
 	root2=ISDP(0,n-1);
 	printf("\n\n| n=100 | Размер | Контр.сумма | Высота | Средн.высота |\n");
 	Sz=size(root2);
 	Sm=sum(root2);
 	H1=height(root2);
 	H2=SRheight(root2,1);
 	H=float(H2)/float(Sz);
 	printf("|  ИСДП | %5d  | %9d   | %4d   | %7.2f      |\n",Sz,Sm,H1,H);
 	Sz=size(root1);
 	Sm=sum(root1);
 	H1=height(root1);
 	H2=SRheight(root1,1);
 	H=float(H2)/float(Sz);
 	printf("|  СДП  | %5d  | %9d   | %4d   | %7.2f      |\n",Sz,Sm,H1,H);
 	Sz=size(root);
 	Sm=sum(root);
 	H1=height(root);
 	H2=SRheight(root,1);
 	H=float(H2)/float(Sz);
 	printf("|  АВЛ  | %5d  | %9d   | %4d   | %7.2f      |\n",Sz,Sm,H1,H);
	system("pause");
 	return 0;
}
