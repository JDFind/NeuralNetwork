
#include "RandomHandler.h"

RandomHandler::RandomHandler() {

	randomEngine.seed(randomDevice());
}

RandomHandler & RandomHandler::getInstance() {

	static RandomHandler mInstance;

	return mInstance;
}

double RandomHandler::getRealUniform(double min, double max) {

	uniform_real_distribution<> distribution(min, max);
			
	return (double) distribution(randomEngine);
}

double RandomHandler::getRealNormal(double min, double max) {

	normal_distribution<> distribution(min, max);

	return (double)distribution(randomEngine);
}