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

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

using namespace std;

class Chromosome {
private:
	string chr;
	int fit;
public:
	Chromosome(vector< vector<int> >, vector< vector<int> >);
	string generateChr(vector< vector<int> >),
		getChr();
	int evaluateFit(vector< vector<int> >, vector< vector<int> >),
		getFit(),
		randnum_with_excep(int, int, vector<int>);
	void Mutate(),
		Crossover();
};

#endif
