#ifndef INCLUDE
#define INCLUDE

#include<vector>
#include<string>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<cmath>
#include<sstream>
#include<iterator>

#endif

#include "Chromosome.h"
#include "Kruskal.h"
using namespace std;

#define POP_SIZE 100 //change later dickhead

vector<Chromosome> SortChr(vector<Chromosome> chromosomes) {
	std::sort(chromosomes.begin(), chromosomes.end());
	return chromosomes;
}

int randnum(int start, int end, vector<int> excep = { -1 }) {
	int range = (end - start);
	int random_int = start + (rand() % range);
	if (std::find(excep.begin(), excep.end(), random_int) != excep.end()) {
		random_int = randnum(start, end, excep);
	}
	return random_int;
}

bool check(const vector<vector<int>>& v, int item) {
	vector< vector<int> >::const_iterator row;
	for (row = v.begin(); row != v.end(); row++) {
		if (find(row->begin(), row->end(), item) != row->end())
			return true;
	}

	return false;
}

bool edgecomp (Edge i, Edge j) {
	return i.weight < j.weight;
}

int main(int argc, char* argv[]) {
	// Seed
	srand(time(nullptr));

	// all output in standard form
	cout << fixed;

	// Variables
	int clustersize = stoi(argv[2]);
	cout << clustersize << endl;
	vector<Point> nodes;
	vector< vector<int> > clusterList;
	vector<Chromosome> chromosomes;
	vector<Chromosome> chromosomes_next;
	int bestfit = 99999;
	int stalemate = 0;
	int gennum = 0;

	std::fstream infile(argv[1], ios_base::in);


	// Input instance
	if (infile.is_open()) {
		string line;
		vector<string> vecstr{};
		vector<float> vecfl{};
		int i = 0;
		while (std::getline(infile, line)) {
			vecstr.clear();
			vecfl.clear();
			istringstream iss(line);
			copy(istream_iterator<string>(iss),
     		istream_iterator<string>(),
     		back_inserter(vecstr));
			nodes.push_back(Point(stof(vecstr[0]), stof(vecstr[1]), stof(vecstr[2])));
			i++;
		}
		for(int i = 0; i < nodes.size(); i++) {
			for (int j = 0; j < nodes.size(); j++) {
				nodes[i].edges.push_back(Edge(i+1, j+1, distance(nodes[i].x, nodes[i].y, nodes[j].x, nodes[j].y)));
			}
		}
		infile.close();
	}

	// Generate clusterList
	vector<Point> nodetmp = nodes;
	sort(nodetmp.begin(), nodetmp.end(), comptoorigin);
	int numclusters = ceil(nodes.size()/clustersize);
	cout << numclusters << endl;
	vector<int> newCol;
	for (int i = 0; i < numclusters; i++)
		clusterList.push_back(newCol);

	for(int i = 0; i < numclusters; i++) {
		Point candidate = nodetmp.back();
		sort(candidate.edges.begin(), candidate.edges.end(), edgecomp);
		int clustercandidates = clustersize;
		for(int j = 0; j < clustercandidates; j++) {
			if(!check(clusterList, candidate.edges[j].dest)) {
					clusterList[i].push_back(candidate.edges[j].dest);
						for(int k = 0; k < nodetmp.size(); k++) {
							if (nodetmp[k].pos == candidate.edges[j].dest) {
								nodetmp.erase(nodetmp.begin()+k);
								break;
							}
						}
			}
			else { clustercandidates++; }
		}
	}
	// last cluster
	clusterList.push_back({});
	int remainder = nodes.size() % clustersize;
	cout << remainder << endl;
	for (int i = 0; i < remainder; i++) {
		clusterList[clusterList.size()-1].push_back(nodetmp[0].pos);
		nodetmp.erase(nodetmp.begin());
	}

	// Start New Population

	cout << "Start New Pop" << endl;
	for (unsigned int i = 0; i < POP_SIZE; i++) {
		Chromosome chr(nodes, clusterList);
		cout << "Chromosome" << i << ":";
		for (auto const& c : chr.getChr())
    	cout << ' ' << c;
		chromosomes.push_back(chr);
		cout << " " << chr.getFit() << endl;
	}

	chromosomes = SortChr(chromosomes);

	// Loop Population until Completion

	while (stalemate != 50) {
		gennum++;
		cout << "Current Generation: " << gennum << endl;
		// Elitism
		for (unsigned int i = 0; i < (POP_SIZE * .02); i++) {
			chromosomes_next.push_back(chromosomes[i]);
		}
		// Crossover
		for (unsigned int i = 0; i < (POP_SIZE * .98); i++) {
			vector<Chromosome> temppopulation = chromosomes;
			int rnum = randnum(0, POP_SIZE);
			Chromosome Chromosome1 = temppopulation[rnum];
			temppopulation.erase(temppopulation.begin() + rnum);
			rnum = randnum(0, POP_SIZE - 1);
			Chromosome Chromosome2 = temppopulation[rnum];
			temppopulation.erase(temppopulation.begin() + rnum);
			rnum = randnum(0, POP_SIZE - 2);
			Chromosome Chromosome3 = temppopulation[rnum];
			temppopulation.erase(temppopulation.begin() + rnum);
			rnum = randnum(0, POP_SIZE - 3);
			Chromosome Chromosome4 = temppopulation[rnum];
			temppopulation.erase(temppopulation.begin() + rnum);
			if (Chromosome3 < Chromosome1) {
				Chromosome1 = Chromosome3;
			}
			if (Chromosome4 < Chromosome2) {
				Chromosome2 = Chromosome4;
			}
			Chromosome1.Crossover(Chromosome2, nodes, clusterList);
			// Chance for Mutation
			if (randnum(0, POP_SIZE) < (POP_SIZE * .4)) {
				(Chromosome1.Mutate(nodes, clusterList));
			}
			chromosomes_next.push_back(Chromosome1);
		}
		// Make next population current population and sort
		chromosomes = chromosomes_next;
		chromosomes = SortChr(chromosomes);
		// Compare best fit
		if (chromosomes[0].getFit() < bestfit) {
			bestfit = chromosomes[0].getFit();
			stalemate = 0;
		}
		else
		{
			stalemate++;
		}
	}

	// Output results
	cout << bestfit << endl;

	return 0;
}
