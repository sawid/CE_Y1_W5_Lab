#include <stdio.h>
#include <conio.h>
#include <windows.h>
int shootStatus[5] = { 0,0,0,0,0 };
int shootX[5] = { 0,0,0,0,0 };
int shootY[5] = { 0,0,0,0,0 };
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y);
	printf(" <-0-> ");
}
void draw_shoot(int x, int y)
{
	gotoxy(x, y);
	printf("|");
}
void erase_ship(int x, int y) {
	gotoxy(x, y);
	printf("       ");
}
void erase_shoot(int x, int y) {
	gotoxy(x, y);
	printf("     ");
}
int main()
{
	
	setcursor(0);
	char ch = ' ',direct = 's',shoot = 'f',shootDirect,shootDirectX,shootLimit = 0;
	int x = 38, y = 20;
	setcolor(2, 4);
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				direct = 'l';
				
			}
			if (ch == 'd') {
				direct = 'r';
				
			}
			if (ch == 's') {
				direct = 's';
				
			}
			if (ch == ' ') {
				if (shootLimit < 5)
				{
					

					int i ;
					for (i = 0; i < 5; i++)
					{
						if (shootStatus[i] == 0) {
							shootLimit++;
							shootStatus[i] = 1;
							shootX[i] = x;
							shootY[i] = y - 2;
							break;
						}
					}
					shoot = 't';
					
					
				}
				
				
			}
			
			fflush(stdin);
		}
		if (direct == 'l')
		{
			setcolor(0, 0);
			draw_ship(x, y);
			setcolor(2, 4);
			--x;
			if (x <= 0) {
				x = 0;
			}
			Sleep(5);
			draw_ship(x, y);
		}
		if (direct == 'r')
		{
			setcolor(0, 0);
			draw_ship(x, y);
			setcolor(2, 4);
			++x;
			if (x >= 75) {
				x = 75;
			}
			Sleep(5);
			draw_ship(x, y);
		}
		if (shoot == 't')
		{
			for (int i = 0; i < 5; i++)
			{
				if (shootY[i] <= -1) {
					shootLimit--;
					if (shootLimit < 0) {
						shootLimit = 0;
					}
					setcolor(0, 0);
					erase_shoot(shootX[i] + 1, shootY[i] + 1);
					shootStatus[i] = 0;
				}
				else
				{
					setcolor(0, 0);
					erase_shoot(shootX[i] + 1, shootY[i] + 1);
					Sleep(1);
					setcolor(2, 4);
					draw_shoot(shootX[i] + 3, shootY[i]);
					shootY[i] = shootY[i] - 1;
				}
			}
				
		}
		if (direct == 's')
		{
			setcolor(2, 4);
			draw_ship(x, y);
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}