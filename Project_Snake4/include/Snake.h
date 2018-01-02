/*
座標資料
x_max = 105
y_max = 65
drawPixel(HWND hwnd,int x, int y, char R, char G, char B);
*/
#define ElapseTimer1 80
#define ElapseTimer2 5
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _Screen {
	int x;
	int y;
	/*畫面的x,y座標*/
}Screen;
Screen screen;/*畫面的x,y座標*/
void formatScreen(Screen screen) {
	screen.x = 0;
	screen.y = 0;/*screen初始位置為(0,0)*/
}
typedef struct _Block {
	int x;
	int y;
}Block;
Block block[50];
void formatBlock(Block *block) {
	for (int i = 0; i < 100; i++)
	{
		block[i].x = -1;
		block[i].y = -1;
		/*block初始位置為(-1,-1)*/
	}
}
typedef struct _Point {
	int x;
	int y;
}Point;
Point point;
typedef struct _Snake {
	int x;
	int y;
	int dir;
	/*
	dir config
	0 → UP
	1 → DOWN
	2 → LEFT
	3 → RIGHT
	*/
}Snake;
Snake snake[99];
void formatSnake(Snake *snake) {
	for (int i = 0; i < 99; i++) {
		snake[i].x = -1;
		snake[i].y = -1;
		snake[i].dir = -1;
	}
}

void timer1(HWND hwnd) {
	static int gameStart = 0;
	static int gameEnd = 0;
	static int body = 0;
	static int bl = 0;
	int i = 0;
	int j;
	if (gameStart == 0 && gameEnd == 0) {
		srand(time(NULL));
		formatScreen(screen);
		formatSnake(snake);
		formatBlock(block);
		snake[0].x = 0;
		snake[0].y = 0;
		snake[0].dir = 0;
		point.x = rand() % 106;//first modify
		point.y = rand() % 65;//first modify
		drawPixel(hwnd, point.x, point.y, 255, 0, 255);//first modify
		gameStart = 1;
	}
	else if (gameStart==1 && gameEnd==0) {
		drawPixel(hwnd, snake[body].x, snake[body].y, 255, 255, 255);//清除身體跟頭
		for (j = body; j >0; j--)
		{
			snake[j].x = snake[j - 1].x;
			snake[j].y = snake[j - 1].y;
			snake[j].dir = snake[j - 1].dir;
			/*身體跟著頭移動*/
		}
		if (snake[0].x == point.x && snake[0].y == point.y)//second modify
		{
			point.x = rand() % 106;
			point.y = rand() % 65;
			body++;
			block[bl].x = (rand() % 106);//block的x
			block[bl].y = (rand() % 65);//block的y
			while(block[bl].x == point.x && block[bl].y == point.y)//如果block跟point同一位置，block重取一次
			{
				block[bl].x = (rand() % 106);//block的x
				block[bl].y = (rand() % 65);//block的y
			}
			drawPixel(hwnd, block[bl].x, block[bl].y, 0, 255, 255);//畫出block且不會被吃掉
			bl++;
			switch (snake[body - 1].dir)
			{
			case 0:
				snake[body].y = snake[body - 1].y + 1;
				snake[body].x = snake[body - 1].x;
				break;
			case 1:
				snake[body].y = snake[body - 1].y - 1;
				snake[body].x = snake[body - 1].x;
				break;
			case 2:
				snake[body].x = snake[body - 1].x + 1;
				snake[body].y = snake[body - 1].y;
				break;
			case 3:
				snake[body].x = snake[body - 1].x - 1;
				snake[body].y = snake[body - 1].y;
				break;
			default:
				break;
				/*吃到計分點，訂出身體座標*/
			}
			snake[body].dir = snake[body - 1].dir;
			drawPixel(hwnd, point.x, point.y, 255, 0, 255);
		}//second modify
		switch (snake[0].dir) {
		case 0:
			snake[0].y--;
			break;
		case 1:
			snake[0].y++;
			break;
		case 2:
			snake[0].x--;
			break;
		case 3:
			snake[0].x++;
			break;
		default:
			break;
		}
		if (snake[0].x < 0) snake[0].x = 105;
		if (snake[0].x > 105) snake[0].x = 0;
		if (snake[0].y < 0) snake[0].y = 65;
		if (snake[0].y > 65) snake[0].y = 0;
		drawPixel(hwnd, snake[0].x, snake[0].y, 0, 0, 0);
		for (int k = 0; k < 100; k++)
		{
			if (snake[0].x == block[k].x&&snake[0].y == block[k].y)
			{
				gameStart = 0;
				gameEnd = 1;
				break;
			}
			/*蛇碰到block*/
		}
		for (int z = 1; z < 99; z++)
		{
			if (snake[0].x == snake[z].x && snake[0].y == snake[z].y)
			{
				gameStart = 0;
				gameEnd = 1;
				break;
			}
			/*蛇碰到自己身體*/
		}
	}
	else if (gameEnd==1 && gameStart==0) {
		int x ;
		int y ;
		for (x = 0; x < 106; x++)
		{
			for (y = 0; y < 66; y++)
			{
				drawPixel(hwnd, x, y, 255, 255, 255);
				/*畫面全部畫成白色*/
			}
		}
		gameStart = 1;
	}
	else if (gameStart == 1 && gameEnd == 1)
	{
		/*顯示計分*/
	}
}

void timer2(HWND hwnd) {
}

void KeyUp() {
	snake[0].dir = 0;
}
void KeyDown() {
	snake[0].dir = 1;
}
void KeyLeft() {
	snake[0].dir = 2;
}
void KeyRight() {
	snake[0].dir = 3;
}
