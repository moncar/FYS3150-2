from matplotlib.pylab import plot, show, hold, figure, xlabel, ylabel, title, legend
from numpy import zeros, linalg, array
from unittest import TestCase, main
import os

class TestWavefunction(TestCase):

    def setUp(self):
        self.eigenTemp = zeros((10, 10))
        filename = open("TESTFILE.txt", "w")
        filename.write("%g \t %g \t %g \t %g" % (0, 1.0, 0, 1))
        for i in range(10):
            filename.write("\n%g \t %g" % (i, 5*i))
        for i in range(10):
            for j in range(10):
                self.eigenTemp[j][i] = j
                filename.write("\n%g" % j)
        filename.close()
        self.Wave = Wavefunction("TESTFILE.txt", 10)

    def test_findValues(self):
        omega, omega_i, rho, eigenvectors, eigenvalues = self.Wave.findValues()
        self.assertEqual(omega, 1.0)
        self.assertEqual(omega_i, 0)
        self.assertEqual(linalg.norm(rho), linalg.norm(array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10])))
        self.assertEqual(linalg.norm(eigenvectors), linalg.norm(self.eigenTemp))
        self.assertEqual(linalg.norm(eigenvalues), linalg.norm(5*array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])))


class Wavefunction:

    def __init__(self, solutions, n):
        self.solutions = solutions
        self.n = n

    def findValues(self):
        self.eigenvalues = zeros(self.n)
        self.eigenvectors = zeros((self.n+2, self.n+2))
        self.rho = zeros(self.n+2)

        filename = open(self.solutions, "r")
        splitted = (filename.readline()).split()
        self.omega_iteration = float(splitted[0])
        self.omega = float(splitted[1])
        self.rho_min = float(splitted[2])
        self.h = float(splitted[3])
        
        i = 0
        while i < self.n:
            splitted = (filename.readline()).split()
            self.rho[i+1] = float(splitted[0])
            self.eigenvalues[i] = float(splitted[1])
            i += 1

        for j in range(self.n):
            i = 1
            while i < self.n+1:
                self.eigenvectors[i][j] = float(filename.readline())
                i += 1

        filename.close()

        # Adding the boundary conditions
        self.rho[self.n+1] = self.rho_min + self.n*self.h;

        return self.omega, self.omega_iteration, self.rho, self.eigenvectors, self.eigenvalues

    def plotFunction(self):
        # Is this the right plot?
        # Should the eigenvector be multiplied by the eigenvalue?
        # Perhaps the boundary conditions should be properly set?
        plot(self.rho, self.eigenvectors[:,0])


if __name__ == '__main__':
    
    n = 200
    omega = zeros(4)
    os.system("./JACOBICPP %g 1" % n)
    for i in range(4):
        wavey = Wavefunction("Solutions%g.txt" % i, n)
        wavey.findValues()
        wavey.plotFunction()
        hold('on')
        title("Potential in ground state")
        xlabel("rho")
        ylabel("eigenvectors")
        omega[i] = wavey.omega
    legend(("Omega_r = %g" % omega[0], "Omega_r = %g" % omega[1], "Omega_r = %g" % omega[2],
            "Omega_r = %g" % omega[3]), loc=1)
    hold('off')
    show()

    print "\n\nRunning Python tests"
    main()
