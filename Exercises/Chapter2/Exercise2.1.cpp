# include <cmath>
# include <string>
# include <iostream>
# include <cstdlib>

using namespace std;

int main() {
  string someNumber = "345.24";
  int largestPower = 0;

  while (someNumber[largestPower] != '.') {
    largestPower++;
  }

  // The loop counts one too many
  largestPower--;

  int temp = 0;
  int inFront = 0;
  int power = largestPower;

  for (int i = 0; i <= power; i++) {
    inFront += pow(someNumber[i], largestPower);
    cout << someNumber[i] << endl;
    //cout << pow(someNumber[i], largestPower) << endl;
    largestPower--;
  }

  int behind = 0;
  int counter = -1;
  int end = someNumber.length() - power + 1;

  for (int i = power; i < end; i++) {
    temp = someNumber[i];
    behind += pow(temp, counter);
    counter--;
  }

  //  cout << inFront << endl;
  //  cout << behind << endl;

  return 0;
}
