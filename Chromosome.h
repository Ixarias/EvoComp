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

#include "Kruskal.cpp"
using namespace std;

class Chromosome {
private:
	vector<int> chr;
	int fit;
public:
	Chromosome(vector<Point>, vector< vector<int> >);
	Chromosome(vector<int>, vector<Point>);
	Chromosome(const Chromosome*);
	vector<int> generateChr(vector<Point>, vector< vector<int> >),
		getChr();
	void Crossover(Chromosome&),
		Mutate(vector< vector<int> >);
	int evaluateFit(vector<Point>, vector< vector<int> >),
		getFit(),
		randnum(int, int, vector<int> = { -1 });
	bool operator< (Chromosome);
};

#endif
