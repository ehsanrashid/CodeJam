from math import *

#Result is 2 * 3 * 2 * 5 * 7 * 2 * 3 * 11 * 13 * 2 * 17 * 19 = 232792560

def SmallestDivisible(k):

    # ----------------------
##    i = k
##    while (True):
##        i += k
##        ok = True
##        for x in range(1, k):
##            if (i%x != 0):
##                ok = False
##                break
##        if (ok):
##            num = i
##            break

    # ----------------------
##    num = k
##    while not delbart(num, k):
##        num += k

    # ----------------------
##    num = 1
##    for k in range(1, k+1):
##        if (num%k > 0):
##            for j in range(1, k+1):
##                if ((num*j)%k == 0):
##                    num *= j
##                    break
    # ----------------------

##    for k in range(1, k+1):
##        num = (num*k) // GCD(num, k)
    #-----
##    num = LCMM(*range(1, k+1))
    # ----------------------

##    num = 1
##    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
##    
##    limit = int(sqrt(k))
##    a = [0]*2*limit
##    i = 0
##    check = True
##    for p in primes:
##        if (p > k): break
##        a[i] = 1
##        if (check):
##            if (p <= limit):
##                a[i] = int(log(k) // log(p))
##            else:
##                check = False
##        num *= p**a[i]
##        i += 1
    # ----------------------
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    num = 1
    limit = int(sqrt(k))
    for p in primes:
        if (p > k): break
        if (p <= limit):
            power = int(log(k) // log(p))
            multiple = p**power
        else:   
            multiple = p
        #print p, "->", multiple
        num *= multiple
    # ----------------------
    primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    num = 1
    limit = int(sqrt(k))
    check = True
    for p in primes:
        if (p > k): break
        power = 1
        if (check):
            if (p <= limit):
                power = int(log(k) // log(p))
            else:
                check = False

        num *= p**power
    # ----------------------
    return num

    
def delbart(t, n):
    if (n > 0):
        if (t%n == 0):
            return delbart(t, n-1)
        return False
    return True

def GCD(n1, n2):
    #Return greatest common divisor using Euclid's Algorithm.
    while (n2 > 0):      
        n1, n2 = n2, n1%n2
    return n1

def LCM(n1, n2):
    return (n1*n2) // GCD(n1, n2)

def LCMM(*args):
    return reduce(LCM, args)


k = 20
print SmallestDivisible(k)
