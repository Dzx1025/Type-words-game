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

int life = 5, score = 0;
int interval = 600;
int max_num = 5;

bool exit();
void fin_words(set<string>& dict, ifstream& inf);
void Create_Word(set<string>& dict, Words& words);
void Clear_Word(string& input, int& score, Menu& m, Words& words);

int main()
{
	Menu menu(ROW, COL);
	Words words(max_num, ROW);
	ifstream inf("dict.txt");

	set<string> dict;
	fin_words(dict, inf);

	srand((unsigned)time(nullptr));

	string input;
	while (!exit()) {
		menu.Renew_Map(words);
		menu.Print_Map(life, score);
		cout << input << endl;

		if (_kbhit()) {
			Clear_Word(input, score, menu, words);
		}
		if (words.Size() < max_num)    //max limit
		{
			Create_Word(dict, words);
		}
		if (words.Drop())
			life--;

		if (!(score % 10) && score)
			interval = static_cast<int>(interval / 1.2);
		this_thread::sleep_for(chrono::milliseconds(interval));
	}

	return 0;
}

//Function
bool exit()
{
	return life < 0;
}

void fin_words(set<string>& dict, ifstream& inf)
{
	string s;
	while (getline(inf, s, '\n'))
		dict.insert(s);
}

void Create_Word(set<string>& dict, Words& words)
{
	auto& ran_word = *select_random(dict, rand() % dict.size());
	const string& s(ran_word);
	int x = 0, y = static_cast<int>(rand() % (COL - s.length()));

	words.dq_words.push_back(std::make_unique<Word>(x, y, s));
}

void Clear_Word(string& input, int& score, Menu& m, Words& words)
{
	bool over = false;
	char c = static_cast<char>(_getch());
	if (c == '\r') over = true;

	input.push_back(c);
	if (c == 8)	input.pop_back();

	//input match successfully
	if (over) {
		if (input.substr(0, input.length() - 1) == words.Top()) {
			cout << endl << "Clear!!!" << endl;

			words.dq_words.pop_front();
			m.Renew_Map(words);
			score++;
		}
		else {
			cout << endl << "Wrong!!!" << endl;
		}
		input.clear();
	}
	//Clear input cache
	cin.clear();
	cin.sync();
}