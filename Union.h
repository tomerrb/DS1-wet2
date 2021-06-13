#include "tree.h"

#ifndef UNION_H
#define UNION_H

int compare_int_keys(int key1, int key2) {
	return key2 - key1;
}

int compare_double_keys(doubleInt key1, doubleInt key2) {
	if (key1.get_score() == key2.get_score())
		return key2.get_number() - key1.get_number();
	return key2.get_score() - key1.get_score();
}

class doubleInt {
	int score;
	int number;
public:
	doubleInt(int score, int number) :
		score(score),
		number(number) {

	}
	~doubleInt() = default;

	int get_score() {
		return score;
	}
	int get_number() {
		return number;
	}

};

namespace Union {
	class Agency
	{
		Tree<int, int> score_tree;
		Tree<doubleInt, doubleInt> final_tree;
		Agency* parent;
		int rank;


	public:

		Agency();
		~Agency();
		Agency* find();
		void change_parent(Agency* agency);
		bool SellCar(int typeID, int k);
		int GetIthSoldType(int i);

	};

	bool UniteAgencies(const Agency& agency1, const Agency& agency2);
}

#endif
