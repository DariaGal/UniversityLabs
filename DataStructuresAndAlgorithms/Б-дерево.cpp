#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>
int const n=100;
int A[n];
int VR=1,HR=1;
struct vertex
	{
		int data;
		int Bal;
		vertex *left;
		vertex *right;
	};
	vertex *root=NULL;
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
void DBinsert(int D,vertex *&p)
{
	vertex *q;
	if(p==NULL)
    {
    	p=new vertex;
    	p->data=D;
    	p->left=NULL;
    	p->right=NULL;
    	p->Bal=0;
    	VR=1;
	}
	else
	{
		if(D<p->data)
		{
		 	DBinsert(D,p->left);
			if(VR==1)
			{ 
				if(p->Bal==0)
				{
					q=p->left;
					p->left=q->right;
					q->right=p;
					p=q;
					q->Bal=1;
					VR=0;
					HR=1;
				}
				else
					{
						p->Bal=0; 
						HR=1;
					}
			}
			else
				{
					HR=0;
				}		
		}
		else
		{
			if(D>p->data)	
			{
				DBinsert(D,p->right);
				if(VR==1)
				{
					p->Bal=1;
					VR=0;
					HR=1;
				}
				else
					{
						if(HR==1)
						{
							if(p->Bal>0)
							{
								q=p->right;
								q->Bal=0;
								p->Bal=0;
								p->right=q->left;
								q->left=p;
								p=q;
								VR=1;
								HR=0;
							}
							else
								{
									HR=0;
								}
						}
					}
			}
		}
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
	vertex /**root=NULL,*/*root1=NULL;
	srand(time(NULL));
	Mass();
	for(i=0;i<n;i++)
	{
		printf("%d ",A[i]);
	}
	puts(" ");
	for(i=0;i<n;i++)
	{
		DBinsert(A[i],root);
	}
	for(i=0;i<n;i++)
 	{
 		AVL(A[i],root1);
 	}
 	puts(" ");
	puts(" ");
	obhod(root);
	printf("\n\n| n=100 | Размер | Контр.сумма | Высота | Средн.высота |\n");
	Sz=size(root1);
 	Sm=sum(root1);
 	H1=height(root1);
 	H2=SRheight(root1,1);
 	H=float(H2)/float(Sz);
	printf("|  АВЛ  | %5d  | %9d   | %4d   | %7.2f      |\n",Sz,Sm,H1,H);
	Sz=size(root);
 	Sm=sum(root);
 	H1=height(root);
 	H2=SRheight(root,1);
 	H=float(H2)/float(Sz);
	printf("|  ДБД  | %5d  | %9d   | %4d   | %7.2f      |\n",Sz,Sm,H1,H);
	system("pause");
	return 0;
}
