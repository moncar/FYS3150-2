# include <iostream>
# include <string>
# include <sstream>

using namespace std;

int main()
{
  string mystr;
  double C;
  double F;

  cout << "Type in degrees Celsius: ";
  getline(cin, mystr);
  stringstream(mystr) >> C;
  F = (C * (9.0/5.0)) + 32;
  cout << C << " degrees Celsius corresponds to: " << F << " degrees Fahrenheit." << endl;
  return 0;
}
