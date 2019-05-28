#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define		MAX_BRD_LEN	(10)

static int g_GoldBrick = 1;
static int comBricks = 0;

/*
flag : print format. 0-sigal space. 
 */
void matrix_print(int *pHead, int w, int h, int flag)
{
	int i, j;
	int *pCur = NULL;

	putchar('\n');
	for(i = 0; i < h; i++)
	{
		pCur = pHead + w * i;	
		for(j = 0; j < w; j++)	
		{
			if(pCur[j] > 0)
			{
				printf("\033[;31m%02d\033[0m ", pCur[j]);	
			}
			else
				printf("%02d ", pCur[j]);		
		//	printf("%02d ", pCur[j]);		
		}
		putchar('\n');
		putchar('\n');
	}

	putchar('\n');
}

void matrix_set_com(int *pHead, int w, int h)
{
	int i, j;
	int brick = -1;
	int *pCur = NULL;
	int r = 0;

	srand(time(NULL));

	for(i = 0; i < h; i++)
	{
		pCur = pHead + w * i;
		for(j = 0; j < w; j++)	
		{
			r = rand();
			if(r % 3 == 0)		
			{
				pCur[j] = -1;	
			}
			usleep(100);
		}

	}

}
static int matrix_map_step(int *pHead, int w, int h, int *pCur, int i, int j)
{
	return 0;
}
void matrix_map_ding(int *pHead, int w, int h, int i, int j)
{
	int *pCur = pHead + i * w + j;
	int *pFore = NULL;
	int *pUp = NULL;
	int sflag = 0;
	int up, fore;


	up = 0;
	fore = 0;
	if(i == 0)
	{
		pUp = NULL;	
		up = 0;
	}
	else
	{
		pUp = pCur - w;
		up = *pUp;	
	}
	if(j == 0)
	{
		pFore = NULL;	
		fore = 0;
	}
	else
	{
		pFore = pCur - 1;
		fore = *pFore;	
	}

	if(up == -1)
	{
		if(fore > 0)	
		{
			*pUp = comBricks;	
			*pCur = comBricks;
		}
		else if(fore == -1)
		{
			*pFore = comBricks;	
			*pUp = comBricks;
			*pCur = comBricks;
			comBricks++;
		}
		else if(fore == 0)
		{
			if(pFore == NULL)
			{
				*pCur = comBricks;	
				*pUp = comBricks;
				comBricks++;
			}
			else
			{
				*pUp = comBricks;	
				*pCur = comBricks;
				comBricks++;
			}
		}
	}
	else if(up > 0)
	{
		if(fore > 0)	
		{
			*pCur = comBricks;
			if(*(pUp - 1) > 0)
			{
				comBricks--;
			}
		}
		else if(fore == -1)
		{
			*pFore = comBricks;	
			*pCur = comBricks;
		}
		else if(fore == 0)
		{
			if(pFore == NULL)
			{
				*pCur = comBricks;	
			}
			else
			{
				*pCur = comBricks;
			}
		}


	}
	else if(up == 0)
	{
		if(pUp == NULL)	
		{
			if(fore > 0)	
			{
				*pCur = comBricks;
			}
			else if(fore == -1)
			{
				*pFore = comBricks;	
				*pCur = comBricks;
				comBricks++;
			}
			else if(fore == 0)
			{
				if(pFore == NULL)
				{
					
				}
				else
				{
				}
			}
		}
		else if(pUp != NULL)
		{
			if(fore > 0)	
			{
				*pCur = comBricks;	
			}
			else if(fore == -1)
			{
				*pFore = comBricks;	
				*pCur = comBricks;	
				comBricks++;
			}
			else if(fore == 0)
			{
			
			}
		}

	}

			
}
void matrix_calc(int *pHead, int w, int h)
{
	int i, j;	
	int *pCur = NULL;
	int brick = 0;
	int *pFore = NULL;
	int *pUp = NULL;

	for(i = 0; i < h; i++)
	{
		pCur = pHead + w * i;	
		for(j = 0; j < w; j++)
		{
			if(pCur[j] == -1 || pCur[j] > 0)	
			{
			//	brick = matrix_map_step(pHead, w, h, &pCur[j], i, j);
			//	void matrix_map_ding(int *pHead, int w, int h, int i, int j)
				matrix_map_ding(pHead, w, h, i, j);
			//	matrix_print(pHead, MAX_BRD_LEN, MAX_BRD_LEN, 0);	
				//if(g_GoldBrick == brick)
				//{
				//	g_GoldBrick++;	
				//}
			}
		}
	}
}

void matrix_max(int *pHead, int w, int h)
{
	int i, j ;
	int *pCur = NULL;
	int temp = 0;
	for(i = 0; i < w; i++)
	{
		for(j = 0; j < h; j++)	
		{
			pCur = pHead + w * i;
			if(temp < pCur[j])	
			{
				temp = pCur[j];	
			}
		}
	}
	printf("temp = %d\n", temp);
}

int main(int argc, char *argv[])
{
	int s32ArrMatrix[MAX_BRD_LEN][MAX_BRD_LEN] = {0};	
	int elem;


	matrix_set_com((int *)&s32ArrMatrix[0][0], MAX_BRD_LEN, MAX_BRD_LEN);

	matrix_print((int *)&s32ArrMatrix[0][0], MAX_BRD_LEN, MAX_BRD_LEN, 0);	

	matrix_calc((int *)&s32ArrMatrix[0][0], MAX_BRD_LEN, MAX_BRD_LEN);

	matrix_print((int *)&s32ArrMatrix[0][0], MAX_BRD_LEN, MAX_BRD_LEN, 0);	

	//matrix_max((int *)&s32ArrMatrix[0][0], MAX_BRD_LEN, MAX_BRD_LEN);

	printf("comBricks:%d\n", comBricks);
	return 0;
}
