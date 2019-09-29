
#include<vector>
#include<iostream>
#include "somefunc.cpp"
using namespace std;

#define NUM_KNAPSACKS 2
#define POP_SIZE 10
#define NUM_OBJECTS 20

int randnum_in_range(int start, int end){
  int range = (end-start)+1;
  int random_int = start+(rand()%range);
  return random_int;
}

string create_chrom(){
  int total = NUM_OBJECTS;
  string chrom = "";
  for(int i = 0; i < total; i++){
    chrom += randnum_in_range(0,1);
  }
  return chrom;
}

class Valuable {
public:
  int value;
  int weight;

  Valuable(int v, int w) {
    value = v;
    weight = w;
  }

  void construct(int v, int w) {
    value = v;
    weight = w;
  }

  int getValue() {
    return value;
  }
  int getWeight() {
    return weight;
  }
  int getRatio() {
    return weight/value;
  }
};

class Knapsack {
public:
  int capacity = 0;
  int total_fit;
  vector<Valuable> contents;

  Knapsack(int c) {
    capacity = c;
  }

  void construct(int c) {
    capacity = c;
  }

  int getFit() {
    int total_fit = 0;
    int size = contents.size();
    for(int i = 0; i < size; i++) {
      total_fit += contents[i].getValue();
    }
    return total_fit;
  }
};

int main()
{
  // generate NUM_KNAPSACKS knapsacks
  vector<Knapsack> knapsacks;
  for(int i = 0; i < NUM_KNAPSACKS; i++) {
    int rnum = randnum_in_range(20, 100);
    knapsacks[i].construct(rnum);
  }
  // generate NUM_OBJECTS (20) objects
  vector<Valuable> valuables;
  for(int i = 0; i < NUM_OBJECTS; i++) {
    int rnum = randnum_in_range(1, 20);
    int rnum2 = randnum_in_range(1, 20);
    Valuable val = Valuable(rnum, rnum2);
    valuables[i] = val;
  }

  // generate POP_SIZE (10) chromosomes
  vector<string> chromosomes;
  for(int i = 0; i < POP_SIZE; i++) {
    string chrom = create_chrom();
    chromosomes[i] = chrom;
  }
}
