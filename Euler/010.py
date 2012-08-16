from math import sqrt


def IsPrime(num):
    num = int(abs(num))
    if (num <= 1): return False
    if (num == 2): return True
    if (num%2 == 0): return False
    if (num < 9): return True
    if (num%3 == 0): return False
    if (num < 25): return True

    limit = int(sqrt(num))
    d = 5
    while (d <= limit):
        if (num%d == 0) or (num%(d+2) == 0):
            return False
        d += 6
    return True



limit = 2000000

psum = 2+3 // we know that 2 and 3 are prime
n = 5

while (n <= limit):
    if IsPrime(n):
        psum += n
    n += 2
    if (n > limit): break

    if IsPrime(n):
        psum += n
    n += 4

##print sum([2] + [x for x in xrange(3, limit+1, 2) if IsPrime(x)])