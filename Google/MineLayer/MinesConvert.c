#include <STDIO.H>

typedef	__int64 ll;

const int sizeBlock = 3;

int ConnectedMines(int x, int y, int R, int C, bool** mineGrid)
{
    int nMines = 0;

    // ----------------------------------------------------
    //int r, c;

    //r = x - 1;
    //c = y - 1;
    //if (r >= 0 && c >= 0 && mineGrid[r][c])
    //    ++nMines;

    //r = x;
    //if (c >= 0 && mineGrid[r][c])
    //    ++nMines;

    //r = x + 1;
    //if (r < R && c >= 0 && mineGrid[r][c])
    //    ++nMines;

    //c = y;
    //if (r < R && mineGrid[r][c])
    //    ++nMines;

    //c = y + 1;
    //if (r < R && c < C && mineGrid[r][c])
    //    ++nMines;

    //r = x;
    //if (c < C && mineGrid[r][c])
    //    ++nMines;

    //r = x - 1;
    //if (r >= 0 && c < C && mineGrid[r][c])
    //    ++nMines;

    //c = y;
    //if (r >= 0 && mineGrid[r][c])
    //    ++nMines;

    //r = x;
    //if (mineGrid[r][c])
    //    ++nMines;

    //----------------------------------------------------

    //for (int dx = -1; dx <= 1; ++dx)
    //    for (int dy = -1; dy <= 1; ++dy)
    //    {
    //        int r = x + dx;
    //        int c = y + dy;
    //        if ((r >= 0 && r < R) && (c >= 0 && c < C))
    //            if (mineGrid[r][c])
    //                ++nMines;
    //    }

    // ----------------------------------------------------

    int minX = x <= 0 ? 0 : x - 1;
    int minY = y <= 0 ? 0 : y - 1;

    int maxX = (x >= R - 1 ? R : x + (sizeBlock - 1)) - 1; // x >= R - 1 ? R : x + sizeBlock - 1;
    int maxY = (y >= C - 1 ? C : y + (sizeBlock - 1)) - 1; // y >= C - 1 ? C : y + sizeBlock - 1;

    for (int r = minX; r <= maxX; ++r) //for (int r = minX; r < maxX; ++r)
    {
        for (int c = minY; c <= maxY; ++c) //for (int c = minY; c < maxY; ++c)
        {
            if (mineGrid[r][c])
            {
                ++nMines;
            }
        }
    }
    return nMines;
}

void ConvertGrid(int R, int C, bool** mineGrid, int** &mapGrid)
{
    mapGrid = new int*[R];
    for (int r = 0; r < R; ++r)
    {
        mapGrid[r] = new int[C];
        for (int c = 0; c < C; ++c)
        {
            mapGrid[r][c] = ConnectedMines(r, c, R, C, mineGrid);
        }
    }
}

void main()
{
    freopen("MinesConvert.in", "r", stdin);
    freopen("MinesConvert.out", "w", stdout);

    int N;
    scanf(" %d", &N);

    for (int i = 1; i <= N; ++i)
    {
        int R, C;
        scanf(" %d %d", &R, &C);

        //char** mineGrid = new char*[R];
        //for (int r = 0; r < R; ++r)
        //{
        //    mineGrid[r] = new char[C];
        //    scanf("%s", mineGrid[r]);
        //}

        bool** mineGrid = new bool*[R];
        for (int r = 0; r < R; ++r)
        {
            mineGrid[r] = new bool[C];
            for (int c = 0; c < C; ++c)
            {
                char cell;
                scanf(" %c[^\n]", &cell);
                mineGrid[r][c] = (cell == '*');
            }
        }

        int** mapGrid = NULL;
        ConvertGrid(R, C, mineGrid, mapGrid);

        printf("%d:\n", i + 1);
        printf("%d %d\n", R, C);
        for (int r = 0; r < R; ++r)
        {
            for (int c = 0; c < C; ++c)
            {
                printf("%2d", mapGrid[r][c]);
            }
            printf("\n");
        }
        
        if (mapGrid != NULL)
        {
            for (int r = 0; r < R; ++r)
            {
                if (mapGrid[r] != NULL) 
                { 
                    delete[] mapGrid[r]; mapGrid[r] = NULL; 
                }
            }
            delete[] mapGrid; mapGrid = NULL;
        }
        if (mineGrid != NULL)
        {
            for (int r = 0; r < R; ++r)
            {
                if (mineGrid[r] != NULL) 
                { 
                    delete[] mineGrid[r]; mineGrid[r] = NULL; 
                }
            }
            delete[] mineGrid; mineGrid = NULL;
        }
    }
}