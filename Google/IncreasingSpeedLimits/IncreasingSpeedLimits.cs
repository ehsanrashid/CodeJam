using System;
using System.IO;
using System.Collections.Generic;

static class IncreasingSpeedLimit
{
    const long MOD = 1000000007;

    public static void GenerateSeq(int n, int m, long X, long Y, long Z, long[] A, out long[] Seq)
    {
        Seq = new long[n];
        for (int i = 0; i < n; ++i)
        {
            int j = i % m;
            Seq[i] = A[j];
            A[j] = (X * A[j] + Y * (i + 1)) % Z;
        }
    }

    public static int IncreasingSubSequences(int n, long[] Seq)
    {
        int nTotalIncSeq = 0;

        // ------------------------------------------------------------------------

        int[] nIncSubSeq = new int[n];
        for (int i = 0; i < n; ++i)
        {
            nIncSubSeq[i] = 1;
            for (int j = 0; j < i; ++j)
            {
                if (Seq[i] > Seq[j])
                {
                    nIncSubSeq[i] = (int)((long)(nIncSubSeq[i] + nIncSubSeq[j]) % MOD);
                }
            }
            nTotalIncSeq = (int)((long)(nTotalIncSeq + nIncSubSeq[i]) % MOD);
            //(nTotalIncSeq += nIncSubSeq[ i ]) %= MOD;
        }

        //for (int i = 0; i < n; ++i)
        //{
        //    nTotalIncSeq = (int)((long)(nTotalIncSeq + nIncSubSeq[i]) % MOD);
        //}

        // ------------------------------------------------------------------------

        //int* nIncSubSeq = new int[n + 1];
        //for (int i = n; i > 0; --i)
        //{
        //    Seq[i] = Seq[i - 1];
        //}
        //nIncSubSeq[0] = 1;
        //Seq[0] = -1;
        //for (int i = 1; i <= n; ++i)
        //{
        //    nIncSubSeq[i] = 0;
        //    for (int j = i - 1; j >= 0; --j)
        //    {
        //        if (Seq[i] > Seq[j])
        //        {
        //            nIncSubSeq[i] = (int)((long)(nTotalIncSeq + nIncSubSeq[i]) % MOD);
        //        }
        //    }
        //    //nTotalIncSeq = (int) ((long) (nTotalIncSeq + nIncSubSeq[ i ]) % MOD);
        //    (nTotalIncSeq += nIncSubSeq[i]) %= MOD;
        //}

        // ------------------------------------------------------------------------

        //long[] SeqClone = new long[n];
        //Array.Copy(Seq, SeqClone, n);
        //Array.Sort(SeqClone);
        //int[] nIncSubSeq = new int[n];
        //int nIncSubSeqCount = 0;
        //for (int i = 0; i < n; i++)
        //{
        //    if (i == 0 || SeqClone[i] > SeqClone[i - 1])
        //    {
        //        nIncSubSeq[nIncSubSeqCount++] = (int)SeqClone[i];
        //    }
        //}
        //data = new int[n];
        //for (int i = 0; i < n; i++)
        //{
        //    int r = 1;
        //    int index = Array.BinarySearch<int>(nIncSubSeq, 0, nIncSubSeqCount, (int)Seq[i]);
        //    if (index > 0)
        //    {
        //        r = (int)((long)(r + Sum(index - 1)) % MOD);
        //    }
        //    Add(index, r);
        //}
        //nTotalIncSeq = Sum(nIncSubSeqCount - 1);

        // ------------------------------------------------------------------------

        return nTotalIncSeq;
    }

    static int[] data;

    // Returns sum of elements in range [0, index];
    private static int Sum(int index)
    {
        int sum = 0;
        while (index >= 0)
        {
            sum = (int)((long)(sum + data[index]) % MOD);
            index = (index & (index + 1)) - 1;
        }
        return sum;
    }

    // Adds x to the i-th element
    private static void Add(int i, int x)
    {
        int n = data.Length;
        while (i < n)
        {
            data[i] = (int)((long)(data[i] + x) % MOD);
            i = i | (i + 1);
        }
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("SpeedLimit.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("SpeedLimit.out", FileMode.Create)))
            {
                int N = int.Parse(reader.ReadLine());

                for (int c = 1; c <= N; ++c)
                {
                    string[] inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    int n = int.Parse(inputs[0]);
                    int m = int.Parse(inputs[1]);
                    long X = long.Parse(inputs[2]);
                    long Y = long.Parse(inputs[3]);
                    long Z = long.Parse(inputs[4]);

                    long[] A = new long[m];
                    for (int i = 0; i < m; ++i)
                    {
                        A[i] = long.Parse(reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)[0]);
                    }

                    long[] Seq = null;
                    GenerateSeq(n, m, X, Y, Z, A, out Seq);

                    int speedLimit = IncreasingSubSequences(n, Seq);
                    writer.WriteLine(c + ": " + speedLimit);
                }
                //writer.Close();
            }
            //reader.Close();
        }
    }
}