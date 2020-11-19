#include "Chromosome.h"

Chromosome::Chromosome(vector<Point> nodes, vector< vector<int> > clusterList) {
	chr = generateChr(nodes, clusterList);
	fit = evaluateFit(nodes, clusterList);
}

Chromosome::Chromosome(vector<int> chromo, vector<Point> nodes, vector< vector<int> > clusterList) {
	chr = chromo;
	fit = evaluateFit(nodes, clusterList);
}

Chromosome::Chromosome(const Chromosome* chromo) {
	chr = chromo->chr;
	fit = chromo->fit;
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

int Chromosome::evaluateFit(vector<Point> nodes, vector< vector<int> > clusterList) {
	int total = 0;
	int e = (chr.size()*(chr.size()-1))/2;
	Graph* graph = createGraph(chr.size(), e);
	for (int i = 0; i < chr.size(); i++) {
		for (int j = i+1; j < chr.size(); j++) {
			graph->edge[total].source = i;
			graph->edge[total].dest = j;
			graph->edge[total].weight = nodes[chr[i]-1].edges[chr[j]-1].weight;
			total++;
		}
	}
	return KruskalMST(graph);
}

int Chromosome::getFit() {
	return fit;
}

void Chromosome::Mutate(vector<Point> nodes, vector< vector<int> > clusterList) {
	Chromosome newchr(this);
	for (unsigned int i = 0; i < chr.size(); i++) {
		if (randnum(1, chr.size() + 1) == chr.size()) {
			int avoid = chr.at(i);
			if (clusterList[i].size() > 1) {
				while (chr.at(i) == avoid) {
					int rnum = randnum(0, clusterList[i].size());
					chr.at(i) = clusterList[i][rnum];
				}
			}
		}
	}
	this->fit = this->evaluateFit(nodes, clusterList);
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
	for(int i = 1; i < chr.size(); i++) {
		if(start <= i && i <= end) {
			chr.at(i) = otherchrc.at(i);
		}
	}
	for (int i = 1; i < chr.size(); i++) {
		if (start <= i && i <= end) {
			otherchr.chr.at(i) = chrc.at(i);

		}
	}
	this->fit = this->evaluateFit(nodes, clusterList);
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
