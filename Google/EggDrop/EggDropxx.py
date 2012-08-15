#!/usr/bin/env python
import sys
from array import array

def Fmax(D, B, Fmaxtable, Fmaxover):
    if B == 0:
        val = 0
    elif B == 1:
        val = D
    else:
        val = D
        for d in range(0, D):
            if Fmaxover[B-1][d]:
                return None
            val += Fmaxtable[B-1][d]
            if val >= 2**32:
                return None
    return val

def computeFmax(Dmax, Bmax):
    Fmaxtable = [] # Fmaxtable[B][D] = Fmax(D,B)
    Fmaxover = []  # Fmaxover[B][D] = True if Fmax(D,B) >= 2**32
    for B in range(Bmax+1):
        Fmaxtable.append(array('L'))
        Fmaxover.append(array('B'))
        for D in range(Dmax+1):
            val = Fmax(D, B, Fmaxtable, Fmaxover)
            if val == None:
                Fmaxtable[B].append(0)
                Fmaxover[B].append(True)
            else:
                Fmaxtable[B].append(val)
                Fmaxover[B].append(False)
    return Fmaxtable, Fmaxover

def D_min(F, B, Fmaxtable):
    Dmin = globalDmax + 1
    for b in range(1, B+1):
        for D in range(1, globalDmax+1):
            if D < Dmin and Fmaxtable[b][D] >= F: Dmin = D
    return Dmin

def B_min(F, D, Fmaxtable):
    Bmin = globalBmax + 1
    for d in range(1, D+1):
        for B in range(1, globalBmax+1):
            if B < Bmin and Fmaxtable[B][d] >= F: Bmin = B
    return Bmin


#filename = sys.argv[1]
filename = 'EggDrop1,in'
if filename.startswith('large'):
    globalDmax = 2000000000
    globalBmax = 2000000000
else:
    globalDmax = 100
    globalBmax = 100

Fmaxtable, Fmaxover = computeFmax(globalDmax, globalBmax)

infile = file(filename, 'r')
N = int(infile.readline().strip())

for i in range(1, N+1):
    line = infile.readline().strip()
    F, D, B = map(int, line.split())
    
    if Fmaxover[B][D]:
        Fmax = -1
    else:
        Fmax = Fmaxtable[B][D]

    Dmin = D_min(F, B, Fmaxtable)
    Bmin = B_min(F, D, Fmaxtable)
    print "%d: %d %d %d" % (i, Fmax, Dmin, Bmin)
