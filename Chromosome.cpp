#include "Chromosome.h"

Chromosome::Chromosome() {
  chr = generateChr();
  fit = evaluateFit();
}

string Chromosome::generateChr() {
  string chromo = "0";
  return chromo;
}

string Chromosome::getChr() {
  return chr;
}

int Chromosome::evaluateFit() {
  int fitness = 0;
  bool flag = true;
  if(!flag){
    fixChr();
  }
  return fitness;
}

int Chromosome::getFit() {
  return fit;
}

void Chromosome::fixChr() {
  string chromo = "0";
  chr = chromo;
}

void Chromosome::Mutate() {
  string chromo = "0";
  chr = chromo;
}

void Chromosome::Crossover() {
  string chromo = "0";
  chr = chromo;
}
