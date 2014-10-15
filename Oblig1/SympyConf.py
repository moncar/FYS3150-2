from sympy import symbols, Matrix
from numpy import exp

A = Matrix([[2, -1, 0, 2], [-1, 2, -1, 4], [0, -1, 2, 6]])
print A.rref()
