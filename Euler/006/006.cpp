#include <STDIO.H>


int SquareOfSum(int k)
{
    return (k*(k+1)/2) ^ 2;
}


int SumOfSquare(int k)
{
    return k*(k+1)*(2*k+1)/6;
}

void main()
{
    int k = 100;

    int squareDiff;

    /*
    int sumOfNum = 0;
    int sumOfSquare = 0;
    for( int n = 0; n <= k; ++n)
    {
        sumOfNum += n;
        sumOfSquare += n ^ 2;
    }

    int squareOfSum = sumOfNum ^ 2;
    squareDiff = squareOfSum - sumOfSquare;
    */
    
    squareDiff = (k * (k**2 - 1) * (3*k + 2)/12);

    printf("%d", squareDiff);
}
