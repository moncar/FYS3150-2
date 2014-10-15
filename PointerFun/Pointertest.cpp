# include <unittest++/UnitTest++.h>
# include <string>
# include <iostream>

using namespace std;

void addisjon(int& sum, int* a, int* b) {
    cout << a << endl;
    cout << *a << endl;
    sum = *a + *b;
}

int main() {

    int k = 2;
    int i = 3;
    int sum;
    addisjon(sum, &k, &i);

    cout << sum << endl;

}
