#ifndef INCLUDE
#define INCLUDE

#include<vector>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<cmath>

#endif

#include "Chromosome.cpp"
using namespace std;

#define POP_SIZE 10 //change later dickhead

/*vector<Chromosome> SortChr(vector<Chromosome> chromosomes) {
	std::sort(chromosomes.begin(), chromosomes.end());
	return chromosomes;
}*/

int randnum(int start, int end, vector<int> excep = { -1 }) {
	int range = (end - start);
	int random_int = start + (rand() % range);
	if (std::find(excep.begin(), excep.end(), random_int) != excep.end()) {
		random_int = randnum(start, end, excep);
	}
	return random_int;
}

int main(int argc, char* argv[]) {
	// Seed
	srand(time(nullptr));

	// Variables
	vector< vector<float> > edgeLength;
	vector<Point> nodes;
	vector<int> clusterList;
	vector<Chromosome> chromosomes;
	vector<Chromosome> chromosomes_next;
	/*int bestfit = 99999;
	int stalemate = 0;
	int gennum = 0;*/

	std::fstream infile(argv[1], ios_base::in);


	// Input instancew
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
			nodes[i].x = stof(vecstr[1]);
			nodes[i].y = stof(vecstr[2]);
			for(int j = i-1; j >= 0; j--) {
				float dist = distance(nodes[i].x, nodes[i].y, nodes[j].x, nodes[j].y);
				vecfl.push_back(dist);
			}
			edgeLength.push_back(vecfl);
			i++;
		}
		infile.close();
	}

	// Generate clusterList


	// Start New Population

	for (unsigned int i = 0; i < POP_SIZE; i++) {
		Chromosome chr(edgeLength, clusterList);
		cout << "Chromosome" << i << ":";
		for (auto const& c : chr.getChr())
    	cout << ' ' << c;
		chromosomes.push_back(chr);
		cout << endl;
	}
	// chromosomes = SortChr(chromosomes);

	cout << "Before:";
	for (auto const& c : chromosomes[6].getChr())
		cout << ' ' << c;
	cout << endl;
	chromosomes[6].Mutate(edgeLength, clusterList);
	cout << "After:";
	for (auto const& c : chromosomes[6].getChr())
		cout << ' ' << c;
	cout << endl;

	cout << "Before - 9:";
	for (auto const& c : chromosomes[9].getChr())
		cout << ' ' << c;
	cout << endl;
	cout << "Before - 3:";
	for (auto const& c : chromosomes[3].getChr())
		cout << ' ' << c;
	cout << endl;
	chromosomes[9].Crossover(chromosomes[3], edgeLength, clusterList);
	cout << "After - 9:";
	for (auto const& c : chromosomes[9].getChr())
		cout << ' ' << c;
	cout << endl;
	cout << "After - 3:";
	for (auto const& c : chromosomes[3].getChr())
		cout << ' ' << c;
	cout << endl;

/*

	// Loop Population until Completion

	while (stalemate != 50) {
		gennum++;
		// Elitism
		for (unsigned int i = 0; i < (POP_SIZE * .05); i++) {
			chromosomes_next.push_back(chromosomes[i]);
		}
		// Crossover
		for (unsigned int i = 0; i < (POP_SIZE * .95); i++) {
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
			Chromosome3 = Chromosome1.Crossover(Chromosome2, edgeLength);
			// Chance for Mutation
			if (randnum(0, POP_SIZE) < (POP_SIZE * .4)) {
				Chromosome3 = (Chromosome3.Mutate(edgeLength));
			}
			chromosomes_next.push_back(Chromosome3);
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
		// cout << "Generation " << gennum << " best: " << chromosomes[0].getChr() << " - " << chromosomes[0].getFit() << " | " << bestfit << endl;
	}

	// Output results
	cout << bestfit << endl;

*/

	return 0;
}
