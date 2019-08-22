import numpy as np

for s in [10, 100, 1000]:
    A = np.random.rand(s, s)
    B = np.random.rand(s, s)
    C = A.dot(B)
    np.savetxt("A_%d.dat" % s, A)
    np.savetxt("B_%d.dat" % s, B)
    np.savetxt("C_%d.dat" % s, C)
