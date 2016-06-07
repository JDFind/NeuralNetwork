#pragma once

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <fstream>
#include "Network.h"

const unsigned short int MENU_OPTION_DISPLAY			= 0;
const unsigned short int MENU_OPTION_CREATE_NEWTORK		= 1;
const unsigned short int MENU_OPTION_LIGHT_TRAIN_XOR	= 2;
const unsigned short int MENU_OPTION_HEAVY_TRAIN_XOR	= 3;
const unsigned short int MENU_OPTION_TEST_XOR			= 4;
const unsigned short int MENU_OPTION_USE_XOR			= 5;
const unsigned short int MENU_OPTION_DISCARD_NETWORk	= 6;
const unsigned short int MENU_OPTION_CLOSE_PROGRAM		= 7;

void displayMenu();

#endif
