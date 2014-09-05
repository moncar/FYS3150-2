from matplotlib.pylab import plot, show, hold, xlabel, ylabel, figure, legend
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
    def __init__(self, solutions, u, n):

        self.solutions = solutions
        self.u = u
        self.n = n

    """
    Reading file and collecting numerical values from the algorithms.
    """
    def reader(self):

        solutions, u, n = self.solutions, self.u, self.n

        self.x = x = zeros(n+2)
        self.v = v = zeros(n+2)
        self.u = u = zeros(n+2)
        file = open(solutions, 'r')
        i = 0

        for values in file:
            splitted = values.split()
            x[i] = float(splitted[0])
            v[i] = float(splitted[1])
            i += 1

    def plotValues(self):

        x, v, u, n = self.x, self.v, self.u, self.n

        plt = plot(x, v)
        hold('on')
        pltEXACT = plot(x, u)

        xlabel('x values')
        ylabel('function values')

        legend(('n = %g' %  n, 'EXACT'), loc = 1)
        hold('off')

        show()




if __name__ == '__main__':

    plotter = Plotter('Solutions.txt')
    plotter.reader()
    plotter.plotValues()
# Plot errors outside

