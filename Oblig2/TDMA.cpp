# include <iostream>
# include <armadillo>
# include <cmath>
# include <unittest++/UnitTest++.h>

using namespace std;
using namespace arma;


class TDMA {
    private:
        vec gamma;
        vec lambda;
        vec v;
    public:
        TDMA(int n) {
            gamma = zeros<vec>(n+2);
            lambda = zeros<vec>(n+2);
            v = zeros<vec>(n+2);
        }

        bool lengthOfVec(int n) {
            if (gamma.n_elem == n+2 && lambda.n_elem == n+2 && v.n_elem == n+2) {
                return true;
            }
            return false;
        }
};

TEST(Constructor) {
    TDMA testTDMA(10);
    CHECK(testTDMA.lengthOfVec(12));
}

int main() {
    return UnitTest::RunAllTests();
}
