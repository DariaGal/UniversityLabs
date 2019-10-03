#define MAXCOLORTC
#pragma pack(1)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "wingraph.h"
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

int main()
{
	
	setlocale(LC_ALL,"Russian" );
	FILE* f1 = fopen("newB.pcx","rb");
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
	fseek(f1,-769,SEEK_END);
	char f;
	fread(&f,1,1,f1);
	printf("%d\n",f);
	for(int i=0;i<256;i++)
	{
		fread(&PCXPalette[i],1,sizeof(PCXPalette[i]),f1);
	}
	
   	fseek(f1,sizeof(PCXHeader),SEEK_SET);
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
   			if(0xC0 == (byte & 0xC0))
   			{
   				count = byte & 0x3F;
   				fread(&data,1,1,f1);
   			}else
   			{
   				count = 1;
   				data = byte;
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
   	}
   	
 	resize(XSize,YSize);
   	for(int i=0;i<YSize;i++)
 	{
 		for(int j=0;j<XSize;j++)
 		{
 			putpixel(j,i,RGB(PCXPalette[raster[i][j]].Red,PCXPalette[raster[i][j]].Green,PCXPalette[raster[i][j]].Blue));
 		}
 	}
	fclose(f1);
	return 0;
}
