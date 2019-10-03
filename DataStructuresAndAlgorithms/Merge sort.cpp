#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
int N=100;
struct list{
	int data;
	struct list *next;
};
list *f,*head,*q;
struct queue{
	list *head;
	list *tail;
};
void ListInc(){
	head=NULL;
	int i;
	for(i=0;i<N;i++)
	{
		f=new list;
		f->data=N-i;
		f->next=head;
		head=f;
	}
	
}
void ListDec() {
	head=NULL;
	int i;
	for(i=0;i<N;i++)
	{
		f=new list;
		f->data=i+1;
		f->next=head;
		head=f;
	}
} 
void ListRand(){
	head=NULL;
	int i;
	for(i=0;i<N;i++)
	{
		f=new list;
		f->data=rand()%N;
		f->next=head;
		head=f;
	}
	
}
void PrintList(){
	f=head;
	while(f!=NULL){
		printf("%d ",f->data);
		f=f->next;
	}
}
void RunNumber(){
int h=1,i;
f=head;
for(i=0;i<(N-1);i++)
{
	if((f->data)>(f->next->data)) h++;
	f=f->next;
}
 printf("\nКол-во серий=%d\n",h);
}
int Divide(list* &S, list* &a, list* &b,int &n, int &M, int &C)
{
	list *k,*p;
	a=S;
	M++;
	b=S->next;
	n=1;
	k=a; p=b;
	M=+2;
	while(p!=NULL)
	{
		n=n+1;
		k->next=p->next;
		k=p;
		p=p->next;
	}
}
void Merging(list* &a,list* &b,queue &c,int q,int r,  int &M, int &C)
{
	list *p;
	while((q!=0)&&(r!=0))
	{
		C++;
		if(a->data<=b->data)
		{
			M++;
			p=a;
			a=a->next;
			p->next=NULL;
			if(c.head!=NULL) c.tail->next=p;
			else c.head=p;
			c.tail=p;
			q--;
		}
		else
		{
			M++;
			p=b;
			b=b->next;
			p->next=NULL;
			if(c.head!=NULL) c.tail->next=p;
			else c.head=p;
			c.tail=p;
			r--;
		}
	}
	while(q>0)
	{
		M++;
		p=a;
		a=a->next;
		p->next=NULL;
		if(c.head!=NULL) c.tail->next=p;
		else c.head=p;
		c.tail=p;
		q--;
	}
	while(r>0)
	{
		M++;
		p=b;
		b=b->next;
		p->next=NULL;
		if(c.head!=NULL) c.tail->next=p;
		else c.head=p;
		c.tail=p;
		r--;
	}
}
void MergeSort(list* &S,  int &M, int &C)
{
	int n,p,q,r,m,i;
	struct queue Cc[2];
	struct list *a,*b;
	Divide(S,a,b,n,M,C);
	p=1;
	while(p<n)
	{
		Cc[0].head=NULL;
		Cc[1].head=NULL;
		Cc[0].tail=NULL;
		Cc[1].tail=NULL;
		i=0; m=n;
		while(m>0)
		{
			if(m>=p)q=p;
			else q=m;
			m=m-q;
			if(m>=p) r=p;
			else r=m;
			m=m-r; 
			Merging(a,b,Cc[i],q,r,M,C);
			i=1-i;
		}
		a=Cc[0].head;
		b=Cc[1].head;
		p=2*p;
	}
	Cc[0].tail->next=NULL;
	S=Cc[0].head;
}
main()
{
	int M,C,IT,DT,RT;
	srand(time(0));
	ListRand();
	PrintList();
	RunNumber();
	MergeSort(head,M,C);
	puts("\n");
	PrintList();
	RunNumber();
		printf("\n\n\n\n n \tinc\t  dec\t    rand \n" );
 	for(N=100;N<=500;N=N+100)
 	{
 		M=0;C=0;
 		printf("%4d",N);
 		ListInc();
 		MergeSort(head,M,C);
 		IT=C+M;
 		M=0;C=0;
 		printf("%8d",IT);
 		ListDec();
 		MergeSort(head,M,C);
 		DT=C+M;
 		M=0;C=0;
 		printf("%10d",DT);
 		ListRand();
 		MergeSort(head,M,C);
 		RT=C+M;
 		M=0;C=0;
 		printf("%10d\n",RT);
 	}
}
