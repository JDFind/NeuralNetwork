
#include "Neuron.h"

//protected
Neuron::Neuron(int numRealInputConnections, bool isInputNeuron, bool isBiasNeuron) {

	this->isInputNeuron = isInputNeuron;
	this->isBiasNeuron = isBiasNeuron;

	if (this->isBiasNeuron) {
		return;
	}

	if (this->isInputNeuron) {

		mInputWeights.push_back(1.0);
		return;
	}

	//take in consideration the bias neuron
	for (unsigned int counter = 0; counter < numRealInputConnections + 1; counter++) {

		double randomWeight;

		//do {
			randomWeight = RandomHandler::getInstance().getRealUniform(MIN_WEIGHT, MAX_WEIGHT);
		//} while (randomWeight > 0.1 * MIN_WEIGHT && randomWeight < 0.1 * MAX_WEIGHT);

		mInputWeights.push_back(randomWeight);
		mInputWeightsDelta.push_back(0.0);
	}
}

//protected
double Neuron::calculateOutput(vector<double> inputVals) {

	if (isBiasNeuron) {
		return 1.0;
	}

	if (inputVals.size() != mInputWeights.size()) {
			
		//TODO: ar trebui sa fac return dupa asta?
		throw runtime_error("Different input values and input weights");
	}

	if (isInputNeuron) {
		return inputVals.back();
	}

	double sum = 0.0;

	//do NOT ignore bias neuron
	for (unsigned int counter = 0; counter < inputVals.size(); counter++) {

		double input = inputVals.at(counter);

		sum += inputVals.at(counter) * mInputWeights.at(counter);
	}

	mOutputValue = activation(sum);

	return mOutputValue;
}

//protected
//A se apela pentru neuronii de pe stratul de Output
void Neuron::updateGradient(double expectedValue) {

	if (isInputNeuron || isBiasNeuron) {
		throw runtime_error("Cannot update gradient of input or bias neurons");
	}

	//DELTAk = (1 - tanh^2(Xk)) * (Ok - Tk)
	mGradient = (1 - pow(mOutputValue, 2)) * (mOutputValue - expectedValue);
}

//protected
//A se apela pentru neuronii de pe straturile Hidden
void Neuron::updateGradient(int currentNeuronIndex, const vector<Neuron> *nextLayerNeurons) {

	if (isInputNeuron || isBiasNeuron) {
		throw runtime_error("Cannot update gradient of input or bias neurons");
	}

	//suma dupa k
	double dow = 0.0;

	//ignore bias neuron on next layer
	for (unsigned int neuronNum = 0; neuronNum < nextLayerNeurons->size() - 1; neuronNum++) {

		const Neuron *nextNeuron = &nextLayerNeurons->at(neuronNum);

		dow += nextNeuron->mGradient * nextNeuron->mInputWeights.at(currentNeuronIndex);
	}

	//DELTAj = (1 - tanh^2(Xj)) * sum(DELTAk * Wjk)
	mGradient = (1 - pow(mOutputValue, 2)) *  dow;
}

//protected
void Neuron::updateWeights(const vector<Neuron> *previousLayerNeurons) {

	if (isInputNeuron || isBiasNeuron) {
		throw runtime_error("Cannot update weights of input or bias neurons");
	}

	//do NOT ignore bias neuron on previous layer
	for (unsigned int prevNeuronNum = 0; prevNeuronNum < previousLayerNeurons->size(); prevNeuronNum++) {

		const Neuron *previousNeuron = &(previousLayerNeurons->at(prevNeuronNum));

		double oldWeightDelta = mInputWeightsDelta.at(prevNeuronNum);

		double newWeightDelta =
			//Individual input, magnified by gradient and train rate
			-eta
			* mGradient
			* previousNeuron->mOutputValue;
			//Add momentum
			+ alpha
			* oldWeightDelta;

		mInputWeightsDelta.at(prevNeuronNum) = newWeightDelta;
		mInputWeights.at(prevNeuronNum) += newWeightDelta;
	}
}

//private
double Neuron::activation(double input) {

	return tanh(input);
}