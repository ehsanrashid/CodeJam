
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

def Factors(n):
    # 1 and n are automatically factors of n
    fact=[1,n]
    # starting at 2 as we have already dealt with 1
    check=2
    # calculate the square root of n and use this as the 
    # limit when checking if a number is divisible as 
    # factors above sqrt(n) will already be calculated as 
    # the inverse of a lower factor IE. finding factors of 
    # 100 only need go up to 10 (sqrt(100)=10) as factors 
    # such as 25 can be found when 5 is found to be a 
    # factor 100/5=25
    rootn = sqrt(n)
    while (check < rootn):
        if (n%check == 0):
            fact.append(check)
            fact.append(n/check)
        check += 1
    # this line checks the sqrt of the number to see if 
    # it is a factor putting it here prevents it appearing 
    # twice in the above while loop and putting it outside
    # the loop should save some time.
    if (rootn == check):
        fact.append(check)
    # return an array of factors sorted into numerial order.
    fact.sort()
    return fact


import operator
# A slightly efficient superset of primes.
def PrimesPlus():
    yield 2
    yield 3
    i = 5
    while (True):
        yield i
        if (i%6 == 1):
            i += 2
        i += 2

# Returns a dict d with n = product p ^ d[p]
def GetPrimeDecomp(n):
    d = {}
    primes = PrimesPlus()
    for p in primes:
        while (n%p == 0):
            n /= p
            d[p] = d.setdefault(p, 0) + 1
        if (n == 1):
            return d

def NumberOfDivisors(n):
    d = GetPrimeDecomp(n)
    powers_plus = map(lambda x: x+1, d.values())
    return reduce(operator.mul, powers_plus, 1)


print NumberOfDivisors(1249540)

##for i in xrange(1, 1000000000):
##    n = i*(i+1) / 2
##    if (prime.num_factors(n) > 500):
##        print n
##        break
