#include "Network.h"

//public
Network::Network(Layer inputNeurons, vector<Layer> hiddenLayers, Layer outputNeurons) {

	mLayers.push_back(inputNeurons);
	mNumLayers += 1;

	//TODO: Un while ar fi mai potrivit
	for (unsigned int currentLayer = 0; currentLayer < hiddenLayers.size(); currentLayer++) {

		mLayers.push_back(hiddenLayers.at(currentLayer));
		mNumLayers++;
	}
	
	mLayers.push_back(outputNeurons);
	mNumLayers += 1;
}

//public
void Network::setNormalization(double expectedMin, double expectedMax) {

	if (expectedMin == expectedMax) {

		//TODO: ar trebui sa fac return dupa asta?
		throw runtime_error("Invalid data range provided");
	}

	normalization.expectedMin = expectedMin;
	normalization.expectedMax = expectedMax;
}

//public
void Network::feedInput(vector<double> inputVals) {

	//for (auto &input : inputVals) {

	//	input = normalizeInput(input);
	//}

	mCurrentInput = inputVals;

	mCurrentOutput = frontPropagation();
}

//public
vector<double> Network::getOutput() {

	return mCurrentOutput;
}

//private
double Network::normalizeInput(double value) {

	double result = (normalization.MIN_RANGE - normalization.MAX_RANGE) / (normalization.expectedMin - normalization.expectedMax) * value
		+ normalization.MAX_RANGE * (normalization.expectedMin + normalization.expectedMax) / (normalization.expectedMin - normalization.expectedMax);

	return result;
}

//private
double Network::deNormalizeOutput(double value) {

	//functia inversa a celei folosite in normalizeInput()
	double result = (value - normalization.MAX_RANGE * (normalization.expectedMin + normalization.expectedMax))
		- (normalization.MIN_RANGE - normalization.MAX_RANGE);

	return result;
}

//private
vector<double> Network::frontPropagation() {

	Layer *inputLayer = &mLayers.at(0);

	if (inputLayer->getType() != LAYER_TYPE_INPUT) {
		throw runtime_error("The first layer is not the input layer");
	}

	vector<double> currentOutput = inputLayer->getOutputs(mCurrentInput);

	for (unsigned int numLayer = 1; numLayer < mNumLayers; numLayer++) {

		currentOutput = mLayers.at(numLayer).getOutputs(currentOutput);
	}

	////input primeste referinta
	//for (auto &output : currentOutput) {

	//	output = deNormalizeOutput(output);
	//}

	return currentOutput;
}

//public
double Network::calculateError(vector<double> outputValues, vector<double> expectedValues) {

	Layer *outputLayer = &mLayers.back();

	double error = 0.0;

	//ignore bias neurons
	for (unsigned int neuronNum = 0; neuronNum < outputLayer->mNeurons.size() - 1; neuronNum++) {

		double delta = outputValues.at(neuronNum) - expectedValues.at(neuronNum);
		error += pow(delta, 2);
	}

	/*
	@deprecated

	//ignore bias neurons
	error /= outputLayer->mNeurons.size() - 1;
	error = sqrt(error); //average RMS

	//In cazul meu, eroarea are veni error / 1
	//In multe locuri am vazut eroarea calculata cu 1/2 * sum (...)
	*/

	error /= 2;

	return error;
}

//public
void Network::backPropagation(vector<double> outputValues, vector<double> expectedValues) {

	Layer *currentLayer = nullptr;
	Layer *nextLayer = nullptr;
	Layer *previousLayer = nullptr;

	for (unsigned int layerNum = mLayers.size() - 1; layerNum > 0; layerNum--) {

		currentLayer = &mLayers.at(layerNum);

		if (layerNum < mLayers.size() - 1) {
			nextLayer = &mLayers.at(layerNum + 1);
		}

		if (layerNum > 0) {
			previousLayer = &mLayers.at(layerNum - 1);
		}

		currentLayer->updateNeurons(nextLayer, previousLayer, &expectedValues);
	}
}

//public
Network::~Network() {
}
