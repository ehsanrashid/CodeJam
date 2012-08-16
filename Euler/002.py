import itertools

def SumEvenFiboSeq(limit):
    efsum = 0
    # ---------------------
##    f1, f2 = 0, 1
##    while (f2 < limit):
##        if (f2%2 == 0): efsum += f2
##        f1, f2 = f2, f1 + f2
    # ---------------------
##    f1, f2 = 1, 1
##    f3 = f1 + f2 # even
##    while (f3 < limit):
##        efsum += f3
##        f1 = f2 + f3
##        f2 = f3 + f1
##        f3 = f1 + f2
    # ---------------------
##    f1, f2 = 1, 2
##    while (f2 < limit):
##        efsum += f2
##        f1, f2 = f1 + 2*f2, 2*f1 + 3*f2
    # ---------------------
##    fib = [0, 1]
##    x = 0
##    while (fib[x] < limit):
##        x = len(fib)
##        fib.append(fib[x-2] + fib[x-1])
##        if (fib[x]%2 == 0):
##            efsum += fib[x]
    # ---------------------
##    efsum = sum(x for x in LimitSeq(FiboSeq(), limit) if (x%2 == 0))
    # ---------------------
##    efsum = sum(EvenSeq(LimitSeq(FiboSeq(), limit)))
    # ---------------------
##    efsum = sum(x for x in itertools.takewhile(lambda x: x < limit, FiboSeq()) if (x%2 == 0))
    # ---------------------
##    efsum = sum([FiboN(x) for x in range(0, int(ceil(log(limit, goldenRatio))) + 2, 3)])
    # ---------------------
    i = 0
    while fib(i) <= 4000000:
        if (fib(i)%2 == 0):
            efsum += fib(i)
        i += 1
    # ---------------------
    
    return efsum

from math import *

root5 = sqrt(5)
goldenRatio  = (root5 + 1)/2
goldenRatio_ = (root5 - 1)/2

def FiboN(n):
    n = int(abs(n))
    if (n == 0): return 0
    if (n <= 2): return 1
    if (n == 3): return 2
    if (n == 4): return 3
    #return FiboN(n - 1) + FiboN(n - 2);
    #return int((pow(goldenRatio, n) - pow(-goldenRatio_, n)) / root5)
    return int((goldenRatio ** n / root5) + 0.5)

## ----------------------------------
def FiboSeq():
    f1, f2 = 0, 1
    while (True):
        yield f1
        f1, f2 = f2, f1 + f2

def LimitSeq(seq, limit):
    for n in seq:
        if (n >= limit):
            break
        yield n

def EvenSeq(seq):
    for n in seq:
        if (n%2 == 0):
            yield n

## ----------------------------------

cache = {}
def fib(n):
    cache[n] = cache.get(n, 0) or (n <= 1 and 1 or fib(n-1) + fib(n-2))
    return cache[n]

## ----------------------------------
##import numpy
##def nFibo(limit):
##    allnum = list(fibfun(limit))  
##    npall = numpy.array(allnum)
##    npeven = npall[np.where(npall%2 == 0)]
##    return numpy.sum(npeven)
## ----------------------------------

limit = 4000000
print SumEvenFiboSeq(limit)
