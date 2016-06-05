#pragma once

#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "Neuron.h"

using namespace std;

const int LAYER_TYPE_INPUT = 11;
const int LAYER_TYPE_HIDDEN = 12;
const int LAYER_TYPE_OUTPUT = 13;

class Layer {

	friend class Network;

	private:
			
		vector<Neuron> mNeurons;
		int mType;

	protected:

		vector<double> getOutputs(vector<double> inputVals);
		void updateNeurons(const Layer *nextLayer, const Layer *previousLayer, const vector<double> *expectedValues);
		int getType();

	public:
		Layer(int numNeurons, int numPreviousNeurons, int layerType);
		~Layer();
};

#endif