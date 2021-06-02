#include <windows.h>

using namespace std;

void GoToRowColumn(int Row, int Column)
{
	int x = Column, y = Row;
	COORD screen;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	screen.X = x;
	screen.Y = y;
	SetConsoleCursorPosition(hOutput, screen);
}