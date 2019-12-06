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

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "Kruskal.h"
using namespace std;

class Chromosome {
private:
	vector<int> chr;
	int fit;
public:
	Chromosome(vector<Point>, vector< vector<int> >);
	Chromosome(vector<int>, vector<Point>);
	vector<int> generateChr(vector<Point>, vector< vector<int> >),
		getChr();
	void Crossover(Chromosome&, vector<Point>, vector< vector<int> >),
		Mutate(vector<Point>, vector< vector<int> >);
	int evaluateFit(vector<Point>),
		getFit(),
		randnum(int, int, vector<int> = { -1 });
	bool operator< (Chromosome);
};

#endif
