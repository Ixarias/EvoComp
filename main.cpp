#ifndef INCLUDE
#define INCLUDE

#include<vector>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>

#endif

using namespace std;

#include "Chromosome.h"

#define POP_SIZE 10

int main() {
	// Seed
	srand(time(nullptr));

	// Variables
	vector< vector<int> > MachineSequences;
	vector< vector<int> > ProcessingTime;
	vector<Chromosome> chromosomes;

	ifstream infile;
	ifstream infile2;

	// Input File #1
	infile.open("MachineSequences.txt", ifstream::in);
	if (infile.is_open()) {
		cout << "MachineSequences.txt is open" << endl;
	}
	string line;
	int i = 0;
	while (getline(infile, line)) {
		for (unsigned int j = 0; j < line.length(); j++) {
			MachineSequences[i][j] = (int)line[j];
		}
		cout << "MachineSequences.txt line" << endl;
		i++;
	}
	infile.close();
	if (!infile.is_open()) {
		cout << "MachineSequences.txt is closed" << endl;
	}

	// Input File #2
	infile2.open("ProcessingTime.txt", ifstream::in);
	if (infile2.is_open()) {
		cout << "ProcessingTime.txt is open" << endl;
	}
  i = 0;
	while (getline(infile2, line)) {
		for (unsigned int j = 0; j < line.length(); j++) {
			ProcessingTime[i][j] = (int)line[j];
		}
		cout << "ProcessingTime.txt line" << endl;
		i++;
	}
	infile2.close();
	if (!infile2.is_open()) {
		cout << "ProcessingTime.txt is closed" << endl;
	}

	for (i = 0; i < POP_SIZE; i++) {
		Chromosome chr(MachineSequences, ProcessingTime);
		chromosomes.push_back(chr);
		cout << chr.getChr() << endl;
	}

	return 0;
}
