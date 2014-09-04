from matplotlib.pylab import plot, show, hold, xlabel, ylabel, figure, legend
from numpy import zeros



class Plotter:

    def __init__(self, solutions10, solutions100, solutions1000):

        self.solutions10 = solutions10
        self.solutions100 = solutions100
        self.solutions1000 = solutions1000

    def reader(self):

        solutions10, solutions100, solutions1000 =\
        self.solutions10, self.solutions100, self.solutions1000

        self.x10 = x10 = zeros(10)
        self.x100 = x100 = zeros(100)
        self.x1000 = x1000 = zeros(1000)
        self.v10 = v10 = zeros(10)
        self.v100 = v100 = zeros(100)
        self.v1000 = v1000 = zeros(1000)
        file10 = open(solutions10, 'r')
        file100 = open(solutions100, 'r')
        file1000 = open(solutions1000, 'r')
        i = 0

        for values in file10: 
            splitted = values.split()
            x10[i] = float(splitted[0])
            v10[i] = float(splitted[1])
            i += 1

        i = 0
        for values in file100: 
            splitted = values.split()
            x100[i] = float(splitted[0])
            v100[i] = float(splitted[1])
            i += 1

        i = 0
        for values in file1000: 
            splitted = values.split()
            x1000[i] = float(splitted[0])
            v1000[i] = float(splitted[1])
            i += 1

    def plotter(self):

        x10, x100, x1000, v10, v100, v1000 =\
        self.x10, self.x100, self.x1000, self.v10, self.v100, self.v1000

        plt10 = plot(x10, v10)
        hold('on')
        plt100 = plot(x100, v100)
        plt1000 = plot(x1000, v1000)

        xlabel('x values')
        ylabel('v values')

        legend(('n = 10', 'n = 100', 'n = 1000'), loc = 1)
        hold('off')

        show()



if __name__ == '__main__':

    plotter = Plotter('Solutions10.txt', 'Solutions100.txt', 'Solutions1000.txt')
    plotter.reader()
    plotter.plotter()

