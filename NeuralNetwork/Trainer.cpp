
#include "Trainer.h"

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

double trainForXOR(Network *network, unsigned long int maxRuns) {

	ofstream outputFile;
	/*string fileName = "output" + to_string(threadIndex) + ".txt";*/
	string fileName = "output_xor.txt";
	outputFile.open(fileName, ios::out);

	vector<double> input;
	vector<double> expectedOutput;

	double meanError = 0.0;

	for (unsigned long int run = 1; run <= maxRuns; run++) {

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

		double error = 0.0;

		if (run >= maxRuns - pow(10, 2) || run <= pow(10, 2)) {

			error = network->calculateError(output, expectedOutput);
			logTrainingToFile(run, input, output.front(), expectedOutput.front(), error, &outputFile);
		}

		if (run % (maxRuns / 10) == 0) {

			cout << (double)run / (double)maxRuns * 100 << "%" << "\t";
		}

		if ((double)run / (double)maxRuns >= 0.9) {

			error = network->calculateRMSError(output, expectedOutput);
			meanError += error;
		}

		network->backPropagation(output, expectedOutput);
	}

	outputFile.close();

	return meanError / (0.1 * maxRuns);
}