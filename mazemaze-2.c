#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init(int size){
	srand(time(NULL));
	if(size % 2 == 0)
		return;
	int msize = size;
	int **maze = malloc(sizeof(int*) * size);
	for (int l = 0; l < size; l++)
	{
		maze[l] = malloc(sizeof(int*) * size);
	}
	for(int y = 0; y < msize; y++)
	{
		for(int x = 0; x < msize; x++)
		{
			if(x % 2 ==0 || y % 2 == 0)
				maze[y][x] = 1;
			else
				maze[y][x] = 0;
		}
	}
	for (int y = 0; y < msize; y++)
	{
		int count = 1;
		for(int x = 0; x < msize; x++)
		{
			if(x % 2 == 0 || y % 2 == 0)
				continue;

			if(x == msize - 2 && y == msize - 2)
				continue;
			
			if(y == msize - 2)
			{
				maze[y][x+1] = 0;
				continue;
			}
			
			if(x == msize - 2)
			{
				maze[y+1][x] = 0;
				continue;
			}
			
			if(rand() % 2 == 0)
			{
				maze[y][x+1] = 0;
				count++;
			}
			else
			{
				int random = rand() % count;
				maze[y+1][x - random * 2] = 0;
				count = 1;
			}
		}
	}
	maze[1][0] = 0; //출발점 지정
	maze[size-2][size-1] = 0; //출구 지정

	for(int i = 0; i < size; i++)
	{
		for(int k = 0; k < size; k++)
		{
			if(maze[i][k] == 0)
				printf("  ");
			else
				printf("■");
		}
		printf("\n");
	}
	
	for (int i = 0; i < size; i++)
	{
		free(maze[i]);
	}
	free(maze);

	
}

int main(void)
{
	init(21);
	return 0;
}
