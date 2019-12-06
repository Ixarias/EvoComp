#include "Chromosome.h"
#include "Kruskal.h"

Chromosome::Chromosome(vector< vector<float> > edgeLength, vector<int> clusterList) {
	chr = generateChr(edgeLength, clusterList);
	// fit = evaluateFit(edgeLength);
}

Chromosome::Chromosome(vector<int> chromo, vector< vector<float> > edgeLength) {
	chr = chromo;
	// fit = evaluateFit(edgeLength);
}

vector<int> Chromosome::generateChr(vector< vector<float> > edgeLength, vector<int> clusterList) {
	vector<int> chromo;
	int prevend = 0;
	for (unsigned int i = 0; i < clusterList.size(); i++) {
			int start = 0 + prevend;
			int end = start + clusterList[i];
			int node = randnum(start, end);
			chromo.push_back(node);
			prevend = end;
	}
	return chromo;
}

vector<int> Chromosome::getChr() {
	return chr;
}

int Chromosome::evaluateFit(vector< vector<float> > edgeLength) {
	int fitness = 0;

	return fitness;
}

int Chromosome::getFit() {
	return fit;
}

void Chromosome::Mutate(vector< vector<float> > edgeLength, vector<int> clusterList) {
	Chromosome newchr(edgeLength, clusterList);
		int prevend = 0;
	for (unsigned int i = 0; i < clusterList.size(); i++) {
		int start = 0 + prevend;
		int end = start + clusterList[i];
		if (randnum(1, clusterList.size() + 1) == clusterList.size()) {
			int avoid = chr.at(i);
			while (chr.at(i) == avoid) {
				int node = randnum(start, end);
				chr.at(i) = node;
			}
		}
		prevend = end;
	}
}

void Chromosome::Crossover(Chromosome& otherchr, vector< vector<float> > edgeLength, vector<int> clusterList) {
	vector<int> chrc = chr;
	vector<int> otherchrc = otherchr.getChr();
	int start = randnum(0, chr.size()) + 1;
	int end = randnum(0, chr.size()) + 1;
	while (end == start) {
		end = randnum(0, chr.size()) + 1;
	}
	if (start > end) {
		int temp = end;
		end = start;
		start = temp;
	}
	cout << "start: " << start << "end: " << end << endl;
	for(int i = 1; i < chr.size(); i++) {
		if(start <= i && i <= end) {
			chr.at(i) = otherchrc.at(i);
		}
	}
	for(int i = 1; i < chr.size(); i++) {
		if(start <= i && i <= end) {
			otherchr.chr.at(i) = chrc.at(i);
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
