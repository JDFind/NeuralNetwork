
#include <iostream>
#include <fstream>
#include <time.h>
#include "Network.h"
#include "Trainer.h"
#include "Menu.h"

using namespace std;

//FIXME: Uneori nu converge nici dupa 10^6 iteratii
//TODO: de ce?

int exit() {

	cout << endl;
	system("PAUSE");
	return 0;
}

void createNetwork(Network **pNetwork) {

	if (*pNetwork != nullptr) {

		delete *pNetwork;
	}

	Layer inputLayer(2, 0, LAYER_TYPE_INPUT);

	vector<Layer> hiddenLayers;
	hiddenLayers.push_back(Layer(4, 2, LAYER_TYPE_HIDDEN));
	hiddenLayers.push_back(Layer(2, 4, LAYER_TYPE_HIDDEN));

	Layer outputLayer(1, 2, LAYER_TYPE_OUTPUT);

	*pNetwork = new Network(inputLayer, hiddenLayers, outputLayer);
	(*pNetwork)->setNormalization(0, 1);

	cout << "New network created" << endl;
}

void trainNetwork(Network *network, bool lightTraining) {

	if (network == nullptr) {

		cout << "Network not initialised." << endl;
		return;
	}

	unsigned long int numIterations;

	if (lightTraining) {
		numIterations = pow(10, 4) * 1;
	}
	else {
		numIterations = pow(10, 5) * 5;
	}

	cout << endl;
	cout << "Training neural network in " << numIterations << " iterations" << endl;

	float startTime = float(clock());

	double meanError;
	meanError = runXOR(network, numIterations, true);

	float timeDiff = float(clock() - startTime) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "Training complete (" << timeDiff << " s)" << endl;

	//intamplator, avand valori de la 0 la 1, RMS este egal cu eroarea relativa medie
	cout << "Mean percentage error for last 10%: " << meanError * 100 << "%"<< endl;

	if ((lightTraining && meanError > 0.2) || (!lightTraining && meanError > 0.10)) {

		cout << endl;
		cout << "This neural network is a failure!" << endl;
	}
}

void testNetwork(Network *network) {

	if (network == nullptr) {

		cout << "Network not initialised." << endl;
		return;
	}

	unsigned long int numIterations;

	numIterations = 100;

	cout << endl;
	cout << "Testing neural network with " << numIterations << " iterations" << endl;

	float startTime = float(clock());

	double meanError;
	meanError = runXOR(network, numIterations, false);

	float timeDiff = float(clock() - startTime) / CLOCKS_PER_SEC;

	cout << endl;
	cout << "Testing complete (" << timeDiff << " s)" << endl;

	//intamplator, avand valori de la 0 la 1, RMS este egal cu eroarea relativa medie
	cout << "Mean percentage error: " << meanError * 100 << "%" << endl;
}

void useNetwork(Network *network) {

	if (network == nullptr) {

		cout << "Network not initialised." << endl;
		return;
	}

	int key = 1;

	do {
		vector<double> input;
		int a, b;

		cout << endl;
		cout << "Solve xOR" << endl;
		cout << "Enter value 1: ";
		cin >> a;
		cout << "Enter value 2: ";
		cin >> b;

		input.push_back(a);
		input.push_back(b);

		network->feedInput(input);

		vector<double> output = network->getOutput();
		network->denormalizeOutput(&output);
		cout << "Result: " << output.front() << endl;

		cout << endl;
		cout << "Press 0 to go back to menu" << endl;
		cin >> key;
	} while (key != 0);
}

void discardNetwork(Network **network) {

	delete *network;
	*network = nullptr;

	cout << "Network discarded" << endl;
}

int main() {

	cout << "Hello" << endl;

	displayMenu();

	unsigned short int key = 0;
	Network *network = nullptr;

	do {

		cout << endl;
		cout << "select: ";
		cin >> key;

		switch (key) {

			case MENU_OPTION_DISPLAY:
				displayMenu();
				break;

			case MENU_OPTION_CREATE_NEWTORK:
				createNetwork(&network);
				break;

			case MENU_OPTION_LIGHT_TRAIN_XOR:
				trainNetwork(network, true);
				break;

			case MENU_OPTION_HEAVY_TRAIN_XOR:
				trainNetwork(network, false);
				break;

			case MENU_OPTION_TEST_XOR:
				testNetwork(network);
				break;

			case MENU_OPTION_USE_XOR:
				useNetwork(network);
				break;

			case MENU_OPTION_DISCARD_NETWORk:
				discardNetwork(&network);
				break;

			case MENU_OPTION_CLOSE_PROGRAM:
				break;

			default:
				cout << "Invalid option" << endl;
				break;
		}
	} while (key != MENU_OPTION_CLOSE_PROGRAM);

	return exit();
}