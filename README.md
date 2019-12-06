# EvoComp3
 Third project for CSCI 443

 cout << "3" << endl;
 cout << "Before:";
 for (auto const& c : chromosomes[6].getChr())
   cout << ' ' << c;
 cout << endl;
 chromosomes[6].Mutate(clusterList);
 cout << "After:";
 for (auto const& c : chromosomes[6].getChr())
   cout << ' ' << c;
 cout << endl;

 cout << "Before - 9:";
 for (auto const& c : chromosomes[9].getChr())
   cout << ' ' << c;
 cout << endl;
 cout << "Before - 3:";
 for (auto const& c : chromosomes[3].getChr())
   cout << ' ' << c;
 cout << endl;
 chromosomes[9].Crossover(chromosomes[3]);
 cout << "After - 9:";
 for (auto const& c : chromosomes[9].getChr())
   cout << ' ' << c;
 cout << endl;
 cout << "After - 3:";
 for (auto const& c : chromosomes[3].getChr())
   cout << ' ' << c;
 cout << endl;
