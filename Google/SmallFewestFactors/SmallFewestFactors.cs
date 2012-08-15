using System;
using System.IO;

static class SmallFewestFactors
{
    public static Int32 SmallFewestFactor(byte[] digits)
    {
        Int32[] fewestFactor = FewestFactors(PossibleNumbers(digits));
        Array.Sort(fewestFactor);
        return fewestFactor[ 0 ];
    }

    private static Int32[] FewestFactors(Int32[] numbers)
    {
        Int32 smallTotalFactor = Int32.MaxValue;
        Int32[] fewFactor = null;
        for (Int32 i = 0; i < numbers.Length; ++i)
        {
            Int32 totalFactor = TotalFactors(numbers[ i ]);
            if (totalFactor == smallTotalFactor)
            {
                fewFactor = AppendNum(fewFactor, numbers[ i ]);
            }
            if (totalFactor < smallTotalFactor)
            {
                smallTotalFactor = totalFactor;
                fewFactor = new Int32[] { numbers[ i ] };
            }
        }
        return fewFactor;
    }

    private static Int32[] AppendNum(Int32[] fewFactor, Int32 num)
    {
        Int32 length = fewFactor == null ? 0 : fewFactor.Length;
        Int32[] newfewFactor = new Int32[ length + 1 ];
        Int32 l;
        for (l = 0; l < length; l++)
        {
            newfewFactor[ l ] = fewFactor[ l ];
        }
        newfewFactor[ l ] = num;
        return newfewFactor;
    }

    private static Int32 TotalFactors(Int32 num)
    {
        Int32 factorCount = 0;
        for (Int32 div = 2; div < num; ++div)
        {
            if (num % div == 0)
            {
                ++factorCount;
            }
        }
        return factorCount;
    }

    private static Int32[] PossibleNumbers(byte[] digits)
    {
        Int32[] results = null;
        PermuteAll(digits, digits, ref results);
        return results;
    }

    private static void PermuteAll(byte[] digits, byte[] things, ref Int32[] results)
    {
        Int32 r = things.Length;
        if (r == 1)
        {
            return;
        }
        for (Int32 j = 0; j < r; ++j)
        {
            PermuteAll(digits, RemoveLast(things), ref results);
            if (r == 2) // if innermost,
            {
                Int32 integer = 0;
                Int32 size = digits.Length;
                for (Int32 i = 0; i < size; ++i)
                {
                    integer += digits[ i ] * (Int32) Math.Pow(10, size - 1 - i);
                }
                results = AppendNum(results, integer);
            }
            Rotate(digits, things.Length);
        }
    }

    private static byte[] RemoveLast(byte[] things)
    {
        Int32 length = things.Length;
        if (length == 0)
        {
            throw new IndexOutOfRangeException("Array Empty");
        }
        byte[] remove = new byte[ length - 1 ];
        for (Int32 i = 0; i < length - 1; ++i)
        {
            remove[ i ] = things[ i ];
        }
        return remove;
    }

    private static void Rotate(byte[] digits, Int32 r)
    {
        Int32 n = digits.Length;

        byte obj = digits[ n - r ];
        for (Int32 i = n - r; i < n; ++i)
        {
            digits[ i ] = i < (n - 1) ? digits[ i + 1 ] : obj;
        }

        //byte obj = digits[ n - 1 ];
        //for (Int32 i = n - 1; i >= n - r; --i)
        //{
        //    digits[ i ] = i > n - r ? digits[ i - 1 ] : obj;
        //}
    }


    private static bool IsNonZeroDigits(byte[] digits)
    {
        bool bNonZeroDigit = false;
        foreach (byte b in digits)
        {
            if (0 > b || b > 9)
            {
                bNonZeroDigit = false;
            }
            if (b != 0)
            {
                bNonZeroDigit = true;
            }
        }
        return bNonZeroDigit;
    }

    public static void Main()
    {
        using (StreamReader reader = new StreamReader(new FileStream("FewFactors.in", FileMode.Open)))
        {
            using (StreamWriter writer = new StreamWriter(new FileStream("FewFactors.out", FileMode.Create)))
            {
                Int32 N = Int32.Parse(reader.ReadLine());
                for (Int32 i = 1; i <= N; ++i)
                {
                    string[] inputs = reader.ReadLine().Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    Int32 length = inputs.Length;

                    if (1 > length || length > 5)
                    {
                        Environment.Exit(length);
                    }

                    byte[] digits = new byte[ length ];
                    for (Int32 i = 0; i < length; i++)
                    {
                        digits[ i ] = byte.Parse(inputs[ i ]);
                    }
                    if (!IsNonZeroDigits(digits))
                    {
                        return;
                    }

                    writer.WriteLine(i + ": " + SmallFewestFactor(digits));
                }
            }
        }
    }
}