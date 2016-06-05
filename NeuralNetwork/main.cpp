
#include <iostream>
#include <fstream>
#include <string>
#include "RandomHandler.h"
#include "Network.h"

using namespace std;

//FIXME: Uneori nu converge nici dupa 10^6 iteratii
//TODO: de ce?

int exit() {

	cout << endl;
	system("PAUSE");
	return 0;
}

int xor(int a, int b) {

	return a ^ b;
}

void logTrainingToFile(int run, vector<double> input, double output, double expectedOutput, double error, ofstream *outputFile) {

	*outputFile << "Iteration: " << run << endl;
	*outputFile << "Input values: " << input.front() << " " << input.back() << endl;
	*outputFile << "Expected: " << expectedOutput << endl;
	*outputFile << "Network output: " << output << endl;
	*outputFile << "Error: " << error << endl;
	*outputFile << endl;
}

void trainNN(Network *network, unsigned long int maxRuns) {

	ofstream outputFile;
	/*string fileName = "output" + to_string(threadIndex) + ".txt";*/
	string fileName = "output.txt";
	outputFile.open(fileName, ios::out);

	vector<double> input;
	vector<double> expectedOutput;

	for (unsigned int run = 1; run <= maxRuns; run++) {

		input.clear();
		expectedOutput.clear();

		int a;
		int b;

		switch (run % 4) {

		case 1:
			a = 0;
			b = 0;
			break;

		case 2:
			a = 0;
			b = 1;
			break;

		case 3:
			a = 1;
			b = 0;
			break;

		case 0:
			a = 1;
			b = 1;
			break;
		}

		input.push_back(a);
		input.push_back(b);
		expectedOutput.push_back(xor (a, b));

		network->feedInput(input);

		vector<double> output = network->getOutput();

		//FIXME: am un bias neuron in output (!)

		//if (output.size() != 1) {
		//	throw runtime_error("Invalid output received");
		//}

		if (run >= maxRuns - pow(10, 2) || run <= pow(10, 2)) {

			double error = network->calculateError(output, expectedOutput);
			logTrainingToFile(run, input, output.front(), expectedOutput.front(), error, &outputFile);
		}

		if (run % (maxRuns / 10) == 0) {
			cout << (float)run / (float)maxRuns * 100 << "%" << "\t";
		}

		network->backPropagation(output, expectedOutput);
	}

	outputFile.close();
}

int main() {

	cout << "Hello" << endl;

	Layer inputLayer(2, 0, LAYER_TYPE_INPUT);
	
	vector<Layer> hiddenLayers;
	hiddenLayers.push_back(Layer(4, 2, LAYER_TYPE_HIDDEN));
	hiddenLayers.push_back(Layer(3, 4, LAYER_TYPE_HIDDEN));

	Layer outputLayer(1, 3, LAYER_TYPE_OUTPUT);
	
	Network network(inputLayer, hiddenLayers, outputLayer);
	network.setNormalization(0, 1);

	trainNN(&network, pow(10, 5) * 5);

	cout << "Neural network is trained." << endl;

	int key;

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

		network.feedInput(input);
		cout << "Result: " << network.getOutput().front() << endl;

		cout << "Press 0 to exit or 1 to continue." << endl;
		cin >> key;
	} while (key != 0);

	return exit();
}