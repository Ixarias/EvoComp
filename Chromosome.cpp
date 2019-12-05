#include "Chromosome.h"
#include "kruskal.cpp"

Chromosome::Chromosome(vector< vector<int> > edgeLength, vector<int> clusterSizes) {
	chr = generateChr(edgeLength, clusterSizes);
	// fit = evaluateFit(edgeLength);
}

Chromosome::Chromosome(vector<int> chromo, vector< vector<int> > edgeLength) {
	chr = chromo;
	// fit = evaluateFit(edgeLength);
}

vector<int> Chromosome::generateChr(vector< vector<int> > edgeLength, vector<int> clusterSizes) {
	vector<int> chromo;
	int prevend = 0;
	for (unsigned int i = 0; i < clusterSizes.size(); i++) {
			int start = 0 + prevend;
			int end = start + clusterSizes[i];
			int node = randnum(start, end);
			chromo.push_back(node);
			prevend = end;
	}
	return chromo;
}

vector<int> Chromosome::getChr() {
	return chr;
}

int Chromosome::evaluateFit(vector< vector<int> > edgeLength) {
	int fitness = 0;

	return fitness;
}

int Chromosome::getFit() {
	return fit;
}

Chromosome Chromosome::Mutate(vector< vector<int> > edgeLength, vector<int> clusterSizes) {
	Chromosome newchr(edgeLength, clusterSizes);
	return newchr;
}

Chromosome Chromosome::Crossover(Chromosome otherchr, vector< vector<int> > edgeLength, vector<int> clusterSizes) {
	Chromosome newchr(edgeLength, clusterSizes);
	return newchr;
}

bool Chromosome::operator<(Chromosome otherchr) {
	return fit < otherchr.getFit();
}

int Chromosome::randnum(int start, int end, vector<int> excep) {
	int range = (end - start);
	int random_int = start + (rand() % range);
	if (std::find(excep.begin(), excep.end(), random_int) != excep.end()) {
		random_int = randnum(start, end, excep);
	}
	return random_int;
}
