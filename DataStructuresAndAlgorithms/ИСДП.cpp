#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>
const int n=100;
int  A[n];
struct vertex
	{
		int data;
		vertex *left;
		vertex *right;
	};
	
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
 		A[i]=i+1;
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
 	vertex *root;
 	Mass();
 	int Sz,Sm,H1,H2,l=0,r=n-1;
 	float H;
 	root=ISDP(l,r);
 	obhod(root);
 	Sz=size(root);
 	Sm=sum(root);
 	H1=height(root);
 	H2=SRheight(root,1);
 	H=float(H2)/float(Sz);
 	printf("\n\nразмер= %d\n",Sz);
 	printf("контрольна€ сумма= %d\n",Sm);
 	printf("высота= %d\n",H1);
 	printf("средн€€ высота= %2.1f\n",H);
 }
