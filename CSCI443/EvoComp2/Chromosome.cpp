#include "Chromosome.h"

Chromosome::Chromosome(vector< vector<int> > MS, vector< vector<int> > PT) {
	chr = generateChr(MS);
	fit = evaluateFit(MS, PT);
}

Chromosome::Chromosome(string chromo, string index, vector< vector<int> > MS, vector< vector<int> > PT) {
	chr = chromo;
	ind = index;
	fit = evaluateFit(MS, PT);
}

string Chromosome::generateChr(vector< vector<int> > MS) {
	string chromo = "";
	vector<int> lengthVector;
	for (unsigned int i = 0; i < MS.size(); i++) {
		lengthVector.push_back(MS[i].size());
	}
	bool full = false;
	vector<int> fullvec;
	while (!full) {
		if (fullvec.size() != lengthVector.size()) {
			int rnum = randnum(0, lengthVector.size(), fullvec);
			if (lengthVector[rnum] != 0) {
				char crnum = '0' + rnum;
				chromo += crnum;
				ind += MS[rnum].size() - lengthVector[rnum] + '0';
				lengthVector[rnum] -= 1;
			}
			else {
				fullvec.push_back(rnum);
			}
		}
		else {
			full = true;
		}
	}
	return chromo;
}

string Chromosome::getChr() {
	return chr;
}

int Chromosome::evaluateFit(vector< vector<int> > MS, vector< vector<int> > PT) {
	vector<int> machSeqNext, taskStart, procStart;
	int start = 0;
	for (unsigned int i = 0; i < MS.size(); i++) {
		machSeqNext.push_back(0);
		taskStart.push_back(0);
	}
	for (unsigned int i = 0; i < PT[0].size(); i++) {
		procStart.push_back(0);
	}
	for(unsigned k = 0; k < chr.length(); k++) {
		int i = chr[k] - '0';
		int j = MS[i][machSeqNext[i]];
		machSeqNext[i] += 1;
		start = max(taskStart[i], procStart[j]);
		taskStart[i] = start + PT[i][j];
		procStart[j] = start + PT[i][j];
	}
	int fitness = 0;
	for(unsigned int i = 0; i < procStart.size(); i++) {
		fitness = max(fitness, procStart[i]);
	}
	return fitness;
}

int Chromosome::getFit() {
	return fit;
}

string Chromosome::getIndex() {
	return ind;
}

Chromosome Chromosome::Mutate(vector< vector<int> > MS, vector< vector<int> > PT) {
	string chromo = chr;
	string index = ind;
	int scramblelength = (ceil(chr.length() * .4));
	int flipamount = ceil(scramblelength / 2);
	int startpoint = randnum(0, chr.length() - scramblelength, { -1 });

	for (unsigned int i = 0; i < flipamount; i++) {
		int flippoint = randnum(startpoint, startpoint + scramblelength, { -1 });
		if (chromo[flippoint] != chromo[flippoint + 1]) {
			char flip = chromo[flippoint + 1];
			chromo[flippoint + 1] = chromo[flippoint];
			chromo[flippoint] = flip;
			flip = index[flippoint + 1];
			index[flippoint + 1] = index[flippoint];
			index[flippoint] = flip;
		}
	}
	Chromosome newchr(chromo, index, MS, PT);
	return newchr;
}

Chromosome Chromosome::Crossover(Chromosome otherchr, vector< vector<int> > MS, vector< vector<int> > PT) {
	bool split = false;
	string otherchrstr = otherchr.getChr();
	string otherindex = otherchr.getIndex();
	int startpoint = randnum(0, otherchrstr.length(), { -1 });
	int substrlength = randnum(ceil(otherchrstr.length() * .34), ceil(otherchrstr.length() * .5) + 1, { -1 });
	int remaininglength;
	string subchromo, subindex, subchromo2, subindex2;
	if (startpoint + substrlength > otherchrstr.length()) {
		split = true;
		subchromo = otherchrstr.substr(startpoint, otherchrstr.length());
		subindex = otherindex.substr(startpoint, otherindex.length());
		remaininglength = substrlength - (otherchrstr.length() - startpoint);
		subchromo2 = otherchrstr.substr(0, remaininglength);
		subindex2 = otherindex.substr(0, remaininglength);
	}
	else {
		subchromo = otherchrstr.substr(startpoint, substrlength);
		subindex = otherindex.substr(startpoint, substrlength);
	}
	string chromo = chr;
	string index = ind;
	if (split) {
		for (unsigned int i = 0; i < subchromo2.length(); i++) {
			for (unsigned int j = 0; j < chromo.length(); j++) {
				if (chromo[j] == subchromo2[i] && index[j] == subindex2[i]) {
					chromo.erase(chromo.begin() + j);
					index.erase(index.begin() + j);
					break;
				}
			}
		}
		chromo.insert(0, subchromo2);
		index.insert(0, subindex2);
	}
	for (unsigned int i = 0; i < subchromo.length(); i++) {
		for (unsigned int j = 0; j < chromo.length(); j++) {
			if (chromo[j] == subchromo[i] && index[j] == subindex[i]) {
				chromo.erase(chromo.begin() + j);
				index.erase(index.begin() + j);
				break;
			}
		}
	}
	if (split) {
		chromo.append(subchromo);
		index.append(subindex);
	}
	else {
		chromo.insert(startpoint, subchromo);
		index.insert(startpoint, subindex);
	}
	Chromosome newchr(chromo, index, MS, PT);
	return newchr;
}

bool Chromosome::operator<(Chromosome otherchr) {
	return fit < otherchr.getFit();
}

int Chromosome::randnum(int start, int end, vector<int> excep = vector<int>()) {
	int range = (end - start);
	int random_int = start + (rand() % range);
	if (std::find(excep.begin(), excep.end(), random_int) != excep.end()) {
		random_int = randnum(start, end, excep);
	}
	return random_int;
}
