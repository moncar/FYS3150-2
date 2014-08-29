# include <cmath>
# include <armadillo>

using namespace std;
using namespace arma;

vec vectorConstructor(int n)
{

    vec a = zeros<vec>(n);
    vec b = zeros<vec>(n);
    vec c = zeros<vec>(n);

    a[0] = 0;
    for (int i = 1; i < n; i++) a[i] = -1;
    for (int i = 0; i < n; i++) b[i] = 2;
    for (int i = 0; i < n-1; i++) c[i] = -1;
    c[n-1] = 0; 

    vec f = zeros<vec>(n);

    return a, b, c, f;

}; 

int main()
{
    return 0;
}
