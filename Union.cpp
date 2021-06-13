#include "Union.h"


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

Union::Agency* Union::Agency::find() {
	if (parent == nullptr)
		return this;
	return parent->find();
}
void Union::Agency::change_parent(Union::Agency* agency) {
	parent = agency;
}


bool Union::Agency::SellCar(int typeID, int k) {
	if (parent != nullptr)
		return this->find()->SellCar(typeID, k);
	if (!score_tree.contains(typeID)) {
		score_tree.insert(typeID, k);
		doubleInt new_double = doubleInt(typeID, k);
		final_tree.insert(new_double, new_double);
		return true;
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