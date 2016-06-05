#pragma once

#ifndef NEURON_H
#define NEURON_H

#include <cmath>
#include <vector>
#include "RandomHandler.h"

using namespace std;

const double eta = 0.25; //learing rage
const double alpha = 0.5; //momentum rate

const double MIN_WEIGHT = -10.0;
const double MAX_WEIGHT = 10.0;

//const double MIN_WEIGHT = -1.0;
//const double MAX_WEIGHT = 1.0;

class Neuron {

	friend class Layer;

	protected:

		Neuron(int numInputConnections, bool isInputNeuron, bool isBiasNeuron);

		double calculateOutput(vector<double> inputVals);

		void updateGradient(double expectedValue);
		void updateGradient(int currentNeuronIndex, const vector<Neuron> *nextLayerNeurons);
		
		void updateWeights(const vector<Neuron> *previousLayerNeurons);

	private:

		vector<double> mInputWeights;
		vector<double> mInputWeightsDelta;

		double mGradient = 0.0; //valoarea default a neuronului bias
		double mOutputValue = 1.0; //valoarea default a neuronului bias

		bool isInputNeuron = false;
		bool isBiasNeuron = false;

		double activation(double input);
};

#endif // !NEURON_H