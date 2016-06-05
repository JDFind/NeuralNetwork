
#include "RandomHandler.h"

RandomHandler::RandomHandler() {

	randomEngine.seed(randomDevice());
}

RandomHandler & RandomHandler::getInstance() {

	static RandomHandler mInstance;

	return mInstance;
}

double RandomHandler::getRealRandom(double min, double max) {

	uniform_real_distribution<> distribution(min, max);
			
	return (double) distribution(randomEngine);
}