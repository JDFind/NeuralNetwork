#include "Layer.h"

//protected
Layer::Layer(int numRealNeurons, int numPreviousRealNeurons, int layerType) {

	//take in consideration the bias neuron
	for (unsigned int neuronNum = 0; neuronNum < numRealNeurons + 1; neuronNum++) {

		bool isBiasNeuron = (neuronNum == numRealNeurons);

		switch (layerType) {
			
			case LAYER_TYPE_INPUT:
				mNeurons.push_back(Neuron(1, true, isBiasNeuron));
				break;
			
			case LAYER_TYPE_HIDDEN:
			case LAYER_TYPE_OUTPUT:
				mNeurons.push_back(Neuron(numPreviousRealNeurons, false, isBiasNeuron));
				break;

			default:
				throw runtime_error("Invalid neuron type provided");
				break;
		}
	}

	mType = layerType;
}

//protected
vector<double> Layer::getOutputs(vector<double> inputVals) {

	vector<double> outputs;

	for (unsigned int neuronNum = 0; neuronNum < mNeurons.size(); neuronNum++) {

		Neuron *currentNeuron = &mNeurons.at(neuronNum);
		double output;

		if (this->mType == LAYER_TYPE_INPUT) {

			//echivalent cu neuronNum == mNeurons.size() - 1
			if (currentNeuron->isBiasNeuron == true) {

				//FIXME: cod urat
				output = 1.0;
			}
			else {

				vector<double> tempInput;
				tempInput.push_back(inputVals.at(neuronNum));

				output = currentNeuron->calculateOutput(tempInput);
			}
		}
		else {
			output = currentNeuron->calculateOutput(inputVals);
		}

		outputs.push_back(output);
	}

	return outputs;
}

//protected
void Layer::updateNeurons(const Layer *nextLayer, const Layer *previousLayer, const vector<double> *expectedValues) {

	//ignore bias neuron
	for (unsigned int neuronNum = 0; neuronNum < mNeurons.size() - 1; neuronNum++) {

		Neuron *currentNeuron = &mNeurons.at(neuronNum);

		if (mType == LAYER_TYPE_OUTPUT) {
			currentNeuron->updateGradient(expectedValues->at(neuronNum));
		}
		else {
			currentNeuron->updateGradient(neuronNum, &(nextLayer->mNeurons));
		}

		if (mType != LAYER_TYPE_INPUT) {
			currentNeuron->updateWeights(&(previousLayer->mNeurons));
		}
	}
}

//protected
int Layer::getType() {
	return mType;
}

//protected
Layer::~Layer() {
}
