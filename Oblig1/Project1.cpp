# include <cmath>
# include <string>
# include <armadillo>

using namespace std;
using namespace arma;

vec TDMA(int n, vec a, vec b, vec c) 
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

    return v;

};


int main(int argc, char* argv[])
{

    // Check the number of parameters
    if (argc < 2)
    {

        cout << "Usage: " << argv[0] << " (int n)" << endl;
        exit(1);

    }

    int n = atoi(argv[1]);

    vec a = zeros<vec>(n);
    vec b = zeros<vec>(n);
    vec c = zeros<vec>(n);
    vec v;

    a.fill(-1);
    b.fill(2);
    c.fill(-1);
    a[0] = 0;
    c[n-1] = 0;

    v = TDMA(n, a, b, c);

    cout << v << endl;

    return 0;

}
