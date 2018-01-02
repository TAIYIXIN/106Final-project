/*
�y�и��
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
	/*�e����x,y�y��*/
}Screen;
Screen screen;/*�e����x,y�y��*/
void formatScreen(Screen screen) {
	screen.x = 0;
	screen.y = 0;/*screen��l��m��(0,0)*/
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
		/*block��l��m��(-1,-1)*/
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
	0 �� UP
	1 �� DOWN
	2 �� LEFT
	3 �� RIGHT
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
		drawPixel(hwnd, snake[body].x, snake[body].y, 255, 255, 255);//�M��������Y
		for (j = body; j >0; j--)
		{
			snake[j].x = snake[j - 1].x;
			snake[j].y = snake[j - 1].y;
			snake[j].dir = snake[j - 1].dir;
			/*�������Y����*/
		}
		if (snake[0].x == point.x && snake[0].y == point.y)//second modify
		{
			point.x = rand() % 106;
			point.y = rand() % 65;
			body++;
			block[bl].x = (rand() % 106);//block��x
			block[bl].y = (rand() % 65);//block��y
			while(block[bl].x == point.x && block[bl].y == point.y)//�p�Gblock��point�P�@��m�Ablock�����@��
			{
				block[bl].x = (rand() % 106);//block��x
				block[bl].y = (rand() % 65);//block��y
			}
			drawPixel(hwnd, block[bl].x, block[bl].y, 0, 255, 255);//�e�Xblock�B���|�Q�Y��
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
				/*�Y��p���I�A�q�X����y��*/
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
			/*�D�I��block*/
		}
		for (int z = 1; z < 99; z++)
		{
			if (snake[0].x == snake[z].x && snake[0].y == snake[z].y)
			{
				gameStart = 0;
				gameEnd = 1;
				break;
			}
			/*�D�I��ۤv����*/
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
				/*�e�������e���զ�*/
			}
		}
		gameStart = 1;
	}
	else if (gameStart == 1 && gameEnd == 1)
	{
		/*body��@�n��*/
		int mod;//�Ӧ�Ʀr
		int q;//�Q��Ʀr
		mod = body % 10;
		q = body / 10;
		switch (q) {
			case 0:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 36; i < 44; i++) {
					for (int j = 26; j < 39; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 1:
				for (int i = 40; i < 42; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				break;
			case 2:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 35; i < 44; i++) {
					for (int j = 26; j < 32; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				for (int i = 36; i < 45; i++) {
					for (int j = 33; j < 39; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 3:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 35; i < 44; i++) {
					for (int j = 26; j < 32; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				for (int i = 35; i < 44; i++) {
					for (int j = 33; j < 39; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 4:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 36; i < 44; i++) {
					for (int j = 25; j < 32; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				for (int i = 35; i < 44; i++) {
					for (int j = 33; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 5:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 36; i < 45; i++) {
					for (int j = 26; j < 31; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				for (int i = 35; i < 44; i++) {
					for (int j = 32; j < 39; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 6:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 36; i < 45; i++) {
					for (int j = 26; j < 31; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				for (int i = 36; i < 44; i++) {
					for (int j = 32; j < 39; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 7:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 35; i < 44; i++) {
					for (int j = 26; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 8:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 36; i < 44; i++) {
					for (int j = 26; j < 32; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				for (int i = 36; i < 44; i++) {
					for (int j = 34; j < 39; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			case 9:
				for (int i = 35; i < 45; i++) {
					for (int j = 25; j < 40; j++)
					{
						drawPixel(hwnd, i, j, 0, 0, 0);
					}
				}
				for (int i = 36; i < 44; i++) {
					for (int j = 26; j < 32; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				for (int i = 35; i < 44; i++) {
					for (int j = 33; j < 39; j++)
					{
						drawPixel(hwnd, i, j, 255, 255, 255);
					}
				}
				break;
			default:
				break;
		}
		switch (mod) {
		case 0:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 56; i < 64; i++) {
				for (int j = 26; j < 39; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 1:
			for (int i = 48; i < 50; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			break;
		case 2:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 55; i < 64; i++) {
				for (int j = 26; j < 32; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			for (int i = 56; i < 65; i++) {
				for (int j = 33; j < 39; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 3:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 55; i < 64; i++) {
				for (int j = 26; j < 32; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			for (int i = 55; i < 64; i++) {
				for (int j = 33; j < 39; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 4:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 56; i < 64; i++) {
				for (int j = 25; j < 32; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			for (int i = 55; i < 64; i++) {
				for (int j = 33; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 5:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 56; i < 65; i++) {
				for (int j = 26; j < 31; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			for (int i = 55; i < 64; i++) {
				for (int j = 32; j < 39; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 6:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 56; i < 65; i++) {
				for (int j = 26; j < 31; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			for (int i = 56; i < 64; i++) {
				for (int j = 32; j < 39; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 7:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 55; i < 64; i++) {
				for (int j = 26; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 8:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 56; i < 64; i++) {
				for (int j = 26; j < 32; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			for (int i = 56; i < 64; i++) {
				for (int j = 34; j < 39; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		case 9:
			for (int i = 55; i < 65; i++) {
				for (int j = 25; j < 40; j++)
				{
					drawPixel(hwnd, i, j, 0, 0, 0);
				}
			}
			for (int i = 56; i < 64; i++) {
				for (int j = 26; j < 32; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			for (int i = 55; i < 64; i++) {
				for (int j = 33; j < 39; j++)
				{
					drawPixel(hwnd, i, j, 255, 255, 255);
				}
			}
			break;
		default:
			break;
		}
		/*��ܭp��*/
	}
}

void timer2(HWND hwnd) {
}

void KeyUp() {
	if(snake[0].dir != 1)snake[0].dir = 0;
}
void KeyDown() {
	if (snake[0].dir != 0)snake[0].dir = 1;
}
void KeyLeft() {
	if (snake[0].dir != 3)snake[0].dir = 2;
}
void KeyRight() {
	if (snake[0].dir != 2)snake[0].dir = 3;
}
