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
	FILE* f1 = fopen("1.bmp","rb");
	FILE* f2 = fopen("new.bmp","wb");
	
  	fread(&head_file,sizeof(head_file),1,f1);
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
 	   int r = palitra[i][0];
 	   int g = palitra[i][1];
 	   int b = palitra[i][2];
 	   
 	   int mean = (r+g+b)/3;
 	   palitra[i][0] = mean;
 	   palitra[i][1] = mean;
 	   palitra[i][2] = mean;
 	   fwrite(palitra[i],4,1,f2);
 	}
 	int n;
 	unsigned char buffer[1024];
 	 do {
  	  n=fread(buffer,1,1024,f1);
  	  fwrite(buffer,1,1024,f2);
  	} while(n==1024);
 	 fclose(f1);
 	 fclose(f2);
  
  return 0;
}
