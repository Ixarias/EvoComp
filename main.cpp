
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
using namespace std;

#define NUM_KNAPSACKS 2
#define POP_SIZE 10
#define MUTATION_RATE 1/NUM_OBJECTS

int randnum_in_range(int start, int end){
  int range = (end-start)+1;
  int random_int = start + (rand() % range);
  return random_int;
}

string create_chrom(int num_object){
  int total = num_object;
  string chrom = "";
  for(int i = 0; i < total; i++){
    chrom += to_string(randnum_in_range(0,1));
  }
  return chrom;
}

string fix_chrom(string chr) {
  int rnum = randnum_in_range(0, chr.length());
  if(chr[rnum] == 1) {
    chr[rnum = 0];
  }
  else {
    fix_chrom(chr);
  }
  return chr;
}

class Valuable {
public:
  int value = 0;
  int weight = 0;

  Valuable(int v, int w) {
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
    return value/weight;
  }

  void display() {
    cout << value << " " << weight << endl;
  }
};

class Knapsack {
public:
  int capacity = 0;
  int current_weight = 0;
  vector<Valuable> contents;

  Knapsack(int c) {
    capacity = c;
  }

  int currentWeight() {
    int current_weight = 0;
    int size = contents.size();
    for(int i = 0; i < size; i++) {
      current_weight += contents[i].getWeight();
    }
    return current_weight;
  }
  void restartWeight() {
    current_weight = 0;
  }
  bool addWeight(int w) {
    if(current_weight + w > capacity) {
      current_weight += w;
      return 1;
    }
    else {
      return 0;
    }
  }

  void display() {
    cout << capacity << " " << currentWeight() << endl;
  }
};

int test_chrom(string chr, vector<Knapsack> kn, vector<Valuable> va) {
  bool result = true;
  bool signal = false;
  int fitness = 0;
  // fitness gram pacer test here
  // iterate through valuables
  for(unsigned int i = 0; i < chr.size(); i++) {
    // check if gene == 1, if yes check its corresponding object against each knapsack
    if(chr[i] == 1) {
      // iterate through knapsacks for each valuable
      for(unsigned int j = 0; j < kn.size(); j++) {
        result = kn[j].addWeight(va[i].getWeight());
        if(result) {
          break;
        }
        else {
          if(j == (kn.size()-1)) {
            signal = true;
            break;
          }
        }
      }
    }
    if(signal) {
      break;
    }
  }
  if (signal) {
    return -1;
  }
  else {
    return fitness;
  }
}

void Mutate(string &bits) {
  for (unsigned int i = 0; i < bits.length(); i++) {
    if ((unsigned int)(randnum_in_range(0, 100)/100) < bits.length()) {
      if (bits.at(i) == '1') {
        bits.at(i) = '0';
      }
      else {
        bits.at(i) = '1';
      }
    }
  }
  return;
}

void Crossover(string &offspring1, string &offspring2) {
  //create a random crossover point
  int len = offspring1.length();
  int crossover = randnum_in_range(0, len);

  string t1 = offspring1.substr(0, crossover) + offspring2.substr(crossover, 1/len);
  string t2 = offspring2.substr(0, crossover) + offspring1.substr(crossover, 1/len);
  Mutate(t1);
  Mutate(t2);
  offspring1 = t1; offspring2 = t2;
}

int twotourney(int pos1, int pos2, vector<int> fit_vec) {
  int winnerval = max(fit_vec[pos1], fit_vec[pos2]);
  if(winnerval == fit_vec[pos1]) {
    return pos1;
  }
  else {
    return pos2;
  }
}

int main() {
  // random seed for rnum
  srand (time(nullptr));

  int best_fit = 0;
  int current_best = 0;
  int stalemate = 0;
  vector<int> fit_vec_now;
  vector<int> fit_vec_next;
  vector<Knapsack> knapsacks_vector;
  vector<Valuable> valuables_vector;
  vector<string> now_gen;

  // [1] enter NUM_KNAPSACKS knapsacks
  ifstream infile;
  infile.open("Knapsacks.txt", ifstream::in);
  string line;
  while(getline(infile, line)) {
    int knap_cap = stoi(line);
    knapsacks_vector.push_back(Knapsack(knap_cap));
  }
  infile.close();

  // enter NUM_OBJECTS objects
  infile.open("Valuables.txt", ifstream::in);
  int filei = 0;
  string word;
  int vec_val;
  int vec_wei;
  while(infile >> word) {
    if(filei == 0) {
      vec_val = stoi(word);
      filei = 1;
    }
    else {
      vec_wei = stoi(word);
      filei = 0;
      valuables_vector.push_back(Valuable(vec_val, vec_wei));
    }
  }
  infile.close();

  // [2] generate POP_SIZE chromosomes
  for(int i = 0; i < 10; i++) {
    string chrom = create_chrom(valuables_vector.size());
    now_gen.push_back(chrom);
    // cout << i << ": " << now_gen[i] << endl;
  }

  // [3] fix current gen
  for(unsigned int i = 0; i < now_gen.size(); i++) {
    int fitness = test_chrom(now_gen[i], knapsacks_vector, valuables_vector);
    if(fitness == -1) {
      now_gen[i] = fix_chrom(now_gen[i]);
      i -= 1;
      continue;
    }
    if(current_best < fitness) {
      current_best = fitness;
    }
    fit_vec_now.push_back(fitness);
  }

  // [4] start evolutionary loop

  while(stalemate != 25){
    current_best = 0;
    vector<string> next_gen;
    // [a] create new population
    // crossover
    while(next_gen.size() < now_gen.size()) {
      int len = now_gen[0].length();
      string buffer1 = now_gen[twotourney(randnum_in_range(0, len), randnum_in_range(0, len), fit_vec_now)];
      string buffer2 = now_gen[twotourney(randnum_in_range(0, len), randnum_in_range(0, len), fit_vec_now)];
      Crossover(buffer1, buffer2);
      int success1 = test_chrom(buffer1, knapsacks_vector, valuables_vector);
      while(success1 == -1) {
        fix_chrom(buffer1);
        success1 = test_chrom(buffer1, knapsacks_vector, valuables_vector);
      }
      int success2 = test_chrom(buffer2, knapsacks_vector, valuables_vector);
      while(success2 == -1) {
        fix_chrom(buffer1);
        success2 = test_chrom(buffer2, knapsacks_vector, valuables_vector);
      }
      if(current_best < success1) {
        current_best = success1;
      }
      if(current_best < success2) {
        current_best = success2;
      }
      next_gen.push_back(buffer1);
      next_gen.push_back(buffer2);
    }
    // prep for next generation
    if(current_best < best_fit || current_best == best_fit) {
      stalemate += 1;
    }
    else {
      best_fit = current_best;
      stalemate = 0;
    }
    cout << best_fit << endl;
    now_gen = next_gen;
    next_gen.clear();
  }

  // [5] exit when fitness has not improved for 25 generations



}
