#include <STDIO.H>
#include <ASSERT.H>

#include <MEMORY.H>

typedef unsigned int        uint;
typedef long long           ll;
typedef unsigned long long  ull;

const uint points = 3;

#pragma region Counting

////compute n!
ull Factorial(int n)
{
    if (n < 0) n = -n;
    if (n == 0 || n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 6;

    // ---------------------------------------------
    //return n * Factorial(n - 1);
    // ---------------------------------------------

    ll fact = 1;
    while (n > 1)
    {
        fact *= n--;
    }
    return fact;
}

ull Permute(int n, int r)
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

    ll permute = 1;
    while (r-- > 0)
    {
        permute *= n--;
    }
    return permute;
}

ull Combine(int n, int r)
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

#pragma endregion

ll CropTriangle(ull n, ull A, ull B, ull C, ull D, ull x0, ull y0, ull M)
{
    ll triangles = 0;

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    int remainderCount[points][points]; // remainders count
    memset(remainderCount, 0, sizeof(remainderCount));

    for (int i = 0; i < n; ++i)
    {
        //printf("%ld, %ld\n", x0, y0);
        ++remainderCount[x0 % points][y0 % points];
        x0 = (A * x0 + B) % M;
        y0 = (C * y0 + D) % M;
    }

    // ------------------------------------------------------------------------
    for (int i = 0; i < points; ++i)
    {
        int horizTri = 1;
        int vertiTri = 1;
        for (int j = 0; j < points; ++j)
        {
            horizTri *= remainderCount[i][j];
            vertiTri *= remainderCount[j][i];

            int cellTri = remainderCount[i][j];
            if (cellTri >= points)
            {
                triangles += cellTri * (cellTri - 1) * (cellTri - 2) / 6;
                //triangles += Combine(cellTri, points); 
            }

            //for (int k = 0; k < points; ++k)
            //    if (i != j && j != k && k != i)
            if (i != j)        // ZigZag
            {
                int k = (2 * (i + j)) % points;
                triangles += remainderCount[0][i] * remainderCount[1][j] * remainderCount[2][k];
                //triangles += remainderCount[i][0] * remainderCount[j][1] * remainderCount[k][2];
            }
        }
        //triangles += (remainderCount[i][0] * remainderCount[i][1] * remainderCount[i][2]    // Horizontal
        //            + remainderCount[0][i] * remainderCount[1][i] * remainderCount[2][i]);  // Vertical

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
    //                int cellTri = remainderCount[i / points][i % points];
    //                if (cellTri < points)
    //                    continue;

    //                triangles += cellTri * (cellTri - 1) * (cellTri - 2) / 6;
    //                //triangles += Combine(cellTri, points);
    //            }
    //            else
    //            {
    //                int ci = remainderCount[i / points][i % points];
    //                int cj = remainderCount[j / points][j % points];
    //                int ck = remainderCount[k / points][k % points];
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
    //            if ((i1 + i2 + i3) % points)
    //                continue;

    //            if ((j1 + j2 + j3) % points)
    //                continue;

    //            int tri = 1;

    //            tri *= remainderCount[i1][j1]--;
    //            tri *= remainderCount[i2][j2]--;
    //            tri *= remainderCount[i3][j3]--;

    //            ++remainderCount[i1][j1];
    //            ++remainderCount[i2][j2];
    //            ++remainderCount[i3][j3];

    //            triangles += tri;
    //        }
    //    }
    //}
    //triangles /= 6;
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------

    //ll* x = new ll[n];
    //ll* y = new ll[n];
    //x[0] = x0;
    //y[0] = y0;
    ////printf("%ld, %ld\n", x[0], y[0]);
    //for (int i = 1; i < n; ++i)
    //{
    //    x[i] = (A * x[i - 1] + B) % M;
    //    y[i] = (C * y[i - 1] + D) % M;
    //    //printf("%ld, %ld\n", x[i], y[i]);
    //}
    //for (int i = 0; i < n; ++i)
    //    for (int j = i + 1; j < n; ++j)
    //        for (int k = j + 1; k < n; ++k)
    //            if ((x[i] + x[j] + x[k]) % points == 0 &&
    //                (y[i] + y[j] + y[k]) % points == 0)
    //                ++triangles;
    // ------------------------------------------------------------------------

    return triangles;
}

void main()
{
    FILE* file = freopen("CropTriangles.in", "r", stdin);
    if (file != NULL)
    {
        freopen("CropTriangles.out", "w", stdout);

        int N;
        scanf(" %d", &N);

        assert(1 <= N && N <= 10);

        for (int i = 1; i <= N; ++i)
        {
            ll n, A, B, C, D, x0, y0, M;
            scanf(" %lld %lld %lld %lld %lld %lld %lld %lld",
                &n, &A, &B, &C, &D, &x0, &y0, &M);

            //assert(3 <= n && n <= 100);   //small
            assert(3 <= n && n <= 100000);  //large

            assert(0 <= A && A <= 1000000000);
            assert(0 <= B && B <= 1000000000);
            assert(0 <= C && C <= 1000000000);
            assert(0 <= D && D <= 1000000000);

            assert(0 <= x0 && x0 <= 1000000000);
            assert(0 <= y0 && y0 <= 1000000000);

            assert(1 <= M && M <= 1000000000);

            ll cropTriangle = CropTriangle(n, A, B, C, D, x0, y0, M);
            printf("%d: %lld\n", i, cropTriangle);
        }
    }
}