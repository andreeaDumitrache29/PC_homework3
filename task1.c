#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

#define max 100

struct color
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
};

int main()
{	
	struct bmp_fileheader bmp_fh;
	struct bmp_infoheader bmp_ih;	

	FILE* f1 = fopen("input.txt","r");

	if(f1 == NULL)
	{
		printf("Nu s-a deschis fisierul1\n");
		return 0;
	
	}
	char* poza = (char*)calloc(max, sizeof(char));
	fscanf(f1, "%s", poza);
	int red,green,blue;

	fscanf(f1, "%d", &blue);
	fscanf(f1, "%d", &green);
	fscanf(f1, "%d", &red);
	
	char *output = malloc(max * sizeof(char));
	strncpy(output, poza, strlen(poza)-4);
	strcat(output,"_task1.bmp");

	FILE* f2 = fopen(poza,"rb+");

	if(f2 == NULL)
	{
		printf("Nu s-a deschis fisierul2\n");
		return 0;
	}

	fread(&bmp_fh, 1, sizeof(bmp_fh), f2);
	fread(&bmp_ih, 1, sizeof(bmp_ih), f2);

	FILE *f = fopen(output, "wb+");
	
	fwrite(&bmp_fh, 1, sizeof(bmp_fh), f);
	fwrite(&bmp_ih, 1, sizeof(bmp_ih), f);	

	int i, j, pad = 0, ptr = 0;

	if(((bmp_ih.width * 3) % 4) != 0)
		{
			pad = 4 - ((bmp_ih.width * 3) % 4);
		}
		
	struct color bitmap[bmp_ih.height][bmp_ih.width];

	for(i=0; i < bmp_ih.height; i++)
	{
		for(j=0; j < bmp_ih.width; j++)
				

		{	fread(&bitmap[i][j], 1 , sizeof(struct color), f2);

			if((bitmap[i][j].r != 255) && (bitmap[i][j].g != 255) && (bitmap[i][j].b != 255))
			{
				bitmap[i][j].b = blue;
				bitmap[i][j].g = green;
				bitmap[i][j].r = red;
			}

			fwrite(&bitmap[i][j], 1, sizeof(struct color), f);
		}
		fwrite(&ptr, pad, 1, f);
		fseek(f2, pad, SEEK_CUR);
	}
	
	fclose(f2);
	fclose(f1);
	fclose(f);
	return 0;
}
