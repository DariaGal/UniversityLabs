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
	FILE* f1 = fopen("newB.pcx","rb");
	FILE* f2 = fopen("newbmp.bmp","wb");
	fread(&PCXHeader,sizeof(PCXHeader),1,f1);

	printf("тип файла: %d\n", PCXHeader.ID);
 	printf("версия: %d\n",PCXHeader.Version);
 	printf("кодирование: %d\n",PCXHeader.Coding);
	printf("число битов на пиксель: %d\n",PCXHeader.BitPerPixel);
	printf("Xmin : %d\n",PCXHeader.XMin);
	printf("Ymin : %d\n",PCXHeader.YMin);
	printf("Xmax : %d\n",PCXHeader.XMax);
	printf("Ymax : %d\n",PCXHeader.YMax);
	printf("resV : %d\n",PCXHeader.VRes);
	printf("resH : %d\n",PCXHeader.HRes);
	printf("числов слоев: %d \n", PCXHeader.Planes);
	printf("Палитра : %d\n",PCXHeader.PaletteInfo);
	
	printf("число байт на строку: %d\n",PCXHeader.BytePerLine);
	int TotalBytes = PCXHeader.Planes * PCXHeader.BytePerLine;
	printf("одна строка развертки: %d байт\n",TotalBytes);
	int XSize = PCXHeader.XMax - PCXHeader.XMin + 1;
	int YSize = PCXHeader.YMax - PCXHeader.YMin + 1;
	printf("%dx%d\n",XSize,YSize);

	
   //	fseek(f1,sizeof(PCXHeader),SEEK_SET);
   	unsigned char **raster = new unsigned char *[YSize];
   	for(int i=0;i<YSize;i++)
   	{
   		raster[i] = new unsigned char [XSize];
   	}
   	for(int i=0;i<YSize;i++)
   	{
   		int j=0,x=0;
   		while(j<TotalBytes)
   		{
   			unsigned char byte,count,data;
   			fread(&byte,1,1,f1);
   		//	printf("%d ",byte);
   			if(0xC0 == (byte & 0xC0))
   			{
   				count = byte & 0x3F;
   				fread(&data,1,1,f1);
   				
   		//	printf("%d ,",data);
   			}else
   			{
   				count = 1;
   				data = byte;//printf("op");
   			}
   			if(x<XSize)
   			{
	   			for(int n=0;n<count;n++)
	   			{
	   				raster[i][x] = data;
	   				x++;
	   				j++;
	   			}
   			}else j++;
   			
   		}
   		//printf("\n");
   		
   	}
   		head_file.bftype = 0x4D42;
   		head_file.bfoffbits = sizeof(head_file)+1024;
        head_file.bfsize =	head_file.bfoffbits + XSize * YSize * 8;
        head_file.bisize = 40;
        head_file.biwidth = XSize;
        head_file.biheight = YSize;
        head_file.biplanes = 1;
        head_file.bibitcount = PCXHeader.BitPerPixel;
        head_file.bicompression = 0;
        head_file.bisizeimage;
        head_file.bix = PCXHeader.HRes;
        head_file.biy = PCXHeader.VRes;
        head_file.biclrused = 0;
     
  		fseek(f1,-769,SEEK_END);
	char f;
	fread(&f,1,1,f1);
	printf("%d\n",f);
	for(int i=0;i<256;i++)
	{
		fread(&PCXPalette[i],1,sizeof(PCXPalette[i]),f1);
	}
  	for(int i=0; i<256; i++) 
	{
 	   palitra[i][2] = PCXPalette[i].Red;
 	   palitra[i][1] = PCXPalette[i].Green;
 	   palitra[i][0] = PCXPalette[i].Blue;
 	   fwrite(palitra[i],4,1,f2);
 	}
 	char p = 0;
   	for(int i=YSize-1;i>=0;i--)
 	{
 		for(int j=0;j<XSize;j++)
 		{
 			fwrite(&raster[i][j],1,1,f2);
 		}
 		
 		fwrite(&p,1,(4-XSize%4)%4,f2);
 	}
	fclose(f1);
	fclose(f2);
	return 0;
}
