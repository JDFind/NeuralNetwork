#pragma once

#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <string>
#include <fstream>
#include "Network.h"


int xor(int a, int b);

void logTrainingToFile(int run, vector<double> input, double output, double expectedOutput, double error, ofstream *outputFile);

double trainForXOR(Network *network, unsigned long int maxRuns);

#endif