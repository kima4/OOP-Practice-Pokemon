#include <iostream>

#include "Testing.h"
#include "../TypeInfo/Types.h"



//--------------------- TypeInfo Tests ---------------------//

// conversion of Type to string
void ConvertFire() {
	string result = getTypeString(FIRE);
	string expected = "Fire";
	
	IS_TRUE(result == expected);
}
















int main() {
	ConvertFire();

	return 0;
}