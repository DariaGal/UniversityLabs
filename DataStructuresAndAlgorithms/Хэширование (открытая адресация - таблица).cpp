#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <time.h>
void createstring(char str[],int n)
{
	int i;
	for(i=0;i<n;i++)
	str[i]='A' + rand() % (('Z' - 'A') + 1);
}
void Createlin(char str[],char T[],int &kol,int n,int m)
{
	int i,tr,k,j;
	i=0;
	for(i=0;i<n;i++){
		
		if(kol>=m) break;
		tr=(int)(str[i]);
		j=tr%m;
	while(1)
	{
		if(T[j]!=0)
		{
			kol++;
			if(str[i]==T[j])break;
			j++;
			if(j>=m)j=j-m;
		}	
		else
		{
			T[j]=str[i]; break;
		}
	}}
}
void Createkvad(char str[],char K[],int &kol, int n,int m)
{
	int i,tr,k,j,d,h=1;
	i=0; 
	for(i=0;i<n;i++){
		if(kol>=m) break;
	    h=1;
		tr=(int)(str[i]);
		j=tr%m;
	while(1)
	{
		if(K[j]!=0)
		{
			kol++;
			if(str[i]==K[j])break;
			if(h>=m) break;
			j=j+h;
			if(j>=m)j=j-m; 
			h=h+2;
			
			
		}	
		else
		{
			K[j]=str[i]; break;
		} 
	}}
}
main()
{
	/*srand(time(NULL));*/
    int n=10,m=15,i;
	char str[100];
	char T[100],K[100];
	for(i=0;i<m;i++)
	K[i]=0;
	puts(" ");
	int kol=0,kol2=0;
	createstring(str,n);
	for(i=0;i<n;i++)
	printf("%c",str[i]);
	Createlin(str,T,kol,n,m);
	puts(" ");
	for(i=0;i<m;i++)
	printf(" | %2d",i);
	puts("\n----------------------------------------------------------------------------");
	for(i=0;i<m;i++)
	printf(" |%3c",T[i]);
	printf("\nколлизий=%d \n",kol);
	Createkvad(str,K,kol2,n,m);
	puts(" \n");
	for(i=0;i<m;i++)
	printf(" | %2d",i);
	puts("\n----------------------------------------------------------------------------");
	for(i=0;i<m;i++)
	printf(" |%3c",K[i]);
	printf("\nколлизий=%d",kol2);
	
	printf("\n| Размер таблицы | Кол-во символов | линейные пробы | квадратичные пробы |\n");
	for(n=5,m=15;n<45;n=n+5,m=m+15)
	{
		kol=0;kol2=0;
		createstring(str,n);
		Createlin(str,T,kol,n,m);
		Createkvad(str,K,kol2,n,m);
		printf("| %7d        | %7d         | %9d      | %9d          |\n",m,n,kol,kol2);
		
	}
}
