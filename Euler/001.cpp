#include <stdio.h>

int SumAP(int a, int l, int n) 
{
    return n*(l + a)/2;
}

int SumMultiplesK(int beg, int end, int n)
{
    a = n*((int) ((beg-1)/n) + 1);
    l = n*((int) ((end-1)/n));
    k = (l - a)/n + 1;
    return SumAP(a, l, k);
}


int SumMultiplesK1K2(int beg, int end, int n1, int n2)
{
    // -----------------------------
    //int sum = 0;
    //for (int x = beg; x < end; ++x)
    //    if ((x%n1 == 0) || (x%n2 == 0))
    //        sum += x;
    //return sum;

    // -----------------------------

    return SumMultiplesK(beg, end, n1) + SumMultiplesK(beg, end, n2) - SumMultiplesK(beg, end, n1*n2);
    // -----------------------------
}

void main()
{
    int beg = 1;
    int end = 1000;
    int n1 = 3;
    int n2 = 5;

    int sum = SumMultiplesK1K2(beg, end, n1, n2);

    printf("%d", sum);
}
