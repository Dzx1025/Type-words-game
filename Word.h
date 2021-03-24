#ifndef _WORD_H
#define _WORD_H

#include <iostream>
#include <deque>
#include <string>
#include <memory>
#include <cstdlib>
#include <utility>

class Word {
public:
	std::string val;
	int row = 1, col;

	Word() : col(), val() {}

	Word(int x, int y, std::string s) : row(x), col(y), val(std::move(s)) {}

	friend std::ostream& operator<<(std::ostream& output, const Word& w)
	{
		output << w.val;
		return output;
	}

	int Down()
	{
		return ++row;    //pos after falling
	}

};

class Words {
	friend class Word;

private:
	int max = 0;
	int edge = 0;

public:

	std::deque<std::unique_ptr<Word>> dq_words;

	Words(int m, int e) : max(m), edge(e) {}

	int Size() const
	{
		return dq_words.size();
	}

	std::string Top() const
	{
		return dq_words.front().get()->val;
	}

	std::string Bottom() const
	{
		return dq_words.back().get()->val;
	}

	bool Drop()    //return hurt
	{
		int cnt = 0;
		for (auto& word : dq_words) {
			if (word->Down() > edge)
				++cnt;
		}
		//pop bottom word (must be front)
		for (int i = 0; i < cnt; i++) dq_words.pop_front();

		return cnt != 0;
	}

};

#endif // !_WORD_H