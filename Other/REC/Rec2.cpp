// Andrea M. Stojanovski
// 20 September 2020

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Formula {
	vector<string> names;
	int carbon;
	int hydrogen;
};

void getFileName(ifstream& hcFile);

void fileToVector(ifstream& hcFile, vector<Formula>& hydrocarbon);

void insertionSort(vector<Formula>& hydrocarbon);

void displayVector(const vector<Formula>& hydrocarbon);

int main() {
	ifstream hcFile;
	vector<Formula> hydrocarbons;
	getFileName(hcFile);
	fileToVector(hcFile, hydrocarbons);
	insertionSort(hydrocarbons);
	displayVector(hydrocarbons);
	hcFile.close();
}

void getFileName(ifstream& hcFile) {
	string filename;
	cout << "Enter file name. \n";
	cin >> filename;
	hcFile.open(filename);
	while (!hcFile) {
		hcFile.clear();
		cerr << "Can't open the file. \n\n";
		cin >> filename;
		hcFile.open(filename);
	}
}

void fileToVector(ifstream& hcFile, vector<Formula>& hydrocarbon) {
	string name;
	int carbon;
	int hydrogen;
	char discard;

	while (hcFile >> name >> discard >> carbon >> discard >> hydrogen) {
		Formula currFormula;
		size_t i = 0;
		while (i < hydrocarbon.size() && currFormula.names.size() == 0) {
			if (hydrocarbon[i].carbon == carbon && hydrocarbon[i].hydrogen == hydrogen) {
				hydrocarbon[i].names.push_back(name);
				currFormula = hydrocarbon[i];
			}
			++i;
		}

		if (currFormula.names.size() == 0) {
			currFormula.names.push_back(name);
			currFormula.hydrogen = hydrogen;
			currFormula.carbon = carbon;
			hydrocarbon.push_back(currFormula);
		}
	}
}

void insertionSort(vector<Formula>& hydrocarbon) {
	Formula temp;
	for (size_t i = 1; i < hydrocarbon.size(); ++i) {
		temp = hydrocarbon[i];
		int j = i;
		--j;
		while (j > -1 && hydrocarbon[i].carbon < hydrocarbon[j].carbon) {
			hydrocarbon[i] = hydrocarbon[j];
			hydrocarbon[j] = temp;
			temp = hydrocarbon[i];
			--j;
		}
		if (j > -1 && hydrocarbon[i].carbon == hydrocarbon[j].carbon) {
			temp = hydrocarbon[i];
			while (j > -1 && hydrocarbon[i].hydrogen < hydrocarbon[j].hydrogen) {
				hydrocarbon[i] = hydrocarbon[j];
				hydrocarbon[j] = temp;
				temp = hydrocarbon[i];
				--j;
			}
		}
	}
}

void displayVector(const vector<Formula>& hydrocarbon) {
	for (Formula currFormula : hydrocarbon) {
		cout << 'C' << currFormula.carbon << 'H' << currFormula.hydrogen << ' ';
		for (string name : currFormula.names) {
			cout << name << ' ';
		}
		cout << endl;
	}
}
