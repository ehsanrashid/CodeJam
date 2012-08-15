// 00108 - Maximum Sum
#include <CSTDIO>
#include <ALGORITHM>

using namespace std;

void ReadData(int **(&arr), int N)
{
    arr = new (nothrow) int*[N];
    if (arr == NULL)
    {
        perror( "Error: memory could not be allocated");
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            arr[i] = new (nothrow) int[N];
            if (arr == NULL)
            {
                perror( "Error: memory could not be allocated");
            }
            else
            {
                for (int j = 0; j < N; ++j)
                    scanf(" %d", &arr[i][j]);
            } 
        }
    }
}

void DelData(int **(&arr), int N)
{
    if (arr != NULL)
    {
        for (int i = 0; i < N; ++i)
        {
            if (arr[i] != NULL)
            { 
                delete[] arr[i]; 
                arr[i] = NULL; 
            }
        }
        delete[] arr;
        arr = NULL;
    }
}

int MaxBlockSum(int **arr, int N)
{
    int maxBlkSum = INT_MIN;
    
    // -----------------------------------

    int x1, y1;
    int x2, y2;
    
    for ( int i1 = 0; i1 < N; ++i1)
    {
        int* colSum = new int[N];
        memset(colSum, 0, sizeof(int)*N);

        for (int i2 = i1; i2 < N; ++i2)
        {
            int maxSum = INT_MIN;

            int sum = 0;
            
            int j1 = 0;
            int j2 = 0;
            
            for (int k2 = 0, k1 = 0; k2 < N; ++k2)
            {
                colSum[k2] += arr[i2][k2];
                
                sum += colSum[k2];
                
                if (sum > maxSum)
                {
                    maxSum = sum;
                    j1 = k1;
                    j2 = k2;
                }
                if (sum < 0)
                {
                    sum = 0;
                    k1 = k2 + 1;
                }
            }

            if (maxSum > maxBlkSum)
            {
                maxBlkSum = maxSum;
                
                x1 = j1;
                y1 = i1;
                x2 = j2;
                y2 = i2;
            }
        }
    }
    
    for (int i = x1; i <= x2; ++i)
    {
        for (int j = y1; j <= y2; ++j)
            printf(" %2d", arr[i][j]);
        printf("\n");
    }

    // -----------------------------------
    //
    //for (int i = 1; i < N; ++i)
    //{
    //    for (int j = 0; j < N; ++j)
    //        arr[i][j] += arr[i - 1][j];
    //}

    //for (int i1 = 1; i1 < N; ++i1)
    //{
    //    for (int i2 = i1; i2 < N; ++i2)
    //    {
    //        int sum = 0;
    //        for (int j = 0; j < N; ++j)
    //        {
    //            int colSum = arr[i2][j] - arr[i2 - i1][j];
    //            
    //            sum = ((sum >= 0) ? sum : 0) + colSum;
    //            maxBlkSum = (sum > maxBlkSum) ? sum : maxBlkSum;

    //            //sum = max(0, sum) + colSum;
    //            //maxBlkSum = max(sum, maxBlkSum);
    //        }
    //    }
    //}

    return maxBlkSum;
}

void main()
{
    FILE* file = freopen("00108.in", "r", stdin);
    if (file)
    {
        freopen("00108.out", "w", stdout);

        int N;
        scanf(" %d", &N);

        int** arr;
        ReadData(arr, N);

        printf(" %2d\n", MaxBlockSum(arr, N));

        DelData(arr, N);
    }
}
