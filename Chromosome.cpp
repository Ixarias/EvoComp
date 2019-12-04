#include "Chromosome.h"

Chromosome::Chromosome(vector<int> MS) {
	chr = generateChr(MS);
	fit = evaluateFit(MS);
}

Chromosome::Chromosome(string chromo, string index, vector<int> MS) {
	chr = chromo;
	ind = index;
	fit = evaluateFit(MS);
}

string Chromosome::generateChr(vector<int> MS) {
	return chromo;
}

string Chromosome::getChr() {
	return chr;
}

int Chromosome::evaluateFit(vector<int> MS) {
	return fitness;
}

int Chromosome::getFit() {
	return fit;
}

string Chromosome::getIndex() {
	return ind;
}

Chromosome Chromosome::Mutate(vector< vector<int> > MS) {
	return newchr;
}

Chromosome Chromosome::Crossover(Chromosome otherchr, vector< vector<int> > MS) {
	return newchr;
}

bool Chromosome::operator<(Chromosome otherchr) {
	return fit < otherchr.getFit();
}

int Chromosome::randnum(int start, int end, vector<int> excep = vector<int>({ -1 })) {
	int range = (end - start);
	int random_int = start + (rand() % range);
	if (std::find(excep.begin(), excep.end(), random_int) != excep.end()) {
		random_int = randnum(start, end, excep);
	}
	return random_int;
}
