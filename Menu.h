#ifndef _MENU_H
#define _MENU_H

#include <vector>
#include <conio.h>
#include "Word.h"
#include <windows.h>
#include <dos.h>

class Point {
public:
	char val;

	Point(const char v = ' ') : val(v) {}
};

class Menu {
private:

	int row, col;
	std::vector<std::vector<Point>> map;

	static void cls()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coordScreen = { 0, 0 };    // home for the cursor
		SetConsoleCursorPosition(hConsole, coordScreen);
	}

public:

	Menu(int r, int c) : row(r), col(c), map(r + 1, std::vector<Point>(c, ' ')) {}

	void Renew_Map(const Words& w)
	{
		map = std::vector<std::vector<Point>>(row + 1, std::vector<Point>(col, ' '));    //reload map

		for (auto& q : w.dq_words) {
			if (q == nullptr) continue;

			auto& word = *q.get();
			int r = word.row, c = word.col;
			int len = word.val.length();

			for (int i = 0; i < len; i++, c++) {
				//Renew word in map
				map[r][c] = word.val[i];
			}
		}
	}

	void Print_Map(int life, int score)
	{
		//clearScreen();
		system("cls");
		//print player information
		Print_Life(life);
		for (int i = 0; i < col / 10; i++) printf("\t");
		Print_Score(score);

		//print game map
		for (int i = 0; i < col; i++) printf("-");
		for (int i = 0; i < row; i++) {
			auto& v = map[i];
			for (const auto& p : v)
				printf("%c", p.val);
			printf("\n");
		}
		for (int i = 0; i < col; i++) printf("-");
		printf("\n");
	}

	static void Print_Life(int life)
	{
		printf("life:%d", life);
	}

	static void Print_Score(int score)
	{
		printf("Score:%d\n", score);
	}
};

#endif // !_MENU_H