// Andrea M. Stojanovski

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Warrior;
class Noble;

class Warrior {
	friend Noble;
public:
	Warrior(const string& name, double strength)
		: name(name), strength(strength) {};
	void display(ostream& os = cout) const {
		os << name << ": " << strength << endl;
	}
	const string& getName() const { return name; }
	double getStrength() const { return strength; }
private:
	const string name;
	double strength;
	Noble* bossP = nullptr;
	bool hired(Noble* nobleP) {
		if (bossP) {
			cerr << name << " already has a boss\n";
			return false;
		}
		bossP = nobleP;
		return true;
	}
	void fired() {
		bossP = nullptr;
	}
	void changeStrength(double amount) { 
		strength -= (strength * amount);
	}
	void dies() {
		strength = -1;
	}
};

class Noble {
public:
	Noble(const string& name) : name(name) {}
	void display() const {
		cout << name << " has an army of " << army.size() << endl;
		for (Warrior* warP : army) {
			cout << "\t";
			warP->display();
		}
	}
	bool hire(Warrior& war) {
		if (armyStrength() < 0) {
			cerr << name << " is already dead\n" ;
			return false;
		}
		if (war.hired(this)) { 
			Warrior* warP = &war;
			army.push_back(warP);
			return true;
		}
		return false;
	}

	bool fire(Warrior& war) {
		if (armyStrength() < 0) {
			cerr << name << " and his warriors are already dead\n";
			return false;
		} else if (army.size() == 0) {
			cerr << name << " has not hired any warriors\n";
			return false;
		} else if (war.bossP != this) {
			cerr << war.getName() << " is not in " << name << "'s army\n";
			return false;
		}

		for (size_t i = 0; i < army.size(); ++i) {
			if (army[i] == &war) {
				cout << "You don't work for me anymore" << army[i]->getName() << "! -- " << name
					<< endl;
				army[i]->fired();
				army[i] = nullptr;
			} else if (i > 0 && army[i - 1] == nullptr) {
				army[i - 1] = army[i];
				army[i] = nullptr;
			}
			if (army[i] == nullptr && i == (army.size() - 1)) {
				army.pop_back();
				return true;
			}
		}
	}

	bool battle(Noble& enemy) {
		cout << name << " battles " << enemy.name << endl;
		if (this == &enemy) {
			cerr << name << " cannot battle himself\n";
			return false;
		}

		double strength = this->armyStrength();
		double enemyStrength = enemy.armyStrength();

		if (strength < 0 && enemyStrength < 0) {
			cerr << "Oh, NO! They're both dead! Yuck!\n";
			return false;
		} else if (strength < 0) {
			cerr << "He's dead, " << enemy.name << endl;
			return false;
		} else if (enemyStrength < 0) {
			cerr << "He's dead, " << name << endl;
			return false;
		}

		if (strength > enemyStrength) {
			reduceStrength(enemyStrength / strength);
			enemy.dies();
			cout << name << " defeats " << enemy.name << endl;
		} else if (enemyStrength > strength) {
			enemy.reduceStrength(strength / enemyStrength);
			dies();
			cout << enemy.name<< " defeats " << name << endl;
		} else {
			dies();
			enemy.dies();
			cout << "Mutual Annihilation: " << name << " and "
				<< enemy.name << " die at each other's hands\n";
		}
		return true;
	}

private:
	const string name;
	vector<Warrior*> army;
	double armyStrength() const {
		double totalStrength = 0;
		for (Warrior* warP : army) {
			totalStrength += warP->getStrength();
		}
		return totalStrength;
	}
	void reduceStrength(double amount) {
		for (Warrior* warP : army) {
			warP->changeStrength(amount);
		}
	}
	void dies() {
		for (Warrior* warP : army) {
			warP->dies();
		}
	}
};
int main() {

	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	cout << "==========\n"
		<< "Status before all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

	art.fire(cheetah);
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "==========\n"
		<< "Status after all battles, etc.\n";
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	cout << "==========\n";

}