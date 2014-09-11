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
                    if (fabs(A(i, j) > max)) {
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

        void runJacobi(mat A, mat& R, int n) {
            constructEigenMatrix(R, n);
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

TEST(Mattematt) {
    int n = 3;
    mat A;
    A << 2 << 1 << 0 << endr
      << 1 << 2 << 1 << endr
      << 0 << 1 << 2 << endr;
    mat R = zeros(3, 3);
    Jacobi jocabi;
    jocabi.runJacobi(A, R, n);
    cout << R << endl;
    CHECK(1 == 1);
}

int main() {
   return UnitTest::RunAllTests();
}
