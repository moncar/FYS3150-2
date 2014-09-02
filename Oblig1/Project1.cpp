# include <cmath>
# include <string>
# include <armadillo>

using namespace std;
using namespace arma;

void TDMA(int n, vec a, vec b, vec c) 
{

    vec gamma = zeros<vec>(n);
    vec lambda = zeros<vec>(n);
    vec b_func = zeros<vec>(n);
    vec v = zeros<vec>(n);
    double h = 1.0/(n+1);
    double x = 0;
    
    /*
     * Implementing the Thomas Algorithm
     */

    // Forward substitution
    b_func[0] = h*h*100*exp(-10*x);
    lambda[0] = b[0];
    v[0] = b_func[0]/lambda[0];
    for (int i = 1; i < n; i++)
    {

        x = i*h;
        b_func[i] = h*h*100*exp(-10*x);
        gamma[i] = c[i-1]/lambda[i-1];
        lambda[i] = b[i] - gamma[i]*a[i];
        v[i] = (b_func[i] - a[i]*v[i-1])/lambda[i];

    }

    // Backward substitution
    for (int i = n-2; i >= 0; i--)
    {

        // gamma[0] = 0...
        v[i] -= gamma[i+1]*v[i+1];

    }

};

int main()
{

    int n = 10;
    vec a = zeros<vec>(n);
    vec b = zeros<vec>(n);
    vec c = zeros<vec>(n);

    a.fill(-1);
    b.fill(2);
    c.fill(-1);
    a[0] = 0;
    c[n-1] = 0;

    TDMA(n, a, b, c);

    return 0;

}
