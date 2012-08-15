import time

def NextNum(n):
    if (n % 2 == 0):
        return n >> 1 # (n / 2)
    else:
        return (n * 3 + 1)

def Memoized(fn):
    memoized_lengths = [0] * 1000000
    def memory(n):
        if not memoized_lengths[n]:
            memoized_lengths[n] = fn(n)
        return memoized_lengths[n]
    return memory

@Memoized
def CycleLength(n):
    if (n == 0): return 2 # Note: 0 treated as odd=> 0: 3*(0) + 1 => 1
    if (n == 1): return 1
    if (n == 2): return 2
    return 1 + CycleLength(NextNum(n))


tblCycleLength = {0: 2, 1: 1, 2: 2}
def MaxCycleLength(lowerBound, upperBound):
    # ------------------------------------------

    ##return max([CycleLength(x) for x in xrange(lowerBound, upperBound + 1)])

    # ------------------------------------------
    #print tblCycleLength
    rangeNum = xrange(lowerBound, upperBound + 1)
    for i in rangeNum:
        n = i
        numOfCycles = 0
        while (n != 1):
            if (n not in tblCycleLength):
                numOfCycles += 1
                n = NextNum(n)
            else:
                numOfCycles += tblCycleLength[n]
                break

        tblCycleLength[i] = numOfCycles

    lstCycleLength = [tblCycleLength.get(k) for k in rangeNum]
    return max(lstCycleLength)
    # ------------------------------------------
    
def test_CycleLength():
    assert CycleLength(22) == 16
    assert CycleLength(10) == 7
    assert CycleLength(11) == 15
    print "OK CycleLength"

def test_MaxCycleLength():
    assert MaxCycleLength(1, 10) == 20
    assert MaxCycleLength(100, 200) == 125
    assert MaxCycleLength(201, 210) == 89
    assert MaxCycleLength(900, 1000) == 174
    print "OK MaxCycleLength"
    
if (__name__ == "__main__"):
    #start = time.time()

    #test_CycleLength()
    #test_MaxCycleLength()
    
    fname_in = "00100.in"
    fin = open(fname_in, "r")
    #fname_out = "00100.out"
    #fout = open(fname_out, "w")
    for line in fin:
        [i, j] = [int(s) for s in line.split()]
        
        lowerBound = min(i, j)
        upperBound = max(i, j)
        maxCycleLength = MaxCycleLength(lowerBound, upperBound)
        print maxCycleLength
        #fout.write(str(maxCycleLength) + "\n")
    #fout.close()
    fin.close()

    #stop = time.time()
    #print stop - start
