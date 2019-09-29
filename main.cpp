
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

void Crossover(string &offspring1, string &offspring2)
{
  //create a random crossover point
  int len = offspring1.length();
  int crossover = randnum_in_range(0, len);

  string t1 = offspring1.substr(0, crossover) + offspring2.substr(crossover, 1/len);
  string t2 = offspring2.substr(0, crossover) + offspring1.substr(crossover, 1/len);

  offspring1 = t1; offspring2 = t2;
}

void Mutate(string &bits)
{
  for (unsigned int i = 0; i < bits.length(); i++)
  {
    if ((unsigned int)(randnum_in_range(0, 100)/100) < bits.length())
    {
      if (bits.at(i) == '1')
      {
        bits.at(i) = '0';
      }
      else
      {
        bits.at(i) = '1';
      }
    }
  }

  return;
}

int main()
{
  // random seed for rnum
  srand (time(nullptr));

  int best_fit = 0;
  int current_best = 0;
  int stalemate = 0;
  vector<int> fit_vec_now;

  // [1] enter NUM_KNAPSACKS knapsacks
  /* cout << "Enter number of knapsacks :";
  cin >> num_knap;
  for (int i = 0; i < num_knap; i++) {
    cout << "Enter capacity for knapsack " << i << ": ";
    int knap_cap = 0;
    cin >> knap_cap;
    knapsacks_vector.push_back(Knapsack(knap_cap));
  } */

  vector<Knapsack> knapsacks_vector;
  ifstream infile;
  infile.open("Knapsacks.txt", ifstream::in);
  string line;
  while(getline(infile, line)) {
    int knap_cap = stoi(line);
    knapsacks_vector.push_back(Knapsack(knap_cap));
  }
  infile.close();

  /* for(int i = 0; i < NUM_KNAPSACKS; i++) {
    int rnum = randnum_in_range(20, 100);
    Knapsack knapinter = Knapsack(rnum);
    knapsacks_vector.push_back(knapinter);
    cout << i << ": "; knapsacks_vector[i].display(); } */

  // enter NUM_OBJECTS objects
  vector<Valuable> valuables_vector;
  infile.open("Valuables.txt", ifstream::in);
  while(getline(infile, line)) {
    int val = stoi(line);
    int wei = stoi(line);
    valuables_vector.push_back(Valuable(val, wei));
  }
  infile.close();

  /* for(int i = 0; i < NUM_OBJECTS; i++) {
    Valuable valinter = Valuable(randnum_in_range(1, 20), randnum_in_range(1, 20));
    valuables_vector.push_back(valinter);
    cout << i << ": "; valuables_vector[i].display(); } */

  // [2] generate POP_SIZE now_gen
  vector<string> now_gen;
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
    vector<string> next_gen;
    // [a] create new population
    // crossover



    // prep for next generation
    if(current_best < best_fit || current_best == best_fit) {
      stalemate += 1;
    }
    else {
      best_fit = current_best;
      stalemate = 0;
    }
    next_gen.clear();
  }

  // [4] exit when fitness has not improved for 25 generations

}
