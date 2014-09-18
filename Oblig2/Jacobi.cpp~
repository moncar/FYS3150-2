# include <iostream>
# include <cmath>
# include <armadillo>
# include <unittest++/UnitTest++.h>
# include <algorithm>

using namespace std;
using namespace arma;

class Jacobi {
    public:

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
            cout << max << endl;
        }

        void rotate(mat& A, mat& R, int k, int l, int n) {
            double s, c;
            double t, tau;
            tau = (A(l, l) - A(k, k))/(2*A(k, l));
            if (tau > 0) t = 1.0/(tau + sqrt(1.0 + tau*tau));
            else t = -1.0/(-tau + sqrt(1.0 + tau*tau));

            c = 1/sqrt(1 + t*t);
            s = c*t;

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
                    A(i, k) = A(i, k) = c*a_ik - s*a_il;
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

    TEST(TestEigen) {

        int n = 5;
        double eps = 1.0e-8;
        mat A, B;

        A << 2 << -1 << 0 << 0 << 0 << endr
          << -1 << 2 << -1 << 0 << 0 << endr
          << 0<< -1 << 2 << -1 << 0 << endr
          << 0 << 0 << -1 << 2 << -1 << endr
          << 0 << 0 << 0 << -1 << 2 << endr;

        B = A;
        mat R = zeros(n, n);
        R.eye();
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

        int n = 100;
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

        B = A;
        R = zeros(n, n);
        R.eye();
        Jacobi jacobi;
        jacobi.runJacobi(A, R, n);
        vec eigval;
        mat eigvec;
        eig_sym(eigval, eigvec, B);
        vec eigvalA = zeros<vec>(n);
        for (int i = 0; i < n; i++) eigvalA[i] = A(i, i);

        sort(eigvalA.begin(), eigvalA.end());

        CHECK_CLOSE(norm(R, "fro"), norm(eigvec, "fro"), eps);

        CHECK_CLOSE(norm(eigval, 2), norm(eigvalA, 2), eps);
    }
}

int main() {
   return UnitTest::RunAllTests();

}
