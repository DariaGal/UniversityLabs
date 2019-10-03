#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
const int n=100;
int	p_to_s[256];
int	s_to_p[256];
struct list{
	int data;
	struct list *next;
};
list *p,*head,*q;
void ListInc(){
	head=NULL;
	int i;
	for(i=0;i<n;i++)
	{
		p=new list;
		p->data=n-i;
		p->next=head;
		head=p;
	}
	
}

void ListDec() {
	head=NULL;
	int i;
	for(i=0;i<n;i++)
	{
		p=new list;
		p->data=i+1;
		p->next=head;
		head=p;
	}
} 
void ListRand(){
	head=NULL;
	int i;
	for(i=0;i<n;i++)
	{
		p=new list;
		p->data=rand()%n;
		p->next=head;
		head=p;
	}
	
}
void PrintList(){
	p=head;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
	}
}
void CheckSum(int *Sum)
{
	*Sum=0;
	p=head;
	while(p!=NULL){
		*Sum=*Sum+(p->data);
		p=p->next;
	}
}
void RunNumber(){
int h=1,i;
p=head;
for(i=0;i<(n-1);i++)
{
	if((p->data)>(p->next->data)) h++;
	p=p->next;
}
 printf("\nКол-во серий=%d\n",h);
}
void Clear(){
	q=p=head;
	while(p!=NULL){
	p=q->next;
	delete q;
	q=p;
	}
	head=NULL;
}
main()
{
	int Sum;
	srand(time(0));
	puts("Возрастающий:");
	ListInc();
	PrintList();
	CheckSum(&Sum);
	printf("\nCheckSum=%d",Sum);
	RunNumber();
	puts("\nУбывающий:");
	ListDec();
	PrintList();
	CheckSum(&Sum);
	printf("\nCheckSum=%d",Sum);
	RunNumber();
	puts("\nСлучайные числа:");
	ListRand();
	PrintList();
	CheckSum(&Sum);
	printf("\nCheckSum=%d",Sum);
	RunNumber();
	getch();
};

