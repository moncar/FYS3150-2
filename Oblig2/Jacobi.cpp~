# include <iostream>
# include <cmath>
# include <armadillo>
# include <unittest++/UnitTest++.h>
# include <algorithm>

using namespace std;
using namespace arma;

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

int main() {

    int n = 10;
    double eps = 1.0e-8;
    mat A, B, R;
    double rho = 0.0;
    double rho_min = 0.0;

    // Try different values
    double rho_max = 5.0;
    double h = (rho_max - rho_min)/((double) n+1);
    vec d, e, V;
    d = zeros<vec>(n);
    e = zeros<vec>(n);
    V = zeros<vec>(n);
    e.fill(-1.0/(h*h));
    A = zeros(n, n);

    vec diag = A.diag();
    vec diag_upper = A.diag(1);
    vec diag_lower = A.diag(-1);

    diag_upper.fill(-1.0/(h*h));
    diag_lower.fill(-1.0/(h*h));

    for (int i = 0; i < n; i++) {
        rho = rho_min + (i+1)*h;
        V[i] = rho*rho;
        diag[i] = 2.0/(h*h) + V[i];
    }

    A.diag() = diag;
    A.diag(1) = diag_upper;
    A.diag(-1) = diag_lower;

    B = A;

    R = zeros(n, n);
    R.eye();

    Jacobi jacobi;
    jacobi.runJacobi(A, R, n);

    mat eigvec;
    vec eigval;

    eig_sym(eigval, eigvec, B);

    vec eigvalA = A.diag();
    sort(eigvalA.begin(), eigvalA.end());
    cout << eigvalA << endl;
    cout << eigval << endl;

    return UnitTest::RunAllTests();
}

