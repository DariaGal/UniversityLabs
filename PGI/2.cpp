#pragma pack(1)
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;
struct  head {
        short bftype;
        long  bfsize;
        short rez1, rez2;
        long  bfoffbits;
        long  bisize;
        long  biwidth;
        long  biheight;
        short biplanes;
        short bibitcount;
        long  bicompression;
        long  bisizeimage;
        long  bix;
        long  biy;
        long  biclrused;
        long  biclrimp;
} head_file;

unsigned char palitra[256][4];


int main() {

	setlocale(LC_ALL,"Russian" );
	FILE* f1 = fopen("_Carib256.bmp","rb");
	FILE* f2 = fopen("new.bmp","wb");
	srand(time(0));
  	
  	fread(&head_file,sizeof(head_file),1,f1);
  	
 	int border = 15;
 	long width = head_file.biwidth;
 	long height = head_file.biheight;
 	long width_new = width+border*2;
 	long height_new = height+border*2;
  	head_file.biheight = height_new;
  	head_file.biwidth = width_new;
  	
  	fwrite(&head_file,sizeof(head_file),1,f2);
  	
  	printf("тип файла: %d\n", head_file.bftype);
 	printf("размер файла: %d\n",head_file.bfsize);
	printf("ширина: %d px\n", head_file.biwidth);
	printf("высота: %d px\n",head_file.biheight);
	printf("размер картинки: %d байт \n", head_file.bisizeimage);
	printf("число битов на пиксель: %d\n",head_file.bibitcount);
  	
  	for(int i=0; i<(head_file.bfoffbits-54)/4; i++) 
	{
 	   fread(palitra[i],4,1,f1);
 	   fwrite(palitra[i],4,1,f2);
 	}
 	
 	int n;
 	char p = 0;
 	char color = rand()%256;
 	
 	char *buf = new char[width];
 	for(int i=0;i<border;i++)
 	{
 		for(int j=0;j<width_new;j++)
 		{
 			fwrite(&color,1,1,f2);
 		}
 		fwrite(&p,1,(4-width_new%4)%4,f2);
 	}
 	
 	for(int i=0;i<height;i++)
 	{
 		for(int j=0;j<border;j++)
 		{
 			fwrite(&color,1,1,f2);
 		}
 			fread(buf,1,width,f1);
 			fwrite(buf,1,width,f2);
 		
 		for(int j=0;j<border;j++)
 		{
 			fwrite(&color,1,1,f2);
 		}
 		
 		fwrite(&p,1,(4-width_new%4)%4,f2);
 		fseek(f1, (4-width%4)%4, SEEK_CUR);
 	}
 	
 	for(int i=0;i<border;i++)
 	{
 		for(int j=0;j<width_new;j++)
 		{
 			fwrite(&color,1,1,f2);
 		}
 		
 		fwrite(&p,1,(4-width_new%4)%4,f2);
 	}
 	 fclose(f1);
 	 fclose(f2);
  
  return 0;
}
