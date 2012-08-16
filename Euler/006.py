def SquareDiff(k):

    # ---------------------------    

##    sumOfNum = 0
##    sumOfSquare = 0
##    for i in ((x, x**2) for x in range(1, k+1)):
##        sumOfNum += i[0]
##        sumOfSquare += i[-1]
##    squareOfSum = sumOfNum**2
##    return (squareOfSum - sumOfSquare)

    # ---------------------------

##    nums, sqrs = zip(*((x, x**2) for x in range(1, k+1)))
##    return (sum(nums)**2 - sum(sqrs))
    # ---------------------------

##    nums = range(1, k+1)
####    sumOfSquare = sum(x**2 for x in nums)
####    squareOfSum = sum(nums)**2
##    return (sum(nums)**2 - sum(x**2 for x in nums))

    # ---------------------------

    return (SquareOfSum(k) - SumOfSquare(k))

    # ---------------------------    

##    return (3*k**4 + 2*k**3 - 3*k**2 - 2*k)//12
##    return (k * (k**2 - 1) * (3*k + 2)//12)
    # ---------------------------    

def SquareOfSum(k):

    # ---------------------------
##    result = 0
##    for n in range(1, k+1):
##        result += n
##    return result**2

    # ---------------------------

##    return sum(range(1, k+1))**2

    # ---------------------------

    return (k*(k+1)//2)**2
    # ---------------------------


def SumOfSquare(k):

    # ---------------------------
##    result = 0
##    for n in range(1, k+1):
##        result += n**2
##    return result
    # ---------------------------

    return k*(k+1)*(2*k+1)//6

    # ---------------------------

    

k = 100
print SquareDiff(k)
