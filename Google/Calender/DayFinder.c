#include <STDIO.H>
#include <CONIO.H>

const int line = 28;

const int ndays = 7;
const int nmonth = 12;

const char *Day[ndays] = 
{ 
	"Satur",
	"Sun",
	"Mon", 
	"Tues",
	"Wednes",
	"Thrus",
	"Fri",
};

const char *Month[nmonth] = 
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

int FindDay(int dd, int mm, int yy, const int A[][line], const int B[][line])
{
    for (int i = 0; i < 6; ++i)
	{
        for (int j = 0; j < line; ++j)
		{
            if (A[i][j] == yy)
			{
                return (dd + B[mm-1][j]) % 7;
			}
		}
	}
    return -1;
}

void main()
{
    int A[6][line] , B[nmonth][line] , C[37];

    // A
    for (int i = 0; i < 6; ++i)
	{
        for (int j = 0; j < line; ++j)
		{
            A[i][j] = 1898 + i*line + j;
		}
	}

    // B
    int num = 5;
    for (int m = 0; m < nmonth; ++m)
    {
        for (int k = 0, j = 0; j < line; ++j, ++k)
        {
            if (j != 0)
			{
                if (m <= 1)
                {
                    if (j%4 == 0)
					{
						++k;
					}
                }
                else
				{
					if ((j+1)%4 == 0)
					{
						++k;
					}
				}
			}
            B[m][j] = (k + num)%7;
        }

        if (m <= 6)
        {
            if (m != 1)
			{
				if (m%2 != 0)
				{
					num = (num+2)%7;
				}
                else
				{
					num = (num+3)%7;
				}
			}
        }
        else
		{
			if (m%2 != 0)
			{
				num = (num+3)%7;
			}
            else
			{
				num = (num+2)%7;
			}
		}
    }

    // C
    for (int i = 0; i < 37; ++i)
	{
		C[i] = i;
	}

    printf("\n Date Conversion Routine (1898 - 2065)\n");
    printf(" Stop - (00 00 00)\n");
    int dd , mm , yy;
    do
    {
        printf("\n Date Month Year : ");
        scanf("%d %d %d", &dd, &mm, &yy);

        int day = FindDay(dd, mm, yy, A, B);
        if (day != -1)
		{
            printf("\n %sday, %d, %d(%s) %d\n", Day[day], dd, C[mm-1], Month[mm-1], yy);
		}
        else
		{
            printf(" Can't find...");
		}
    }
    while (dd > 0 && mm > 0 && yy > 0);
}