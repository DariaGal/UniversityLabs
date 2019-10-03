#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>
int const n=100;
int A[n],w[n],Aw[n+1][n+1],Ap[n+1][n+1],Ar[n+1][n+1];
struct vertex
	{
		int data;
		int W;
		bool use;
		vertex *left;
		vertex *right;
	};
vertex *root=NULL;
vertex V[n];
void Mass()
 {
 	int i;
 	for(i=0;i<n;i++)
 	{
 		A[i]=i;
 		w[i]=rand()%10+1;	
 	}
 } 
 void AW()
 {
 	for(int i=0;i<=n;i++)
 		for(int j=i+1;j<=n;j++)
 			Aw[i][j]=Aw[i][j-1]+w[j-1];
 }
 void AP_AR()
 {
 	int j,i,m,min,x,k,h;
 	h=1;
 	for(i=0;i<=(n-1);i++)
 	{
 		j=i+1;
 		Ap[i][j]=Aw[i][j];
 		Ar[i][j]=j;
 	}
 	for(h=2;h<=n;h++)
 	{
 		for(i=0;i<=(n-h);i++)
 		{
 			j=i+h;
 			m=Ar[i][j-1];
 			min=Ap[i][m-1]+Ap[m][j];
 			for(k=m+1;k<=Ar[i+1][j];k++)
 			{
 				x=Ap[i][k-1]+Ap[k][j];
 				if(x<min) {m=k; min=x;}
 			}
 			Ap[i][j]=min+Aw[i][j];
 			Ar[i][j]=m;
 		}
 	}
 }
 void ADD(int A,int B,vertex *&p)
{
	
	if(p==NULL)
	{
		p=new vertex;
		p->data=A;
		p->W=B;
		p->left=NULL;
		p->right=NULL;
	}
	else if(A<p->data)  ADD(A,B,p->left);
		else if(A>p->data)  ADD(A,B,p->right);
			else return;
	return;
}
void CreateTree(int L,int R, vertex *&p)
{
	int k;
	if(L<R)
	{
		k=Ar[L][R];
		ADD(A[k-1],w[k-1],root);
		CreateTree(L,k-1,p);
		CreateTree(k,R,p);
		
	}
}

void A1(vertex *&root1)
{
	int index,max;
	for(int i=0;i<n;i++)
	{
		V[i].use=false;
	}
	for(int i=0;i<n;i++)
	{
		max=0;
		index=0; 
		for(int j=0;j<n;j++)
			if((w[j]>max)&&(V[j].use==false))
			{
				max=w[j];
				index=j;
			}
		V[index].use=true;
		ADD(A[index],w[index],root1);
	}
}
void A2(vertex *&p,int L,int R)
{
	int wes=0; 
	int sum=0;
	int i;
	if(L<=R)
	{
		for(i=L;i<=R;i++)
		{
			wes=wes+w[i];
		}
		for(i=L;i<R;i++)
		{
			if((sum<wes/2)&&(sum+w[i]>=wes/2)) break;
			sum=sum+w[i];
		}
		
		ADD(A[i],w[i],p);
		A2(p,L,i-1);
		A2(p,i+1,R);
	}
}
void obhod(vertex *p)
{
	int i=0;
	if(p!=NULL)
	{
		obhod(p->left);
		printf(" %d",p->data);
	/*	printf("(%d) ",p->W);*/
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
int WA(vertex *p)
{
	if(p==NULL) return 0;
	else
	{
		return(p->W+WA(p->left)+WA(p->right));
	}
}
void height(int x, int u, int &wh, vertex *p)
{	
	if(x==p->data) {wh=(p->W)*u;}
	else
	if(x<p->data){u++; height(x,u,wh,p->left);}
		else if(x>p->data){ u++;height(x,u,wh,p->right); }
}
main()
{
	int i,Sz,Sm,W,u,WH,wh;
	float H;
	vertex *rootA1=NULL,*rootA2=NULL;
	Mass();
	AW();
	AP_AR();
	for(i=0;i<n;i++)
	{
		CreateTree(0,n,root);
	}
	A1(rootA1);
	A2(rootA2,0,n);
	printf("\nДОП:\n");
	obhod(root);
	printf("\nA1:\n");
	obhod(rootA1);
	printf("\nA2:\n");
	obhod(rootA2);
	Sz=size(root);
 	Sm=sum(root);
 	W=WA(root);
 	WH=0;
 	for(i=0;i<n;i++)
	{
		height(A[i],1,wh,root);
		WH=WH+wh;
	}
 	H=float(WH)/float(W);
 	printf("\n\n| n=100 | Размер | Контр.сумма | Средневзвешенная высота |\n");
	printf("|  ДОП  | %5d  | %9d   |     %9.2f           |\n",Sz,Sm,H);
	Sz=size(rootA1);
 	Sm=sum(rootA1);
 	W=WA(rootA1);
 	WH=0;
 	for(i=0;i<n;i++)
	{
		height(A[i],1,wh,rootA1);
		WH=WH+wh;
	}
 	H=float(WH)/float(W);
	printf("|  A1   | %5d  | %9d   |     %9.2f           |\n",Sz,Sm,H);
	Sz=size(rootA2);
 	Sm=sum(rootA2);
 	W=WA(rootA2);
 	WH=0;
 	for(i=0;i<n;i++)
	{
		height(A[i],1,wh,rootA2);
		WH=WH+wh;
	}
 	H=float(WH)/float(W);
	printf("|  A2   | %5d  | %9d   |     %9.2f           |\n",Sz,Sm,H);
}
