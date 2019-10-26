#include "Chromosome.h"

Chromosome::Chromosome(vector< vector<int> > MS, vector< vector<int> > PT) {
	chr = generateChr(MS);
	fit = evaluateFit(MS, PT);
}

string Chromosome::generateChr(vector< vector<int> > MS) {
	string chromo = "";
	vector<int> lengthVector;
	for (unsigned int i = 0; i < MS.size(); i++) {
		lengthVector.push_back(MS[i].size());
	}
	bool full = false;
	vector<int> fullvec;
	while (!full) {
		if (fullvec.size() != MS.size()) {
			int rnum = randnum_with_excep(0, MS.size(), fullvec);
			if (MS[rnum].size() != 0) {
				char crnum = (char)rnum;
				chromo += crnum;
			}
			else {
				fullvec.push_back(rnum);
			}
		}
		else {
			full = true;
		}
	}
	return chromo;
}

string Chromosome::getChr() {
	return chr;
}

int Chromosome::evaluateFit(vector< vector<int> > MS, vector< vector<int> > PT) {
	int fitness = 0;
	for (unsigned int i = 1; i <= chr.length(); i++) {
		fitness = 0;
	}
	return fitness;
}

int Chromosome::getFit() {
	return fit;
}

void Chromosome::Mutate() {
	string chromo = "0";
	chr = chromo;
}

void Chromosome::Crossover() {
	string chromo = "0";
	chr = chromo;
}

int Chromosome::randnum_with_excep(int start, int end, vector<int> excep) {
	int range = (end - start);
	int random_int = start + (rand() % range);
	if (std::find(excep.begin(), excep.end(), random_int) != excep.end()) {
		random_int = randnum_with_excep(start, end, excep);
	}
	return random_int;
}
