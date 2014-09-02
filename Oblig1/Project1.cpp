# include <cmath>
# include <armadillo>

using namespace std;
using namespace arma;

void TDMA(int n) 
{

    /*
     * Consider using int instead
     */
    vec a = zeros<vec>(n);
    vec b = zeros<vec>(n);
    vec c = zeros<vec>(n);
    vec gamma = zeros<vec>(n);
    vec lambda = zeros<vec>(n);
    vec b_func = zeros<vec>(n);
    vec y = zeros<vec>(n); 
    double h = 1.0/(n+1);
    double x = 0;

    for (int i = 0; i < n; i++)
    {

        a[i] = -1;
        b[i] = 2;
        c[i] = -1;
        b_func[i] = h*h*100*exp(-10*x);
        x = i*h;

    }
    a[0] = 0;
    c[n-1] = 0;

    /*
     * Implementing the Thomas Algorithm
     */

    // Forward substitution
    lambda[0] = b[0];
    y[0] = b_func[0];
    for (int i = 1; i < n; i++)
    {

        gamma[i] = a[i]/lambda[i-1];
        lambda[i] = b[i] - gamma[i]*c[i-1];
        y[i] = b_func[i] - gamma[i]*y[i-1];

    }

    // Backward substitution
    v[n-1] = y[n-1]/gamma[n-1];
    for (int i = n-2; i >= 0; i--)
    {

        // gamma[0] = 0...
        v[i] = (y[i] - c[i]*v[i+1])/gamma[i];

    }

};
