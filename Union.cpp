#include "Union.h"

int compare_int_keys(int key1, int key2) {
	return key1 - key2;
}

int compare_double_keys(doubleInt key1, doubleInt key2) {
	if (key1.get_score() == key2.get_score())
		return key1.get_number() - key2.get_number();
	return key1.get_score() - key2.get_score();
}


Union::Agency::Agency() :
	score_tree(Tree<int, int>(compare_int_keys)),
	final_tree(Tree<doubleInt, doubleInt>(compare_double_keys)),
	parent(nullptr),
	rank(1)
{

}

Union::Agency::~Agency() {
	score_tree.~Tree();
	final_tree.~Tree();
}

Union::Agency* Union::Agency::find(){
	if (parent == nullptr)
		return this;
	Union::Agency* new_parent = parent->find();
	parent = new_parent;
	return new_parent;
}
void Union::Agency::change_parent(Union::Agency* agency) {
	parent = agency;
}


void Union::Agency::SellCar(int typeID, int k) {
	if (parent != nullptr) {
		this->find()->SellCar(typeID, k);
		return;
	}
	if (!score_tree.contains(typeID)) {
		score_tree.insert(typeID, k);
		doubleInt new_double = doubleInt(k, typeID);
		final_tree.insert(new_double, new_double);
		return;
	}
	int old_score = score_tree.get_value(typeID);
	int new_score = old_score + k;
	doubleInt old_double = doubleInt(old_score, typeID);
	doubleInt new_double = doubleInt(new_score, typeID);
	score_tree.remove(typeID);
	final_tree.remove(old_double);
	score_tree.insert(typeID, new_score);
	final_tree.insert(new_double, new_double);

}

void Union::Agency::Unite(Union::Agency* agency) {
	if (score_tree.get_root() != nullptr && agency->score_tree.get_root() != nullptr) {
		Tree<int, int> new_score_tree(unite(score_tree, agency->score_tree));
		Tree<doubleInt, doubleInt> new_final_tree(unite(final_tree, agency->final_tree));

		score_tree.~Tree();
		final_tree.~Tree();

		agency->score_tree.~Tree();
		agency->final_tree.~Tree();

		if (rank >= agency->rank) {
			rank = rank + agency->rank;
			agency->rank = 0;
			agency->parent = this;
			score_tree = new_score_tree;
			final_tree = new_final_tree;
			return;
		}
		agency->rank = rank + agency->rank;
		rank = 0;
		parent = agency;
		agency->score_tree = new_score_tree;
		agency->final_tree = new_final_tree;
		return;
	}
	if (score_tree.get_root() == nullptr && agency->score_tree.get_root() == nullptr) {
		if (rank >= agency->rank) {
			rank = rank + agency->rank;
			agency->rank = 0;
			agency->parent = this;
			return;
		}
		agency->rank = rank + agency->rank;
		rank = 0;
		parent = agency;
		return;
	}
	if (score_tree.get_root() == nullptr) {
		if (rank >= agency->rank) {
			rank = rank + agency->rank;
			agency->rank = 0;
			agency->parent = this;
			score_tree = agency->score_tree;
			final_tree = agency->final_tree;
			agency->score_tree.~Tree();
			agency->final_tree.~Tree();
			return;
		}
		agency->rank = rank + agency->rank;
		rank = 0;
		parent = agency;
		return;
	}
	else {
		if (rank >= agency->rank) {
			rank = rank + agency->rank;
			agency->rank = 0;
			agency->parent = this;
			
			return;
		}
		agency->rank = rank + agency->rank;
		rank = 0;
		parent = agency;
		agency->score_tree = score_tree;
		agency->final_tree = final_tree;
		score_tree.~Tree();
		final_tree.~Tree();
		return;
	}
}

void Union::Agency::UniteAgencies(Union::Agency* agency) {
	this->find()->Unite(agency->find());
}

bool Union::Agency::GetIthSoldTypeNew(int i, int* res) {
	doubleInt* copy = (doubleInt*)malloc(sizeof(doubleInt));
	if (final_tree.get_ith_value(i, copy)) {
		res[0] = copy[0].get_number();
		free(copy);
		return true;
	}
	free(copy);
	return false;
}

bool Union::Agency::GetIthSoldType(int i, int* res) {
	return this->find()->GetIthSoldTypeNew(i, res);
}
