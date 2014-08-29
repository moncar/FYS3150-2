# include <iostream>
using namespace std;

int main() {

  char myword[20] = "LOL";
  //  myword[0] = 'L';
  //  myword[1] = 'O';
  //  myword[2] = 'L';
  //  myword[3] = '\0';

  for (int i = 0; i < sizeof(myword); i++) {
    cout << myword[i];
  }

  cout << '\n';

  return 0;

}
