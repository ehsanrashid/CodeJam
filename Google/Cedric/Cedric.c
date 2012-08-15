#include <CSTDIO>
#include <CSTDLIB>
#include <CMATH>

#include <LIST>
using namespace std;

const int baseN = 10;

void NonRepeatDigitNums(short start, int numDigits, list<int> &nonrepeatDigitNum, bool used[], int value)
{
    for (short digit = start; digit < baseN; ++digit)
    {
        if (!used[ digit ])
        {
            if (numDigits == 1)
            {
                nonrepeatDigitNum.push_back(value + digit);
                continue;
            }

            used[ digit ] = true;
            value += (int) (digit * pow((float) baseN, (float) (numDigits - 1)));

            NonRepeatDigitNums(0, numDigits - 1, nonrepeatDigitNum, used, value);

            used[ digit ] = false;
            value -= (int) (digit * pow((float) baseN, (float) (numDigits - 1)));
        }
    }
}

void RepeatDigitNums(short start, int numDigits, list<int> &repeatDigitNum, bool used[], int value)
{
    for (short digit = start; digit < baseN; ++digit)
    {
        if (!used[ digit ])
        {
            if (numDigits == 1)
            {
                used[ digit ] = true;
                value += (int) (digit * pow((float) baseN, (float) (numDigits - 1)));

                RepeatDigitNums(0, numDigits - 1, repeatDigitNum, used, value);

                used[ digit ] = false;
                value -= (int) (digit * pow((float) baseN, (float) (numDigits - 1)));
            }
        }
        else
        {
            if (numDigits == 1)
            {
                repeatDigitNum.push_back(value + digit);
                continue;
            }

            bool *oused = new bool[ baseN ];

            memcpy(oused, used, baseN * sizeof(bool));
            memset(used, true, baseN * sizeof(bool));
            value += (int) (digit * pow((float) baseN, (float) (numDigits - 1)));

            RepeatDigitNums(0, numDigits - 1, repeatDigitNum, used, value);

            memcpy(used, oused, baseN * sizeof(bool));
            value -= (int) (digit * pow((float) baseN, (float) (numDigits - 1)));

            delete[] oused; oused = NULL;
        }
    }
}

void Numbers(short start, int numDigits, list<int> &numbers)
{
    bool *used = new bool[ baseN ];
    memset(used, false, baseN*sizeof(bool));

    NonRepeatDigitNums(start, numDigits, numbers, used, 0);
    //RepeatDigitNums(start, numDigits, numbers, used, 0);

    delete[] used; used = NULL;
}

void main()
{
    int countNum = 0;
    int maxJump = 0;

    int maxNumDigits = 2;

    for (int numDigits = 1; numDigits <= maxNumDigits; ++numDigits)
    {
        int lnum = 0;

        list<int> numbers;

        Numbers(1, numDigits, numbers);

        for (list<int>::const_iterator 
            iter = numbers.begin();
            iter != numbers.end();
            ++iter)
        {
            int num = *iter;
            maxJump = max(num - lnum, maxJump);
            lnum = num;
            ++countNum;

            printf(" %4d", num);
        }
    }

    printf("\n");
    printf("Count: %d\n", countNum);
    printf("Gap: %d\n", maxJump);

    printf("\n"); system("PAUSE");
}