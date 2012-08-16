from math import factorial
from operator import add
from operator import mul
from string import digits


def SumDigitFactorial(num):

    #----------------------------------

##    return sum(int(x) for x in str(Factorial(num)))
    #----------------------------------

##    return sum(map(int, str(Factorial(num)))))
    #----------------------------------    
    return SumDigit(Factorial(num))


def Factorial(num):
    num = int(abs(num))

    #----------------------------------

##    return reduce(lambda x, y: x*y, range(1, num+1))
##    return reduce(mul, range(1, num+1))
##    return reduce(mul, xrange(num, 0, -1))
    #----------------------------------

##    if (num == 0 || num == 1): return 1
##    if (num == 2): return 2
##    if (num == 3): return 6
##    return num * Factorial(num - 1)
    #----------------------------------
    return factorial(num)


def SumDigit(num):

    #----------------------------------

    num = int(abs(num))
    sumDig = 0
    #----------------------------------

##    while (num > 0):
##        d = num%10
##        sumDig += d
##        num /= 10
    #----------------------------------

##    strNum = str(num)
##    for i in range(0, len(strNum)):
##        sumDig += int(strNum[i])
    #----------------------------------

##    for char in str(num):
##        sumDig += int(char)
    #----------------------------------

##    sumDig = reduce(lambda x, y: x + y, Digits(num))
##    sumDig = reduce(add, Digits(num))
    #----------------------------------
    sumDig = sum(Digits(num))
    #----------------------------------
    
    return sumDig


def Digits(num):
    num = int(abs(num))

    #----------------------------------

##    return [int(d) for d in str(num) if d in digits]
    #----------------------------------

    return map(int, str(num))
    #----------------------------------
               

num = 10
print factorial(num)
print SumDigitFactorial(num)
