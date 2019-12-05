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
	vector<int> chromo = chr;
		int prevend = 0;
	for (unsigned int i = 0; i < clusterSizes.size(); i++) {
		int start = 0 + prevend;
		int end = start + clusterSizes[i];
		if (randnum(1, clusterSizes.size() + 1) == clusterSizes.size()) {
`			while (chromo.at(i) == chr.at(i)) {
				int node = randnum(start, end);
				chromo.at(i) = node;
			}
		}
		prevend = end;
	}

	return chromo;
}

void Chromosome::Crossover(Chromosome& otherchr, vector< vector<int> > edgeLength, vector<int> clusterSizes) {
	vector<int> chrc = chr;
	vector<int> otherchrc = otherchr.getChr();
	int start = randnum(0, chr.size());
	int end = randnum(0, chr.size());
	while (end == start) {
		end = randnum(0, chr.size());
	}
	if (start > end) {
		int temp = end;
		end = start;
		start = temp;
	}
	for(int i = 0; i < chr.size(); i++) {
		if(start < i && i < end) {
			chr.at(i) = otherchrc.at(i);
		}
	}
	for(int i = 0; i < chr.size(); i++) {
		if(start < i && i < end) {
			otherchr.getChr().at(i) = chrc.at(i);
		}
	}
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
