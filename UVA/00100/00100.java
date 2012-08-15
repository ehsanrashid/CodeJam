import java.util.*;
import java.math.*;
import java.io.*;

public class Main 
{
    // cache for already computed cycle lengths
    public static int[] cache = new int[1000000];

    // a function that returns the
    // next number in the sequence
    public static long next(long n) 
    {
        if (n % 2 == 0)
            return n / 2;
        else
            return 3 * n + 1;
    }

    public static int cycleLength(long n) 
    {
        // our base case
        // 1 has a cycle length of 1
        if (n == 1)
            return 1;

        // check if we've already cached the
        // cycle length of the current number
        if (n < 1000000 && cache[(int)n] != 0)
            return cache[(int)n];

        // the cycle length of the current number is 1 greater
        // than the cycle length of the next number
        int length = 1 + cycleLength(next(n));

        // we cache the result if the
        // current number is not too big
        if (n < 1000000)
            cache[(int)n] = length;

        return length;
    }

    public static int maxCycleLength(int lowerBound, int upperBound) 
    {
        int maxCycleLength = 0;
        // loop through all the numbers and find the max cycle
        for (int n = lowerBound; n <= upperBound; ++n) 
        {
            maxCycleLength = Math.max(cycleLength(n), maxCycleLength);
        }
	return maxCycleLength;
    }

    public static void main(String[] args) throws Exception 
    {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out, true);

        // while there is some input to read
        while (in.hasNextInt()) 
        {
            int i = in.nextInt(),
                j = in.nextInt();
            int lowerBound = Math.min(i, j),
                upperBound = Math.max(i, j);

            int maxCycleLength = maxCycleLength(lowerBound, upperBound);

            out.printf("%d\n", i, j, max);
        }
    }
}