#pragma once

#ifndef RANDOM_HANDLER
#define RANDOM_HANDLER

#include <random>

using namespace std;

class RandomHandler {

	private:

		random_device randomDevice;
		mt19937 randomEngine;

		RandomHandler();

	public:

		// C++ 11
		// =======
		// You want to make sure they
		// are unacceptable otherwise you may accidentally get copies of
		// your singleton appearing.
		// We can use the better technique of deleting the methods
		// we don't want.
		RandomHandler(RandomHandler const&) = delete;
		void operator=(RandomHandler const&) = delete;

		static RandomHandler &getInstance();

		double getRealRandom(double min, double max);
};

#endif