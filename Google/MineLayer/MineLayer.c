#include <STDIO.H>
#include <MATH.H>
#include <ASSERT.H>
#include <STDLIB.H>
#include <XUTILITY>
#include <LIST>

using namespace std;

typedef __int64   ll;

const int BlockSize = 3;

void EqualSetBits(int onebits, int totalbits, ll num, list<ll> &bitNums)
{
    if (onebits == 0)
    {
        //bitNums.push_front(num);
        bitNums.push_back(num);
        return;
    }

    for (int idx = totalbits - 1; (idx + 1) >= onebits; --idx)
    {
        //int x = 1LL << idx; //if((num & x) == 0)

        EqualSetBits(onebits - 1, idx, num | (1LL << idx), bitNums);
    }
}

int MaxCentreMines(int R, int C, int** mapGrid)
{
    assert(R % 2 != 0);
    assert(BlockSize <= R && R <= 49);
    assert(BlockSize <= C && C <= 49);

    int maxCentreMines = 0;

    int rowCentre = (R - 1)/2;

    int rowStrip = R % BlockSize == 0 ? 1 : 0;
    int colStrip = C % BlockSize == 0 ? 1 : 0;

    // ------------------------------------------------------------------------
#pragma region EqualSetBits
    //*-----------------------------
    //| R <= 7, C <= 5, area <= 64 |
    //-----------------------------*/

    //bool** mineGrid = new bool*[R];
    //for (int r = 0; r < R; ++r)
    //    mineGrid[r] = new bool[C];

    //int area = R * C;

    //int totalMines = 0;
    //for (int i = rowStrip; i < R; i += BlockSize)
    //    for (int j = colStrip; j < C; j += BlockSize)
    //        totalMines += mapGrid[i][j];

    //ll finalSet = -1;

    //list<ll> sets;
    //EqualSetBits(totalMines, area, 0, sets);

    ////for (ll set = 0; finalSet == -1 && set < (1LL << area); ++set)
    //for (list<ll>::const_iterator 
    //    numIter = sets.begin(); 
    //    numIter != sets.end();
    //    ++numIter)
    //{
    //    ll set = *numIter;
    //    int centreMines = 0;
    //    for (int j = 0; j < C; ++j)
    //    {
    //        for (int i = 0; i < R; ++i)
    //        {
    //            ll cell = 1LL << (i * C + j);
    //            mineGrid[i][j] = ((set & cell) != 0);
    //        }
    //        if (mineGrid[rowCentre][j])
    //            ++centreMines;
    //    }

    //    if (centreMines > maxCentreMines)
    //    {
    //        bool isOK = true;

    //        for (int x = 0; isOK && x < R; ++x)
    //        {
    //            for (int y = 0; isOK && y < C; ++y)
    //            {
    //                int minesConnect = 0;

    //                // -----------------------------
    //                //for (int dx = -1; dx <= 1; ++dx)
    //                //{
    //                //    for (int dy = -1; dy <= 1; ++dy)
    //                //    {
    //                //        int r = x + dx;
    //                //        int c = y + dy;
    //                //        if (r >= 0 && r < R && c >= 0 && c < C)
    //                //            if (mineGrid[r][c])
    //                //                ++minesConnect;
    //                //    }
    //                //}
    //                // -----------------------------
    //                int minX = (x <= 0) ? 0 : x - 1;
    //                int minY = (y <= 0) ? 0 : y - 1;

    //                int maxX = (x >= R - 1) ? R - 1 : x + 1;
    //                int maxY = (y >= C - 1) ? C - 1 : y + 1;

    //                for (int r = minX; r <= maxX; ++r)
    //                    for (int c = minY; c <= maxY; ++c)
    //                        if (mineGrid[r][c])
    //                            ++minesConnect;
    //                // -----------------------------
    //                isOK = (minesConnect == mapGrid[x][y]);
    //            }
    //        }

    //        if (isOK)
    //        {
    //            finalSet = set;
    //            //maxCentreMines = std::max(centreMines, maxCentreMines);
    //            maxCentreMines = centreMines;
    //            break;
    //        }
    //    }
    //}
    //if (finalSet == -1)
    //{
    //    maxCentreMines = -1;
    //}
    //else
    //{
    //    //printf("%X\n", finalSet);
    //    //for (int i = 0; i < R; ++i)
    //    //{
    //    //	for (int j = 0; j < C; ++j)
    //    //    {
    //    //        ll cell = 1LL << (i * C + j);
    //    //        printf("%c", ((finalSet & cell) != 0) ? '*' : 'o');
    //    //    }
    //    //	printf("\n");
    //    //}
    //}

    //if (mineGrid != NULL)
    //for (int r = 0; r < R; ++r)
    //{
    //    if (mineGrid[r] != NULL)
    //    {
    //        delete[] mineGrid[r]; mineGrid[r] = NULL;
    //    }
    //    delete[] mineGrid; mineGrid = NULL;
    //}
#pragma endregion

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
#pragma region
    //// Mines inside the strip lines
    //int totalMines = 0;
    //for (int i = rowStrip; i < R; i += BlockSize)
    //    for (int j = colStrip; j < C; j += BlockSize)
    //        totalMines += mapGrid[i][j];

    //// Mines outside the center lines
    //switch (R % BlockSize)
    //{
    //case 0:
    //    for (int j = colStrip; j < C; j += BlockSize)
    //    {
    //        for (int i = 0; i < rowCentre; i += BlockSize)
    //            maxCentreMines += mapGrid[i][j];
    //        //for (int i = rowCentre + 1; i < R; i += BlockSize)
    //        for (int i = R-1; i >= rowCentre; i -= BlockSize)
    //            maxCentreMines += mapGrid[i][j];
    //    }
    //    //maxCentreMines -= totalMines;
    //    break;

    //case 1:
    //    for (int j = colStrip; j < C; j += BlockSize)
    //    {
    //        for (int i = 1; i < rowCentre; i += BlockSize)
    //            maxCentreMines += mapGrid[i][j];
    //        //for (int i = rowCentre + 1; i < R-1; i += BlockSize)
    //        for (int i = R-2; i >= rowCentre; i -= BlockSize)
    //            maxCentreMines += mapGrid[i][j];
    //    }
    //    //maxCentreMines = totalMines - maxCentreMines;
    //    break;

    //case 2:
    //    for (int j = colStrip; j < C; j += BlockSize)
    //    {
    //        for (int i = 1; i < rowCentre; i += BlockSize)
    //            maxCentreMines += mapGrid[i][j];
    //        //for (int i = rowCentre + 1; i < R-1; i += BlockSize)
    //        for (int i = R-2; i >= rowCentre; i -= BlockSize)
    //            maxCentreMines += mapGrid[i][j];
    //    }
    //    //maxCentreMines -= totalMines;
    //    break;
    //}

    //maxCentreMines = abs(totalMines - maxCentreMines);
#pragma endregion

    // ------------------------------------------------------------------------
#pragma region
    //// Mines inside the strip lines
    //int totalMines = 0;
    //for (int i = rowStrip; i < R; i += BlockSize)
    //    for (int j = colStrip; j < C; j += BlockSize)
    //        totalMines += mapGrid[i][j];

    //// Mines outside the center lines
    //int outCentreMines = 0;
    //for (int j = colStrip; j < C; j += BlockSize)
    //{
    //    for (int i = 1 - rowStrip; i < rowCentre; i += BlockSize)
    //        outCentreMines += mapGrid[i][j];
    //    for (int i = R-2 + rowStrip; i >= rowCentre; i -= BlockSize)
    //        outCentreMines += mapGrid[i][j];
    //}

    //maxCentreMines = abs(totalMines - outCentreMines);
#pragma endregion

    // ------------------------------------------------------------------------
#pragma region
    //int rowOffset = rowCentre % BlockSize;
    //int r = (rowCentre - rowOffset)/BlockSize;
    //switch (rowOffset)
    //{
    //case 0:
    //    r = r - 1;
    //    for (int j = colStrip; j < C; j += BlockSize)
    //    {
    //        for (int i = 0; i <= 2*r + 2; ++i)
    //            maxCentreMines += mapGrid[i*BlockSize + 0][j];
    //        for (int i = 0; i <= r; ++i)
    //            maxCentreMines -= mapGrid[i*BlockSize + 1][j];
    //        for (int i = r+1; i <= 2*r + 1; ++i)
    //            maxCentreMines -= mapGrid[i*BlockSize + 2][j];
    //    }
    //    break;

    //case 1:
    //    for (int j = colStrip; j < C; j += BlockSize)
    //    {
    //        for (int i = 0; i <= r; ++i)
    //            maxCentreMines += mapGrid[i*BlockSize + 0][j];
    //        for (int i = 0; i <= 2*r; ++i)
    //            maxCentreMines -= mapGrid[i*BlockSize + 1][j];
    //        for (int i = r; i <= 2*r; ++i)
    //            maxCentreMines += mapGrid[i*BlockSize + 2][j];
    //    }
    //    break;

    //case 2:
    //    for (int j = colStrip; j < C; j += BlockSize)
    //    {
    //        for (int i = 0; i <= r; ++i)
    //        {
    //            maxCentreMines += mapGrid[i*BlockSize + 1][j];
    //            maxCentreMines -= mapGrid[i*BlockSize + 0][j];
    //        }
    //    }
    //    break;
    //}
#pragma endregion

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
#pragma region
    int* rowMines = new int[R];
    //memset(rowMines, 0, R*sizeof(int));
    for (int i = 0; i < R; ++i)
    {
        rowMines[i] = 0;
        for (int j = colStrip; j < C; j += BlockSize)
            rowMines[i] += mapGrid[i][j];
    }

    int* exactMines = new int[R];
    for (int i = 0; i < R; ++i)
        exactMines[i] = INT_MIN;

    int* trialMines = new int[R];
    for (int mine = 0; mine < C+1; ++mine)
    {
        trialMines[0] = mine;
        int mineDiff;

        // ------------------------------------------------
        //for (int row = 0; row < R-1; ++row)
        //{
        //    mineDiff = rowMines[row] - trialMines[row];
        //    if (row > 0) mineDiff -= trialMines[row-1];
        //    if (mineDiff < 0) break;
        //
        //    trialMines[row+1] = mineDiff;
        //}
        // ------------------------------------------------
        mineDiff = rowMines[0] - trialMines[0];
        if (mineDiff < 0) continue;

        trialMines[1] = mineDiff;

        for (int row = 1; row < R-1; ++row)
        {
            mineDiff = rowMines[row] - (trialMines[row-1] + trialMines[row]);
            if (mineDiff < 0) break;

            trialMines[row+1] = mineDiff;
        }
        // ------------------------------------------------

        if (mineDiff < 0) continue;

        if (rowMines[R-1] != (trialMines[R-2] + trialMines[R-1]))
            continue;

        //maxCentreMines = std::max(maxCentreMines, trialMines[rowCentre]);
        if (trialMines[rowCentre] > exactMines[rowCentre])
            for (int i = 0; i < R; ++i)
                exactMines[i] = trialMines[i];

    }

    maxCentreMines = exactMines[rowCentre];
    if (maxCentreMines != INT_MIN)
    {
        //for (int i = 0; i < R; ++i)
        //    printf(" %d", exactMines[i]);
        //printf("\n");
    }

    if (trialMines != NULL)
    {
        delete[] trialMines; trialMines = NULL;
    }
    if (exactMines != NULL)
    {
        delete[] exactMines; exactMines = NULL;
    }
    if (rowMines != NULL)
    {
        delete[] rowMines; rowMines = NULL;
    }
#pragma endregion

    // ------------------------------------------------------------------------

    return maxCentreMines;
}

void main()
{
    freopen("MineLayer.in", "r", stdin);
    freopen("MineLayer.out", "w", stdout);

    int N;
    scanf(" %d", &N);
    for (int i = 1; i <= N; ++i)
    {
        int R, C;
        scanf(" %d %d", &R, &C);

        int** mapGrid = new int*[R];
        for (int r = 0; r < R; ++r)
        {
            mapGrid[r] = new int[C];
            for (int c = 0; c < C; ++c)
                scanf(" %d", &mapGrid[r][c]);
        }

        int maxCentreMines = MaxCentreMines(R, C, mapGrid);
        printf("%d: %d\n", i, maxCentreMines);

        if (mapGrid != NULL)
        {
            for (int r = 0; r < R; ++r)
            {
                if (mapGrid[r] != NULL) 
                { 
                    delete[] mapGrid[r]; 
                    mapGrid[r] = NULL; 
                }
            }
            delete[] mapGrid; mapGrid = NULL;
        }
    }
}