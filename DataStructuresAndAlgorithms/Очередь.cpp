#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
const int n=100;
struct queue{
	int data;
	struct queue *next;
};
queue *p,*head,*tail,*q;
void QueueInc(){
	int i;
	head=NULL;
	p=new queue;
	p->data=1;
	p->next=NULL;
	head=p;
	tail=p;
	for(i=1;i<n;i++)
	{
		p=new queue;
		p->data=i+1;
		p->next=NULL;
		tail->next=p;
		tail=p;
	}
}
void QueueDec(){
	int i;
	head=NULL;
	p=new queue;
	p->data=n;
	p->next=NULL;
	head=p;
	tail=p;
	for(i=1;i<n;i++)
	{
		p=new queue;
		p->data=n-i;
		p->next=NULL;
		tail->next=p;
		tail=p;
	}
}
void QueueRand(){
	int i;
	head=NULL;
	p=new queue;
	p->data=rand()%n;
	p->next=NULL;
	head=p;
	tail=p;
	for(i=1;i<n;i++)
	{
		p=new queue;
		p->data=rand()%n;
		p->next=NULL;
		tail->next=p;
		tail=p;
	}
}
void PrintQueue(){
	p=head;
	while(p!=NULL){
		printf("%d ",p->data);
		p=p->next;
}
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

main(){
	srand(time(0));
	puts("Возрастающий:");
	QueueInc();
	PrintQueue();
	puts("\nУбывающий:");
	QueueDec();
	PrintQueue();
	puts("\nСлучайные числа:");
	QueueRand(); 	
	PrintQueue();
	Clear();
	PrintQueue();
	getch();
}
