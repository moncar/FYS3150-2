from matplotlib.pylab import plot, show, hold, figure, xlabel, ylabel, title
from numpy import zeros, linalg, array
from unittest import TestCase, main

class TestWavefunction(TestCase):

    def setUp(self):
        filename = open("TESTFILE.txt", "w")
        filename.write("%g \t %g" % (0, 1.0))
        for i in range(10):
            # HER VA DU!!!
            filename.write("\n%g \t %g \t %g" % (i, 2*i, 5*i))
        filename.close()
        self.Wave = Wavefunction("TESTFILE.txt", 10)

    def test_findValues(self):
        omega, omega_i, rho, eigenvectors, eigenvalues = self.Wave.findValues()
        self.assertEqual(omega, 1.0)
        self.assertEqual(omega_i, 0)
        self.assertEqual(linalg.norm(rho), linalg.norm(array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])))
        self.assertEqual(linalg.norm(eigenvectors), linalg.norm(2*array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])))
        self.assertEqual(linalg.norm(eigenvalues), linalg.norm(5*array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])))


class Wavefunction:

    def __init__(self, solutions, n):
        self.solutions = solutions
        self.n = n

    def findValues(self):
        self.eigenvalues = zeros(self.n)
        self.eigenvectors = zeros(self.n)
        self.rho = zeros(self.n)

        filename = open(self.solutions, "r")
        splitted = (filename.readline()).split()
        self.omega_iteration = float(splitted[0])
        self.omega = float(splitted[1])
        
        i = 0
        for line in filename:
            splitted = line.split()
            self.rho[i] = float(splitted[0])
            self.eigenvectors[i] = float(splitted[1])
            self.eigenvalues[i] = float(splitted[2])
            i += 1

        filename.close()

        return self.omega, self.omega_iteration, self.rho, self.eigenvectors, self.eigenvalues

    def plotFunction(self):
        plot(self.rho, self.eigenvectors)
        show()


if __name__ == '__main__':
    wavey = Wavefunction("Solutions0.txt", 100)
    wavey.findValues()
    wavey.plotFunction()
    main()
