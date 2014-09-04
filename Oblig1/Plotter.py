from matplotlib.pylab import plot, show, hold, xlabel, ylabel, figure, legend
from numpy import zeros



class Plotter:

    def __init__(self, solutions10, solutions100, solutions1000):

        self.solutions10 = solutions10
        self.solutions100 = solutions100
        self.solutions1000 = solutions1000

    def reader():

        solutions10, solutions100, solutions1000 =
        self.solutions10, self.solutions100, self.solutions1000

        self.x10 = zeros(10)
        self.x100 = zeros(100)
        self.x1000 = zeros(1000)
        self.v10 = zeros(10)
        self.v100 = zeros(100)
        self.v1000 = zeros(1000)
        solutions10 = open("Solutions10.txt")
        solutions100 = open("Solutions100.txt")
        solutions1000 = open("Solutions1000.txt")

        for i in range(10):
            splitted = solutions10.split()
            x10[i] = float(splitted[0])
            v10[i] = float(splitted[1])

        for i in range(100):
            splitted = solutions100.split()
            x100[i] = float(splitted[0])
            v100[i] = float(splitted[1])

        for i in range(1000):
            splitted = solutions1000.split()
            x1000[i] = float(splitted[0])
            v1000[i] = float(splitted[1])

    def plotter():

        x10, x100, x1000, v10, v100, v1000 =
        self.x10, self.x100, self.x1000, self.v10, self.v100, self.v1000

        plt = figure()
        plt10 = plt.plot(x10, v10)
        hold('on')
        plt100 = plt.plot(x100, v100)
        plt1000 = plt.plot(x1000, v1000)

        plt.xlabel('x values')
        plt.ylabel('v values')

        plt.legend([plt10, plt100, plt1000], ['n = 10', 'n = 100', 'n = 1000'])
        hold('off')

        show()
