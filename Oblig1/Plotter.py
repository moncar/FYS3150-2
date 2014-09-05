from matplotlib.pylab import plot, show, hold, xlabel, ylabel, figure, legend, title
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
    def __init__(self, solutions, n):

        self.solutions = solutions
        self.n = n

    """
    Reading file and collecting numerical values from the algorithms.
    """
    def reader(self):

        solutions, n = self.solutions, self.n

        self.x = x = zeros(n+2)
        self.v = v = zeros(n+2)
        self.u = u = zeros(n+2)
        file = open(solutions, 'r')
        i = 0

        for values in file:
            splitted = values.split()
            x[i] = float(splitted[0])
            v[i] = float(splitted[1])
            u[i] = float(splitted[2])
            i += 1

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
        plotter = Plotter("Solutions.txt", n)
        plotter.reader()
        plotter.plotValues("LU factorization")

    for exponent in range(1, 6):
        n = 10**exponent
        os.system("./PROJECT1CPP-01 1 %g" % n)
        plotter = Plotter("Solutions.txt", n)
        plotter.reader()
        plotter.plotValues("TDMA")
    os.system("./PROJECT1CPP-01 1 1000000")
    plotter = Plotter("Solutions.txt", 1000000)
    plotter.reader()
    plotter.plotValues("TDMA")
# Plot errors outside

