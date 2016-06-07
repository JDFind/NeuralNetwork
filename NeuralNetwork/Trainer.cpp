
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

void setInput(vector<double> *input, unsigned long int currentRun) {

	//BEGIN construct input
	input->clear();

	int a;
	int b;

	switch (currentRun % 4) {

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

	input->push_back(a);
	input->push_back(b);
	//END
}

double runXOR(Network *network, unsigned long int maxRuns, bool trainNetwork) {

	ofstream outputFile;
	/*string fileName = "output" + to_string(threadIndex) + ".txt";*/
	string fileName = "output_xor.txt";
	outputFile.open(fileName, ios::out);

	vector<double> input;
	vector<double> expectedOutput;

	double meanError = 0.0;

	for (unsigned long int run = 1; run <= maxRuns; run++) {

		setInput(&input, run);

		network->feedInput(input);
		vector<double> output = network->getOutput();

		//FIXME: am un bias neuron in output (!)
		//if (output.size() != 1) {
		//	throw runtime_error("Invalid output received");
		//}

		expectedOutput.clear();
		expectedOutput.push_back(xor (input.front(), input.back()));
		network->normalizeInput(&expectedOutput);

		double error = 0.0;

		if (!trainNetwork || ((double)run / (double)maxRuns >= 0.9)) {

			error = network->calculateRMSError(output, expectedOutput);
			meanError += error;
		}

		if (trainNetwork) {

			if (run >= maxRuns - pow(10, 2) || run <= pow(10, 2)) {

				error = network->calculateRMSError(output, expectedOutput);

				vector<double> denormOutput = output;
				network->denormalizeOutput(&denormOutput);

				vector<double> denormExpectedOutput = expectedOutput;
				network->denormalizeOutput(&denormExpectedOutput);

				logTrainingToFile(run, input, denormOutput.front(), denormExpectedOutput.front(), error, &outputFile);
			}

			if (run % (maxRuns / 10) == 0) {

				cout << (double)run / (double)maxRuns * 100 << "%" << "\t";
			}

			network->backPropagation(output, expectedOutput);
		}
	}

	outputFile.close();

	if (trainNetwork) {
		meanError /= 0.1 * maxRuns;
	}
	else {
		meanError /= maxRuns;
	}

	return meanError;
}