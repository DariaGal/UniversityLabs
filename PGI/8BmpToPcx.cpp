#define MAXCOLORTC
#pragma pack(1)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "wingraph.h"
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
typedef struct TPCXHeaderStruct
 {
  unsigned char ID;
  unsigned char Version;
  unsigned char Coding;
  unsigned char BitPerPixel;
  unsigned short  XMin;
  unsigned short  YMin;
  unsigned short  XMax;
  unsigned short  YMax;
  unsigned short  HRes;
  unsigned short  VRes;
  unsigned char Palette[48];
  unsigned char Reserved;
  unsigned char Planes;
  unsigned short  BytePerLine;
  unsigned short  PaletteInfo;
  unsigned short  HScreenSize;
  unsigned short  VScreenSize;
  unsigned char Filler[54];
 } TPCXHeader;

typedef struct TPaletteStruct
 {
  unsigned char Red;
  unsigned char Green;
  unsigned char Blue;
 } TPalette;

TPCXHeader PCXHeader;
TPalette PCXPalette[256];
unsigned char palitra[256][4];

int main()
{
	
	setlocale(LC_ALL,"Russian" );
	FILE* f1 = fopen("CAT256.bmp","rb");
	FILE* f2 = fopen("newB.pcx","wb");
	
  	fread(&head_file,sizeof(head_file),1,f1);
  	
 	long width = head_file.biwidth;
 	long height = head_file.biheight;
  	printf("тип файла: %d\n", head_file.bftype);
 	printf("размер файла: %d\n",head_file.bfsize);
	printf("ширина: %d px\n", head_file.biwidth);
	printf("высота: %d px\n",head_file.biheight);
	printf("размер картинки: %d байт \n", head_file.bisizeimage);
	printf("число битов на пиксель: %d\n",head_file.bibitcount);
	
	
	
//	printf("head_file.bix: %d  \n", head_file.bix);
//	printf("head_file.biy: %d\n",head_file.biy);
	for(int i=0; i<(head_file.bfoffbits-54)/4; i++) 
	{
 	   fread(palitra[i],4,1,f1);
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
	PCXHeader.ID = 10;
	PCXHeader.Version = 5;
	PCXHeader.Coding = 1;
	PCXHeader.BitPerPixel = head_file.bibitcount;
	PCXHeader.XMin = 0;
	PCXHeader.YMin = 0;
	PCXHeader.XMax = width - 1;
	PCXHeader.YMax = height - 1;
	PCXHeader.HRes = 96;//head_file.bix;
	PCXHeader.VRes = 96;//head_file.biy;
	PCXHeader.Planes = 1;
	PCXHeader.BytePerLine = PCXHeader.XMax + (4-PCXHeader.XMax%4)%4;
	PCXHeader.PaletteInfo = 1;
	printf("bpl = %d\n",PCXHeader.BytePerLine);
  	fwrite(&PCXHeader,sizeof(PCXHeader),1,f2);
  	
  	for(int i=height-1;i>=0;i--)
//  for(int i=0;i<height;i++)
 	{
 		unsigned char old,next,count = 1;
 		for(int j=0;j<width-1;j++)
 		{
 			old = raster[i][j];
 			next = raster[i][j+1];
 			if(raster[i][j] == raster[i][j+1])
 			{
 				if(count==0x3F)
 				{
 					unsigned char c = 0xC0 | count;
	 				fwrite(&c,1,1,f2);
	 				fwrite(&raster[i][j],1,1,f2);
	 				count = 0;
 				}
 				count++;
 			}else
 			{
 				if(count>1 || raster[i][j]>=192){
 					
	 				unsigned char c = 0xC0 | count;
	 				fwrite(&c,1,1,f2);
	 				fwrite(&raster[i][j],1,1,f2);
	 				count = 1;
 				}else { fwrite(&raster[i][j],1,1,f2);
 			}
 			}
 		}
 		if(old == next)
 		{
 			unsigned char c = 0xC0 | count;
	 				fwrite(&c,1,1,f2);
	 				fwrite(&next,1,1,f2);
 		}
 		else 
		 {
		 	if(count>1 || next>=192)
		 	{
		 		unsigned char c = 0xC0 | count;
	 				fwrite(&c,1,1,f2);
	 				fwrite(&old,1,1,f2);
		 	} else fwrite(&next,1,1,f2);
		 }
 		unsigned char garb = PCXHeader.BytePerLine - width;
 		unsigned char p=1;
 		if(garb>0)fwrite(&p,1,garb,f2);
 	}
	unsigned char f = 12;
	fwrite(&f,1,1,f2);
	for(int i = 0; i < 256; i++)
	{
		PCXPalette[i].Red = palitra[i][2];
		PCXPalette[i].Green = palitra[i][1];
		PCXPalette[i].Blue = palitra[i][0];
		fwrite(&PCXPalette[i],sizeof(PCXPalette[i]),1,f2);
		
	}
	
	fclose(f1);
	fclose(f2);
	return 0;
}
