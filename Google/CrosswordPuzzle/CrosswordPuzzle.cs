using System;
using System.IO;
using System.Text;
using System.Diagnostics;

class CrossWordPuzzle
{
    char[ , ] _board;

    public CrossWordPuzzle(char[ , ] board)
    {
        _board = board;
    }

    public int CountWords(int size)
    {
        return CountWordsExactly(size);
    }

    public int CountWordsExactly(int size)
    {
        int height = _board.GetLength(0);
        int width = _board.GetLength(1);

        int wordCountHorizontal = 0;
        for (int line = 0; line < height; ++line)
        {
            int countHSize = 0;
            for (int col = 0; col < width; ++col)
            {
                if (_board[ line, col ] == 'X')
                {
                    if (countHSize == size)
                    {
                        ++wordCountHorizontal;
                    }
                    countHSize = 0;
                    continue;
                }
                ++countHSize;
            }
            if (countHSize == size)
            {
                ++wordCountHorizontal;
            }
        }

        int wordCountVertical = 0;
        //for (int col = 0; col < width; ++col)
        //{
        //    int countVSize = 0;
        //    for (int line = 0; line < height; ++line)
        //    {
        //        if (_board[ line, col ] == 'X')
        //        {
        //            if (countVSize == size)
        //            {
        //                ++wordCountVertical;
        //            }
        //            countVSize = 0;
        //            continue;
        //        }
        //        ++countVSize;
        //    }
        //    if (countVSize == size)
        //    {
        //        ++wordCountVertical;
        //    }
        //}


        return wordCountHorizontal + wordCountVertical;
    }

    public int CountWordsAtleast(int size)
    {
        int height = _board.GetLength(0);
        int width = _board.GetLength(1);

        int wordCountHorizontal = 0;
        for (int line = 0; line < height; ++line)
        {
            int countHSize = 0;
            for (int pos = 0; pos < width; ++pos)
            {
                if (_board[ line, pos ] == 'X')
                {
                    if (countHSize >= size)
                    {
                        wordCountHorizontal += (countHSize - size + 1);
                    }
                    countHSize = 0;
                    continue;
                }
                ++countHSize;
            }
            if (countHSize >= size)
            {
                wordCountHorizontal += (countHSize - size + 1);
            }
        }

        int wordCountVertical = 0;
        for (int col = 0; col < width; ++col)
        {
            int countVSize = 0;
            for (int line = 0; line < height; ++line)
            {
                if (_board[ line, col ] == 'X')
                {
                    if (countVSize >= size)
                    {
                        wordCountVertical += (countVSize - size + 1);
                    }
                    countVSize = 0;
                    continue;
                }
                ++countVSize;
            }
            if (countVSize >= size)
            {
                wordCountVertical += (countVSize - size + 1);
            }
        }

        return wordCountHorizontal + wordCountVertical;
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("CrosswordPuzzle.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("CrosswordPuzzle.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());

                for (int i = 1; i <= N; ++i)
                {
                    string splitLine;
                    do
                    {
                        splitLine = reader.ReadLine().Trim();
                    }
                    while (String.IsNullOrEmpty(splitLine));

                    string[] inputs = splitLine.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    Assert.Check(inputs.Length == 1, "inputs.Length == 1", "Limits");

                    int size = int.Parse(inputs[ 0 ]);
                    Assert.Check(2 <= size && size <= 50, "2 <= size && size <= 50", "Limits");

                    StringBuilder strBuild = new StringBuilder();

                    do
                    {
                        string line = reader.ReadLine();
                        if (String.IsNullOrEmpty(line) || line.Trim() == String.Empty)
                        {
                            break;
                        }
                        strBuild.AppendLine(line);
                    }
                    while (true);

                    inputs = strBuild.ToString().Split(new char[] { '\r', '\n' }, StringSplitOptions.RemoveEmptyEntries);

                    int height = inputs.Length;
                    int width = inputs[ 0 ].Length;

                    Assert.Check(3 <= height && height <= 50, "3 <= height && height <= 50", "Limits");
                    Assert.Check(3 <= width && width <= 50, "3 <= width && width <= 50", "Limits");

                    char[ , ] board = new char[ height, width ];
                    for (int i = 0; i < height; ++i)
                    {
                        for (int j = 0; j < width; ++j)
                        {
                            board[ i, j ] = inputs[ i ][ j ];
                        }
                    }

                    writer.WriteLine(i + ": " + new CrossWordPuzzle(board).CountWords(size));
                }
            }
        }
    }
}