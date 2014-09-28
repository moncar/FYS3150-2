from matplotlib.pylab import plot, show, hold, figure, xlabel, ylabel, title, legend
from numpy import zeros, linalg, array, dot, sqrt
from unittest import TestCase, main
import os

class TestWavefunction(TestCase):

    def setUp(self):
        self.eigenTemp = zeros((10, 10))
        filename = open("TESTFILE.txt", "w")
        filename.write("%g \t %g \t %g \t %g" % (0, 1, 0, 1))
        for i in range(10):
            filename.write("\n%g" % (5*i))
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
        self.assertEqual(linalg.norm(rho), linalg.norm(array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12])))
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
            self.eigenvalues[i] = float(filename.readline())
            self.rho[i] = self.rho_min + (i+1)*self.h
            i += 1

        for j in range(self.n):
            i = 1
            while i < self.n+1:
                self.eigenvectors[i][j] = float(filename.readline())
                i += 1

        filename.close()

        # Adding the boundary conditions
        # Should be five, but due to numerical roundoff in the filewriting and reading
        # it doesnt get enough significants to solve this
        self.rho[self.n] = self.rho_min + (self.n+1)*self.h
        self.rho[self.n+1] = self.rho_min + (self.n+2)*self.h

        return self.omega, self.omega_iteration, self.rho, self.eigenvectors, self.eigenvalues

    def trapezoidal(self, v):
        s = 0
        for i in range(self.n+1):
            s += v[i+1] + v[i]
        return (self.h/2.0)*s

    
    def normalize(self):
        for i in range(self.n+2):
            self.eigenvectors[:, i] = self.eigenvectors[:, i]/float(sqrt(self.trapezoidal(self.eigenvectors[:, i]**2)) + 1.0e-10)

        

    def plotFunction(self):
        plot(self.rho, self.eigenvectors[:, 0]**2)


if __name__ == '__main__':

    n = 200
    wavey = []
    omega = zeros(4)
    os.system("./JACOBICPP %g 1" % n)
    for i in range(4):
        wavey.append(Wavefunction("Solutions%g.txt" % i, n))
        wavey[i].findValues()
        wavey[i].normalize()
        wavey[i].plotFunction()
        hold('on')
        title("Potential in ground state")
        xlabel("rho")
        ylabel("potential")
        omega[i] = wavey[i].omega
    legend(("Omega_r = %g" % omega[0], "Omega_r = %g" % omega[1], "Omega_r = %g" % omega[2],
            "Omega_r = %g" % omega[3]), loc=1)
    hold('off')
    show()

    os.system("./JACOBICPP %g 0" % n)
    wavey.append(Wavefunction("Solutions_old.txt", n))
    wavey[4].findValues();
    wavey[4].normalize()
    figure()
    wavey[4].plotFunction()
    hold('on')
    wavey[2].plotFunction()
    title("Potential with and without Coulomb interaction")
    xlabel("rho")
    ylabel("potential")
    legend(("Without Coulomb interaction", "With Coulomb interaction and omega_r = 1.0"))
    hold('off')
    show()

    for i in range(4):
        figure()
        wavey[i].plotFunction()
        title("Potential in ground state for omega_r = %g" % omega[i])
        xlabel("rho")
        ylabel("potential")
        show()

    print "\n\nRunning Python tests"
    main()
