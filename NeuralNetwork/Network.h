#pragma once

#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include "Layer.h"

using namespace std;

//FIXME: nu este folosita
//TODO: ar trebui sa o folosesc?
typedef struct normalizationParameters {

	//TODO: cat sa le pun?
	//FIXME: strica convergenta
	const double MIN_RANGE = -0.0;
	const double MAX_RANGE = 0.5;

	double expectedMin = 0.0;
	double expectedMax = 0.0;

} normParams;


class Network {

	private:

		int mNumLayers = 0;

		vector<Layer> mLayers;
		vector<double> mCurrentInput;
		vector<double> mCurrentOutput;

		normParams normalization;

		void normalizeInput(vector<double> *inputVals);
		void denormalizeOutput(vector<double> *outputVals);

		vector<double> frontPropagation();

	public:

		Network(Layer inputNeurons, vector<Layer> hiddenLayer, Layer outputNeurons);
		~Network();

		void setNormalization(double expectedMin, double ExpectedMax);
		void feedInput(vector<double> inputVals);

		void backPropagation(vector<double> outputValues, vector<double> expectedValues);
		double calculateRMSError(vector<double> outputValues, vector<double> expectedValues);
		
		vector<double> getOutput();
};

#endif

