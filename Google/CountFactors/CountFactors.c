#include <STDIO.H>
#include <STDLIB.H>


//int CountPrimeFactors(int num)
//{
//    if (num < 0)
//    {
//        num = -num;
//    }
//
//    int primeFactCount = 0;
//    for (int div = 2; num > 1;)
//    {
//        //if (num % div != 0)
//        //{
//        //    ++div;
//        //    continue;
//        //}
//        //++primeFactCount;
//        //num /= div;
//
//        if (num % div == 0)
//        {
//            ++primeFactCount;
//            num /= div;
//            continue;
//        }
//        ++div;
//    }
//    return primeFactCount;
//}


int CountPrimeFactors(int num)
{
    if (num < 0) num = -num;
    if (num > 1)
    {
        for (int prime = 2; prime <= num; ++prime)
        {
            if ((num % prime) == 0)
            {
                return 1 + CountPrimeFactors(num / prime);
            }
        }
    }
    return 0;
}

void main()
{
    int num;
    scanf(" %d", &num);

    int counts = 0;
    for (int n = 2; n <= num; ++n)
    {
        counts += CountPrimeFactors(n);
    }
    printf("%d\n", counts);

    system("PAUSE");
}