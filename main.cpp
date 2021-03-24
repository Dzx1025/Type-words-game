#include <fstream>
#include <memory>
#include <set>
#include <algorithm>
#include <thread>
#include "Word.h"
#include "Menu.h"
using namespace std;

template<typename S>
auto select_random(const S& s, size_t n)
{
	auto it = std::begin(s);
	std::advance(it, n);
	return it;
}

constexpr auto ROW = 25;
constexpr auto COL = 50;

void fin_words(set<string>& dict, ifstream& inf);
void Create_Word(set<string>& dict, Words& words);
void Clear_Word(string& input, Menu& m, Words& words);

int main()
{
	/*
	-------------------------Config-----------------------
	*/
	int interval = 10;
	int life = 0;
	const int max_num = 5;

	Menu menu(ROW, COL, life);
	Words words(max_num, ROW);
	ifstream inf("dict.txt");

	set<string> dict;
	fin_words(dict, inf);

	srand((unsigned)time(nullptr));

	/*
	--------------------Game Start------------------------
	*/
	string input;
	int time = 0;
	while (!menu.live()) {
		menu.Renew_Map(words);
		menu.Print_Map();

		if (_kbhit()) {
			Clear_Word(input, menu, words);
		}
		cout << input << endl;

		if (!(time % 10))
		{
			if (words.Size() < max_num)    //max limit
				Create_Word(dict, words);

			if (words.Drop())
				menu.Hurt();
		}

		if (menu.Score() != 0 && !(menu.Score() % 10)) {
			interval = static_cast<int>(interval / 1.2);
			words.More_Word(1);
		}

		this_thread::sleep_for(chrono::milliseconds(interval));
		++time;
	}
	/*
	---------------------Game Over---------------------------
	*/
	printf("Your Score : %d\n", menu.Score());
	return 0;
}

//Function

void fin_words(set<string>& dict, ifstream& inf)
{
	string word;
	while (getline(inf, word, '\n'))
		dict.insert(word);
}

void Create_Word(set<string>& dict, Words& words)
{
	auto& ran_word = *select_random(dict, rand() % dict.size());
	const string& s(ran_word);
	int x = 0, y = static_cast<int>(rand() % (COL - s.length()));

	words.dq_words.push_back(std::make_unique<Word>(x, y, s));
}

void Clear_Word(string& input, Menu& m, Words& words)
{
	bool over = false;
	char c = static_cast<char>(_getch());

	input.push_back(c);

	if (c == '\r') over = true;
	else if (c == 8) {
		input.pop_back();	//for back
		input.pop_back();	//for erase char
	}

	if (over) {
		//input match successfully
		string in = input.substr(0, input.length() - 1);

		if (words.Find_Clear(in)) {
			cout << endl << "Clear!!!" << endl;

			m.Renew_Map(words);
			m.Add_Score(1);
		}
		else {
			cout << endl << "Wrong!!!" << endl;
		}
		input.clear();
	}
	//Clear cin cache
	cin.clear();
	cin.sync();
}