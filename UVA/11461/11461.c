// 11461 - Square Numbers

#include <CSTDIO>

#define MAX 318
int squares[MAX];

void main()
{
    FILE* file = freopen("11461.in", "r", stdin);
    if (file)
    {
        freopen("11461.out", "w", stdout);

        for (int i = 1; i < MAX;i++) 
            squares[i] = i*i;

        int a, b;
        while (scanf("%d %d", &a, &b))
        {
            if (a == b && b == 0) break;
            int count = 0;
            
            int i = 0;
            while (squares[i++] < a);
            while (squares[i++] <= b)
                ++count;

            printf("%d\n", count);
        }
    }
}
