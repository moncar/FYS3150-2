# include <cmath>
# include <armadillo>

using namespace std;
using namespace arma;

/*
 * A method accepting an int n which is used to construct vectors
 * of length n. The values from assignemnt a are put into the
 * vectors a, b and c. The method returns the vectors a, b, c and f.
 */
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
    double h = 1.0/(n+1);
    double x;
    for (int i = 0; i < n; i++) 
    {

        x = i*h;
        f[i] = x;
//        d[i] = 100*exp(-10*x);

    }  

    vec v = zeros<vec>(n);
    v[0] = 0;
    v[n-1] = 0;

    cout << a[1] << endl;
    return a, b, c, f, v;

};


vec ForwardSubstitution(vec a, vec b, vec f, vec v, double h, int n)
{
    /*   
     * The /float(b[i]) has been removed to prevent a double division.
     * This is also done in the Backward Substitution.
    */
    for (int i = 0; i < n; i++) v[i] = h*h*f[i] - a[i]*v[i-1];
    return v;

};

vec BackwardSubstitution(vec b, vec c, vec f, vec v, double h, int n)
{

    for (int i = n-2; i > 0; i--) v[i-1] = (h*h*f[i-1] - c[i-1]*v[i])/double(b[i-1]);
    return v;

};

int main()
{
    vec a, b, c, f, v;
    a, b, c, f, v = vectorConstructor(3);
    cout << a[1] << endl;
    v = ForwardSubstitution(a, b, f, v, (1.0/4), 3);
    v = BackwardSubstitution(b, c, f, v, (1.0/4), 3);
    for (int i = 0; i < 3; i++) cout << v[i] << endl;
    return 0;
}
