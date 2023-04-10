#include <iostream>
#include <string>
#include <tuple>

#include "Move.h"
#include "MoveDatabase.h"


map<Category, string> CategoryStr = {
	{ PHYSICAL, "Physical" },
	{ SPECIAL, "Special" },
	{ STATUS, "Status" }
};

string getCategoryString(Category category) {
	return CategoryStr.at(category);
}

Move::Move(string name) {
	tuple<int, int, int, Type, Category> move = MoveData.at(name);
	mName = name;
	mBasePower = get<0>(move);
	mBaseAccuracy = get<1>(move);
	mBasePP = get<2>(move);
	mType = get<3>(move);
	mCategory = get<4>(move);
}

string Move::getMoveName() {
	return mName;
}

int Move::getBasePower() {
	return mBasePower;
}

int Move::getBaseAccuracy() {
	return mBaseAccuracy;
}

int Move::getBasePP() {
	return mBasePP;
}

int Move::getPriority() {
	return mPriority;
}

Type Move::getType() {
	return mType;
}

Category Move::getCategory() {
	return mCategory;
}

void Move::print() {
	cout << getMoveName() << '\n';
	cout << getTypeString(getType()) << "  " << getCategoryString(getCategory()) << '\n';
	cout << "  Base Power: " << getBasePower() << '\n';
	cout << "  Base Accuracy: " << getBaseAccuracy() << '\n';
	cout << "  Base PP: " << getBasePP() << '\n';

}
