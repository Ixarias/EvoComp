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

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

using namespace std;

class Chromosome {
private:
	string chr, ind;
	int fit;
public:
	Chromosome(vector< vector<int> >, vector< vector<int> >);
	Chromosome(string, string, vector< vector<int> >, vector< vector<int> >);
	string generateChr(vector< vector<int> >),
		getChr(),
		getIndex();
	Chromosome Crossover(Chromosome, vector< vector<int> >, vector< vector<int> >),
		Mutate(vector< vector<int> >, vector< vector<int> >);
	int evaluateFit(vector< vector<int> >, vector< vector<int> >),
		getFit(),
		randnum(int, int, vector<int>);
	bool operator< (Chromosome);
};

#endif
