#ifndef _WORD_H
#define _WORD_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include <utility>
#include <cassert>

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
	std::vector<std::unique_ptr<Word>> dq_words;

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

	void Clean_Null()
	{
		std::vector<std::unique_ptr<Word>> new_dq;
		for (auto& word : dq_words) {
			if (word != nullptr)
				new_dq.push_back(std::move(word));
		}
		swap(dq_words, new_dq);
	}

	bool Find_Clear(const std::string input)
	{
		bool res = false;
		for (auto& word : dq_words) {
			if (input == word->val) {
				word = nullptr;
				res = true;
				break;
			}
		}
		Clean_Null();
		return res;
	}

	void More_Word(int i)
	{
		max += i;
	}

	bool Drop()
	{
		bool res = false;
		for (auto& word : dq_words) {
			if (word->Down() > edge) {
				word = nullptr;
				res = true;
			}
		}
		Clean_Null();
		return res;
	}

};

#endif // !_WORD_H