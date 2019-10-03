#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>
struct queue{
	char data;
	struct queue *next;
};
const int n=30,m=8;
	char str[n];
		queue *head[m], *tail[m];  
void createstring()
{
	int i;
	for(i=0;i<n;i++)
	str[i]='A' + rand() % (('Z' - 'A') + 1);
	for(i=0;i<n;i++)
	printf("%c",str[i]);
}
void createLists()
{
	char x;
	int i,k;
	queue *p;
	int tr;
	for(i=0;i<m;i++)
		head[i]=NULL;
	for(i=0;i<n;i++)
	{
		tr=(int)(str[i]);
		k=tr%m;
	if(head[k]==NULL)
	{
		p=new queue;
		p->data=str[i];
		p->next=NULL;
		head[k]=p;
		tail[k]=p;
	}
	else
	{	p=head[k];
	while(p->next!=NULL){
		if(p->data==str[i])break;
	p=p->next;
	}
		if(p->data!=str[i]){
		p=new queue;
		p->data=str[i];
		p->next=NULL;
		tail[k]->next=p;
		tail[k]=p;}
	}
	}
	for(i=0;i<m;i++){
	p=head[i]; 
	printf("\nочередь %d\n",i);
	while(p!=NULL){
		printf("%c ",p->data);
		p=p->next;}
	}
}
void Search()
{
	
	char x;
	queue *p;
	int tr,k,i=0;
	printf("\nВведите символ:");
	scanf("%c",&x);
	tr=(int)(x);
	k=tr%m;
	p=head[k];
	while(p!=NULL){
	if (p->data==x) {printf("Найден символ %c в очереди %d",p->data,k);i=1;break;}
	else p=p->next;}
	if(i==0)printf("\nСимвол не найден.");
}
main()
{
	int i;
/*	srand(time(NULL));*/
	createstring();
	createLists();
	Search();
	getch();
}

