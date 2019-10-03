#define MAXCOLORTC
#pragma pack(1)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "wingraph.h"
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
}rgb_triple ;
unsigned char palitra[256][4];


int main() {

	setlocale(LC_ALL,"Russian" );
	FILE* f1 = fopen("test.bmp","rb");

  	
  	fread(&head_file,sizeof(head_file),1,f1);
  	
 	int border = 15;
 	long width = head_file.biwidth;
 	long height = head_file.biheight;
  	
  	
  	printf("тип файла: %d\n", head_file.bftype);
 	printf("размер файла: %d\n",head_file.bfsize);
	printf("ширина: %d px\n", head_file.biwidth);
	printf("высота: %d px\n",head_file.biheight);
	printf(": %d px\n",head_file.bisize);
	printf("размер картинки: %d байт \n", head_file.bisizeimage);
	printf("число битов на пиксель: %d\n",head_file.bibitcount);
  	
  	for(int i=0; i<(head_file.bfoffbits-54)/4; i++) 
	{
 	   fread(palitra[i],4,1,f1);
 	  // fwrite(palitra[i],4,1,f2);
 	}
 	
 	resize(width,height);
 	char p = 0;
 	if(head_file.bibitcount==8){
 	
    unsigned char **raster = new unsigned char*[height];
    for(int i=0;i<height;i++)
    	raster[i] = new unsigned char[width];
    	
    for(int i=height-1;i>=0;i--)
 	{
 		fread(raster[i],1,width,f1);
 		fseek(f1, (4-width%4)%4, SEEK_CUR);
 	}
 	for(int i=0;i<height;i++)
 	{
 		for(int j=0;j<width;j++)
 		{
 			putpixel(j,i,RGB(palitra[raster[i][j]][2],palitra[raster[i][j]][1],palitra[raster[i][j]][0]));
 			//printf("%d ",raster[i][j]);
 		}
 	}
 }
 else if(head_file.bibitcount == 24)
 {
 	 for(int i=height-1;i>=0;i--)
 	{
 		for(int j=0;j<width;j++)
 		{
 			fread(&rgb_triple,1,sizeof(rgb_triple),f1);
 			putpixel(j,i,RGB(rgb_triple.rgbtRed,rgb_triple.rgbtGreen,rgb_triple.rgbtBlue));
 		}
 		fseek(f1, width%4, SEEK_CUR);
 	}
 	
 } else if (head_file.bibitcount == 4)
 {
 	
 	unsigned char raster;
 	for(int i=height-1;i>=0;i--)
 	{
 		int j=0;
 		while(j<width)
 		{
 			fread(&raster,1,1,f1);
 			unsigned char c = raster & 0xF;
 			putpixel(j,i,RGB(palitra[c][2],palitra[c][1],palitra[c][0]));
 			c = (raster & 0xF0)>>4;
 			j++;
 			putpixel(j,i,RGB(palitra[c][2],palitra[c][1],palitra[c][0]));
 			j++;
 		}
 		fseek(f1, width%4, SEEK_CUR);
 	}
 }
 	 fclose(f1);
  
  return 0;
}
