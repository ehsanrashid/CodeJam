#include <STDIO.H>

typedef          __int64  ll;
typedef unsigned __int64  ull;

const ll MOD = 1000000007;

void GenerateSeq(int n, int m, ll X, ll Y, ll Z , ll A[], ll *&Seq)
{
    Seq = new ll[n];
    for (int i = 0; i < n; ++i)
    {
        int j = i % m;
        Seq[i] = A[j];
        A[j] = (X * A[j] + Y * (i+1)) % Z;
    }
}

int IncreasingSubSequences(int n, ll *&Seq)
{
    int TotalIncSeq = 0;

    int *IncSubSeq;

    // ------------------------------------------------------------------------
    //IncSubSeq = new int[n+1];
    //for (int i = n; i > 0; --i)
    //{
    //    Seq[i] = Seq[i - 1];
    //}
    //IncSubSeq[0] = 1;
    //Seq[0] = -1;
    //for (int i = 1; i <= n; ++i)
    //{
    //    IncSubSeq[i] = 0;
    //    for (int j = i - 1; j >= 0; --j)
    //    {
    //        if (Seq[i] > Seq[j])
    //        {
    //            IncSubSeq[i] = (IncSubSeq[i] + IncSubSeq[j]) % MOD;
    //        }
    //    }
    //    TotalIncSeq = (TotalIncSeq + IncSubSeq[i]) % MOD;
    //    //(TotalIncSeq += IncSubSeq[i]) %= MOD;
    //}
    // ------------------------------------------------------------------------

    IncSubSeq = new int[n];
    for (int i = 0; i < n; ++i)
    {
        IncSubSeq[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (Seq[i] > Seq[j])
            {
                IncSubSeq[i] = (IncSubSeq[i] + IncSubSeq[j]) % MOD;
            }
        }
        TotalIncSeq = (TotalIncSeq + IncSubSeq[i]) % MOD;
        //(TotalIncSeq += IncSubSeq[i]) %= MOD;
    }
    // ------------------------------------------------------------------------
    ////
    //for (int i = 0; i < n; ++i)
    //{
    //    TotalIncSeq = (TotalIncSeq + IncSubSeq[i]) % MOD;
    //}

    if (IncSubSeq != NULL)
    {
        delete[] IncSubSeq; IncSubSeq = NULL;
    }

    return TotalIncSeq;
}

void main()
{
    freopen("SpeedLimit.in", "r", stdin);
    freopen("SpeedLimit.out", "w", stdout);

    int N;
    scanf(" %d", &N);
    assert(1 <= N && N <= 20);

    for (int i = 1; i <= N; ++i)
    {
        int n, m;	
        ll X, Y, Z;
        scanf(" %d %d %lld %lld %lld", &n, &m, &X, &Y, &Z);
        assert(1 <= n && n <= 500000);
        assert(1 <= m && m <= 500000);

        assert(0 <= X && X <= 1000000000);
        assert(0 <= Y && Y <= 1000000000);
        assert(1 <= Z && Z <= 1000000000);

        ll *A = new ll[m];
        for (int i = 0; i < m; ++i)
        {
            scanf(" %lld", &A[i]);
            assert(1 <= A[i] && A[i] <= 1000000000);
        }

        ll *Seq = NULL;
        GenerateSeq(n, m, X, Y, Z, A, Seq);

        if (A != NULL) { delete[] A; A = NULL; }

        int speedLimit = IncreasingSubSequences(n, Seq);
        printf("%d: %d\n", i, speedLimit);

        if (Seq != NULL) { delete[] Seq; Seq = NULL; }
    }

}