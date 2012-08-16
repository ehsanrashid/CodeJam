from math import sqrt

def nth(gen, n):
    for i in xrange(n - 1):
        gen.next()
    return gen.next()

def GenPrimes():
    yield 2
    yield 3
    n = 5
    while True:
        if IsPrime(n):
            yield n
        n += 2
	
def IsPrime(num):
    num = int(abs(num))
    if (num <= 1): return False
    if (num == 2): return True
    if (num%2 == 0): return False
    if (num < 9): return True
    if (num%3 == 0): return False
    if (num < 25): return True

    limit = int(sqrt(num))

    # ------------------------

##    d = 3
##    while (d <= limit):
##        if (num%d == 0):
##            return False
##        d += 2
##    return True

    # ------------------------
    d = 5
    while (d <= limit):
        if (num%d == 0) or (num%(d+2) == 0):
            return False
        d += 6
    return True

    
if (__name__ == "__main__"):
    k = 10001

    ##primes = [2]
    ##num = 3
    ##while (len(primes) < k):
    ##    if IsPrime(num):
    ##        primes.append(num)
    ##    num += 2
    ##
    ##print primes[-1]

    print nth(GenPrimes(), k)