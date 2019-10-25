#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include<vector>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
using namespace std;

class Chromosome {
private:
  string chr;
  int fit;
public:
  Chromosome();
  string generateChr(), getChr();
  int evaluateFit(), getFit();
  void Mutate(), Crossover(), fixChr();
};

#endif
