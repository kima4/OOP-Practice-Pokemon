#ifndef MOVE_H
#define MOVE_H

#include <string>

#include "../MiscInfo/Types.h"

using namespace std;


enum Category { PHYSICAL, SPECIAL, STATUS };

extern map<Category, string> CategoryStr;

string getCategoryString(Category category);


class Move {
public:
	Move(string name);
	void initMoveDetails(string name);

	string getMoveName();
	int getBasePower();
	int getBaseAccuracy();
	int getBasePP();
	int getPriority();
	int getCritRate();

	Type getType();
	Category getCategory();

	void print();


private:
	string mName;
	int mBasePower;
	int mBaseAccuracy;
	int mBasePP;
	int mPriority;
	int mCritRate;

	Type mType;
	Category mCategory;



};

#endif
