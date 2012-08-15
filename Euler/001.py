#import math
    
def SumMultiplesK1K2(beg, end, n1, n2):
    #----------------------------------
##    sum = 0
##    for x in xrange(beg, end):
##        if (x%n1 == 0) or (x%n2 == 0):
##            sum += x
##    return sum
    #----------------------------------
    #----------------------------------
##    multiples = [x for x in xrange(beg, end) if (x%n1 == 0) or (x%n2 == 0)]
##    return sum(multiples)
    #----------------------------------
##    return reduce(lambda x, y: (x+y), multiples)
    #----------------------------------
##    return sum(filter(lambda x: (x%n1 == 0) or (x%n2 == 0), xrange(beg, end)))
    #----------------------------------
##    a1 = n1*(int((beg-1)/n1) + 1)
##    a2 = n2*(int((beg-1)/n2) + 1)
##    return sum(set(xrange(a1, end, n1)) | set(xrange(a2, end, n2)))
    #----------------------------------
    #----------------------------------
##    return SumMultiplesK(beg, end, n1) + SumMultiplesK(beg, end, n2) - SumMultiplesK(beg, end, n1*n2)
    #----------------------------------
##    return sum(MultiplesK1K2(beg, end, n1, n2))
    return sum(MultiplesKn(beg, end, [n1, n2]))


def MultiplesK1K2(beg, end, n1, n2):
    for x in xrange(beg, end):
        if (x%n1 == 0) or (x%n2 == 0):
            yield x

def MultiplesKn(beg, end, n):
    for x in xrange(beg, end):
        multiple = False
        for d in n:
            if (x%d == 0):
                multiple = True
                break
        if (multiple): yield x
            
def SumMultiplesK(beg, end, n):
    a = n*(int((beg-1)/n) + 1)
    l = n*(int((end-1)/n))
    #return SumAP_k(a, l, (l - a)/n + 1)
    return SumAP_d(a, l, n)

def SumAP_k(a, l, k):    # SumK(k): SumAP_k(1, k, k) 
    return k*(l + a)/2

def SumAP_d(a, l, d):    # SumK(k): SumAP_d(1, k, 1)
    return ((l - a)/d + 1)*(l + a)/2

def SumK(k):
##    return SumAP_k(1, k, k)
    return SumAP_d(1, k, 1)

beg = 1
end = 1000
n1 = 3
n2 = 5
print SumMultiplesK1K2(beg, end, n1, n2)
##n = [7, 11, 13]
##print [x for x in MultiplesKn(beg, end, n)]
