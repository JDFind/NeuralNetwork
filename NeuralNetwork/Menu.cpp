#include "Menu.h"

void displayMenu() {

	cout << endl;
	cout << "Menu" << endl;
	cout << "[" << MENU_OPTION_DISPLAY << "]" << " Display menu" << endl;
	cout << "[" << MENU_OPTION_CREATE_NEWTORK << "]" << " Create new network" << endl;
	cout << "[" << MENU_OPTION_LIGHT_TRAIN_XOR << "]" << " Train for xOR - QUICK" << endl;
	cout << "[" << MENU_OPTION_HEAVY_TRAIN_XOR << "]" << " Train for xOR - Thorough" << endl;
	cout << "[" << MENU_OPTION_TEST_XOR << "]" << " Test for xOR" << endl;
	cout << "[" << MENU_OPTION_USE_XOR << "]" << " Use NN" << endl;
	cout << "[" << MENU_OPTION_DISCARD_NETWORk << "]" << " Discard current NN" << endl;
	cout << "[" << MENU_OPTION_CLOSE_PROGRAM << "]" << " Terminate program" << endl;
}