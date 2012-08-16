## a= 2mn; b= m^2 - n^2; c= m^2 + n^2;
## a + b + c = 1000;
##
## 2mn + (m^2 -n^2) + (m^2 + n^2) = 1000;
## 2mn + 2m^2 = 1000;
## 2m(m+n) = 1000;
## m(m+n) = 500;
##
## m>n;
##
## m= 20; n= 5;
##
## a= 200; b= 375; c= 425;

##h=0
##while True:
##    for p in range(1, h):
##        for b in range(1, p):
##            if b**2 + p**2 == h**2:
##                if b+p+h == 1000:
##                    print "b=%d, p=%d, h=%d b*p*h=%d" % (b,p,h,b*p*h)
##    h += 1

##for b in range(1, 334):
##    for h in range(997-b, 334, -1):
##        p = 1000 - h - b;
##        if (h <= p): break
##        if ((b*b)+(p*p) == (h*h)):
##            print "b, p, h, b*p*h", (b,p,h,b*p*h)


##n = 1000
##for h in xrange(n/3 + 1, n/2):
##    for b in xrange(1, (n-h)/2+1):
##        p = n - h - b
##        if (b**2 + p**2 == h**2):
##            print b, p, h
##            print b*p*h

##n = 1000
##for b in xrange(1, n/3):
##    for p in xrange(n/3-1, n/2):
##        h = (b*b + p*p)**.5
##        if (b + p + h == n):
##            print b, p, int(h)
##            print int(b*p*h)


##print ([a*b*(n - b -a) \
##    for a in range(1, n/2) \
##        for b in range(1, n/2) \
##            if ((a*a + b*b) == ((n - b - a)**2))][0])

##
##def squares():
##    i = 1
##    while i < 1000:
##        yield (i,i**2)
##        i += 1
##        
##prev = []
##seen = {}
##found = False
##for (i,isq) in squares():
##    for (j, jsq) in prev:
##        k = seen.get(isq-jsq)
##        if not k: continue
##        if i + j + k == 1000:
##            print j, k, i
##            found = True
##            break
##    if found: break
##    prev.append((i,isq))
##    seen[isq] = i

