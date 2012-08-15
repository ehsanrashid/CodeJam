from math import *

def MaxPrimeFactor(num):
    #----------------------------
##    primes = set([2])
##    div = 3
##    while (div < sqrt(num)):
##        for p in primes:
##            if (div%p == 0):
##                div += 2
##                continue
##        primes.add(div)
##        if (num%div == 0):
##            num /= div
##    maxPrimeFactor = num
    #----------------------------
    primeFac = list(PrimeFactors(num))
    maxPrimeFactor = primeFac[-1]
    #maxPrimeFactor = max(PrimeFactors(num))
    #----------------------------
    return maxPrimeFactor

##prime factors of n
def PrimeFactors(n):
    # -----------------------
    x = 2
    while (n > x):        
        if (n%x == 0):
            while (n%x == 0):
                yield x
                n /= x               
        x += x%2 + 1
    if (n%x == 0):
            yield x
    # -----------------------
##    for p in Primes(2, n):
##        if (n%p == 0):
##            n /= p
##            yield p
##        if (n == 1):
##            break
    # -----------------------
##    for p in Sieve(n):
##        if (n%p == 0):
##            yield p
    # -----------------------


def Sieve(n):
    limit = int(n**0.5) ##candidates below sqrt of n -- this is the upper limit
    candidates = list(range(limit+1)) ##This is an change of the wiki code
    # Loop over the candidates, marking out each multiple.
    for i in xrange(2, limit+1): 
        if candidates[i]:
            # replaces all multiples of i with None
            candidates[2*i::i] = [None] * (limit//i - 1)        
    # Filter out non-primes and return the list.
    primes = [p for p in candidates[2:] if p]
    return primes


plist = [2]
def Primes(min, max):
    if min <= 2: yield 2
    for n in lrange(3, max, 2):
        for p in plist:
            if (n%p == 0) or (p*p > n):
                break
        if (n%p != 0):
            plist.append(n)
            if (n >= min):
                yield n

import operator
def lrange(num1, num2 = None, step = 1):
    op = operator.__lt__

    if (num2 is None):
        num1, num2 = 0, num1
    if (num2 < num1):
        if (step > 0):
            num1 = num2
        op = operator.__gt__
    elif (step < 0):
        num1 = num2

    while op(num1, num2):
        yield num1
        num1 += step

num = 600851475143
print MaxPrimeFactor(num)
