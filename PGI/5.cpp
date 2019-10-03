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
} head_file, head_logo;
struct triple {
  unsigned char rgbtBlue;
  unsigned char rgbtGreen;
  unsigned char rgbtRed;
}rgb_triple,rgb_new;

unsigned char palitra[256][4];


int main() {

	setlocale(LC_ALL,"Russian" );
	FILE* f1 = fopen("_carib_TC.bmp","rb");
	FILE* flogo = fopen("logo4.bmp","rb");
	FILE* f2 = fopen("new.bmp","wb");
  	
  	fread(&head_file,sizeof(head_file),1,f1);
  	fread(&head_logo,sizeof(head_logo),1,flogo);
  	fwrite(&head_file,sizeof(head_file),1,f2);
 	long width = head_file.biwidth;
 	long height = head_file.biheight;
 	
 	long widthLogo = head_logo.biwidth;
 	long heightLogo = head_logo.biheight;
  	
  	
  	printf("тип файла: %d\n", head_file.bftype);
 	printf("размер файла: %d\n",head_file.bfsize);
	printf("ширина: %d px\n", head_file.biwidth);
	printf("высота: %d px\n",head_file.biheight);
	printf("размер картинки: %d байт \n", head_file.bisizeimage);
	printf("число битов на пиксель: %d\n",head_file.bibitcount);
	
	
	printf("ширина logo: %d px\n", head_logo.biwidth);
	printf("высота: %d px\n",head_logo.biheight);
	printf("число битов на пиксель: %d\n",head_logo.bibitcount);
	
  	for(int i=0; i<(head_file.bfoffbits-54)/4; i++) 
	{
 	   fread(palitra[i],4,1,f1);
 	   fwrite(palitra[i],4,1,f2);
 	}
 	fseek(flogo, head_file.bfoffbits-54, SEEK_CUR);
 	
 	triple **r_logo = new triple*[heightLogo];
 	for(int i=0;i<heightLogo;i++)
 	{
 		r_logo[i] = new triple[widthLogo];
 	}
 	char p = 0;
	  for(int i=0;i<heightLogo;i++)
 	{
 		for(int j=0;j<widthLogo;j++)
 		{
 			fread(&r_logo[i][j],1,sizeof(rgb_triple),flogo);
		 }
		 fseek(flogo, widthLogo%4, SEEK_CUR);
	}
	int startH = (height - heightLogo)/2;
	int startW = (width - widthLogo)/2;
	int h=0,w=0;
 if(head_file.bibitcount == 24)
 {
 	 for(int i=0;i<height;i++)
 	{
 		w=0;
 		for(int j=0;j<width;j++)
 		{ 
 			fread(&rgb_triple,1,sizeof(rgb_triple),f1);
 			if(i>=startH && i<startH+heightLogo && j>startW && j<startW+widthLogo)
 			{
 				if(r_logo[h][w].rgbtBlue > 100 && r_logo[h][w].rgbtRed> 100 && r_logo[h][w].rgbtGreen> 100)
 				{
 					fwrite(&rgb_triple,1,sizeof(rgb_triple),f2);
 				}
 				else{
			  		rgb_new.rgbtBlue = (r_logo[h][w].rgbtBlue + ALPHA) + (rgb_triple.rgbtBlue * (1.0 - ALPHA));
 					rgb_new.rgbtRed = (r_logo[h][w].rgbtRed + ALPHA) + (rgb_triple.rgbtRed * (1.0 - ALPHA));
 					rgb_new.rgbtGreen = (r_logo[h][w].rgbtGreen + ALPHA) + (rgb_triple.rgbtGreen * (1.0 - ALPHA));
 					
 				fwrite(&rgb_new,1,sizeof(rgb_new),f2);
 				}
 					w++;
 			} else {
 				
 				fwrite(&rgb_triple,1,sizeof(rgb_triple),f2);
 				
 			}
 		}
 		if(i>=startH && i<startH+heightLogo)
 		h++;
 		fseek(f1, width%4, SEEK_CUR);
 		fwrite(&p,1,width%4,f2);
 	}
 	
 }
 	 fclose(f1); fclose(f2); fclose(flogo);
  
  return 0;
}
