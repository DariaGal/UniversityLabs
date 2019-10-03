#define MAXCOLORTC
#pragma pack(1)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define ALPHA 0.6
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
struct triple {
  unsigned char rgbtBlue;
  unsigned char rgbtGreen;
  unsigned char rgbtRed;
}rgb_triple,rgb_new;

unsigned char palitra[256][4];
char readdata[4096];

int main() {

	setlocale(LC_ALL,"Russian" );
	FILE* f1 = fopen("new.bmp","rb");
  	
  	fread(&head_file,sizeof(head_file),1,f1);
 	long width = head_file.biwidth;
 	long height = head_file.biheight;
 	
  	printf("тип файла: %d\n", head_file.bftype);
 	printf("размер файла: %d\n",head_file.bfsize);
	printf("ширина: %d px\n", head_file.biwidth);
	printf("высота: %d px\n",head_file.biheight);
	printf("размер картинки: %d байт \n", head_file.bisizeimage);
	printf("число битов на пиксель: %d\n",head_file.bibitcount);
	
  	for(int i=0; i<(head_file.bfoffbits-54)/4; i++) 
	{
 	   fread(palitra[i],4,1,f1);
 	}


	int j = 2;
	
 	short int s1=0,s2=0,size;
 	fread(&rgb_triple,1,sizeof(rgb_triple),f1);
	s1 = (rgb_triple.rgbtRed & 0x07)<<5;
	s1 = ((rgb_triple.rgbtGreen & 0x03)<<3)|s1;
	s1 = (rgb_triple.rgbtBlue & 0x07)|s1;
	
 	fread(&rgb_triple,1,sizeof(rgb_triple),f1);
 	s2 = (rgb_triple.rgbtRed & 0x07)<<5;
	s2 = ((rgb_triple.rgbtGreen & 0x03)<<3)|s2;
	s2 = (rgb_triple.rgbtBlue & 0x07)|s2;
	size = (s2<<8)|s1;
	
	printf("size = %d\n",size);
 	int k=0;
 	bool f =false;
 	for(int i=0;i<height;i++)
 	{
 		while(j<width)
		{
 			fread(&rgb_triple,1,sizeof(rgb_triple),f1);
 			char c = 0;
 			c = (rgb_triple.rgbtRed & 0x07)<<5;
			c = ((rgb_triple.rgbtGreen & 0x03)<<3)|c;
			c = (rgb_triple.rgbtBlue & 0x07)|c;
 			if(k==size){f=true;break;}
 			
			printf("%c",c);
 			k++;
 			j++;
 		}
 		if(f)break;
 		j=0;
 	}
 	
	fclose(f1); 
  return 0;
}
