# include <iostream>
# include <string>
# include <sstream>

/* Adding a comment
 * Llolkoloplo
 * GIVE ME TEMP RAWRAWR!!!!
 * ANOTHER ONE!!! LOL
 */

using namespace std;

class Character {
  string name;
  string charClass;
public:
  void setName(string s) {name = s;}
  void setClass(string s) {charClass = s;}
  void printVal() {
    cout << "Your fierce character is called " << name << " and he is a " << charClass << endl;
  }
};

class Hunter : public Character {
public:
  Hunter(string s) {
    setName(s);
    setClass("Hunter");
  }
};


int main() {
  string name;
  int charClass;
  cout << "Enter a name: " << endl;
  cin >> name;
  cout << "Pick a class: " << "\n1: Hunter" << endl;
  cin >> charClass;

  if (charClass == 1) {
    Hunter hunt = Hunter(name);
    hunt.printVal();
  }
}
