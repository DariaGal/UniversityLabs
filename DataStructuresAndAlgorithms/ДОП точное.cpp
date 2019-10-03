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
		vertex *left;
		vertex *right;
	};
vertex *root=NULL;
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
	Mass();
	AW();
	AP_AR();
	for(i=0;i<n;i++)
	{
		CreateTree(0,n,root);
	}
	obhod(root);
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
 /*	H=float(Ap[0][n])/float(Aw[0][n]);
 	printf("\n%2.2f",H);*/
 	printf("\n\n| n=100 | Размер | Контр.сумма | Средневзвешенная высота |\n");
	printf("|  ДОП  | %5d  | %9d   |     %9.2f           |\n",Sz,Sm,H);
	
/*	for(int i=0;i<=n;i++){
 		for(int j=0;j<=n;j++)
 		printf("%2d ",Aw[i][j]);
		printf("\n"); }
		printf("\n");
	for(int i=0;i<=n;i++){
 		for(int j=0;j<=n;j++)
 		printf("%2d ",Ap[i][j]);
		printf("\n"); }
		printf("\n");
	for(int i=0;i<=n;i++){
 		for(int j=0;j<=n;j++)
 		printf("%2d ",Ar[i][j]);
		printf("\n"); }*/
}

