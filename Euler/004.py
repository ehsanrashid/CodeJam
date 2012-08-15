# Find the largest palindrome number made from the product of two 3-digit numbers.

def LargestPalindrome(beg, end):
    #----------------------------
##    d1max = d2max = 0
##    largest = 0
##    dd = xrange(beg, end)
##    for d1 in dd:
##        for d2 in dd:
##            prod = d1*d2
##            if IsPalindrome(prod):
##                if (prod > largest):
##                    d1max, d2max = d1, d2
##                    largest = prod
##    #print largest, d1max, d2max
    #----------------------------
##    largest = 0
##    common = 11
##
##    d1 = end-1
##    while (d1 >= beg):
##        if (d1%common == 0):
##            d2 = end-1
##            dd2 = 1
##        else:
##            d2 = common*((end-1)//common)
##            dd2 = common
##        while (d2 >= d1):
##            prod = d1 * d2
##            if (prod <= largest): break
##            if IsPalindrome(prod):
##                largest = prod
##                d1max, d2max = d1, d2
##            d2 -= dd2
##        d1 -= 1
##    #print largest, d1max, d2max
    #----------------------------
##    minN = beg**2
##    maxN = end**2
##    for n in range(maxN-1, minN-1, -1):
##        if IsPalindrome(n):
##            for d in xrange(end-1, beg-1, -11):
##                if (n%d == 0) and (n/d < end):
##                    #print d, n/d
##                    return n
    #----------------------------
##    digits = range(9, -1, -1)
##    for d1 in digits:
##        for d2 in digits:
##            for d3 in digits:
##                n = d1*100001 + d2*010010 + d3*001100
##                #print d1, d2, d3, n
##                for d in xrange(990, beg-1, -11):
##                    if (n%d == 0) and (n/d < end):
##                        return n
    #----------------------------
    largest = max([d1*d2 for d1 in range(beg, end) for d2 in range(beg, end) if IsPalindrome(d1*d2)])
    #----------------------------
    n = 0
    for a in xrange(end-1, beg, -1):
        for b in xrange(a, beg, -1):
            x = a * b
            if (x > n):
                if IsPalindrome(x):
                    n = x
    return n
    #----------------------------
    return largest

    
def IsPalindrome(num):
    string = ToString(num)
    return (string == Reverse(string))

def ToString(num):
    return str(num)

def Reverse(string):
##    return "".join([string[i] for i in range(len(string)-1, -1, -1)])
    return string[::-1]

def ReverseN(n):
    reverse = 0
    while (n > 0):
        reverse = 10*reverse + n%10
        n /= 10
    return reverse


import math
import itertools

def Palindromic():
    for n in [ x*100001 + y*010010 + z*001100 for x in range(1, 10) for y in range(10) for z in range(10) ]:
        yield n
    
def InRange(n, lst, x):                         
    y = reduce(lambda x, y: x*y, lst) 
        
    if (100 < x and x < 999 and 100 < y and y < 999):     
        return True
    
    if (len(lst) > 1):
        for i in range(len(lst)):
            y = x * lst 
            if (y < 999):
                if InRange(n, lst[:i] + lst[i+1:], y):
                    return True
    return False        

def FactorPalindromic(beg, end):  # (100, 999)
    palindrom = list(Palindromic())
    for n in [x*y for x in range(beg, end) for y in range(beg, end)]:   
        if (n in palindrom):
            yield n


def PE004(n=3):
    pMax, deuxX1 = 0, 0
    for tot in range(2*10**n - 2, 2*10**(n-1) - 1, -1):
        for i in range(10**n-1, (tot-1)//2, -1):
            p = i*(tot-i)
            if (pMax < p):
                s = str(p)
                if (s == s[::-1]):
                    pMax = p
                    #print(pMax)
                    deuxX1 = max(deuxX1, 2*(tot-i))
    if (tot <= deuxX1):
        return pMax

def PE004e(n=3):
    F=[ [(3,3), (7,7), (9,1)] ]
    i = 0
    e = 1
    E = 10
    fin = 10**(n//2) 
    while (E < fin):
        i += 1
        e = E
        E *= 10
        tmp = []
        for x, y in F[i-1]:
            for c in range(0,E,e):
                for d in range(0,c+1,e):
                    if (((c+x)*(d+y)+1)%E == 0):
                        tmp.append((c+x, d+y))
        F.append(tmp)
    flag = False
    for i in range(n//2):
        M1 = 10**n-10**(n-n//2+i)
        M2 = 10**(n//2-i)
        #F[-(1+i)].sort(key=sum, reverse=True)
        mini = 0
        res = 0
        for tot in range(2*10**(2*i+1)-2, -1, -1):
            if (tot < mini): return res
            for d in range(10**(2*i+1)-1, (tot-1)//2, -1):
                c = tot-d
                for x, y in F[-(1+i)]:
                    X = M1 + c*M2 + x
                    Y = M1 + d*M2 + y
                    p = str(X*Y)
                    if (p == p[::-1]):
                        print(X, Y, X*Y)
                        res = max(X*Y, res)
                        mini = max(mini, 2*c)
                    X = M1 + d*M2 + x
                    Y = M1 + c*M2 + y
                    p = str(X*Y)
                    if (p == p[::-1]):
                        print(X, Y, X*Y)
                        res = max(X*Y, res)
                        mini = max(mini, 2*c)

            
beg = 9*10**2
end = 10**3
print LargestPalindrome(beg, end)
