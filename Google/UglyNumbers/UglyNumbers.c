#include <STDIO.H>
#include <STRING.H>
#include <ASSERT.H>

typedef	unsigned __int32 uint;
typedef	         __int64 ll;
typedef	unsigned __int64 ull;

const int MAXCHAR = 50;

char digits[ MAXCHAR ];
int N;

const int P2 = 2;
const int P3 = 3;
const int P5 = 5;
const int P7 = 7;

const int MOD = P2 * P3 * P5 * P7;

uint Mod(uint start, uint end, int modr)
{
    int r = 0;
    for (int i = start; i < end; ++i)
    {
        r = (10*r + digits[ i ] - '0') % modr;
    }
    return r;
}

// ------------------------------------------------------------------------

//ll ways[ 50 ][ P2 ][ P3 ][ P5 ][ P7 ];
//
//ll TotalWays(int pos, uint mod2, uint mod3, uint mod5, uint mod7)
//{
//    //printf("go %d %d %d %d %d\n", pos, mod2, mod3, mod5, mod7);
//    assert(0 <= mod2 && mod2 <= (P2-1));
//    assert(0 <= mod3 && mod3 <= (P3-1));
//    assert(0 <= mod5 && mod5 <= (P5-1));
//    assert(0 <= mod7 && mod7 <= (P7-1));
//
//    if (pos == N && (mod2 == 0 || mod3 == 0 || mod5 == 0 || mod7 == 0))
//    {
//        return 1;
//    }
//
//    ll& way = ways[ pos ][ mod2 ][ mod3 ][ mod5 ][ mod7 ];
//
//    if (way == -1)
//    {
//        way = 0;
//        for (int np = pos+1; np <= N; ++np)
//        {
//            int m2 = Mod(pos, np, P2);
//            int m3 = Mod(pos, np, P3);
//            int m5 = Mod(pos, np, P5);
//            int m7 = Mod(pos, np, P7);
//
//            // adding numbers
//            way += TotalWays(np, (mod2 + m2) % P2, (mod3 + m3) % P3, (mod5 + m5) % P5, (mod7 + m7) % P7);
//            // subtracting numbers
//            if (pos > 0)
//            {
//                way += TotalWays(np, (mod2 - m2 + P2) % P2, (mod3 - m3 + P3) % P3, (mod5 - m5 + P5) % P5, (mod7 - m7 + P7) % P7);
//            }
//
//            assert(way <= 4052555153018976267LL);
//        }
//    }
//    return way;
//}


// ------------------------------------------------------------------------

ll ways[ 50 ][ MOD ][ MOD ][ 2 ];

ll TotalWays(int pos, int rem, int remlast, bool plus)
{
    if (pos >= N)
    {
        if ((rem + remlast) % P2 == 0 ||
            (rem + remlast) % P3 == 0 ||
            (rem + remlast) % P5 == 0 ||
            (rem + remlast) % P7 == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    ll& way = ways[ pos ][ rem ][ remlast ][ plus ? 1 : 0 ];

    if (way < 0) // == -1
    {
        int digit = digits[ pos ] - '0';
        way =
            TotalWays(pos + 1, rem, (plus ? (10 * remlast + digit) : (10 * remlast - digit + MOD)) % MOD, plus)
            + TotalWays(pos + 1, (rem + remlast) % MOD, digit % MOD, true)
            + TotalWays(pos + 1, (rem + remlast) % MOD, (MOD - digit) % MOD, false)
            ;
    }
    return way;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

//ll** ways;
//
//void Alloc(int value)
//{
//    ways = new ll*[ N+1 ];
//
//    for (int i = 0 ; i <= N ; ++i)
//    {
//        ways[ i ] = new ll[ MOD ];
//        for (int j = 0 ; j < MOD ; ++j)
//        {
//            ways[ i ][ j ] = value;
//        }
//    }
//
//    //memset(ways, value, sizeof(ways));
//}

// ------------------------------------------------------------------------

//ll TotalWays(int pos, int mod)
//{
//    if (ways[ pos ][ mod ] >= 0)
//    {
//        return ways[ pos ][ mod ];
//    }
//
//    ll &way = ways[ pos ][ mod ];
//    way = 0;
//
//    int m = 0;
//    for (int np = pos; np < N; ++np)
//    {
//        m = (10*m + digits[ np ] - '0') % MOD;
//
//        if (np < N-1)
//        {
//            way += TotalWays(np+1, (mod + m) % MOD)	+ TotalWays(np+1, (mod - m + MOD) % MOD);
//        }
//        else
//        {
//            int ugly = (mod + m) % MOD;
//            if (ugly % P2 == 0 || ugly % P3 == 0 || ugly % P5 == 0 || ugly % P7 == 0)
//            {
//                ++way;
//            }
//        }
//    }
//    return way;
//}

// ------------------------------------------------------------------------

//ll TotalWays()
//{
//    Alloc(0);
//
//    for (int np = 0; np <= N; ++np)
//    {
//        for (int pos = 0; pos < np; ++pos)
//        {
//            int m = Mod(pos, np, MOD);
//            if (pos == 0)
//            {
//                ++ways[ np ][ m ];
//            }
//            else
//            {
//                for (int k = 0; k < MOD; ++k)
//                {
//                    int a = (k + m) % MOD;
//                    int b = (k - m + MOD) % MOD;
//                    ways[ np ][ a ] += ways[ pos ][ k ];
//                    ways[ np ][ b ] += ways[ pos ][ k ]; 						
//                }
//            }
//        }
//    }
//
//    ll way = 0;
//    for (int i = 0; i < MOD; ++i)
//    {
//        if (i % P2 == 0 || i % P3 == 0 || i % P5 == 0 || i % P7 == 0)
//        {
//            way += ways[ N ][ i ];
//        }
//    }
//
//    return way;
//}

// ------------------------------------------------------------------------

ll TotalUglyNumbers()
{
    ll uglyNumbers;

    N = strlen(digits);

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    memset(ways, -1, sizeof(ways));

    // ------------------------------------------------------------------------
    //uglyNumbers = TotalWays(0, 0, 0, 0, 0);

    // ------------------------------------------------------------------------

    uglyNumbers = TotalWays(1, 0, digits[ 0 ] - '0', true);

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    //Alloc(-1);
    //uglyNumbers = TotalWays(0, 0);
    // ------------------------------------------------------------------------

    //uglyNumbers = TotalWays();

    return uglyNumbers;
}
// ------------------------------------------------------------------------

void main()
{
    FILE* file = freopen("UglyNumbers.in", "r", stdin);
    if (file != NULL)
    {
        freopen("UglyNumbers.out", "w", stdout);

        int N;
        scanf(" %d", &N);

        for (int i = 1; i <= N; ++i)
        {
            scanf(" %s", digits);
            printf("%d: %lld\n", i, TotalUglyNumbers());
        }
    }
}