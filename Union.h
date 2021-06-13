#include "tree.h"

#ifndef UNION_H
#define UNION_H



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
	bool operator==(const doubleInt& double_int) const {
		if (score == double_int.score && number == double_int.number)
			return true;
		return false;
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
		void SellCar(int typeID, int k);
		void UniteAgencies(Agency* agency);
		void Unite(Agency* agency);
		int GetIthSoldType(int i);

	};
	
	
}

#endif
