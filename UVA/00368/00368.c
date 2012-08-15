// 00386 - Perfect Cubes

#include <cstdio>

void main()
{
    for (int i = 6; i < 201; i++)
    {
        for (int j = 2; j < i-2; j++)
        {
            for (int k = j+1; k < i-1; k++)
            {
                for (int l = k+1; l < i; l++)
                {
                    if (j*j*j+k*k*k+l*l*l == i*i*i)
                    {
                        printf("Cube = %u, Triple = (%u,%u,%u)\n", i, j, k, l);
                    }
                }
            }
        }
    }
}