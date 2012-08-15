using System;
using System.IO;

static class MineLayer
{
    static readonly int BlockSize = 3;

    public static int MaxCentreMines(int R, int C, int[,] mapGrid)
    {
        //Debug.Assert(R % 2 != 0);
        //Debug.Assert(BlockSize <= R && R <= 49);
        //Debug.Assert(BlockSize <= C && C <= 49);

        int maxCentreMines = 0;

        int rowCentre = (R - 1) / 2;
        int colOff = C % BlockSize == 0 ? 1 : 0;

        int rowOff = rowCentre % BlockSize;

        // ------------------------------------------------------------------------

        #region
        //// In the strip lines
        //int goodSum = 0;
        //int rowStrip = R % BlockSize == 0 ? 1 : 0;
        //for (int j = colOff; j < C; j += BlockSize)
        //    for (int i = rowStrip; i < R; i += BlockSize)
        //        goodSum += mapGrid[ i, j ];

        //// Outside the center line
        //switch (R % BlockSize)
        //{
        //    case 0:
        //        for (int j = colOff; j < C; j += BlockSize)
        //        {
        //            for (int i = 0; i < rowCentre; i += BlockSize)
        //                maxCentreMines += mapGrid[ i, j ];
        //            //for( int i = rowCentre + 1; i < R; i += BlockSize )
        //            for (int i = R - 1; i >= rowCentre; i -= BlockSize)
        //                maxCentreMines += mapGrid[ i, j ];
        //        }
        //        //maxCentreMines -= goodSum;
        //        break;

        //    case 1:
        //        for (int j = colOff; j < C; j += BlockSize)
        //        {
        //            for (int i = 1; i < rowCentre; i += BlockSize)
        //                maxCentreMines += mapGrid[ i, j ];
        //            //for( int i = rowCentre + 1; i < R-1; i += BlockSize )
        //            for (int i = R - 2; i >= rowCentre; i -= BlockSize)
        //                maxCentreMines += mapGrid[ i, j ];
        //        }
        //        //maxCentreMines = goodSum - maxCentreMines;
        //        break;

        //    case 2:
        //        for (int j = colOff; j < C; j += BlockSize)
        //        {
        //            for (int i = 1; i < rowCentre; i += BlockSize)
        //                maxCentreMines += mapGrid[ i, j ];
        //            //for( int i = rowCentre + 1; i < R-1; i += BlockSize )
        //            for (int i = R - 2; i >= rowCentre; i -= BlockSize)
        //                maxCentreMines += mapGrid[ i, j ];
        //        }
        //        //maxCentreMines -= goodSum;
        //        break;
        //}

        //maxCentreMines = Math.Abs(maxCentreMines - goodSum);

        #endregion
        // ------------------------------------------------------------------------
        #region
        //int r = (rowCentre - rowOff) / BlockSize;
        //switch (rowOff)
        //{
        //    case 0:
        //        r = r - 1;
        //        for (int j = colOff; j < C; j += BlockSize)
        //        {
        //            for (int i = 0; i <= 2 * r + 2; ++i)
        //                maxCentreMines += mapGrid[ i * BlockSize + 0, j ];
        //            for (int i = 0; i <= r; ++i)
        //                maxCentreMines -= mapGrid[ i * BlockSize + 1, j ];
        //            for (int i = r + 1; i <= 2 * r + 1; ++i)
        //                maxCentreMines -= mapGrid[ i * BlockSize + 2, j ];
        //        }
        //        break;

        //    case 1:
        //        for (int j = colOff; j < C; j += BlockSize)
        //        {
        //            for (int i = 0; i <= r; ++i)
        //                maxCentreMines += mapGrid[ i * BlockSize + 0, j ];
        //            for (int i = 0; i <= 2 * r; ++i)
        //                maxCentreMines -= mapGrid[ i * BlockSize + 1, j ];
        //            for (int i = r; i <= 2 * r; ++i)
        //                maxCentreMines += mapGrid[ i * BlockSize + 2, j ];
        //        }
        //        break;

        //    case 2:
        //        for (int j = colOff; j < C; j += BlockSize)
        //        {
        //            for (int i = 0; i <= r; ++i)
        //            {
        //                maxCentreMines += mapGrid[ i * BlockSize + 1, j ];
        //                maxCentreMines -= mapGrid[ i * BlockSize + 0, j ];
        //            }
        //        }
        //        break;
        //}

        #endregion
        // ------------------------------------------------------------------------
        // ------------------------------------------------------------------------

        #region

        //int[] rowMines = new int[ R ];
        //for (int i = 0; i < R; ++i)
        //{
        //    rowMines[ i ] = 0;
        //    for (int j = colOff; j < C; j += BlockSize)
        //        rowMines[ i ] += mapGrid[ i, j ];
        //}

        //int[] exactMines = new int[ R ];
        //int[] trialMines = new int[ R ];
        //for (int mine = 0; mine < C + 1; ++mine)
        //{
        //    trialMines[ 0 ] = mine;
        //    for (int row = 0; row < R - 1; ++row)
        //    {
        //        int mineDiff = rowMines[ row ] - trialMines[ row ];
        //        if (row > 0) mineDiff -= trialMines[ row - 1 ];
        //        if (mineDiff < 0) goto NextMine;

        //        trialMines[ row + 1 ] = mineDiff;
        //    }

        //    if ((trialMines[ R - 2 ] + trialMines[ R - 1 ]) != rowMines[ R - 1 ])
        //        continue;
        //    if (exactMines[ rowCentre ] < trialMines[ rowCentre ])
        //        Array.Copy(trialMines, exactMines, R);

        //NextMine: ;
        //}
        //maxCentreMines = exactMines[ rowCentre ];

        #endregion
        // ------------------------------------------------------------------------

        #region
        int area = R * C;

        bool[,] mineGrid = new bool[R, C];

        Int64 finalSet = -1;
        for (Int64 set = 0; set < (1L << area); ++set)
        {
            for (int i = 0; i < R; ++i)
            {
                for (int j = 0; j < C; ++j)
                {
                    Int64 cell = 1L << (i * C + j);
                    mineGrid[i, j] = (set & cell) != 0;
                }
            }

            int centreMines = 0;
            for (int j = 0; j < C; ++j)
            {
                if (mineGrid[rowCentre, j])
                {
                    ++centreMines;
                }
            }

            if (centreMines > maxCentreMines)
            {
                bool isRight = true;
                for (int x = 0; isRight && x < R; ++x)
                {
                    for (int y = 0; isRight && y < C; ++y)
                    {
                        int connectMines = 0;

                        // -----------------------------

                        //for( int dx = -1; dx <= 1; ++dx )
                        //{
                        //	for( int dy = -1; dy <= 1; ++dy )
                        //	{
                        //		int r = x + dx;
                        //		int c = y + dy;
                        //		if( r >= 0 && r < R && c >= 0 && c < C )
                        //		{
                        //			if( mineGrid[ r, c ] )
                        //			{
                        //				++connectMines;
                        //			}
                        //		}
                        //	}
                        //}

                        // -----------------------------

                        int minX = x <= 0 ? 0 : x - 1;
                        int minY = y <= 0 ? 0 : y - 1;

                        int maxX = x >= R - 1 ? R - 1 : x + 1;
                        int maxY = y >= C - 1 ? C - 1 : y + 1;

                        for (int r = minX; r <= maxX; ++r)
                            for (int c = minY; c <= maxY; ++c)
                                if (mineGrid[r, c])
                                    ++connectMines;

                        // -----------------------------

                        isRight = (connectMines == mapGrid[x, y]);
                    }
                }

                if (isRight)
                {
                    finalSet = set;

                    //maxCentreMines = std::max(maxCentreMines, centreMines);
                    maxCentreMines = centreMines;
                }
            }
        }

        if (finalSet == -1)
        {
            maxCentreMines = -1;
        }
        else
        {
            Console.WriteLine("%X", finalSet);
            for (int i = 0; i < R; ++i)
            {
                for (int j = 0; j < C; ++j)
                {
                    Int64 cell = 1L << (i * C + j);
                    if ((finalSet & cell) != 0)
                    {
                        Console.Write("*");
                    }
                    else
                    {
                        Console.Write("o");
                    }
                }
                Console.WriteLine();
            }
        }

        #endregion
        // ------------------------------------------------------------------------

        return maxCentreMines;
    }

    /*
    public static int PowTwo( int n )
    {
        return 1 << n;
    }

    public static bool Contain( int S, int X )
    {
        return (S & PowTwo( X )) != 0;
    }
    */

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("MineLayer.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("MineLayer.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());

                for (int i = 1; i <= N; ++i)
                {
                    string[] inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    int R = int.Parse(inputs[0]);
                    int C = int.Parse(inputs[1]);

                    int[,] mapGrid = new int[R, C];
                    for (int r = 0; r < R; ++r)
                    {
                        inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                        for (int c = 0; c < C; ++c)
                        {
                            mapGrid[r, c] = int.Parse(inputs[c]);
                        }
                    }

                    int maxCentreMines = MaxCentreMines(R, C, mapGrid);
                    writer.WriteLine(i + ": " + maxCentreMines);
                }
            }
        }
    }
}