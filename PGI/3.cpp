#pragma pack(1)
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
	FILE* f1 = fopen("new.bmp","rb");
	FILE* f2 = fopen("new1.bmp","wb");

  	
  	fread(&head_file,sizeof(head_file),1,f1);
  	
 	int border = 15;
 	long width = head_file.biwidth;
 	long height = head_file.biheight;
  	head_file.biheight = width;
  	head_file.biwidth = height;
  	
  	fwrite(&head_file,sizeof(head_file),1,f2);
  	
  	printf("��� �����: %d\n", head_file.bftype);
 	printf("������ �����: %d\n",head_file.bfsize);
	printf("������: %d px\n", head_file.biwidth);
	printf("������: %d px\n",head_file.biheight);
	printf("������ ��������: %d ���� \n", head_file.bisizeimage);
	printf("����� ����� �� �������: %d\n",head_file.bibitcount);
  	
  	for(int i=0; i<(head_file.bfoffbits-54)/4; i++) 
	{
 	   fread(palitra[i],4,1,f1);
 	   fwrite(palitra[i],4,1,f2);
 	}
 	
 	char p = 0;
    unsigned char **raster = new unsigned char*[height];
    for(int i=0;i<height;i++)
    	raster[i] = new unsigned char[width];
    	
    for(int i=0;i<height;i++)
 	{
 		fread(raster[i],1,width,f1);
 		fseek(f1, (4-width%4)%4, SEEK_CUR);
 	}
 	
 	for(int i=width-1;i>=0;i--)
 	{
 		 for(int j=0;j<height;j++)
 		{
 			fwrite(&raster[j][i],1,1,f2);
 		}
 		fwrite(&p,1,(4-height%4)%4,f2);
	}
 	 fclose(f1);
 	 fclose(f2);
  
  return 0;
}
