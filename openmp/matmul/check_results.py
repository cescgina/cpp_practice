import numpy as np

for i in [10, 100, 1000]:
    gold = np.loadtxt("C_%d.dat" % i)
    ans = np.loadtxt("C_calc_%d.dat" % i)
    np.testing.assert_array_almost_equal(ans, gold, decimal=3)
    # np.testing.assert_allclose(ans, gold, rtol=1e-3)
print("Everything correct!")
