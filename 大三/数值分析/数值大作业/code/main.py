
import matplotlib.pyplot as plt
import math
import numpy as np
from scipy.special import *
from scipy.misc import derivative

print(zeta(2.1,1))

def f(x):
    return zeta(x,1)
def fp(x):
    return derivative(f, x, dx=1e-5)
def fpp(x):
    return derivative(fp, x, dx=1e-5)

print(fpp(2))

x = np.arange(1.1, 10, 0.01)
y = [fpp(i)/(fp(i))**2 for i in x]

plt.plot(x, y, label="zeta")
plt.xlabel("x")
plt.ylabel("y")
plt.ylim(-10, 10)
plt.legend()
plt.show()