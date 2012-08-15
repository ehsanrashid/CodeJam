using System;
using System.IO;

static class CropTriangles
{
    static readonly int points = 3;

    #region Counting

    public static UInt64 Factorial(int n)
    {
        if (n < 0) n = -n;
        if (n == 0 || n == 1) return 1;
        if (n == 2) return 2;
        if (n == 3) return 6;

        // ---------------------------------------------
        //return n * Factorial(n - 1);
        // ---------------------------------------------

        long fact = 1;
        while (n > 1)
            fact *= n--;
        return fact;
    }

    public static UInt64 Permute(int n, int r)
    {
        if (n < 0) n = -n;
        if (r < 0) r = -r;
        if (n < r) return 0;
        if (n == 0 || n == 1) return 1;
        if (r == 0) return 1;
        if (r == 1) return n;
        if (r == n) return Factorial(n);

        // ---------------------------------------------
        //return Factorial(n) / Factorial(n - r);
        // ---------------------------------------------

        long permute = 1;
        while (r-- > 0)
            permute *= n--;
        return permute;
    }

    public static UInt64 Combine(int n, int r)
    {
        if (n < 0) n = -n;
        if (r < 0) r = -r;
        if (n < r) return 0;
        if (n == 0 || n == 1) return 1;
        if (r == 0 || r == n) return 1;
        if (r == 1 || r == n - 1) return n;

        if (r > n / 2) r = n - r;

        return
            Permute(n, r) / Factorial(r);
        //Combine(n - 1, r - 1) + Combine(n - 1, r);
    }
    #endregion

    public static long CropTriangle(long n, long A, long B, long C, long D, long x0, long y0, long M)
    {
        long triangles = 0;

        // ------------------------------------------------------------------------
        // ------------------------------------------------------------------------

        long[ , ] remainderCount = new long[ points, points ]; // remainders count
        for (int i = 0; i < n; ++i)
        {
            //Console.WriteLine("(" + x0 + ", " + y0 + ")");
            ++remainderCount[ x0 % points, y0 % points ];
            x0 = (A * x0 + B) % M;
            y0 = (C * y0 + D) % M;
        }

        // ------------------------------------------------------------------------

        for (int i = 0; i < points; ++i)
        {
            long horizTri = 1;
            long vertiTri = 1;
            for (int j = 0; j < points; ++j)
            {
                horizTri *= remainderCount[ i, j ];
                vertiTri *= remainderCount[ j, i ];

                long cellTri = remainderCount[ i, j ];
                if (cellTri >= points)
                {
                    triangles += cellTri * (cellTri - 1) * (cellTri - 2) / 6;
                    //triangles += Combine(cellTri, points); 
                }

                //for( int k = 0; k < points; ++k )
                //    if( i != j && j != k && k != i )
                if (i != j)        // ZigZag
                {
                    int k = (2 * (i + j)) % points;
                    triangles += remainderCount[ 0, i ] * remainderCount[ 1, j ] * remainderCount[ 2, k ];
                    //triangles += remainderCount[ i, 0 ] * remainderCount[ j, 1 ] * remainderCount[ k, 2 ];
                }
            }
            //triangles += remainderCount[ i, 0 ] * remainderCount[ i, 1 ] * remainderCount[ i, 2 ];  // Horizontal
            //triangles += remainderCount[ 0, i ] * remainderCount[ 1, i ] * remainderCount[ 2, i ];  // Vertical

            triangles += (horizTri + vertiTri);
        }


        // ------------------------------------------------------------------------

        //for (int i = 0; i < points * points; ++i)
        //{
        //    for (int j = i; j < points * points; ++j)
        //    {
        //        for (int k = j; k < points * points; ++k)
        //        {
        //            if ((i / points + j / points + k / points) % points != 0)
        //                continue;
        //            if ((i % points + j % points + k % points) % points != 0)
        //                continue;

        //            if (i == j && j == k && k == i)
        //            {
        //                long cellTri = remainderCount[ i / points, i % points ];
        //                if (cellTri >= points)
        //                {
        //                    triangles += cellTri * (cellTri - 1) * (cellTri - 2) / 6;
        //                    //triangles += Combine(cellTri, points);
        //                }
        //            }
        //            else
        //            {
        //                long ci = remainderCount[ i / points, i % points ];
        //                long cj = remainderCount[ j / points, j % points ];
        //                long ck = remainderCount[ k / points, k % points ];
        //                triangles += ci * cj * ck;
        //            }
        //        }
        //    }
        //}

        // ------------------------------------------------------------------------

        //for (int i1 = 0; i1 < points; ++i1) for (int j1 = 0; j1 < points; ++j1)
        //{
        //    for (int i2 = 0; i2 < points; ++i2) for (int j2 = 0; j2 < points; ++j2)
        //    {
        //        for (int i3 = 0; i3 < points; ++i3) for (int j3 = 0; j3 < points; ++j3)
        //        {
        //            if ((i1 + i2 + i3) % points != 0)
        //                continue;
        //            if ((j1 + j2 + j3) % points != 0)
        //                continue;

        //            long tri = 1;
        //            tri *= remainderCount[ i1, j1 ]--;
        //            tri *= remainderCount[ i2, j2 ]--;
        //            tri *= remainderCount[ i3, j3 ]--;

        //            ++remainderCount[ i1, j1 ];
        //            ++remainderCount[ i2, j2 ];
        //            ++remainderCount[ i3, j3 ];

        //            triangles += tri;
        //        }
        //    }
        //}
        //triangles /= 6;

        // ------------------------------------------------------------------------
        // ------------------------------------------------------------------------

        //long[] x = new long[ n ];
        //long[] y = new long[ n ];
        //x[ 0 ] = x0;
        //y[ 0 ] = y0;
        ////writer.WriteLine("(" + x[ 0 ] + ", " + y[ 0 ] + ")");
        //for (int i = 1; i < n; ++i)
        //{
        //    x[ i ] = (A * x[ i - 1 ] + B) % M;
        //    y[ i ] = (C * y[ i - 1 ] + D) % M;
        //    //Console.WriteLine("(" + x[ i ] + ", " + y[ i ] + ")");
        //}

        //for (int i = 0; i < n; ++i)
        //    for (int j = i + 1; j < n; ++j)
        //        for (int k = j + 1; k < n; ++k)
        //            if ((x[ i ] + x[ j ] + x[ k ]) % points == 0 &&
        //                (y[ i ] + y[ j ] + y[ k ]) % points == 0)
        //                ++triangles;

        // ------------------------------------------------------------------------

        return triangles;
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("CropTriangles.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("CropTriangles.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());

                for (int i = 1; i <= N; ++i)
                {
                    string[] inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    long n = long.Parse(inputs[ 0 ]);
                    long A = long.Parse(inputs[ 1 ]);
                    long B = long.Parse(inputs[ 2 ]);
                    long C = long.Parse(inputs[ 3 ]);
                    long D = long.Parse(inputs[ 4 ]);
                    long x0 = long.Parse(inputs[ 5 ]);
                    long y0 = long.Parse(inputs[ 6 ]);
                    long M = long.Parse(inputs[ 7 ]);

                    long cropTriangle = CropTriangle(n, A, B, C, D, x0, y0, M);
                    writer.WriteLine(i + ": " + cropTriangle);
                }
            }
        }
    }
}