#include <stdio.h> 
#include <stdlib.h> 

#define MAX_SIZE 100 
#define MAZE_SIZE 7

typedef struct Pos {
	int x;
	int y;
}Pos;

typedef struct Stack {
	Pos data[MAX_SIZE];
	int top;
}Stack;
// s : 시작점 , e : 도착점 
// 1 : 벽, 0 : 길
char maze[MAZE_SIZE][MAZE_SIZE] = { {'1','1','1','1','1','1','1'},
								 {'s','0','1','0','1','1','1'},
								 {'1','0','0','0','0','1','1'},
								 {'1','0','1','0','0','0','e'},
								 {'1','0','1','0','1','1','1'},
								 {'1','0','1','0','1','1','1'},
								 {'1','1','1','1','1','1','1'}
};
void init(Stack *p)
{
	p->top = -1;
}

int isfull(Stack *p)
{
	if (p->top == MAX_SIZE - 1)
		return 1;
	else
		return 0;
}
int isempty(Stack *p)
{
	if (p->top == -1)
		return 1;
	else
		return 0;
}
void push(Stack *p, Pos data)
{
	if (isfull(p) == 1)
	{
		printf("스택 포화\n");
		exit(1);
	}
	else
	{
		p->top++;
		p->data[p->top].x = data.x; //스택에 x좌표값 저장
		p->data[p->top].y = data.y; //스택에 y좌표값 저장
	}
}
Pos peek(Stack* p)
{
	if (isempty(p) == 1)
	{
		printf("스택 공백\n");
		exit(1);
	}
	return p->data[(p->top)];
}
Pos pop(Stack *p)
{
	if (isempty(p) == 1)
	{
		printf("스택 공백\n");
		exit(1);
	}
	return p->data[(p->top)--];
}
void findway(Stack *s, int x, int y)
{
	if (x<0 || y< 0 || x>MAZE_SIZE || y>MAZE_SIZE) //미로 범위를 벗어나면
		return 0;

	//갈 수 있는 좌표를 모두 스택에 push로 넣어둔다.
	if (maze[x][y] != '1' && maze[x][y] != '.') // 1 :벽 / . : 이미 방문한 곳
	{
		Pos tmp;
		tmp.x = x;
		tmp.y = y;
		push(s, tmp); //스택 s에 갈 수 있는 좌표값 push
	}
}
int main()
{
	Stack s;
	Pos position;
	int i, j, x, y;
	init(&s);


	// 시작점 탐색
	for (i = 0; i < MAZE_SIZE; i++)
	{
		for (j = 0; j < MAZE_SIZE; j++)
		{
			if (maze[i][j] == 's')
			{
				position.x = i;
				position.y = j;
			}
		}
	}
	//미로 출력
	printf("미로 \n");
	for (int i = 0; i < MAZE_SIZE; i++) {
		for (int j = 0; j < MAZE_SIZE; j++) {
			if (maze[i][j] == '0') {
				printf("0");
			}
			else if (maze[i][j] == '1') {
				printf("1");
			}
			else {
				printf("%c", maze[i][j]);
			}
		}
		printf("\n");
	}

	printf("\n시작 점 : (%d,%d) \n", position.x, position.y);

	//미로 탐색
	while (maze[position.x][position.y] != 'e')
	{
		x = position.x;
		y = position.y;

		maze[x][y] = '.'; //방문한 곳 . 으로 표시

		//탐색
		findway(&s, x, y + 1);
		findway(&s, x + 1, y);
		findway(&s, x - 1, y);
		findway(&s, x, y - 1);

		if (isempty(&s) == 1)
		{
			printf("실패\n");
			exit(1);
		}
		
		//막다른길이면 돌아감
		else if ((maze[position.x][position.y + 1] == '1' || maze[position.x][position.y + 1] == '.') &&
			(maze[position.x + 1][position.y] == '1' || maze[position.x + 1][position.y] == '.') &&
			(maze[position.x - 1][position.y] == '1' || maze[position.x - 1][position.y] == '.') &&
			(maze[position.x][position.y - 1] == '1' || maze[position.x][position.y - 1] == '.')) {
			position = pop(&s);
			printf("(%d,%d) ->", position.x, position.y);
		}	
		else
		{
			position = peek(&s);
			printf("(%d,%d) ->", position.x, position.y);
		}
		
	}

	printf("도착 점 (%d,%d)\n", position.x, position.y);
	printf("탐색 성공\n");

	return 0;

}
