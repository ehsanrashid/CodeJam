import sys

def CountPrimeFactors(num):
    num = abs(int(num))
    if (num > 1):
        for prime in range(2, num+1):
            if (num % prime == 0):
                return 1 + CountPrimeFactors(num / prime)
    return 0

if (__name__ == "__main__"):
    num = 5
    counts = 0
    for x in range(2, num+1):
        counts += CountPrimeFactors(x)
    print "%d\n" % (counts)
