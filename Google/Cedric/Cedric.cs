using System;
using System.Collections.Generic;
using System.Diagnostics;

static class Cedric
{
    const int baseN = 10;
    // --------------------------------------------------------------
    #region Method 1

    public static IEnumerable<int> Numbers(Int16 start, int numDigits)
    {
        return NonRepeatDigitNums(start, numDigits, new bool[baseN], 0);
        //return RepeatDigitNums(start, numDigits, new bool[ baseN ], 0);
    }

    private static IEnumerable<int> NonRepeatDigitNums(Int16 start, int numDigits, bool[] used, int value)
    {
        for (Int16 digit = start; digit < baseN; ++digit)
        {
            if (!used[digit])
            {
                if (numDigits == 1)
                {
                    yield return value + digit;
                    continue;
                }

                used[digit] = true;
                value += (int)(digit * Math.Pow(baseN, (numDigits - 1)));

                foreach (int x in NonRepeatDigitNums(0, numDigits - 1, used, value))
                {
                    yield return x;
                }

                used[digit] = false;
                value -= (int)(digit * Math.Pow(baseN, (numDigits - 1)));
            }
        }
    }

    private static IEnumerable<int> RepeatDigitNums(Int16 start, int numDigits, bool[] used, int value)
    {
        // TODO::

        yield return 0;
    }

    #endregion
    // --------------------------------------------------------------
    #region Method 2

    public static void Numbers(Int16 start, int numDigits, ref List<int> numbers)
    {
        //NonRepeatDigitNums(start, numDigits, ref numbers, new bool[ baseN ], 0);
        RepeatDigitNums(start, numDigits, ref numbers, new bool[baseN], 0);
    }

    private static void NonRepeatDigitNums(Int16 start, int numDigits, ref List<int> nonrepeatDigitNum, bool[] used, int value)
    {
        //nonrepeatDigitNum.Capacity += baseN - 1;
        for (Int16 digit = start; digit < baseN; ++digit)
        {
            if (!used[digit])
            {
                if (numDigits == 1)
                {
                    nonrepeatDigitNum.Add(value + digit);
                    continue;
                }

                used[digit] = true;
                value += (int)(digit * Math.Pow(baseN, (numDigits - 1)));

                NonRepeatDigitNums(0, numDigits - 1, ref nonrepeatDigitNum, used, value);

                used[digit] = false;
                value -= (int)(digit * Math.Pow(baseN, (numDigits - 1)));
            }
        }
    }

    private static void RepeatDigitNums(Int16 start, int numDigits, ref List<int> repeatDigitNum, bool[] used, int value)
    {
        //repeatDigitNum.Capacity += baseN - 1;
        for (Int16 digit = start; digit < baseN; ++digit)
        {
            if (!used[digit])
            {
                if (numDigits != 1)
                {
                    used[digit] = true;
                    value += (int)(digit * Math.Pow(baseN, (numDigits - 1)));

                    RepeatDigitNums(0, numDigits - 1, ref repeatDigitNum, used, value);

                    value -= (int)(digit * Math.Pow(baseN, (numDigits - 1)));
                    used[digit] = false;
                }
            }
            else
            {
                if (numDigits == 1)
                {
                    repeatDigitNum.Add(value + digit);
                    continue;
                }

                bool[] oused = new bool[baseN];
                Array.Copy(used, oused, baseN);
                for (Int16 index = 0; index < baseN; ++index)
                {
                    used[index] = true;
                }

                value += (int)(digit * Math.Pow(baseN, (numDigits - 1)));

                RepeatDigitNums(0, numDigits - 1, ref repeatDigitNum, used, value);

                value -= (int)(digit * Math.Pow(baseN, (numDigits - 1)));
                Array.Copy(oused, used, baseN);
            }
        }

    }

    #endregion
    // --------------------------------------------------------------

    public static void Main()
    {
        int countNum = 0;
        int maxJump = 0;

        Stopwatch timer = new Stopwatch();
        timer.Start();

        int maxNumDigits = 3;

        for (int numDigits = 1; numDigits <= maxNumDigits; ++numDigits)
        {
            int lnum = 0;

            // -----------------------------------
            //foreach (int num in Numbers(1, numDigits))
            //{
            //    maxJump = Math.Max(num - lnum, maxJump);
            //    lnum = num;
            //    ++countNum;
            //    Console.Write("  {0}", num);
            //}
            // -----------------------------------
            List<int> numbers = new List<int>();
            Numbers(1, numDigits, ref numbers);
            foreach (int num in numbers)
            {
                maxJump = Math.Max(num - lnum, maxJump);
                lnum = num;
                ++countNum;
                Console.Write("  {0}", num);
            }
            // -----------------------------------
        }

        timer.Stop();

        Console.WriteLine();
        Console.WriteLine("Count: {0}", countNum);
        Console.WriteLine("Gap: {0}", maxJump);

        Console.WriteLine("Time: {0}", timer.Elapsed);
        Console.Read();
    }

}