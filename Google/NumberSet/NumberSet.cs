using System;
using System.IO;

static class NumberSet
{
    static long[] numSets;
    static long[] rank;

    public static long GCD(long num1, long num2)
    {
        if (num1 < 0) num1 = -num1;
        if (num2 < 0) num2 = -num2;

        if (num2 == 0) return num1;
        if (num1 == num2) return num1;

        //---------------------------------

        //return num1 % num2 == 0 ? num2 : GCD(num2, num1 % num2);
        //---------------------------------

        while (num1 > 0 && num2 > 0)
        {
            if (num1 > num2)
            {
                num1 %= num2;
            }
            else
            {
                num2 %= num1;
            }
        }
        return num1 + num2;
        //---------------------------------
    }

    public static bool IsPrime(long num)
    {
        if (num < 0) num = -num;
        if (num <= 1) return false;
        if (num == 2) return true;
        if (num % 2 == 0) return false;

        for (int div = 3; div * div <= num; div += 2)
        {
            if (num % div == 0)
            {
                return false;
            }
        }
        return true;
    }

    public static long MaxPrimeFactor(long num)
    {
        if (num < 0) num = -num;
        if (num > 3)
        {
            //for (long div = 2; div * div <= num && num >= 1; ++div)
            //{
            //    if (num % div == 0)
            //    {
            //        while (num % div == 0)
            //        {
            //            num /= div;
            //        }
            //        if (num == 1)
            //        {
            //            return div;
            //        }
            //    }
            //}

            long maxPrimeFact = 0;
            for (long div = 2; div * div <= num && num >= 1; ++div)
            {
                if (num % div == 0)
                {
                    while (num % div == 0)
                    {
                        num /= div;
                    }
                    maxPrimeFact = Math.Max(div, maxPrimeFact);
                }
            }
            //maxPrimeFact = Math.Max(n, maxPrimeFact);
            return maxPrimeFact;
        }
        return num;
    }

    public static bool ShareMaxPrime(long num1, long num2, long P)
    {
        long maxPrime = GCD(num1, num2);
        for (int div = 2; div < P && maxPrime >= P; ++div)
        {
            while (maxPrime % div == 0)
            {
                maxPrime /= div;
            }
        }
        return maxPrime >= P;
    }

    public static long Root(long x)
    {
        if (numSets[x] != x)
        {
            numSets[x] = Root(numSets[x]);
        }
        return numSets[x];
    }

    public static void Unite(long set1, long set2)
    {
        //while (numSets[set1] != -1) set1 = numSets[set1];
        //while (numSets[set2] != -1) set2 = numSets[set2];
        //if (set1 != set2) numSets[set1] = set2;

        //set1 = Root(set1);
        //set2 = Root(set2);
        //if (set1 != set2) numSets[set1] = set2;

        //////////////////////////

        set1 = Root(set1);
        set2 = Root(set2);
        if (rank[set1] < rank[set2])
        {
            numSets[set1] = set2;
        }
        else
        {
            numSets[set2] = set1;
            if (rank[set1] == rank[set2])
            {
                ++rank[set1];
            }
        }
    }

    public static long NumSets(long A, long B, long P)
    {
        long sets = 0;

        // ------------------------------------------------------------------------
        // ------------------------------------------------------------------------
        //numSets = new long[ B + 1 ];
        //rank = new long[ B + 1 ];

        // ------------------------------------------------------------------------

        //for (long i = A; i <= B; ++i)
        //{
        //    //numSets[ i ] = -1;
        //    numSets[i] = i;
        //    rank[i] = 0;
        //}
        //for (long i = A; i < B; ++i)
        //{
        //    for (long j = i + P; j <= B; ++j)
        //    {
        //        if (MaxPrimeFactor(GCD(i, j)) >= P)
        //        {
        //            Unite(i, j);
        //        }
        //    }
        //}
        //for (long i = A; i <= B; ++i)
        //{
        //    //if( numSets[ i ] == -1 )
        //    if (numSets[i] == i)
        //    {
        //        ++sets;
        //    }
        //}
        // ------------------------------------------------------------------------

        //long interval = B - A + 1;
        //for (long i = A; i <= B; ++i)
        //{
        //    numSets[i] = i;
        //    rank[i] = 0;
        //}
        //sets = interval;
        //for (long prime = P; prime <= B; ++prime)
        //{
        //    if (IsPrime(prime))
        //    {
        //        long last = -1;
        //        for (long i = A; i <= B; ++i)
        //        {
        //            if (i % prime == 0)
        //            {
        //                if (last == -1)
        //                {
        //                    last = i;
        //                }
        //                else
        //                {
        //                    --sets;
        //                    Unite(last, i);
        //                }
        //            }
        //        }
        //    }
        //}
        // ------------------------------------------------------------------------

        //long interval = B - A + 1;
        //numSets = new long[interval];
        //rank = new long[interval];
        //for (long i = 0; i < interval; ++i)
        //{
        //    numSets[i] = i;
        //    rank[i] = 0;
        //}

        //sets = interval;

        //for (long prime = P; prime <= B; ++prime)
        //{
        //    if (!IsPrime(prime))
        //    {
        //        continue;
        //    }
        //    long x = A / prime * prime;
        //    if (x < A)
        //    {
        //        x += prime;
        //    }

        //    x -= A; // 0 indexing
        //    for (long y = x; y < interval; y += prime)
        //    {
        //        long rootX = Root(x);
        //        if (rootX != Root(y))
        //        {
        //            --sets;
        //            Unite(x, y);
        //        }
        //    }
        //}

        //// ------------------------------------------------------------------------

        //long interval = B - A + 1;
        //bool[] isComposite = new bool[interval + 1];

        //for (long i = 2; i * i <= interval; ++i)
        //{
        //    if (!isComposite[i])
        //    {
        //        for (long j = i + i; j <= interval; j += i)
        //        {
        //            isComposite[j] = true;
        //        }
        //    }
        //}

        //numSets = new long[interval];
        //rank = new long[interval];
        //for (long i = 0; i < interval; ++i)
        //{
        //    numSets[i] = i;
        //    rank[i] = 1;
        //}

        //sets = interval - 1;

        //for (long prime = P; prime <= interval; prime++)
        //{
        //    if (!isComposite[prime])
        //    {
        //        long first = prime - (A - 1) % prime;
        //        long other = first;

        //        while (true)
        //        {
        //            other += prime;
        //            if (other >= interval) break;

        //            long j = other;
        //            while (numSets[first] != first)
        //            {
        //                first = numSets[first];
        //            }

        //            while (numSets[j] != j)
        //            {
        //                j = numSets[j];
        //            }

        //            if (j != first)
        //            {
        //                long k = first;
        //                if (rank[j] < rank[k])
        //                {
        //                    long tmp = j;
        //                    j = k;
        //                    k = tmp;
        //                }

        //                rank[j] += rank[k];
        //                numSets[k] = j;

        //                --sets;
        //            }
        //        }
        //    }
        //}

        // ------------------------------------------------------------------------
        // ------------------------------------------------------------------------

        long interval = B - A + 1;
        numSets = new long[interval];
        //rank = new long[ interval ];
        for (long i = 0; i < interval; ++i)
        {
            numSets[i] = A + i;
            //rank[ i ] = 1;
        }

        sets = interval;

        for (long i = 0; i < interval; ++i)
        {
            long num1 = A + i;
            for (long j = i + P; j < interval; ++j)
            {
                long num2 = A + j;

                if (numSets[i] != numSets[j])
                {
                    //if( MaxPrimeFactor(GCD(num1, num2)) >= P )
                    if (ShareMaxPrime(num1, num2, P))
                    {
                        long pi = numSets[i], pj = numSets[j];
                        for (long k = 0; k < interval; ++k)
                        {
                            if (numSets[k] == pi)
                            {
                                numSets[k] = pj;

                                //if( rank[ j ] < rank[ k ] )
                                //{
                                //    rank[ k ] += rank[ j ];
                                //}
                                //else
                                //{
                                //    rank[ j ] += rank[ k ];
                                //}

                            }
                        }

                        --sets;
                    }
                }
            }
        }

        // ------------------------------------------------------------------------

        return sets;
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("NumberSet.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("NumberSet.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());
                for (int i = 1; i <= N; ++i)
                {
                    string[] inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    long A = long.Parse(inputs[0]);
                    long B = long.Parse(inputs[1]);
                    long P = long.Parse(inputs[2]);

                    long numSets = NumSets(A, B, P);
                    writer.WriteLine(i + ": " + numSets);
                }
            }
        }
    }
}