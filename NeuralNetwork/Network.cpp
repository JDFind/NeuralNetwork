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
void Network::normalizeInput(vector<double> *inputVals) {

	for (auto &value : *inputVals) {

		value =
			(normalization.MIN_RANGE - normalization.MAX_RANGE) / (normalization.expectedMin - normalization.expectedMax)
			* value
			+ normalization.MAX_RANGE
			* (normalization.expectedMin + normalization.expectedMax) / (normalization.expectedMin - normalization.expectedMax);
	}
}

//private
//functia inversa a celei folosite in normalizeInput()
void Network::denormalizeOutput(vector<double> *outputVals) {

	for (auto &value : *outputVals) {

		value =
			value
			* (normalization.expectedMin - normalization.expectedMax) / (normalization.MIN_RANGE - normalization.MAX_RANGE)
			- normalization.MAX_RANGE
			* (normalization.expectedMin + normalization.expectedMax) / (normalization.MIN_RANGE - normalization.MAX_RANGE);
	}
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
//functia NU este apelata pentru calculul gradientului
double Network::calculateRMSError(vector<double> outputValues, vector<double> expectedValues) {

	Layer *outputLayer = &mLayers.back();

	double error = 0.0;

	//ignore bias neurons
	unsigned int numNeurons = outputLayer->mNeurons.size() - 1;
	
	for (unsigned int neuronNum = 0; neuronNum < numNeurons; neuronNum++) {

		double delta = outputValues.at(neuronNum) - expectedValues.at(neuronNum);
		error += pow(delta, 2);
	}

	error = sqrt(error);
	error /= numNeurons;

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
