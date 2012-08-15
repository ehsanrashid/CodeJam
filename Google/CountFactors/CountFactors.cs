using System;

static class CountFactor
{
    public static int CountPrimeFactors(int num)
    {
        if (num < 0) num = -num;

        int primeCount = 0;
        for (int div = 2; num > 1; )
        {
            //if (num % div != 0)
            //{
            //    ++div;
            //    continue;
            //}
            //++primeCount;
            //num /= div;

            if (num % div == 0)
            {
                ++primeCount;
                num /= div;
                continue;
            }
            ++div;
        }
        return primeCount;
    }

    int primeCount = 0;
    public static void CountPrimeFactors(int num)
    {
        if (num < 0) num = -num;
        if (num == 1) return;

        for (int div = 2; div * div <= num; ++div)
        {
            if (num % div == 0)
            {
                break;
            }
        }
        ++primeCount;
        CountPrimeFactors(num / div);
    }

    public static void Main()
    {
        int num = int.Parse(Console.ReadLine());
        int counts = 0;
        for (int i = 2; i <= num; ++i)
        {
            counts += CountPrimeFactors(i);
        }
        Console.WriteLine(counts);
    }
}