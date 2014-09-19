# include <iostream>
# include <cmath>
# include <armadillo>
# include <unittest++/UnitTest++.h>
# include <algorithm>
# include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;

class Jacobi {
    public:

        // Perhaps the program will be faster for a mat& A?
        double maxoffdiag(mat A, int* k, int* l, int n) {
            double max = 0.0;
            for (int i = 0; i < n; i++) {
                for (int j = i+1; j < n; j++) {
                    if (fabs(A(i, j)) > max) {
                        max = fabs(A(i, j));
                        *l = i;
                        *k = j;
                    }
                }
            }
            return max;
        }

        void rotate(mat& A, mat& R, int k, int l, int n) {
            double s, c;
            double t, tau;
            if (A(k,l) != 0.0) {
                tau = (A(l, l) - A(k, k))/(2*A(k, l));
                if (tau > 0) t = 1.0/(tau + sqrt(1.0 + tau*tau));
                else t = -1.0/(-tau + sqrt(1.0 + tau*tau));

                c = 1/sqrt(1 + t*t);
                s = c*t;
            } else {
                c = 1.0;
                s = 0.0;
            }

            double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
            a_kk = A(k, k);
            a_ll = A(l, l);

            // Changing the matrix elements with indices k and l
            A(k, k) = c*c*a_kk - 2.0*c*s*A(k, l) + s*s*a_ll;
            A(l, l) = s*s*a_kk + 2.0*c*s*A(k, l) + c*c*a_ll;
            A(k, l) = 0.0;
            A(l, k) = 0.0;

            // change the remaining elements
            for (int i = 0; i < n; i++) {
                if (i != k && i != l) {
                    a_ik = A(i, k);
                    a_il = A(i, l);
                    A(i, k) = A(k, i) = c*a_ik - s*a_il;
                    A(i, l) = A(l, i) = c*a_il + s*a_ik;
                }

                // Compute the new eigenvectors
                r_ik = R(i, k);
                r_il = R(i, l);
                R(i, k) = c*r_ik - s*r_il;
                R(i, l) = c*r_il +  s*r_ik;
            }
        } 

        void runJacobi(mat& A, mat& R, int n) {
            int k, l;
            double max_offdiag = maxoffdiag(A, &k, &l, n);
            double eps = 1.0e-8;
            int iterations = 0;
            double max_number_iterations = (double) n * (double) n * (double) n; 
            while (fabs(max_offdiag) > eps && (double) iterations < max_number_iterations) {
                max_offdiag = maxoffdiag(A, &k, &l, n);
                rotate(A, R, k, l, n);
                iterations++;
            }
            cout << "Number of iterations: " << iterations << "\n";
        }
};

SUITE(TestJacobi) {

    /*
     * Performing one Jacobi rotation by hand and checking it
     * against the values obtained numerically.
     */
    TEST(Rotation) {
        int n = 3;
        int k = 1;
        int l = 2;
        double eps = 1.0e-8;
        mat A, R;

        A << 2 << -1 << 0 << endr
          << -1 << 2 << -1 << endr
          << 0 << -1 << 2 << endr;

        R = zeros(n, n);
        R.eye();
        Jacobi rotation;
        rotation.rotate(A, R, k, l, n);

        mat A_exact, R_exact;
        
        A_exact << 2 << -1/sqrt(2) << 1/sqrt(2) << endr
                << -1/sqrt(2) << 1 << 0 << endr
                << -1/sqrt(2) << 0 << 3 << endr;

        R_exact << 1 << 0 << 0 << endr
                << 0 << 1/sqrt(2) << 1/sqrt(2) << endr
                << 0 << -1/sqrt(2) << 1/sqrt(2) << endr;

        CHECK_CLOSE(norm(A, "fro"), norm(A_exact, "fro"), eps);
        CHECK_CLOSE(norm(R, "fro"), norm(R_exact, "fro"), eps);

    }

    /*
     * Testing maxoffdiag-function for a 3 by 3 matrix where
     * we easily see the correct answer.
     */
    TEST(Max) {
        int n = 3;
        int k = 0;
        int l = 0;
        double max;
        mat A;

        A << 1 << -1 << 3 << endr
          << -1 << 3 << -1 << endr
          << 0 << -1 << 2 << endr;

        Jacobi maxoff;
        max = maxoff.maxoffdiag(A, &k, &l, n);
        
        CHECK(max == 3);
    }

    /*
     * Checking the class against exact values obtained
     * from Wolfram Alpha.
     */
    TEST(Total) {
        int n = 3;
        double eps = 1.0e-8;
        mat A, R;
        A << 1 << 0 << 1 << endr
          << 0 << 1 << 0 << endr
          << 1 << 0 << 1 << endr;

        R = zeros(n, n);
        R.eye();

        Jacobi total;
        total.runJacobi(A, R, n);

        mat A_exact, R_exact;
        A_exact << 2 << 0 << 0 << endr
                << 0 << 1 << 0 << endr
                << 0 << 0 << 0 << endr;

        R_exact << 1 << 0 << -1 << endr
                << 0 << 1 << 0 << endr
                << 1 << 0 << 1 << endr;

        // The norm of the eigenvectors in Jacobi is 1.
        // Wolfram Alpha gives us "nice" values, we therefore make sure
        // that the norm of each column (eigenvector) will be 1.
        R_exact.col(0) = R_exact.col(0)/norm(R_exact.col(0), "fro");
        R_exact.col(1) = R_exact.col(1)/norm(R_exact.col(1), "fro");
        R_exact.col(2) = R_exact.col(2)/norm(R_exact.col(2), "fro");

        CHECK_CLOSE(norm(A, "fro"), norm(A_exact, "fro"), eps);
        CHECK_CLOSE(norm(R, "fro"), norm(R_exact, "fro"), eps);
    }
}

void Schrodinger(vec* V, mat* A, mat* B, mat* R, int n) {

    Jacobi jacobi;

    // Starting clock
    auto start = high_resolution_clock::now();
    jacobi.runJacobi(*A, *R, n);
    auto finish = high_resolution_clock::now();

    cout << "Duration of Jacobi with n = " << n << ": "
         << duration_cast<nanoseconds>(finish - start).count()
         << "ns" << endl;

    mat eigvec;
    vec eigval;

    eig_sym(eigval, eigvec, *B);

    // Try to fix eigenvector values and sorting
    // Consider a test for the values
    vec eigvalA = (*A).diag();
    sort(eigvalA.begin(), eigvalA.end());
}


int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " (int) n (Potential from a) 0/1 (Potential from c)" << endl;
        exit(1);;
    }

    int n = atoi(argv[1]);
    mat A, B, R;

    // Check dependency to rho_max
    double rho = 0.0;
    double rho_min = 0.0;
    double rho_max = 5.0;
    double h = (rho_max - rho_min)/((double) n+1);
    vec d, e;
    d = zeros<vec>(n);
    e = zeros<vec>(n);
    e.fill(-1.0/(h*h));
    A = zeros(n, n);

    vec diag = A.diag();
    vec diag_upper = A.diag(1);
    vec diag_lower = A.diag(-1);

    diag_upper.fill(-1.0/(h*h));
    diag_lower.fill(-1.0/(h*h));
    A.diag(1) = diag_upper;
    A.diag(-1) = diag_lower;

    R = zeros(n, n);
    R.eye();

    vec V = zeros<vec>(n);

    if (atoi(argv[2]) == 0) {
        for (int i = 0; i < n; i++) {
            rho = rho_min + (i+1)*h;
            V[i] = rho*rho;
            diag[i] = 2.0/(h*h) + V[i];
        }
        A.diag() = diag;
        B = A;
        Schrodinger(&V, &A, &B, &R, n);
    } else {
        vec omega = zeros<vec>(4);
        omega[0] = 0.01;
        omega[1] = 0.5;
        omega[2] = 1.0;
        omega[3] = 5;
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < n; i++) {
                rho = rho_min + (i+1)*h;
                V[i] = omega[j]*omega[j]*rho*rho + 1.0/rho;
                diag[i] = 2.0/(h*h) + V[i];
            }
            A.diag() = diag;
            B = A;
            mat A_temp = A;
            mat B_temp = B;
            mat R_temp = R;
            vec V_temp = V;
            Schrodinger(&V_temp, &A_temp, &B_temp, &R_temp, n);
        }
    }

    cout << "\nTEST" << endl;
    return UnitTest::RunAllTests();
}

