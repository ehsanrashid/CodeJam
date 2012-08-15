using System;
using System.IO;

static class Mines
{
    static readonly int sizeBlock = 3;

    public static void ConvertGrid(int R, int C, char[,] mineGrid, out int[,] mapGrid)
    {
        mapGrid = new int[R, C];
        for (int i = 0; i < R; ++i)
        {
            for (int j = 0; j < C; ++j)
            {
                mapGrid[i, j] = ConnectedMines(i, j, R, C, mineGrid);
            }
        }
    }

    public static int ConnectedMines(int x, int y, int R, int C, char[,] mineGrid)
    {
        int nMines = 0;

        // ----------------------------------------------------
        //int r, c;
        //r = x - 1;
        //c = y - 1;
        //if( r >= 0 && c >= 0 && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //r = x;
        //if( c >= 0 && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //r = x + 1;
        //if( r < R && c >= 0 && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //c = y;
        //if( r < R && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //c = y + 1;
        //if( r < R && c < C && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //r = x;
        //if( c < C && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //r = x - 1;
        //if( r >= 0 && c < C && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //c = y;
        //if( r >= 0 && mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}
        //r = x;
        //if( mineGrid[ r, c ] == '*' )
        //{
        //    ++nMines;
        //}

        // ----------------------------------------------------

        int minX = x <= 0 ? 0 : x - 1;
        int minY = y <= 0 ? 0 : y - 1;


        int maxX = x >= R - 1 ? R - 1 : x + 1; // x >= R - 1 ? R : x + sizeBlock - 1;
        int maxY = y >= C - 1 ? C - 1 : y + 1; // y >= C - 1 ? C : y + sizeBlock - 1;
        for (int i = minX; i <= maxX; ++i) //for( int i = minX; i < maxX; ++i )
        {
            for (int j = minY; j <= maxY; ++j) //for( int j = minY; j < maxY; ++j )
            {
                if (mineGrid[i, j] == '*')
                {
                    ++nMines;
                }
            }
        }

        return nMines;
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("MinesConvert.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("MinesConvert.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());
                for (int i = 1; i <= N; ++i)
                {
                    string[] inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    int R = int.Parse(inputs[0]);
                    int C = int.Parse(inputs[1]);

                    char[,] mineGrid = new char[R, C];
                    for (int r = 0; r < R; ++r)
                    {
                        string line = reader.ReadLine();
                        for (int c = 0; c < C; ++c)
                        {
                            mineGrid[r, c] = line[c];
                        }
                    }

                    int[,] mapGrid = null;
                    ConvertGrid(R, C, mineGrid, out mapGrid);

                    writer.WriteLine("{0}:", i);
                    writer.WriteLine("{0} {1}", R, C);
                    for (int r = 0; r < R; ++r)
                    {
                        for (int c = 0; c < C; ++c)
                        {
                            writer.Write("{0,2}", mapGrid[r, c]);
                        }
                        writer.WriteLine();
                    }
                }
            }
        }
    }
}