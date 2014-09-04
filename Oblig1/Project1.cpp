# include <cmath>
# include <string>
# include <armadillo>
# include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;

vec TDMA(int n, vec a, vec b, vec c, vec b_func) 
{

    vec gamma = zeros<vec>(n);
    vec lambda = zeros<vec>(n);
    vec v = zeros<vec>(n);

    // Starting clock
    auto start = high_resolution_clock::now();
    
    /*
     * Implementing the Thomas Algorithm
     */

    // Forward substitution
    lambda[0] = b[0];
    v[0] = b_func[0]/lambda[0];
    for (int i = 1; i < n; i++)
    {

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

    auto finish = high_resolution_clock::now();
    cout << "Duration of TDMA: " << duration_cast<nanoseconds>(finish - start).count()
         << "ns" << endl;


    return v;

};


vec Gaussian(int n, vec a, vec b, vec c, vec b_func)
{

    mat A = zeros(n, n);
    vec v;

    A(0, 0) = b[0];
    A(0, 1) = c[1];

    for (int i = 1; i < n-1; i++) {
        A(i, i-1) = a[i];
        A(i, i) = b[i];
        A(i, i+1) = c[i];
    }

    A(n-1, n-2) = a[n-1];
    A(n-1, n-1) = b[n-1];

    auto start = high_resolution_clock::now();

    v = solve(A, b_func);

    auto finish = high_resolution_clock::now();
    cout << "Duration of Gaussian Elimination (without the construction of the matrix A): "
         << duration_cast<nanoseconds>(finish - start).count()
         << "ns" << endl;

    return v;

};


void Plot(vec x, vec v)
{

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
    vec x = zeros<vec>(n);
    double h = 1.0/(n+1);

    vec a = zeros<vec>(n);
    vec b = zeros<vec>(n);
    vec c = zeros<vec>(n);
    vec b_func = zeros<vec>(n);
    vec v;

    a.fill(-1);
    b.fill(2);
    c.fill(-1);
    a[0] = 0;
    c[n-1] = 0;

    b_func[0] = h*h*100*exp(-10*x[0]);
    for (int i = 1; i < n; i++) {

        x[i] = i*h;
        b_func[i] = h*h*100*exp(-10*x);

    }

    v = Gaussian(n, a, b, c, b_func);
    v = TDMA(n, a, b, c, b_func);

    return 0;

}
