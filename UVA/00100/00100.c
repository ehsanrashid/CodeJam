// 00100 - The 3n+1 problem (Max Cycle Length)

#include <stdio.h>
#include <queue>

using namespace std;

typedef unsigned short       ushort;
typedef unsigned int         uint;
typedef unsigned long long   ull;

const uint SIZE = 1000001;

ushort CycleLengths[SIZE];

uint NextNum(uint n)
{
    // Note: 0 treated as odd=> 0: 3*(0) + 1 => 1
    return
        //(n != 0 && n%2 == 0)
        (n != 0 && (n&1) == 0)
            //? n/2 : 3*n +1;
            ? n>>1 : 3*n +1;
}

ushort CycleLength(uint n)
{
    // Note: 0 treated as odd=> 0: 3*(0) + 1 => 1
    // 0 has Sequence [0 1] => length = 2
    
    // base case :
    // 0 has a cycle length of 2
    // 1 has a cycle length of 1
    if (CycleLengths[n] == 0)
    {
        if (n == 0) CycleLengths[n] = 2;
        if (n == 1) CycleLengths[n] = 1;
        //if (n == 2) CycleLengths[n] = 2;
    }
    if (n < SIZE)
    {
        // if we've already cached the cycle length of the current number
        if (CycleLengths[n] != 0) return CycleLengths[n];
    }

    // --------------------------------------------------

    uint nn = n;
    queue<uint> numChain;
    do
    {
        nn = NextNum(nn);
        numChain.push((nn < SIZE) ? nn : 0);
    }
    while ((nn >= SIZE) || (CycleLengths[nn] == 0));

    ushort cyclelength = numChain.size();
    CycleLengths[n] = CycleLengths[nn] + cyclelength;

    while (cyclelength > 1)
    {
        uint num = numChain.front(); numChain.pop();
        --cyclelength; // = numChain.size();
        CycleLengths[num] = CycleLengths[nn] + cyclelength;
    }

    // --------------------------------------------------
    // --------------------------------------------------
    
    // general case:
    //uint nn = NextNum(n);
    //ushort cyclelength = 1 + CycleLength(nn);
    // --------------------------------------------------
    //// specific case: not work if NextNum changed
    //uint nn = NextNum(n);
    //ushort cyclelength;
    //if ((n&1) == 1)
    //{
    //    nn >>= 1;
    //    cyclelength = 2 + CycleLength(nn);
    //}
    //else
    //{
    //    cyclelength = 1 + CycleLength(nn);
    //}
    // --------------------------------------------------

    //if (n < SIZE)
    //{
    //    CycleLengths[n] = cyclelength;
    //}
    // --------------------------------------------------
    // --------------------------------------------------
    
    return CycleLengths[n];
}

ushort MaxCycleLength(uint lowerBound, uint upperBound)
{
    ushort maxCycleLength = 0;
    for (uint num = lowerBound; num <= upperBound; ++num)
    {
        maxCycleLength = max(CycleLength(num), maxCycleLength);
    }
    return maxCycleLength;
}

void main()
{	
    FILE* file = freopen("00100.in", "r", stdin);
    if (file != NULL)
    {
        freopen("00100.out", "w", stdout);

        // initalize table
        CycleLengths[0] = 2;
        CycleLengths[1] = 1;

        uint i, j;
        while (scanf("%u %u", &i, &j) == 2) // != EOF
        {		
            uint lowerBound = min(i, j);
            uint upperBound = max(i, j);

            ushort maxCycleLength = MaxCycleLength(lowerBound, upperBound);

            printf(" %d\n", maxCycleLength);
        }
    }
    fflush(stdin);
}