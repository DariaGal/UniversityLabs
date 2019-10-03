#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>

int const n=15;
int A[n];
struct vertex
	{
		int data;
		int Bal;
		vertex *left;
		vertex *right;
	};
	vertex *q;
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
	q->Bal=0; p->Bal=0;
	p->left=q->right;
	q->right=p;
	p=q;
}
void RR(vertex *&p)	
{
	vertex *q;
	q=p->right;
	q->Bal=0; p->Bal=0;
	p->right=q->left;
	q->left=p;
	p=q;
}
 void LL1(vertex *&p,bool U)	
{ 	vertex *q;
	q=p->left;
	if (q->Bal==0) {q->Bal=1;  p->Bal=-1; U=false;}
	else {q->Bal=0; p->Bal=0;}
	p->left=q->right;
	q->right=p;
	p=q;
}
void RR1(vertex *&p,bool U)	
{  
	vertex *q;
	q=p->right;
	if (q->Bal==0) {q->Bal=1;  p->Bal=-1; U=false;}
	else {q->Bal=0; p->Bal=0;}
	p->right=q->left;
	q->left=p;
	p=q;
}
void LR(vertex *&p)	
{ 
	vertex *q,*r;
	q=p->left;
	r=q->right;
	if(r->Bal<0) p->Bal=1;
		else p->Bal=0;
	if(r->Bal>0) q->Bal=-1;
		else q->Bal=0;
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
	if(r->Bal>0) p->Bal=-1;
		else p->Bal=0;
	if(r->Bal<0) q->Bal=1;
		else q->Bal=0;
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
						if(p->Bal>0){p->Bal=0;Rost=false;}
							else
							{ 
								if(p->Bal==0){p->Bal=-1;Rost=true;}
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
									if(p->Bal==0){p->Bal=1;Rost=true;}
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
void BL(vertex *&p,bool U)
{  
	if(p->Bal==-1) { p->Bal=0;}
		else{ 
			if(p->Bal==0) 	
				{	
					p->Bal=1; 
					U=false;
				}
				else { if(p->Bal==1)
						{ 
						if(p->right!=NULL){
							if (p->right->Bal>=0) RR1(p,U);
								else RL(p);}
						}
					}
			}
			
}
void BR(vertex *&p,bool U){
	if(p->Bal==1) p->Bal=0;
		else{ if(p->Bal==0) {p->Bal=-1; U=false;}
				else { if(p->Bal==-1)
						{ 
						if(p->left!=NULL){
							if (p->left->Bal<=0) LL1(p,U);
								else LR(p);}
						}
					}
			}
}
void del(vertex *&r, bool U)
{ 
	if(r->right!=NULL)
	{
		del(r->right,U); 
		if (U==true) BR(r,U);
	}
	else 
	{
		q->data=r->data;
		q=r;
		r=r->left;
		U=true;
	}
				
}
void Delete(int x,vertex *&p,bool U)
{
	
	if(p==NULL){printf("не найдено \n"); return;}
		else {
			if(x<p->data) 
			{
				Delete(x,p->left,U);
				if(U==true) BL(p,U); 
			}
			else{
				if(x>p->data) 
					{
					Delete(x,p->right,U);
					if(U==true) { BR(p,U);}
					}
					else{ 
						q=p; 
						if(q->left==NULL)
						{  
							p=q->right; 
							U=true;
						}
						else{ 
							if(q->right==NULL)
							{ 
								p=q->left;
								U=true;
							}
							else { 
								del(q->left,U);
								if(U==true) {BL(p,U);}
							}
						}free(q);
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
main()
{
	int i,x;
	srand(time(NULL));
	bool U;
	vertex *root=NULL;
	Mass();
	for(i=0;i<n;i++)
 	{
 		printf("%d ",A[i]);
 	}
 	printf("\n ");
	for(i=0;i<n;i++)
 	{
 		AVL(A[i],root);
 	}
 	printf("\n ");
 	obhod(root);
 	printf("\n ");
 	for(i=0;i<9;i++)
	 {
    	printf("\nВершина: ");
 		scanf("%d",&x);
 		Delete(x,root,U);
 		obhod(root);
 		printf("\n ");
 	}
 	system("pause");
 	return 0;
 }
