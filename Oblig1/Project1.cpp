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

}
