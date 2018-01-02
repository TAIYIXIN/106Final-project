/*
	�y�и��
	x_max = 105
	y_max = 65
	drawPixel(HWND hwnd,int x, int y, char R, char G, char B);
*/
#define ElapseTimer1 50
#define ElapseTimer2 5


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
	static int gameStart = 1;
	static int gameEnd = 0;
	if (!gameStart && !gameEnd) {
		formatSnake(snake);
		snake[0].x = 0;
		snake[0].y = 0;
		snake[0].dir = 0;
	}
	else if (gameStart) {
		drawPixel(hwnd, snake[0].x, snake[0].y, 255, 255, 255);
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
	}
	else if (gameEnd) {
	
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
