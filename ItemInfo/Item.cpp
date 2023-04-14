#include <iostream>
#include <string>
#include <map>
#include <tuple>

#include "Item.h"
#include "ItemDatabase.h"


Item::Item(string name) : mName(name) {
	tuple<int, int> item = ItemData.at(name);
	mPrice = get<0>(item);
	mParameter = get<0>(item);
}

string Item::getItemName() {
	return mName;
}

int Item::getBuyPrice() {
	return mPrice;
}

int Item::getSellPrice() {
	return mPrice / 2;
}

int Item::getParameterVal() {
	return mParameter;
}

ItemType Item::getItemType() {
	return mItemType;
}

string Item::getItemTypeStr() {
	switch (mItemType) {
	case POKEBALL:
		return "Pokeball";
	case MEDICINE:
		return "Medicine";
	case TM:
		return "TM";
	case HM:
		return "HM";
	case BERRY:
		return "Berry";
	case HELD:
		return "Held Item";
	case BATTLE:
		return "Battle Item";
	case KEY:
		return "Key Item";
	default:
		return "Item";
	}
}

void Item::useInBattle() {
	cout << "Using in battle" << endl;
}

void Item::useOutOfBattle() {
	cout << "Using out of battle" << endl;
}


void Item::print() {
	cout << mName << endl;
	cout << "  Item Type: " << getItemTypeStr() << endl;
	cout << "  Buy Price: " << getBuyPrice() << endl;
	cout << "  Sell Price: " << getSellPrice() << endl;
}
