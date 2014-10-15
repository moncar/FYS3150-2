# include <iostream>
# include <new>

using namespace std;

int main() {

  int i;
  int * p;
  cout << "How many numbers do you wish to enter? ";
  cin >> i;
  p = new (nothrow) int[i];

  if (p == NULL) {
    cout << "Error: Could not allocate to memory." << endl;
  } else {

    for (int n = 0; n < i; n++) {
      cout << "Enter number: ";
      cin >> p[n];
    }

    cout << "You have entered: ";
    for (int n = 0; n < i; n++) {
      cout << p[n] << ", ";
    }
    cout << "\n";
    delete[] p;

    if (p == NULL) {
      cout << "NULL";
    }
  }

  return 0;
}
