using System;
using System.IO;
using System.Collections.Generic;

static class UglyNumbers
{

    const int P2 = 2;
    const int P3 = 3;
    const int P5 = 5;
    const int P7 = 7;

    const int MOD = P2 * P3 * P5 * P7;

    static string digits;
    static int N;

    public static int Mod(int start, int end, int modr)
    {
        int r = 0;
        for (int i = start; i < end; ++i)
        {
            r = (10 * r + digits[ i ] - '0') % modr;
        }
        return r;
    }

    static int num;
    public static int Number(int end)
    {
        num = 0;
        for (int i = 0; i < end; ++i)
        {
            num = 10 * num + digits[ i ] - '0';
        }
        return num;
    }

    // ------------------------------------------------------------------------
    static long[ , , , , ] ways = null;
    static long TotalWays(int pos, int mod2, int mod3, int mod5, int mod7)
    {
        //Console.WriteLine("{0} ({1} {2} {3} {4})", pos, mod2, mod3, mod5, mod7);

        if (0 > mod2 && mod2 >= P2) Environment.Exit(mod2);
        if (0 > mod3 && mod3 >= P3) Environment.Exit(mod3);
        if (0 > mod5 && mod5 >= P5) Environment.Exit(mod5);
        if (0 > mod7 && mod7 >= P7) Environment.Exit(mod7);

        if (pos == N && (mod2 == 0 || mod3 == 0 || mod5 == 0 || mod7 == 0))
        {
            //Console.WriteLine("{0} ({1} {2} {3} {4}) = {5}", pos, mod2, mod3, mod5, mod7, num);
            return 1;
        }

        long way = ways[ pos, mod2, mod3, mod5, mod7 ];
        if (way >= 0) return way;

        way = 0;
        for (int np = pos + 1; np <= N; ++np)
        {
            //int num = Number(np);
            int m2 = Mod(pos, np, P2);
            int m3 = Mod(pos, np, P3);
            int m5 = Mod(pos, np, P5);
            int m7 = Mod(pos, np, P7);

            // adding numbers
            way += TotalWays(np, (mod2 + m2) % P2, (mod3 + m3) % P3, (mod5 + m5) % P5, (mod7 + m7) % P7);
            // subtracting numbers
            if (pos > 0)
            {
                way += TotalWays(np, (mod2 - m2 + P2) % P2, (mod3 - m3 + P3) % P3, (mod5 - m5 + P5) % P5, (mod7 - m7 + P7) % P7);
            }
        }

        return ways[ pos, mod2, mod3, mod5, mod7 ] = way;
    }

    // ------------------------------------------------------------------------

    //static long[ , , , ] ways = null;
    //static long TotalWays( int pos, int rem, int remlast, bool plus )
    //{
    //    if (pos >= N)
    //    {
    //        if(
    //            (rem + remlast) % P2 == 0 ||
    //            (rem + remlast) % P3 == 0 ||
    //            (rem + remlast) % P5 == 0 ||
    //            (rem + remlast) % P7 == 0
    //          )
    //            return 1;
    //        else
    //            return 0;
    //    }

    //    long way = ways[ pos, rem, remlast, plus ? 1 : 0 ];
    //    if (way >= 0) return way;
    //    int digit = digits[ pos ] - '0';
    //    way =
    //        TotalWays( pos + 1, rem, (10 * remlast + (plus ? digit : MOD - digit)) % MOD, plus )
    //      + TotalWays( pos + 1, (rem + remlast) % MOD,              digit % MOD, true )
    //      + TotalWays( pos + 1, (rem + remlast) % MOD,      (MOD - digit) % MOD, false )
    //    ;

    //    return ways[ pos, rem, remlast, plus ? 1 : 0 ] = way;
    //}

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    //long** ways;

    //void Alloc(int value)
    //{
    //    ways = //new (long* )[ N+1 ];
    //        (long**) malloc((N+1) * sizeof(long*));

    //    for( int i = 0 ; i <= N ; ++i )
    //    {
    //        ways[ i ] = new long[ MOD ];
    //        for( int j = 0 ; j < MOD ; ++j )
    //            ways[ i ][ j ] = value;
    //    }
    //    //memset( ways, value, sizeof(ways) );
    //}

    // ------------------------------------------------------------------------

    //long TotalWays(int pos, int mod)
    //{
    //    if( ways[pos][mod] >= 0 )
    //        return ways[pos][mod];

    //    //long &way = ways[pos][mod];
    //    long way;
    //    way = 0;

    //    int m = 0;
    //    for( int np = pos; np < N; ++np )
    //    {
    //        m = (10 * m + digits[np] - '0') % MOD;

    //        if (np < N-1)
    //        {
    //            way += TotalWays(np+1, (mod + m) % MOD)	+ TotalWays(np+1, (mod - m + MOD) % MOD);
    //        }
    //        else
    //        {
    //            int ugly = (mod + m) % MOD;
    //            if( ugly % P2 == 0 || ugly % P3 == 0 || ugly % P5 == 0 || ugly % P7 == 0 )
    //            {
    //                ++way;
    //            }
    //        }
    //    }
    //    ways[pos][mod] = way;
    //    return way;
    //}

    // ------------------------------------------------------------------------

    static long TotalWays()
    {
        long[ , ] ways = new long[ N + 1, MOD ];

        for (int np = 1; np <= N; ++np)
        {
            for (int pos = 0; pos < np; ++pos)
            {
                int m = Mod(pos, np, MOD);
                if (pos == 0)
                {
                    ++ways[ np, m ];
                }
                else
                {
                    for (int k = 0; k < MOD; ++k)
                    {
                        int add = (k + m) % MOD;
                        int sub = (k - m + MOD) % MOD;
                        ways[ np, add ] += ways[ pos, k ];
                        ways[ np, sub ] += ways[ pos, k ];
                    }
                }
            }
        }

        long way = 0;
        for (int i = 0; i < MOD; ++i)
        {
            if (i % P2 == 0 || i % P3 == 0 || i % P5 == 0 || i % P7 == 0)
            {
                way += ways[ N, i ];
            }
        }
        return way;
    }


    static long TotalUglyNumbers()
    {
        long uglyNumbers = 0;

        N = digits.Length;
        /*
        ways = new long[ N + 1, P2, P3, P5, P7 ];
        for( int n = 0; n < N; ++n )
            for( int p2 = 0; p2 < P2; ++p2 )
                for( int p3 = 0; p3 < P3; ++p3 )
                    for( int p5 = 0; p5 < P5; ++p5 )
                        for( int p7 = 0; p7 < P7; ++p7 )
                            ways[ n, p2, p3, p5, p7 ] = -1;
        uglyNumbers = TotalWays( 0, 0, 0, 0, 0 );
        */

        /*
        ways = new long[ N + 1, MOD, MOD, 2 ];
        for( int n = 0; n < N; ++n )
            for( int m1 = 0; m1 < MOD; ++m1 )
                for( int m2 = 0; m2 < MOD; ++m2 )
                    for( int t = 0; t < 2; ++t )
                        ways[ n, m1, m2, t ] = -1;
        uglyNumbers = TotalWays( 1, 0, digits[ 0 ] - '0', true );
        */

        /////////
        /*
        Alloc( -1 );
        uglyNumbers = TotalWays(0, 0);
        */

        /////
        uglyNumbers = TotalWays();

        return uglyNumbers;
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("UglyNumbers.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("UglyNumbers.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());
                for (int i = 1; i <= N; ++i)
                {
                    string[] inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                    digits = inputs[ 0 ];
                    writer.WriteLine(i + ": " + TotalUglyNumbers());
                }
            }
        }
    }
}