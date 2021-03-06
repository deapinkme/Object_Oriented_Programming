// Andrea M. Stojanovski

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& war) {
		os << "Warrior: " << war.name << ", " << war.hisWeapon;
		return os;
	}
public:
	Warrior(const string& hisName, const string& weapName, int strength) :
		name(hisName), hisWeapon(weapName, strength) {}

	int strength() const { return hisWeapon.getStrength(); }
	void decreaseStrength(int opponentStrength) {
		hisWeapon.changeStrength(strength() - opponentStrength);
	}
	void dies() {
		hisWeapon.changeStrength(0);
	}
	string getName() const { return name; }
private:
	class Weapon {
		friend ostream& operator<<(ostream& os, const Weapon& weap) {
			os << "weapon: " << weap.name << ", " << weap.strength;
			return os;
		}
	public:
		Weapon(const string& name, int strength) :
			name(name), strength(strength) {}

		int getStrength() const { return strength; }
		void changeStrength(int newStrength) {
			strength = newStrength;
		}
	private:
		string name;
		int strength;
	};

	Weapon hisWeapon;
	string name;
};

void status(const vector<Warrior>& warriors);
void battle(ifstream& warriorFile, vector<Warrior>& warriors);
void createWarrior(ifstream& warriorFile, vector<Warrior>& warriors);

int main(){
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
			createWarrior(warriorFile, warriors);
		} else {
			battle(warriorFile, warriors);
		}
	}
	warriorFile.close();
}

void status(const vector<Warrior>& warriors) {
	cout << "There are: " << warriors.size() << " warriors \n";
	for (Warrior currWar : warriors) {
		cout << currWar << endl;
	}
}

void createWarrior(ifstream& warriorFile, vector<Warrior>& warriors) {
	string warName, weapName;
	int strength;
	warriorFile >> warName >> weapName >> strength;
	Warrior newWarrior(warName, weapName, strength);
	warriors.push_back(newWarrior);
}

void battle(ifstream& warriorFile, vector<Warrior>& warriors) {
	string name1, name2;
	int warInd1, warInd2;
	bool foundOther = false;
	warriorFile >> name1 >> name2;

	if (name1 == name2) {
		cerr << "Warrior cannot fight himself";
		return;
	}

	for (size_t curr = 0; curr < warriors.size(); ++curr) {
		if (warriors[curr].getName() == name1) {
			warInd1 = curr;
			if (foundOther) {
				break;
			}
			foundOther = true;
		} else if (warriors[curr].getName() == name2) {
			warInd2 = curr;
			if (foundOther) {
				break;
			}
			foundOther = true;
		}
	}

	Warrior& war1 = warriors[warInd1];
	Warrior& war2 = warriors[warInd2];
	cout << war1.getName() << " battles " << war2.getName() << endl;

	if (war1.strength() == 0 && war2.strength() == 0) {
		cerr << "Oh, NO! They're both dead! Yuck!\n";
		return;
	} else if (war1.strength() == 0) {
		cerr << "He's dead, " << war2.getName() << endl;
		return;
	} else if (war2.strength() == 0) {
		cerr << "He's dead, " << war1.getName() << endl;
		return;
	}

	if (war1.strength() == war2.strength()) {
		cout << "Mutual Annihilation: " << war1.getName() << " and " <<
			war2.getName() <<" die at eachother's hands" << endl;
		war1.dies();
		war2.dies();
	} else if (war1.strength() < war2.strength()) {
		cout << war2.getName() << " defeats " << war1.getName() << endl;
		war2.decreaseStrength(war1.strength());
		war1.dies();
	} else {
		cout << war1.getName() << " defeats " << war2.getName() << endl;
		war1.decreaseStrength(war2.strength());
		war2.dies();
	}
}

