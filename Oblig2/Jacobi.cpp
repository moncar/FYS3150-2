# include <iostream>
# include <cmath>
# include <armadillo>
# include <unittest++/UnitTest++.h>

using namespace std;
using namespace arma;

class Jacobi {
    public:

        void constructEigenMatrix(mat& R, int n) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i == j) R(i, j) = 1.0;
                    else R(i, j) = 0.0;
                }
            }
        }

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
            if (A(k, l) != 0.0) {
                double t, tau;
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
                    A(i, k) = c*a_ik - s*a_il;
                    A(k, i) = A(i, k);
                    A(i, l) = c*a_il + s*a_ik;
                    A(l, i) = A(i, l);
                }
                // Compute the new eigenvectors
                r_ik = R(i, k);
                r_il = R(i, l);
                R(i, k) = c*r_ik - s*r_il;
                R(i, l) = c*r_il +  s*r_ik;
            }
        } 

        void runJacobi(mat& A, mat& R, int n) {
            constructEigenMatrix(R, n);
            int k, l;
            double max_offdiag = maxoffdiag(A, &k, &l, n);
            double eps = 1.0e-12;
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

    TEST(TestEigen) {

        int n = 5;
        double eps = 1.0e-12;
        mat A, B;

        A << 2 << -1 << 0 << 0 << 0 << endr
          << -1 << 2 << -1 << 0 << 0 << endr
          << 0<< -1 << 2 << -1 << 0 << endr
          << 0 << 0 << -1 << 2 << -1 << endr
          << 0 << 0 << 0 << -1 << 2 << endr;

        B = A;
        mat R = zeros(n, n);
        Jacobi jocabi;
        jocabi.runJacobi(A, R, n);
        vec eigval;
        mat eigvec;
        eig_sym(eigval, eigvec, B);
        vec eigvalA = zeros<vec>(n);
        for (int i = 0; i < n; i++) eigvalA[i] = A(i, i);

        CHECK_CLOSE(norm(R, "fro"), norm(eigvec, "fro"), eps);

        CHECK_CLOSE(norm(eigval, n), norm(eigvalA, n), eps);
    }

    TEST(Schrodinger) {

        int n = 10;
        double eps = 1.0e-8;
        mat A, B, R;
        double rho = 0.0;
        double rho_min = 0.0;

        // Try different values
        double rho_max = 10.0;
        double h = (rho_max - rho_min)/((double) n);
        vec d, e, V;
        d = zeros<vec>(n+2);
        e = zeros<vec>(n+2);
        V = zeros<vec>(n+2);
        e.fill(-1.0/(h*h));
        A = zeros(n, n);

        for (int i = 0; i < n+1; i++) {
            rho = rho_min + i*h;
            V[i] = rho*rho;
            d[i] = (2.0/(h*h)) - V[i];
        }

        A(0, 0) = d[0];
        A(0, 1) = e[0];

        for (int i = 1; i < n-1; i++) {
            A(i, i-1) = e[i-1];
            A(i, i) = d[i];
            A(i, i+1) = e[i];
        }

        A(n-1, n-2) = e[n];
        A(n-1, n-1) = d[n];

        B = A;
        R = zeros(n, n);
        Jacobi jacobi;
        jacobi.runJacobi(A, R, n);
        vec eigval;
        mat eigvec;
        eig_sym(eigval, eigvec, B);
        vec eigvalA = zeros<vec>(n);
        for (int i = 0; i < n; i++) eigvalA[i] = A(i, i);

        CHECK_CLOSE(norm(R, "fro"), norm(eigvec, "fro"), eps);

        CHECK_CLOSE(norm(eigval, n), norm(eigvalA, n), eps);
    }
}

int main() {
   return UnitTest::RunAllTests();

}
