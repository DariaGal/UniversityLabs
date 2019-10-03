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
	FILE* ft = fopen("text.txt","r");
	FILE* f1 = fopen("_carib_TC.bmp","rb");
	FILE* f2 = fopen("new.bmp","wb");
  	
  	fread(&head_file,sizeof(head_file),1,f1);
  	fwrite(&head_file,sizeof(head_file),1,f2);
 	long width = head_file.biwidth;
 	long height = head_file.biheight;
 	
  	printf("тип файла: %c\n", head_file.bftype);
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
 	
   fseek(ft,0,SEEK_END);
   short int file_length=ftell(ft);
   printf("File  lenght is %d\n",file_length);
 
   fseek(ft,0,SEEK_SET);
   int k=0;
   while(!feof(ft) && k<file_length)
    readdata[k++]=fgetc(ft);

	int j = 2;
	
 	fread(&rgb_triple,1,sizeof(rgb_triple),f1);
 	short int c = file_length;
 	rgb_new.rgbtBlue = (rgb_triple.rgbtBlue & 0xF8) | (c & 0x07);
 	c = c >> 3;
 	rgb_new.rgbtGreen = (rgb_triple.rgbtGreen & 0xFC) | (c & 0x03);
 	c = c>>2;
 	rgb_new.rgbtRed = (rgb_triple.rgbtRed & 0xF8) | (c & 0x07);
 	c = c >> 3;
 	fwrite(&rgb_new,1,sizeof(rgb_triple),f2);
 /*		printf("b = %d, g = %d, r = %d \n",rgb_triple.rgbtBlue,rgb_triple.rgbtGreen,rgb_triple.rgbtRed);
 	printf("new b = %d, g = %d, r = %d \n",rgb_new.rgbtBlue,rgb_new.rgbtGreen,rgb_new.rgbtRed);*/
 	fread(&rgb_triple,1,sizeof(rgb_triple),f1);
 	rgb_new.rgbtBlue = (rgb_triple.rgbtBlue & 0xF8) | (c & 0x07);
 	c = c >> 3;
 	rgb_new.rgbtGreen = (rgb_triple.rgbtGreen & 0xFC) |( c & 0x03);
 	c = c>>2;
 	rgb_new.rgbtRed = (rgb_triple.rgbtRed & 0xF8) |(c & 0x07);
 
 	fwrite(&rgb_new,1,sizeof(rgb_triple),f2);
 	k=0;
 	for(int i=0;i<height;i++)
 	{
 		while(j<width)
		{
 			fread(&rgb_triple,1,sizeof(rgb_triple),f1);
 			if(k<file_length)
 			{
 			unsigned char s = readdata[k++];
 				rgb_new.rgbtBlue = (rgb_triple.rgbtBlue & 0xF8) | (s & 0x07);
			 	s = s >> 3;
			 	rgb_new.rgbtGreen = (rgb_triple.rgbtGreen & 0xFC) | (s & 0x03);
			 	s = s>>2;
			 	rgb_new.rgbtRed = (rgb_triple.rgbtRed & 0xF8) | (s & 0x07);
 			fwrite(&rgb_new,1,sizeof(rgb_triple),f2);
 		}else fwrite(&rgb_triple,1,sizeof(rgb_triple),f2);	
 			j++;
 		}
 		j=0;
 	}
 	
	fclose(f1); fclose(f2); 
   fclose(ft);
  return 0;
}
