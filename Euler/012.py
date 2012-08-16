##from math import head
import math
import operator

def euler12(ndivisors):
    """What is the first triangle number to have over five-hundred divisors?"""
    num_factors = lambda x: mul((exp+1) for (base, exp) in factorize(x))
    return head(x for x in triangle_numbers() if num_factors(x) > ndivisors)


def triangle_number(x):
    """"Return the xth triangle number."""
    # The nth triangle number is defined as the sum of [1, n] values.
    # A brute-force approach could be sum(xrange(1, n+1)),
    # but let's take pencil&paper, do some nice draws,
    # (forget that Gauss ever existed) and get...
    return (x*(x+1))/2
 
def triangle_numbers(start=1):
    """Generate triangle numbers tn(n) = 1+2+3+....+n"""
    first = triangle_number(start-1)
    return reduce(operator.add, count(start), first)

def head(items): return items[0]

def tail(items): return items[1:]

def count(items):
    if (items == []):
        return 0
    else:
        return 1 + tail(items)
        
euler12(500)