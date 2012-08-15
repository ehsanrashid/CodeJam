#include <STDIO.H>
#include <STRING.H>
#include <ASSERT.H>
#include <XUTILITY>
//#include <LIMITS.H>

const int BufferSize = 50000;

// ------------------------------------------------------------------
// ------------------------------------------------------------------
#pragma region
//int normal[16][16];	// = {{0}};
//int cross[16][16];	// = {{0}};
//int memo[16][16][(1 << 16)];
//
//int Travel(int x, int y, int k, int mask)
//{
//    int &ans = memo[x][y][mask];
//
//    if (ans == -1)
//    {
//        if (mask == 0) return ans = normal[x][y];
//
//        ans = INT_MAX;
//        for (int i = 0; i < k; ++i)
//        {
//            int sub = 1 << i;
//            if ((mask & sub) != 0)
//                ans = std::min(ans, normal[x][i] + Travel(i, y, k, mask ^ sub));
//        }
//    }
//    return ans;
//}
//
//int SizePermRLE(int k, char S[])
//{
//    assert(2 <= k && k <= 16);
//
//    int lengthS = strlen(S);
//    assert(lengthS <= BufferSize);
//    assert(lengthS % k == 0);
//
//    memset(normal, 0, sizeof(normal));
//    memset(cross, 0, sizeof(cross));
//    memset(memo, -1, sizeof(memo));
//
//    for (int index1 = 0; index1 < k; ++index1)
//        for (int index2 = 0; index2 < k; ++index2)
//            for (int block = 0; block < lengthS; block += k)
//            {
//                if (S[block + index1] != S[block + index2]) 
//                    ++normal[index1][index2];
//
//                if (block >= k)
//                    if (S[block - k + index1] != S[block + index2])
//                        ++cross[index1][index2];
//            }
//
//    int permGains = INT_MAX;
//    for (int i = 0; i < k; ++i)
//        for (int j = 0; j < k; ++j)
//            if (i != j)
//            {
//                int mask = (1 << k) - 1;
//                mask &= ~(1 << i);
//                mask &= ~(1 << j);
//                permGains = std::min(permGains, Travel(i, j, k, mask) + cross[j][i]);
//            }
//
//    return permGains + 1;
//}
//
//------------------------------------------------------------------
//    ------------------------------------------------------------------
//
//short **allGains;
//short **permGains; 
//
//short SizeBestPermutation(short x, int L, short block, short k, int lengthS) 
//{
//    if (L == 0) return allGains[x][k + block];
//
//    short &sizeGain = permGains[x][L];
//    if (sizeGain == -1)
//    {
//        sizeGain = 0;
//        for (short y = 0; y < k && (1 << y) <= L; ++y)
//        {
//            if ((L & (1 << y)) != 0)
//            {
//                short totalGain = SizeBestPermutation(y, L & ~(1 << y), block, k, lengthS) + allGains[x][y];
//                sizeGain = std::max(sizeGain, totalGain);
//            }
//        }
//    }
//    return sizeGain;
//}
//
//int SizePermRLE(short k, char S[])
//{
//    assert(2 <= k && k <= 16);
//
//    int lengthS = strlen(S);
//    assert(lengthS <= BufferSize);
//    assert(lengthS % k == 0);
//
//#pragma region Allocation
//    allGains = new short*[k];
//    if (allGains != NULL)
//        for (int i = 0; i < k; ++i)
//            allGains[i] = new short[2*k];
//
//    permGains = new short*[k];
//    if (permGains != NULL)
//        for (int i = 0; i < k; ++i)
//            permGains[i] = new short[(1 << k)];
//
//#pragma endregion
//
//    for (short i = 0; i < k; ++i)
//        for (short j = 0; j < 2*k; ++j)
//        {
//            allGains[i][j] = 0;
//            for (int index = 0; index + j < lengthS; index += k)
//                if (S[index + i] == S[index + j])
//                    ++allGains[i][j];
//        }
//
//    short sizeGain = 0;
//    for (short block = 0; block < k; ++block)
//    {
//        for (short i = 0; i < k; ++i)
//            for (int j = 0; j < (1 << k); ++j)
//                permGains[i][j] = -1;
//
//        short totalGain = SizeBestPermutation(block, (1 << k) - (1 << block) - 1, block, k, lengthS);
//        sizeGain = std::max(sizeGain, totalGain);
//    }
//
//#pragma region DeAllocation
//    for (short i = 0; i < k; ++i)
//    {
//        if (permGains[i] != NULL) { delete[] permGains[i]; permGains[i] = NULL; }
//        if (allGains[i] != NULL) { delete[] allGains[i]; allGains[i] = NULL; }
//    }
//
//    if (permGains != NULL) { delete[] permGains; permGains = NULL; }
//    if (allGains != NULL) { delete[] allGains; allGains = NULL; }
//#pragma endregion
//
//    return lengthS - sizeGain;
//}
#pragma endregion
// ------------------------------------------------------------------

int SizePermRLE(short k, char S[])
{
    assert(2 <= k && k <= 16);

    int lengthS = strlen(S);
    assert(lengthS <= BufferSize);
    assert(lengthS % k == 0);

    //short groups = lengthS / k;

#pragma region Allocation
    // k x k
    short **edgeGains = new short*[k];
    if(edgeGains != NULL)
        for (int i = 0; i < k; ++i)
            edgeGains[i] = new short[k];

    // k x k
    short **nextGains = new short*[k];
    if (nextGains != NULL)
        for (int i = 0; i < k; ++i)
            nextGains[i] = new short[k];

    // k x (1 << k)
    short **permGains = new short*[k];
    if (permGains != NULL)
        for (int i = 0; i < k; ++i)
            permGains[i] = new short[(1 << k)];

#pragma endregion

    for (short i = 0; i < k; ++i)
    {
        for (short j = 0; j < k; ++j)
        {
            edgeGains[i][j] = 0;
            for (int index = 0; index + j < lengthS; index += k)
                if (S[index + i] == S[index + j])
                    ++edgeGains[i][j];

            nextGains[i][j] = 0;
            for (int index = 0; index + k + j < lengthS; index += k)
                if (S[index + i] == S[index + k + j])
                    ++nextGains[i][j];
        }
    }

    short sizeGain = 0;

    for (short block = 0; block < k; block++)
    {
        for (short i = 0; i < k; ++i)
            for (int j = 0; j < (1 << k); ++j)
                permGains[i][j] = SHRT_MIN;

        permGains[block][1 << block] = 0;

        for (int mask = 0; mask < (1 << k); ++mask)
        {
            for (short cur = 0; cur < k; ++cur)
            {
                for (short next = 0; next < k; ++next)
                {
                    int perm = (1 << next);
                    if ((mask & perm) == 0)
                    {
                        short totalGain = permGains[cur][mask] + edgeGains[cur][next];
                        permGains[next][mask | perm] = std::max(permGains[next][mask | perm], totalGain);
                    }
                }
            }
        }
        for (short fn = 0; fn < k; ++fn)
        {
            short totalGain = permGains[fn][(1 << k) - 1] + nextGains[fn][block];
            sizeGain = std::max(sizeGain, totalGain);
        }
    }

#pragma region DeAllocation
    for (int i = 0; i < k; ++i)
    {
        if (edgeGains[i] != NULL) { delete[] edgeGains[i]; edgeGains[i] = NULL; }
        if (nextGains[i] != NULL) { delete[] nextGains[i]; nextGains[i] = NULL; }
        if (permGains[i] != NULL) { delete[] permGains[i]; permGains[i] = NULL; }
    }

    if (edgeGains != NULL) { delete[] edgeGains; edgeGains = NULL; }
    if (nextGains != NULL) { delete[] nextGains; nextGains = NULL; }
    if (permGains != NULL) { delete[] permGains; permGains = NULL; }
#pragma endregion

    return lengthS - sizeGain;
}
// ------------------------------------------------------------------

//int A[BufferSize][16], C[16][16];
//int f[1 << 16][16];
//
//int Solve(int used, int last, int final)
//{
//    if (used == two(n) - 1)
//    {
//        return C[last][final];
//    }
//    int &ret = f[used][last];
//    if (ret != -1) return ret;
//
//    ret = 1000000;
//    for (int i=0; i < n; ++i)
//    {
//        if (!contain(used, i))
//        {
//            checkmin(ret, solve(used + two(i), i, final) + C[last][i]);
//        }
//    }
//    return ret;
//}


void main()
{
    FILE* file = freopen("PermRLE.in", "r", stdin);
    if (file != NULL)
    {
        freopen("PermRLE.out", "w", stdout);

        int N;
        scanf(" %d", &N);
        for (int i = 1; i <= N; ++i)
        {
            int k;
            scanf(" %d", &k);

            char S[BufferSize];
            scanf(" %s", S);

            int compressedSize = SizePermRLE(k, S);
            printf(" %d: %d\n", i, compressedSize);
        }
    }
}