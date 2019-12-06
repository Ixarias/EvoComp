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
#include<sstream>
#include<iterator>

#endif

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

using namespace std;

class Chromosome {
private:
	vector<int> chr;
	int fit;
public:
	Chromosome(vector< vector<float> >, vector<int>);
	Chromosome(vector<int>, vector< vector<float> >);
	vector<int> generateChr(vector< vector<float> >, vector<int>),
		getChr();
	void Crossover(Chromosome&, vector< vector<float> >, vector<int>),
		Mutate(vector< vector<float> >, vector<int>);
	int evaluateFit(vector< vector<float> >),
		getFit(),
		randnum(int, int, vector<int> = { -1 });
	bool operator< (Chromosome);
};

#endif
