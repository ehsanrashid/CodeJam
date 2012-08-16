// 00106 - Fermat vs. Pythagoras

#include <stdio.h>
#include <string.h>
#include <vector>

#include <algorithm>

using namespace std;

#define LIM 1000050

typedef unsigned int uint;

struct Triple
{
    uint a,b,c;
    Triple()
    {}

    Triple(uint x, uint y, uint z)
    {
        a = x;
        b = y;
        c = z;
    }
};

uint A,B,C,didnt,first[LIM],i,kA,kB,kC,m,n,sqm,sqn;
vector<Triple> prim;
vector<Triple>::iterator it;

uint GCD(uint a, uint b)
{
    if (a) 
        return GCD(b%a,a); 
    else 
        return b;
}

bool ord(Triple a, Triple b)
{
    return (a.c < b.c);
}

void show(Triple x)
{
    printf("{ %u, %u, %u }\n",x.a,x.b,x.c);
}

void main()
{
    Triple last;
    
    memset(first, 1000001, sizeof(first));
    
    for (m = 1; m < 710; m++)
    {
        sqm = m*m;
        for (n = m+1; sqm + (sqn = n*n) < LIM; n+=2)
        {
            if (GCD(m,n) == 1)
            {
                prim.push_back(Triple(2*m*n,sqn-sqm,sqm+sqn));
                last = prim.back();
                A = last.a; B = last.b; C = last.c;
                for (i = 1; i*C < 1000001; i++)
                {
                    kA = i*A; kB = i*B; kC = i*C;
                    if (first[kA] > kC) first[kA] = kC;
                    if (first[kB] > kC) first[kB] = kC;
                    first[kC] = kC;
                }
            }
        }
    }

    sort(prim.begin(), prim.end(), ord);
    while (scanf("%u",&n) != EOF)
    {
        didnt = n;
        for (n = n+1, it = prim.begin(); (*it).c < n; it++);
        for (i = 1; i < n; i++) 
            if (first[i] < n) 
                didnt--;
        printf("%u %u\n",it-prim.begin(),didnt);
    }
    return 0;
}
