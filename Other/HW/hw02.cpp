// Andrea M. Stojanovski
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct Warrior {
	string name;
	int strength;
	Warrior(const string& name, int strength) : name(name), strength(strength) {}
};

void battle(Warrior& w1, Warrior& w2) {
	cout << w1.name << " battles " << w2.name << endl;
	if (w1.strength == 0) {
		if (w2.strength == 0) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		cout << "He's dead, " << w2.name << endl;
	} else if (w2.strength == 0) {
		cout << "He's dead, " << w1.name << endl;
	} else {
		if (w1.strength == w2.strength) {
			cout << "Mutual Annihilation: " << w1.name << " and " << w2.name <<
				" die at eachother's hands" << endl;
			w1.strength = 0;
			w2.strength = 0;
		} else if (w1.strength > w2.strength) {
			cout << w1.name << " defeats " << w2.name << endl;
			w1.strength = w1.strength - w2.strength;
			w2.strength = 0;
		} else {
			cout << w2.name << " defeats " << w1.name << endl;
			w2.strength = w2.strength - w1.strength;
			w1.strength = 0;
		}
	}
}

void status(const vector<Warrior>& warriors) {
	cout << "There are: " << warriors.size() << " warriors" << endl;
	for (Warrior curr : warriors) {
		cout << "Warrior: " << curr.name << ", strength: " << curr.strength << endl;
	}
}

int main() {
	vector<Warrior> warriors;
	string command;
	ifstream warriorFile("warriors.txt");

	if (!warriorFile) {
		cerr << "Could not open file.";
		exit(1);
	}

	while (warriorFile >> command) {
		if (command == "Status") {
			status(warriors);
		} else if (command == "Warrior") {
			string currname;
			int currstrength;
			warriorFile >> currname >> currstrength;
			Warrior newWarrior(currname, currstrength);
			warriors.push_back(newWarrior);
		} else {
			string name1, name2;
			int warInd1, warInd2;
			bool found = false;
			warriorFile >> name1 >> name2;

			for (size_t i = 0; i < warriors.size(); ++i) {
				if (warriors[i].name == name1) {
					warInd1 = i;
					if (found) {
						break;
					}
					else {
						found = true;
					}
				}
				if (warriors[i].name == name2) {
					warInd2 = i;
					if (found) {
						break;
					}
					else {
						found = true;
					}
				}
			}
			battle(warriors[warInd1], warriors[warInd2]);
		}
	}
	warriorFile.close();
}