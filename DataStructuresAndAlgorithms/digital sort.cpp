#include <stdio.h>
 #include <conio.h>
#include <time.h>
#include <locale>
#include <graphics.h>
#include <math.h>
#include <stdlib.h>
int M=0,C=0;
struct list
{   
	struct list *next;
	union { 
   int data;// ��� 4 ����
   //short int data // ��� 2 ����
	unsigned char Digit[4];
             };

};
  
void digitalsort(struct list *&S,int n)
{
	int j=0;
	struct list *p;
	struct list *head[256], *tail[256];    
	while(j<4)// ��� 4 ����
	//while(j<2)// ��� 2 ����
    {
	
    for (int i=0; i<=255; i++) 
    tail[i]=(struct list*)&head[i];// ������������� �������

	p=S;
	int d;
	while (p!=NULL)
    {  
        //d- ����� �������
        //j- ����� �����
        d=p->Digit[j];
        tail[d]->next=p;//�������� ������� � �������
        tail[d]=p;//
        p=p->next;
    }


	 p=(struct list*)&S;
    //for (int i=255; i>=0; i--)// ��� ��������� ������ ������ �� �������� � ��������
    for (int i=0; i<=155; i++)// ��� �������  ������ �� �������� � ��������
    //���� ����� ��� ������� �������� ��� ���������� ��������� ������� ������ ������ ������� ������������� ������ 2 � �.�.
    {
        if (tail[i]!=(struct list*)&head[i])
        {
            p->next=head[i];//��� ���������� ���������� ���
            p=tail[i];
        }
    }
     
    p->next=NULL;
    j=j+1;//��������� �� ��������� ����
	}
// KDI � �� ��������� ����� �������� �� ������ ������!
//������� ��� union � �� ��� ��� �������� ������ � ��� �� ������ �� �� ������� ��� ��� �������� ������ �������!
//����� ������ ��� ������ � ��� �� �� �� ��������! 
}

    


void FillIncQueue(struct list *&head,int n)
{struct list *pp,*tail;
 head=(struct list*)malloc(sizeof(struct list));
        
       head->data=1;
	   tail=head;    
   
	    for( int i=2;i<=n;i++)
     {
      pp=(struct list*)malloc(sizeof(struct list));
      pp->data=i;
      tail->next =pp;
      tail=pp;
	 
	 }
		tail->next=NULL;

}

void FillDecQueue(struct list *&head,int n)
{  struct list *pp,*tail;
   head=(struct list*)malloc(sizeof(struct list));
        
       head->data=n;
	   tail=head; 
	    for( n=n-1;  n>0  ; n--)
     {
      pp=(struct list*)malloc(sizeof(struct list));
     pp->data=n;
     tail->next =pp;
      tail=pp;
	 
	 }
		tail->next=NULL;

}


void FillRandQueue(struct list *&head,int n)
{  struct list *pp,*tail;
   head=(struct list*)malloc(sizeof(struct list));
        
       head->data=rand()%n*3;
	   tail=head;
	    for( int i=2;  i<=n  ; i++)
     {
      pp=(struct list*)malloc(sizeof(struct list));
     pp->data=rand()%n*3;
     tail->next =pp;
      tail=pp;
	 
	 }
		tail->next=NULL;

}

int  sumlist(struct list *head)
{    int sum=0;
 
    while (head!=NULL)  
   {

     sum=sum+head->data;
     head= head->next;
    
  }
	return sum;
}

int  runnumberlist(struct list *head)
{    int k=1;
 
    while (head->next!=NULL)  
   {
	   if(head->next->data<head->data) k=k+1;
       head=head->next;          
   }
	return k;
}


void clearlist(struct list *&head)
{
	struct list *p=head,*pp=head;

 pp=p=head;
   while (p!=NULL)
   {
     p=pp->next;
     free(pp) ;
     pp=p;
   }   
  head=NULL;
  
}

 void printququ(struct list *head)
{    
 
  while (head!=NULL)  
   {

    printf("%d ", head->data);
     head=head->next;
          
  }

}

void check(struct list *&head,int n)
{ 
    FillRandQueue(head,n);
     printququ(head);

    printf("\n ���������� ����� %d \n",runnumberlist(head));
    printf("\n ����� ��������� %d \n",sumlist(head));
    
    
     
     
     digitalsort(head,n);

	printququ(head);
 
    printf("\n ���������� ����� %d \n",runnumberlist(head));
    printf("\n ����� ��������� %d \n",sumlist(head));
     
     
} 


int main()
{ 
	int n=50,N=n;
    srand(time(0));
	struct list *head,*headq;
 
    check(head ,n);
    

    int s;
    int *A;
    A=new int[N];

getch();
}









