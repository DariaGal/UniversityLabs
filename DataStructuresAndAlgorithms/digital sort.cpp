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
   int data;// для 4 байт
   //short int data // для 2 байт
	unsigned char Digit[4];
             };

};
  
void digitalsort(struct list *&S,int n)
{
	int j=0;
	struct list *p;
	struct list *head[256], *tail[256];    
	while(j<4)// для 4 байт
	//while(j<2)// для 2 байт
    {
	
    for (int i=0; i<=255; i++) 
    tail[i]=(struct list*)&head[i];// инициализация очереди

	p=S;
	int d;
	while (p!=NULL)
    {  
        //d- номер очереди
        //j- номер байта
        d=p->Digit[j];
        tail[d]->next=p;//помещаем элемент в очередь
        tail[d]=p;//
        p=p->next;
    }


	 p=(struct list*)&S;
    //for (int i=255; i>=0; i--)// для обратного вывода тоесть от большего к меньшему
    for (int i=0; i<=155; i++)// для прямого  тоесть от меньшего к большему
    //цикл нужен для слияния очередей это происходит следуещим образом хвосту первой очереди присваивается голова 2 и т.д.
    {
        if (tail[i]!=(struct list*)&head[i])
        {
            p->next=head[i];//это присвоение происходит тут
            p=tail[i];
        }
    }
     
    p->next=NULL;
    j=j+1;//переходим на следующий байт
	}
// KDI я не использую сразу сортирую по нужным байтам!
//почитай про union я хз как она работает тоесть я кка бы пнимаю но не доконца так что навсякий случай почитай!
//кроме метода она больше у нас ни че не смотрела! 
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

    printf("\n количетсво серий %d \n",runnumberlist(head));
    printf("\n сумма элементов %d \n",sumlist(head));
    
    
     
     
     digitalsort(head,n);

	printququ(head);
 
    printf("\n количетсво серий %d \n",runnumberlist(head));
    printf("\n сумма элементов %d \n",sumlist(head));
     
     
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









