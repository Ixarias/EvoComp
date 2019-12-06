#include "Chromosome.h"

Chromosome::Chromosome(vector<Point> nodes, vector< vector<int> > clusterList) {
	chr = generateChr(nodes, clusterList);
	// fit = evaluateFit(nodes);
}

Chromosome::Chromosome(vector<int> chromo, vector<Point> nodes) {
	chr = chromo;
	// fit = evaluateFit(nodes);
}

vector<int> Chromosome::generateChr(vector<Point> nodes, vector< vector<int> > clusterList) {
	vector<int> chromo;
	for(int i = 0; i < clusterList.size(); i++) {
		int rnum = randnum(0, clusterList[i].size());
		chromo.push_back(clusterList[i][rnum]);
	}
	return chromo;
}

vector<int> Chromosome::getChr() {
	return chr;
}

int Chromosome::evaluateFit(vector<Point> nodes) {
	int fitness = 0;
	int total = 0;
	int e = (chr.size()*(chr.size()-1))/2;
	Kruskal kru;
	Kruskal::Graph* graph = kru.createGraph(chr.size(), e);
	for (int i = 0; i < chr.size(); i++) {
		for (int j = 0; j < chr.size(); j++) {
			if(j != i) {
				graph->edge[total].source =  0;
				graph->edge[total].dest = 0;
				graph->edge[total].weight = 0;
			}
		}
	}
	return fitness;
}

int Chromosome::getFit() {
	return fit;
}

void Chromosome::Mutate(vector<Point> nodes, vector< vector<int> > clusterList) {
	/*Chromosome newchr(nodes, clusterList);
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
	}*/
}

void Chromosome::Crossover(Chromosome& otherchr, vector<Point> nodes, vector< vector<int> > clusterList) {
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
