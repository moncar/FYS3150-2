from numpy import zeros
from matplotlib.pylab import plot, hold, title, xlabel, ylabel, show
import os

class Error:

    def __init__(self, errors):
        self.errors = errors

    def readFile(self):
        self.delta_lambda = zeros(3)

        filename = open(self.errors, 'r')

        i = 0
        for line in filename:
            self.delta_lambda[i] = float(line)
            i += 1

        filename.close()

if __name__ == '__main__':
    n = zeros(8)
    eigenvalues = zeros((8, 3))
    n[0] = 10
    n[1] = 25
    n[2] = 50
    n[3] = 75
    n[4] = 100
    n[5] = 150
    n[6] = 200
    n[7] = 250

    for i in range(8):
        os.system("./JACOBICPP %g 0" % n[i])
        errors = Error("Errors%g.txt" % n[i])
        errors.readFile()
        eigenvalues[i, :] = errors.delta_lambda

    plot(n, eigenvalues[:, 0])
    hold('on')
    title("Precision of the eigenvalues in Jacobi's method")
    xlabel('n_step')
    ylabel('error(n_step)')
    plot(n, eigenvalues[:, 1])
    plot(n, eigenvalues[:, 2])
    hold('off')
    show()
