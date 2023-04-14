#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

enum ItemType { POKEBALL, MEDICINE, TM, HM, BERRY, HELD, BATTLE, KEY, MISC };

class Item {
public:
	Item(string name);

	string getItemName();

	int getBuyPrice();
	int getSellPrice();

	int getParameterVal();

	ItemType getItemType();
	string getItemTypeStr();

	virtual void useInBattle();
	virtual void useOutOfBattle();

	void print();

private:
	string mName;
	int mPrice;
	int mParameter;

	ItemType mItemType;


};


#endif