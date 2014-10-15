# include <iostream>
# include <sstream>
# include <string>

using namespace std;

struct movies {
  string title;
  int year;
} mine, yours;

// Try without this one
void printmovie(movies movie);

int main() {

  string str;

  mine.title = "The Grand Budapest Hotel";
  mine.year = 2014;

  cout << "Enter title: ";
  getline(cin, yours.title);
  cout << "Enter year: ";
  getline(cin, str);
  stringstream(str) >> yours.year;

  cout << "My favorite movie is:\n";
  printmovie(mine);
  cout << "And yours is:\n";
  printmovie(yours);

  return 0;

}


void printmovie(movies movie) {
  cout << movie.title;
  cout << " (" << movie.year << ")\n";
}
