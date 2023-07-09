#include "header.h"

//Thay doi vi tri con tro
void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Ve khung
void drawBox(int width, int height, int left, int top) {
	gotoXY(left, top);
	cout << char(201);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(187);
	for (int i = top + 1; i < height + top; i++) {
		gotoXY(left, i);
		cout << char(186);
	}
	gotoXY(left, height + top);
	cout << char(200);
	for (int i = 0; i < width; i++) {
		cout << char(205);
	}
	cout << char(188);
	for (int i = height + top - 1; i > top; i--) {
		gotoXY(left + width + 1, i);
		cout << char(186);
	}
}

//In dong chu nam giua
void textAlignCenter(string s, int left, int width, int y) {
	int x = ((width - (int)s.length()) / 2) + left + 1;
	gotoXY(x, y); cout << s;
}

//Thong bao
void notifyBox(string s) {
	system("cls");
	int width = 45;
	int height = 5;
	int left = 40;
	int top = 9;
	int yPos = 11;
	gotoXY(57, 8); cout << "NOTIFICATION";
	textAlignCenter(s, left, width, yPos);
	drawBox(width, height, left, top);
	gotoXY(45, yPos+1); 
	system("pause");
	system("cls");
}