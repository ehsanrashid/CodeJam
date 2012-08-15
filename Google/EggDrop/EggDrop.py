#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys

DROPS = 100
BREAKS = 100
INF = 0x7FFFFFFF
OUT_FLOOR = INF #-1

FLOOR = [[-1 for i in range(BREAKS+1)] for j in range(DROPS+1)]

#               b  ┌ d ┐
# FLOOR(d, b) = Σ  │   │
#              i=1 └ i ┘
# FLOOR(d, b) = FLOOR(d-1, b-1) + FLOOR(d-1, b) + 1
# FLOOR(1, b) = 1 -> FLOOR(1, 1) = 1
# FLOOR(d, 0) = 0
# FLOOR(d, 1) = d
# FLOOR(d, 2) = d(d + 1)/2
# FLOOR(d, 3) = d(d(d + 0) + 5)/6;
# FLOOR(d, 4) = d(d(d(d - 2) + 11) + 14)/24;
# FLOOR(x, x) = 2^x - 1 = 1<<x - 1
# FLOOR(x, y) = FLOOR(x, x), if y >= x
def Initialize():
##    for b in range(BREAKS+1): FLOOR[ 1 ][ b ] = 1
    FF(DROPS, BREAKS)

def FF(D, B):
    #---------------------
##    if (D == 0) | (B == 0): return 0
##    if (D <= B): return (1 << D) - 1
##    if (FLOOR[ D ][ B ] == -1): FLOOR[ D ][ B ] = FF(D-1, B-1) + FF(D-1, B) + 1
##    if (FLOOR[ D ][ B ] >= INF): FLOOR[ D ][ B ] = INF
    #---------------------        
    for d in range(1, D+1):
        b = 1; FLOOR[ d ][ b ] = d
        b = 2; FLOOR[ d ][ b ] = d * (d + 1) / 2
        b = 3; FLOOR[ d ][ b ] = d * (d * (d + 0) + 5) / 6
        b = 4; FLOOR[ d ][ b ] = d * (d * (d * (d - 2) + 11) + 14) / 24
        for b in range(b+1, B+1):
            ybFloor = FLOOR[ d - 1 ][ b - 1 ]
            nbFloor = FLOOR[ d - 1 ][ b ]
            
            if (ybFloor == OUT_FLOOR) | (nbFloor == OUT_FLOOR):
                FLOOR[ d ][ b ] = OUT_FLOOR
                continue
            
            nextFloor = 0
            if (b < d):    nextFloor = ybFloor + nbFloor + 1
            elif (b == d): nextFloor = (1 << d) - 1
            else:          nextFloor = FLOOR[ d ][ b - 1 ]

            if (nextFloor >= INF): nextFloor = OUT_FLOOR
                
            FLOOR[ d ][ b ] = nextFloor
    #---------------------
    return FLOOR[ d ][ b ]

def Factorial(n):
    n = abs(int(n))
    if (n == 0 | n == 1): return 1
    if (n == 2): return 2
    if (n == 3): return 6

    x = 1
    #------------------------
    #while (n > 1):
    #    x *= n
    #    n -= 1
    #------------------------    
    for i in range(n, 1, -1):
        x *= i
    #------------------------
    return x

def Permute(n, r):
    n = abs(int(n))
    r = abs(int(r))
    if (n < r): return 0
    if (n == 0 | n == 1): return 1
    if (r == 0): return 1
    if (r == 1): return n
    if (r == n-1): return Factorial(n)
    if (r == n): return Factorial(n)

    x = 1
    #------------------------
    #while (r > 0):
    #    x *= n
    #    n -= 1
    #    r -= 1
    #------------------------
    for i in range(n, n-r, -1):
        x *= i    
    #------------------------
    return x

def Combine(n, r):
    n = abs(int(n))
    r = abs(int(r))
    if (n < r): return 0
    if (n == 0 | n == 1): return 1
    if (r == 0 | r == n): return 1
    if (r == 1 | r == n - 1): return n

    if (r > n / 2): r = n - r;

    return Permute(n, r) / Factorial(r)

def F_max(D, B):
    maxF = 0

    if (D > DROPS): return 0
    if (B > BREAKS): B = BREAKS

    if (B == 0): return 0
    if (B == 1): return D
    if (B == 2): return D * (D + 1) / 2
    if (B == 3): return D * (D * (D + 0) + 5) / 6
    if (B == 4): return D * (D * (D * (D - 2) + 11) + 14) / 24

    #-------------------------GENERAL
##    incF = 1;
##    for b in range(1, B+1):
##        if (incF == 0): break
##        incF = incF * (D - b + 1) / b;
##        maxF += incF;
##        if (maxF >= INF): return OUT_FLOOR 
    #-------------------------
##    for b in range(1, B+1):
##        maxF += Combine(D, b)
##        if (maxF >= INF): return OUT_FLOOR
    #-------------------------
    maxF = FLOOR[ D ][ B ]
    #-------------------------
    return maxF

def D_min(F, maxD, B):
    if (B == 1): return F
    #-------------------------
##    minD = 1
##    for d in range (1, maxD+1):
##        maxF = F_max(d, B)
##        if (maxF >= F | maxF == OUT_FLOOR):
##            minD = d
##            break
    #-------------------------
    min = 0
    max = maxD
    while (max - min > 1):
        mid = int((max + min) / 2)
        maxF = F_max(mid, B)
##        if (maxF >= F | maxF == OUT_FLOOR):
##            max = mid
##        else:
##            min = mid
        if (F > maxF):
            min = mid
        else:
            max = mid
    minD = max
    #-------------------------
    return minD

def B_min(F, D, maxB):
    #-------------------------
##    minB = 1
##    for b in range (1, maxB+1):
##        maxF = F_max(D, b)
##        if (maxF >= F | maxF == OUT_FLOOR):
##            minB = b
##            break
    #-------------------------
    min = 0
    max = maxB
    while (max - min > 1):
        mid = int((max + min) / 2)
        maxF = F_max(D, mid)
##        if (maxF >= F | maxF == OUT_FLOOR):
##            max = mid
##        else:
##            min = mid
        if (F > maxF):
            min = mid
        else:
            max = mid

    minB = max
    #-------------------------
    return minB

def FloorTable(D, B):
    print "  d\\e",
    for b in range(1, B+1):
        print "      %d" % b,
    print   
    print '-' * (5 + 8 * B)
    for d in range(1, D+1):
        print "%3d|" % d,
        for b in range(1, B+1):
            if (b > d): break
            print "  %5d" % F_max(d, b),
        print

if (__name__ == "__main__"):
    Initialize()
    FloorTable(16, 8)

    ##filename = sys.argv[1]
    filename = "EggDrop.in"

    infile = file(filename, 'r')
    N = int(infile.readline().strip())

    for i in range(1, N+1):
        line = infile.readline().strip()
        F, D, B = map(int, line.split())

        print "%d: %d %d %d" % (i, F_max(D, B), D_min(F, D, B), B_min(F, D, B))

    infile.close()
