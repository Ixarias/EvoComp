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
	Chromosome();
	Chromosome();
	string generateChr(),
		getChr(),
		getIndex();
	Chromosome Crossover(),
		Mutate();
	int evaluateFit(),
		getFit(),
		randnum(int, int, vector<int> = { -1 });
	bool operator< (Chromosome);
};

#endif
