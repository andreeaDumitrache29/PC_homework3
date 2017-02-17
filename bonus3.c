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

int dif(char **mat, char a[5][5], int i, int j)
{
	int k, l, count = 0;
	
	for(k = 0; k < 5; k++)
	{
		for(l = 0; l < 5; l++)
		{
			if(mat[i + k][j - l] != a[k][4 - l])
			{
				count ++;
			}
		}
	}

	return count;
}

int cifra(char **mat, int i, int j)
{
	char zero[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};
	char unu[5][5]  = {'.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x'};
	char doi[5][5]  = {'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x'};
	char trei[5][5] = {'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x','x', 'x', 'x', 'x', 'x'};
	char patru[5][5] = {'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x'};
	char cinci[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};
	char sase[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};
	char sapte[5][5] = {'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x'};
	char opt[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'}; 
	char noua[5][5] = {'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x'};
	
	char zero2[5][5] = {'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', '.', '.', '.', 'x', 'x', 'x', 'x', 'x', 'x', '.', '.', '.', '.', '.'};
	char sapte2[5][5] = {'.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', 'x', '.', '.', '.', '.', '.'};

	int m, n;

	int *v = calloc(10, sizeof(int));

	v[0] = dif(mat, zero, i, j);
	v[1] = dif(mat, unu, i, j);
	v[2] = dif(mat, doi, i, j);
	v[3] = dif(mat, trei, i, j);
	v[4] = dif(mat, patru, i, j);
	v[5] = dif(mat, cinci, i, j);
	v[6] = dif(mat, sase, i, j);
	v[7] = dif(mat, sapte, i, j);
	v[8] = dif(mat, opt, i, j);
	v[9] = dif(mat, noua, i, j);

	int min = v[9];
	int p, pos;

	if( (i != 0) && (j >= 4) && mat[i - 1][j - 1] == 'x' && mat[i - 1][j - 2] == 'x' 
	&& mat[i - 1][j - 3] == 'x' && mat[i - 1][j - 4] == 'x' && (dif(mat,sapte2, i, j) == 0))
	{	pos = 7;
		return 7;
	}

	if(dif(mat, zero2, i, j) == 0)
	{	pos = 0;
		return 0;	
	}

	
	for(p = 9; p >= 0; p--)
	{	
		if(v[p] <= min)
		{
			min = v[p];
			pos = p;
		}
	}
	return pos;
}

int main()
{		

	FILE* f1 = fopen("input.txt", "rt");

	if(f1 == NULL)
	{
		printf("Nu s-a deschis fisierul1\n");
		return 0;
	}

	char* poza = (char*)calloc(max, sizeof(char));
	fscanf(f1, "%s", poza);
	int red, green, blue;

	fscanf(f1, "%d %d %d", &blue, &green, &red);
	
	int v[10], n = 0;

	while(fscanf(f1, "%d", &v[n]))
	{
		n++;
	}	

	char *bonus = (char*)calloc(max, sizeof(char));

	fscanf(f1, "%s", bonus);

	char *output = malloc(max * sizeof(char));
	strncpy(output, bonus, strlen(bonus) - 4);
	strcat(output, "_bonus.txt");

	FILE *f2 = fopen(bonus, "rb");
	
	if(f2 == NULL)
	{
		printf("Nu s-a deschis fisierul2\n");
		return 0;
	}

	fread(&bmp_fh, 1, sizeof(bmp_fh), f2);
	fread(&bmp_ih, 1, sizeof(bmp_ih), f2);

	FILE *f3 = fopen(output, "wt");

	struct color bitmap[bmp_ih.height][bmp_ih.width];

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
		for(j = 0; j < bmp_ih.width ; j++)
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

	int c[50], k = 0, l, m;	

	for(i = 0; i < bmp_ih.height; i++)
	{
		for(j = 0; j < bmp_ih.width; j++)
		{
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}

	for(j = bmp_ih.width - 1; j >= 0; j--)
	{
		for(i = 0; i < bmp_ih.height; i++)
		{
			if(mat[i][j] == 'x')
			{
				c[k] = cifra(mat, i, j);
				k++;

				for(m = 0; m < 5; m++)
				{
					for(l = 0; l < 5; l++)
					{
						mat[i + m][j - l] = '.';
					}
				}
			}
		}
	}

	for (i = k - 1; i >= 0; i--)
	{
		fprintf(f3, "%d", c[i]);
	}

	fclose(f1);
	fclose(f2);

	return 0;
}