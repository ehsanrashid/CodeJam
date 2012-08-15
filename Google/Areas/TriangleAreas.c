#include <STDIO.H>
#include <ASSERT.H>
#include <ALGORITHM>

bool TestArea(int area, int N, int M, int &base, int &height)
{
    if (area < 0) return false;
    if (area == 0)
    {
        base = height = 0;
        return true;
    }

    for (base = (area - 1)/M + 1; base <= N; ++base) // atleast base = 1
    {
        if (area % base == 0)
        {
            height = area / base;
            if (height <= M)
            {
                return true; // base & height found
            }
        }
    }

    return false;
}

bool FindPoints(int N, int M, int A,
    int &x1, int &y1,
    int &x2, int &y2,
    int &x3, int &y3)
{
    if (A > N * M) return false;

    // --------------------------------------------------------------

    //int H = A / M;	// N
    //int R = A % M;	// N

    //x1 = 0; y1 = 0;
    //x2 = M;		// N
    //if (R == 0)
    //{
    //    y2 = 0;
    //    x3 = 0; y3 = H;
    //}
    //else
    //{
    //    y2 = 1;
    //    x3 = M - R;	//(N*M - A) % M;
    //    y3 = H + 1;
    //}
    //return true;

    // --------------------------------------------------------------

    //int P = A - A % N;
    //if (P < A)
    //{
    //    P += N;
    //}

    //x1 = 0;     y1 = 0;
    //x2 = M;     y2 = 1;
    //x3 = P - A; y3 = P / N;
    //return true;

    // --------------------------------------------------------------

    //x1 = 0; y1 = 0;
    //x2 = M; y2 = 1;

    //x3 = -(A % M);
    //while (x3 < 0)
    //{
    //    x3 += M;
    //}
    //y3 = A / M + 1;
    //return true;

    // --------------------------------------------------------------
    // --------------------------------------------------------------

    int area = 0;
    // (x1 y1)
    x1 = 0; y1 = 0;
    while ((area + A) <= (N * M))
    {
        // {x2} [y2 x3] {y3}
        if (TestArea(area, N, M, x3, y2) &&
            TestArea(area + A, N, M, x2, y3))
        {
            return true;
        }
        ++area;
    }
    return false;

    // --------------------------------------------------------------
    // --------------------------------------------------------------

    //int size = 0;
    //int areas[ 20000 ];

    //for (int i = 0; i <= N; ++i)
    //{
    //    for (int j = 0; j <= M; ++j)
    //    {
    //        areas[ size++ ] = i * j;
    //    }
    //}

    //std::sort//<int[]>
    //	(areas, areas + size);
    //int k = 0;
    //x1 = 0; y1 = 0;
    //for (int i = 0; i < size; ++i)
    //{
    //    for (; k < size && areas[ k ] - areas[ i ] < A; ++k)
    //        ;
    //    if (k == size) break;
    //
    //    if (areas[ k ] - areas[ i ] == A)
    //    {
    //        TestArea(areas[ i ], N, M, x3, y2);
    //        TestArea(areas[ k ], N, M, x2, y3);
    //        return true;
    //    }
    //}
    //return false;

    // --------------------------------------------------------------
}


void main()
{
    FILE* file = freopen("TriangleAreas.in", "r", stdin);
    if (file != NULL)
    {
        freopen("TriangleAreas.out", "w", stdout);

        int C;
        scanf(" %d", &C);
        assert(1 <= C && C <= 1000);

        for (int i = 1; i <= C; ++i)
        {
            int N, M, A;
            scanf(" %d %d %d", &N, &M, &A);

            printf("%d: ", i);

            int x1, y1, x2, y2, x3, y3;

            if (FindPoints(N, M, A, x1, y1, x2, y2, x3, y3))
                printf("%d %d %d %d %d %d", x1, y1, x2, y2, x3, y3);
            else
                printf("IMPOSSIBLE");

            printf("\n");
        }
    }
}