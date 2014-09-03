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



vec GE(int n, vec a, vec b, vec c)
{

    vec v = zeros<vec>(n);
    mat A = zeros(n, n);
    double h = 1.0/(n+1);
    double x = 0;

    A(0, 0) = b[0];
    A(0, 1) = b[1];



};

vec LU(int n, vec a, vec b, vec c)
{

    vec v = zeros<vec>(n);
    vec gamma = zeros<vec>(n);
    vec lambda = zeros<vec>(n);
    vec y = zeros<vec>(n);
    mat A = zeros(n, n);
    mat L, U, P;
    double h = 1.0/(n+1);
    double x = 0;

    A(0, 0) = b[0];
    A(0, 1) = b[1];

    for (int i = 1; i < n-1; i++) {
        A(i-1, i) = a[i];
        A(i, i) = b[i];
        A(i+1, i) = c[i];
    }

    A(n-1, n-2) = a[n-1];
    A(n-1, n-1) = b[n-1];

    lu(L, U, P, A);

    y[0] = h*h*exp(-10*x);
    gamma[0] = y[0]*L(1, 0);
    for (int i = 1; i < n; i++) {

        x = i*h;
        y[i] = h*h*exp(-10*x) - gamma[i-1];
        for (int j = 0; j < i; j++) {

            gamma[i] += L(i, j)*y[j];

        }
    }

    lambda[n-1] = U(n-1, n-1);
    for (int i = n-1, i >= 0; i--) {

        v[i] = y[i]/lambda[i];

        for (int j = n-1; j >= i; 

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

    v = LU(n, a, b, c);
    v = TDMA(n, a, b, c);



    return 0;

}
