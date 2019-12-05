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
	vector<int> chr;
	int fit;
public:
	Chromosome(vector< vector<int> >, vector<int>);
	Chromosome(vector<int>, vector< vector<int> >);
	vector<int> generateChr(vector< vector<int> >, vector<int>),
		getChr();
	Chromosome Crossover(Chromosome, vector< vector<int> >, vector<int>),
		Mutate(vector< vector<int> >, vector<int>);
	int evaluateFit(vector< vector<int> >),
		getFit(),
		randnum(int, int, vector<int> = { -1 });
	bool operator< (Chromosome);
};

#endif
