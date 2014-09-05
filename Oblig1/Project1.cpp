# include <cmath>
# include <string>
# include <armadillo>
# include <cstdlib>
# include <iostream>
// <fstream> allows for running command line in C++
# include <fstream>
# include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;

/*
 * Method implementing the Tridiagonal Matrix Algorithm (TDMA).
 */
vec TDMA(int n, vec a, vec b, vec c, vec b_func) {

    vec gamma = zeros<vec>(n+2);
    vec lambda = zeros<vec>(n+2);
    vec v = zeros<vec>(n+2);

    // Starting clock
    auto start = high_resolution_clock::now();
    
    /*
     * Implementing the Thomas Algorithm
     */

    // Forward substitution
    lambda[1] = b[1];
    v[1] = b_func[1]/lambda[1];
    for (int i = 2; i < n+1; i++) {
        gamma[i] = c[i-1]/lambda[i-1];
        lambda[i] = b[i] - gamma[i]*a[i];
        v[i] = (b_func[i] - a[i]*v[i-1])/lambda[i];
    }

    // Backward substitution
    for (int i = n; i > 0; i--) {
        v[i] -= gamma[i+1]*v[i+1];
    }

    auto finish = high_resolution_clock::now();
    cout << "Duration of TDMA with n = " << n+2 << ": " 
         << duration_cast<nanoseconds>(finish - start).count()
         << "ns" << endl;


    return v;

};


/*
 * Method implementing the LU decomposition and solution.
 */
vec LU(int n, vec a, vec b, vec c, vec b_func) {

    // Here be dragons
    mat A = zeros(n+2, n+2);
    mat L, U, P;
    vec v = zeros(n+2);
    vec y = zeros(n+2);
    double temp;

    A(0, 0) = b[0];
    A(0, 1) = c[0];

    for (int i = 1; i < n+1; i++) {
        A(i, i-1) = a[i];
        A(i, i) = b[i];
        A(i, i+1) = c[i];
    }

    A(n+1, n) = a[n+1];
    A(n+1, n+1) = b[n+1];

    auto start = high_resolution_clock::now();

    // Impelement LU

    lu(L, U, P, A);

    y[1] = b_func[1]/L(1, 1);
    y[2] = (b_func[2] - L(2, 1)*y[1])/L(2, 2);
    for (int i = 3; i < n+1; i++) {
        for (int j = 1; j < i; j++) {
            temp += L(i, j)*y[j];
        }
        y[i] = (b_func[i] - temp)/L(i, i);
    }

    temp = 0;
    v[n] = y[n]/U(n, n);
    v[n-1] = (y[n-1] - U(n-1, n)*v[n])/U(n-1, n-1);
    for (int i = n-2; i > 0; i--) {
        for (int j = n; j > i; j--) {
            temp += U(i, j)*v[j];
        }
        v[i] = (y[i] - temp)/U(i, i);
    }
    
    cout << v << endl;

    auto finish = high_resolution_clock::now();
    cout << "Duration of Gaussian Elimination with n = " << n+2 << ": " 
         << duration_cast<nanoseconds>(finish - start).count()
         << "ns" << endl;

    return v;

};

// Ampersand after type means reference. The variable is treated as a value
// and changed globally.
void ErrorEstimate(int n, vec u, vec v, double& epsilon, int& location) {

    double temp;

    for (int i = 1; i < n+1; i++) {
        temp = abs((v[i] - u[i])/u[i]);
        if (epsilon < temp) epsilon = temp; location = i;
    }
    epsilon = log10(epsilon);
};


int main(int argc, char* argv[]) {

    // Check the number of parameters
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " 0 (Gaussian)/ 1 (TDMA) (int n)" << endl;
        exit(1);
    }

    // Creating vectors of length n
    int n = atoi(argv[2]);
    int errorLocation;
    vec x = zeros<vec>(n+2);
    double h = 1.0/(n+1);
    double epsilon;

    vec a = zeros<vec>(n+2);
    vec b = zeros<vec>(n+2);
    vec c = zeros<vec>(n+2);
    vec b_func = zeros<vec>(n+2);
    vec u = zeros<vec>(n+2);
    vec v;

    // Fill entire arrays with single value
    a.fill(-1);
    b.fill(2);
    c.fill(-1);
    a[0] = 0;
    c[n+1] = 0;

    // Implementing function values
    // Fixing endpoints
    // Adding exact values
    b_func[1] = h*h*100*exp(-10*x[1]);
    x[1] = 1*h;
    u[1] = 1 - (1 - exp(-10))*x[1] - exp(-10*x[1]);
    for (int i = 2; i < n+1; i++) {
        x[i] = i*h;
        b_func[i] = h*h*100*exp(-10*x[i]);
        u[i] = 1 - (1 - exp(-10))*x[i] - exp(-10*x[i]);
    }

    // Choosing method for solution 
    if (atoi(argv[1]) == 0) {
        v = LU(n, a, b, c, b_func);
        ErrorEstimate(n, u, v, epsilon, errorLocation);
    }
    else if (atoi(argv[1]) == 1) {
        v = TDMA(n, a, b, c, b_func);
        ErrorEstimate(n, u, v, epsilon, errorLocation);
    }
    else {
        cout << "Please choose 0 (Gaussian) or 1 (TDMA) for impelementation." << endl;
        exit(1);
    }

    // Creating file containing x and v values
    ofstream file("Solutions.txt");
    if (file.is_open()) {
        for (int i = 0; i < n+2; i++) {
            file << x[i] << "\t" << v[i] << "\n";
        }
    } else cout << "Unable to write to file" << endl;

    // Creating file containing error values
    ofstream errorFile("Errors.txt");
    if (errorFile.is_open()) errorFile << errorLocation << "\t" << x[errorLocation] << "\t" << epsilon << endl;
    else cout << "Unable to write to file" << endl;

    return 0;

}
