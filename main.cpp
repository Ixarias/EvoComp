
#include<iostream>
#include "somefunc.cpp"
using namespace std;

#define NUM_KNAPSACKS 2
#define POP_SIZE 100
#define NUM_OBJECTS 20

int randnum_in_range(int start, int end){
  int range = (end-start)+1;
  int random_int = start+(rand()%range);
  return random_int;
}

string create_chrome(){
  int total = NUM_OBJECTS;
  string chrom = "";
  for(int i = 0; i < total; i++){
    chrom += randnum_in_range(0,1);
  }
  return chrom;
}

Class Valuable {
public:
  int value;
  int weight;

  int Valuable::Valuable(int v, int w) {
    int value = v;
    int weight = w;
  }

  int Valuable::getValue() {
    return value;
  }
  int Valuable::getWeight() {
    return weight;
  }
  int Valuable::getRatio() {
    return weight/value;
  }
}

Class Knapsack {
public:
  int capacity;
  int total_fit;
  Valuable contents[];

  int Knapsack::Knapsack(int c) {
    int capacity = c;
  }

  int Knapsack::getFit() {
    int total_fit = 0;
    for(int i = 0; i < contents.size(); i++) {
      total_fit += contents[i].getValue();
    }
    return total_fit;
  }



}

int main()
{
  // generate NUM_KNAPSACKS knapsacks
  for(int i = 0; i < NUM_KNAPSACKS; i++) {

  }
  // generate POP_SIZE (100) objects
  for(int i = 0; i < POP_SIZE; i++) {

  }

}
