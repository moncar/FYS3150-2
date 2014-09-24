from matplotlib.pylab import plot, show, hold, figure, xlabel, ylabel, title
from numpy import zeros, linalg, array
from unittest import TestCase, main

class TestWavefunction(TestCase):

    def setUp(self):
        self.eigenTemp = zeros((10, 10))
        filename = open("TESTFILE.txt", "w")
        filename.write("%g \t %g" % (0, 1.0))
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
        self.assertEqual(linalg.norm(rho), linalg.norm(array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])))
        self.assertEqual(linalg.norm(eigenvectors), linalg.norm(self.eigenTemp))
        self.assertEqual(linalg.norm(eigenvalues), linalg.norm(5*array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])))


class Wavefunction:

    def __init__(self, solutions, n):
        self.solutions = solutions
        self.n = n

    def findValues(self):
        self.eigenvalues = zeros(self.n)
        self.eigenvectors = zeros((self.n, self.n))
        self.rho = zeros(self.n)

        filename = open(self.solutions, "r")
        splitted = (filename.readline()).split()
        self.omega_iteration = float(splitted[0])
        self.omega = float(splitted[1])
        
        i = 0
        while i < self.n:
            splitted = (filename.readline()).split()
            self.rho[i] = float(splitted[0])
            self.eigenvalues[i] = float(splitted[1])
            i += 1

        for j in range(self.n):
            i = 0
            while i < self.n:
                self.eigenvectors[i][j] = float(filename.readline())
                i += 1

        filename.close()

        return self.omega, self.omega_iteration, self.rho, self.eigenvectors, self.eigenvalues

    def plotFunction(self):
        # Is this the right plot?
        # Should the eigenvector be multiplied by the eigenvalue?
        # Perhaps the boundary conditions should be properly set?
        plot(self.rho, self.eigenvectors[:,0])
        show()


if __name__ == '__main__':
    wavey = Wavefunction("Solutions0.txt", 200)
    wavey.findValues()
    wavey.plotFunction()
    main()
