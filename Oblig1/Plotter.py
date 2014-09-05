from matplotlib.pylab import plot, show, hold, xlabel, ylabel, figure, legend, title, xscale
from numpy import zeros, exp
import os


"""
Class Plotter accepts string filename.format.
The class implements two methods writing and plotting 
"""
class Plotter:

    """
    Storing filename, the exact solution and grid points.
    """
    def __init__(self, solutions, errors, n):

        self.solutions = solutions
        self.errors = errors
        self.n = n

    """
    Reading file and collecting numerical values from the algorithms.
    """
    def reader(self):

        solutions, errors, n = self.solutions, self.errors, self.n

        self.x = x = zeros(n+2)
        self.v = v = zeros(n+2)
        self.u = u = zeros(n+2)
        fileVals = open(solutions, 'r')
        fileErrors = open(errors, 'r')
        for line in fileErrors:
            errorSplit = line.split()
            errorLocation = float(errorSplit[0])
            epsilon = float(errorSplit[2])
        
        i = 0

        for values in fileVals:
            splitted = values.split()
            x[i] = float(splitted[0])
            v[i] = float(splitted[1])
            u[i] = float(splitted[2])
            i += 1

        return errorLocation, epsilon

    def plotValues(self, TITLE):

        x, v, u, n = self.x, self.v, self.u, self.n

        plt = plot(x, v)
        hold('on')
        pltEXACT = plot(x, u)

        xlabel('x values')
        ylabel('function values')

        legend(('n = %g' %  n, 'EXACT'), loc = 1)
        title(TITLE)
        hold('off')

        show()




if __name__ == '__main__':

    for exponent in range(1, 4):
        n = 10**exponent
        os.system("./PROJECT1CPP-01 0 %g" % n)
        plotter = Plotter("Solutions.txt", "Errors.txt", n)
        plotter.reader()
        plotter.plotValues("LU factorization")

    error = zeros(6)
    errorLocation = zeros(6)
    for exponent in range(1, 6):
        n = 10**exponent
        os.system("./PROJECT1CPP-01 1 %g" % n)
        plotter = Plotter("Solutions.txt", "Errors.txt", n)
        errorLocation[exponent - 1], error[exponent - 1] = plotter.reader()
        plotter.plotValues("TDMA")
    os.system("./PROJECT1CPP-01 1 1000000")
    plotter = Plotter("Solutions.txt", "Errors.txt", 1000000)
    errorLocation[5], error[5] = plotter.reader()
    plotter.plotValues("TDMA")

    plot(errorLocation, error)
    title("Errors in TDMA")
    xlabel("Number of iterations")
    ylabel("The largest error")
    xscale('log')
    show()
# Plot errors outside

