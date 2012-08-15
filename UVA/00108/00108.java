import java.util.Scanner;

public class MaxBlockSum
{
    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        while (in.hasNext()) 
        {
	    int N = in.nextInt();
            int[][] arr = new int[N + 1][N + 1];
            for (int i = 1; i <= N; i++)
                for (int j = 0; j < N; j++)
                    arr[i][j] = in.nextInt() + arr[i - 1][j];

            System.out.println(maxBlockSum(arr, N));
        }
    }

    static long maxBlockSum(int[][] colPrefix, int N)
    {
        int maxBlkSum = Integer.MIN_VALUE;

        for (int i1 = 1; i1 < N; ++i1)
        {
            for (int i2 = i1; i2 < N; ++i2)
            {
                int sum = 0;
                for (int j = 0; j < N; ++j)
                {
                    int colSum = colPrefix[i2][j] - colPrefix[i2 - i1][j];
                    sum = ((sum >= 0) ? sum : 0) + colSum;
                    maxBlkSum = (sum > maxBlkSum) ? sum : maxBlkSum;
                }
            }
        }
        return maxBlkSum;
    }
}