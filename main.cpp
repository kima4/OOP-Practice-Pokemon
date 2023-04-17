
#include "BattleInfo/BattleOverview.h"

void TestBattle() {
	vector<Pokemon*> party1;
	Pokemon* igglybuff = new Pokemon("Hitmonchan", 51);
	Pokemon* mewtwo = new Pokemon("Mewtwo", 4);
	Pokemon* jolteon = new Pokemon("Jolteon", 32);
	party1.push_back(igglybuff);
	party1.push_back(mewtwo);
	party1.push_back(jolteon);
	Trainer* trainer1 = new Trainer("Suzzane", party1);

	Pokemon* tyranitar = new Pokemon("Zapdos", 33);

	BattleOverview* battle = new BattleOverview(trainer1, tyranitar);
	battle->battle();

}

int main() {
	TestBattle();
	return 0;
}

