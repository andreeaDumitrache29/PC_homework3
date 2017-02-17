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


	struct bmp_fileheader bmp_fh;
	struct bmp_infoheader bmp_ih;

int verify(char **mat, char b[5][5], int i, int j)
{
	int k, l, sw = 1;
	
	for(k = 0; k < 5; k++)
	{
		for(l = 0; l < 5; l++)
		{
			if(mat[i + k][j - l] != b[k][4 - l])
			{
				sw = 0;
				break;
			}
		}
	}

	return sw;
}

int main()
{		

	FILE* f1 = fopen("input.txt","r");

	if(f1 == NULL)
	{
		printf("Nu s-a deschis fisierul1\n");
		return 0;
	}

	char* poza = (char*)calloc(max, sizeof(char));
	fscanf(f1, "%s", poza);

	char *output = malloc(max * sizeof(char));
	strncpy(output, poza, strlen(poza) - 4);
	strcat(output,"_task2.txt");

	FILE *f2 = fopen(poza, "rb");
	
	if(f2 == NULL)
	{
		printf("Nu s-a deschis fisierul2\n");
		return 0;
	}

	fread(&bmp_fh, 1, sizeof(bmp_fh), f2);
	fread(&bmp_ih, 1, sizeof(bmp_ih), f2);

	FILE *f3 = fopen(output,"wt");

	struct color bitmap[bmp_ih.height][bmp_ih.width];

	char zero[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};
	char unu[5][5]  = {'.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x'};
	char doi[5][5]  = {'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x'};
	char trei[5][5] = {'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x','x', 'x', 'x', 'x', 'x'};
	char patru[5][5] = {'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x'};
	char cinci[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};
	char sase[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};
	char sapte[5][5] = {'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x'};
	char opt[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'}; 
	char noua[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x',+ '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};

	int i, j, pad = 0;
	if(((bmp_ih.width * 3) % 4) != 0)
		{
			pad = 4 - ((bmp_ih.width * 3) % 4);
		}
		
	char **mat;
	mat = (char**)malloc(bmp_ih.height * sizeof(char*));
	
	for(i = 0; i < bmp_ih.width; i++)
		mat[i] = (char*)malloc(bmp_ih.width * sizeof(char));

	for(i = bmp_ih.height - 1; i >= 0; i--)

	{
		for(j = 0; j<bmp_ih.width ; j++)
		{
			fread(&bitmap[i][j], 1 , sizeof(struct color), f2);
			
			if(!((bitmap[i][j].b == 255) && (bitmap[i][j].g == 255) && (bitmap[i][j].r == 255)))
			{
				mat[i][j]= 'x';
			
			}
			else
			{
				mat[i][j] = '.';
				
			}
			
		}

		fseek(f2, pad, SEEK_CUR);
		
	}	

	int cifra[50], n = 0, k, l;

	for(j = bmp_ih.width - 1; j >= 0; j--)
	{
		for(i = 0; i < bmp_ih.height; i++)
		{
			if(mat[i][j] == 'x')
			{		
				if( verify(mat, zero, i,j))
					cifra[n++] = 0;
				else if(verify(mat, unu, i, j))
					cifra[n++] = 1;
				else if(verify(mat, doi, i, j))
					cifra[n++] = 2;
				else if(verify(mat, trei, i, j))
					cifra[n++] = 3;
				else if(verify(mat, patru, i, j))
					cifra[n++] = 4;	
				else if(verify(mat, cinci, i, j))
					cifra[n++] = 5;	
				else if(verify(mat, sase, i, j))
					cifra[n++] = 6;	
				else if(verify(mat, sapte, i, j))
					cifra[n++] = 7;	
				else if(verify(mat, opt, i, j))
					cifra[n++] = 8;
				else if(verify(mat, noua , i, j))
					cifra[n++] = 9;		

				for(k = 0; k < 5; k++)
				{
					for(l = 0; l < 5; l++)
					{
						mat[i + k][j - l] = '.';
					}
				}
				
			}
			
		}
	}

	for (i = n - 1; i >= 0; i--)
	{
		fprintf(f3, "%d", cifra[i]);
	}

	fclose(f1);
	fclose(f2);


	return 0;
}