# include <cmath>
# include <string>
# include <armadillo>
# include <cstdlib>
# include <iostream>
# include <fstream>
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
    cout << "Duration of Gaussian Elimination: " 
         << duration_cast<nanoseconds>(finish - start).count()
         << "ns" << endl;

    return v;

};


int main(int argc, char* argv[])
{

    // Check the number of parameters
    if (argc < 2)
    {

        cout << "Usage: " << argv[0] << " 0 (Gaussian)/ 1 (TDMA)" << endl;
        exit(1);

    }

    vec x10 = zeros<vec>(10);
    vec x100 = zeros<vec>(100);
    vec x1000 = zeros<vec>(1000);
    double h10 = 1.0/11;
    double h100 = 1.0/101;
    double h1000 = 1.0/1001;

    vec a10 = zeros<vec>(10);
    vec b10 = zeros<vec>(10);
    vec c10 = zeros<vec>(10);
    vec b_func10 = zeros<vec>(10);
    vec a100 = zeros<vec>(100);
    vec b100 = zeros<vec>(100);
    vec c100 = zeros<vec>(100);
    vec b_func100 = zeros<vec>(100);
    vec a1000 = zeros<vec>(1000);
    vec b1000 = zeros<vec>(1000);
    vec c1000 = zeros<vec>(1000);
    vec b_func1000 = zeros<vec>(1000);
    vec v10, v100, v1000;

    a10.fill(-1);
    b10.fill(2);
    c10.fill(-1);
    a10[0] = 0;
    c10[9] = 0;
    a100.fill(-1);
    b100.fill(2);
    c100.fill(-1);
    a100[0] = 0;
    c100[99] = 0;
    a1000.fill(-1);
    b1000.fill(2);
    c1000.fill(-1);
    a1000[0] = 0;
    c1000[999] = 0;

    b_func10[0] = h10*h10*100*exp(-10*x10[0]);
    b_func100[0] = h100*h100*100*exp(-10*x100[0]);
    b_func1000[0] = h1000*h1000*100*exp(-10*x1000[0]);
    for (int i = 1; i < 10; i++) {

        x10[i] = i*h10;
        b_func10[i] = h10*h10*100*exp(-10*x10[i]);

    }

    for (int i = 1; i < 100; i++) {

        x100[i] = i*h100;
        b_func100[i] = h100*h100*100*exp(-10*x100[i]);

    }

    for (int i = 1; i < 1000; i++) {

        x1000[i] = i*h1000;
        b_func1000[i] = h1000*h1000*100*exp(-10*x1000[i]);

    }

    if (atoi(argv[1]) == 0) {
        v10 = Gaussian(10, a10, b10, c10, b_func10);
        v100 = Gaussian(100, a100, b100, c100, b_func100);
        v1000 = Gaussian(1000, a1000, b1000, c1000, b_func1000);
    } else {
        v10 = TDMA(10, a10, b10, c10, b_func10);
        v100 = TDMA(100, a100, b100, c100, b_func100);
        v1000 = TDMA(1000, a1000, b1000, c1000, b_func1000);
    }

    ofstream file10 ("Solutions10.txt");
    if (file10.is_open()) {
        for (int i = 0; i <  10; i++) {
            file10 << x10[i] << "\t" << v10[i] << "\n";
        }
        file10.close();
    } else cout << "Unable to write to file" << endl;

    ofstream file100 ("Solutions100.txt");
    if (file100.is_open()) {
        for (int i = 0; i <  100; i++) {
            file100 << x100[i] << "\t" << v100[i] << "\n";
        }
        file100.close();
    } else cout << "Unable to write to file" << endl;

    ofstream file1000 ("Solutions1000.txt");
    if (file1000.is_open()) {
        for (int i = 0; i <  1000; i++) {
            file1000 << x1000[i] << "\t" << v1000[i] << "\n";
        }
        file1000.close();
    } else cout << "Unable to write to file" << endl;

    system("python Plotter.py");

    return 0;

}
