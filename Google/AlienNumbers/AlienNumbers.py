import sys

def ToValue(nm, d1):
    base_d1 = len(d1)
    n = 0
    for c in list(nm):
        n = n*base_d1 + d1.find(c)
    return n
    
def FromValue(n, d2):
    base_d2 = len(d2)
    r = ""
    while (n != 0):
        r += d2[ n % base_d2 ]
        n /= base_d2
    #r = "".join(reversed(r))
    r = r[::-1]
    return r

def AlienNumber(nm, d1, d2):
    #val = {}
    #v = 0
    #for c in d1:
    #    val[ c ] = v
    #    v += 1
    #
    #base_d1 = len(d1)
    #n = 0
    #for c in list(nm):
    #    n = n*base_d1 + val[ c ]
    #
    #base_d2 = len(d2)
    #r = ""
    #while (n != 0):
    #    r += d2[ n % base_d2 ]
    #    n /= base_d2
    #r = r[::-1]

    n = ToValue(nm, d1)
    r = FromValue(n, d2)
    return r

#filename = sys.argv[1]
filename = "AlienNumbers"

infile = open(filename + ".in", "r")
#outfile = open(filename + ".out", "w")

N = int(infile.readline().strip())

for i in range(1, N+1):
    line = infile.readline().strip()
    #(nm, d1, d2) = line.split()
    nm, d1, d2 = map(str, line.split())

    r = AlienNumber(nm, d1, d2)

    print "%d: %s" % (i, r)
    #outfile.write("%d: %s\n" % (i, r))

#outfile.close()
infile.close()