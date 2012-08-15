// This program asks the year after 1900 and prints the calendar for that year
#include <STDIO.H>
#include <CONIO.H>

const int Months = 12;

enum Days
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
};

void PrintCalendarYear(int year);
void IndentFirstLine(int weekday);
int MonthDays(int month, int year);
int FirstDayOfMonth(int month, int year);
void PrintMonthName(int month);
bool IsLeapYear(int year);


void PrintCalendarYear(int year)
{
    for (int month = 1; month <= Months ; ++month)
    {
        // print the name of the month followed by the year
        PrintMonthName(month);
        printf(" %d\n", year);
        // print the days of the week
        printf(" Su Mo Tu We Th Fr Sa\n");
        // determine number of day in a given month
        int monthDays = MonthDays(month, year);
        // determine which day of the week is the 1st of the month
        Days weekday = FirstDayOfMonth(month, year);
        // set the cursor under the day of the week for which the month starts
        IndentFirstLine((int) weekday);
        // print the entire month
        for (int day = 1; day <= monthDays; ++day)
        {
            printf(" %2d",day);
            if (weekday == Saturday) // go to a new line after saturday
            {
                printf("\n");
            }
            weekday = (weekday + 1) % 7; // keep track of the day of the week
        }

        if (weekday != Sunday)
        {
            printf("\n");
        }

        _getch();
        printf("\n");
    }
}

// This function indents the first line of each month
// place the cursor under the day of the weeks that marks the beginning of the month.
void IndentFirstLine(int weekday)
{
    for (int w = 0; w < weekday; ++w)
    {
        printf("   ");
    }
}

// Returns: an integer that represents the number of day in a given month
// Description: This function determines how many days should be printed for a given month.
int MonthDays(int month, int year)
{
    switch (month)
    {
    case 2:
        if (IsLeapYear(year))
        {
            return 29;
        }
        return 28;
    case 4: case 6: case 9: case 11:
        return 30;
    default:
        return 31;
    }
}

// Returns an integer between 0 to 6 to identify the day of the week.
// This function determines which day of the week is the first of the month
Days FirstDayOfMonth(int month, int year)
{
    Days weekday = Monday; // January 1st, 1900 is a Monday
    // find what day of the week is Jan 1 for the current year
    for (int y = 1900; y < year; ++y)
    {
        if (IsLeapYear(y))
        {
            weekday = (weekday + 366) % 7; // weekday should be betwee 0 and 6
        }
        else
        {
            weekday = (weekday + 365) % 7;
        }
    }
    // Find the day of the week for the first day of the month
    for (int m = 1; m < month; ++m)
    {
        weekday = ((weekday + MonthDays(m, year)) % 7);
    }
    return weekday;
}

// This function prints the name of given month
void PrintMonthName(int month)
{
    switch (month)
    {
    case 1: printf(" January"); break;
    case 2: printf(" February"); break;
    case 3: printf(" March"); break;
    case 4: printf(" April"); break;
    case 5: printf(" May"); break;
    case 6: printf(" June"); break;
    case 7: printf(" July"); break;
    case 8: printf(" August"); break;
    case 9: printf(" September"); break;
    case 10: printf(" October"); break;
    case 11: printf(" November"); break;
    case 12: printf(" December"); break;
    default: printf(" ");
    }
}

// This function detemines if the year is a leap year.
// A year is a leap year if it is multiple of 4 but not a multiple of 100.
// All years which are multiple of 400 are leap years
bool IsLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// number of nomal days = year * 365
// number of leap days = year / 4 - year / 100 + year / 400
// total days = normal days + leap days


void main()
{
    int year;
    do
    {
        printf("Calendar of year (>=1900) :");
        scanf(" %d", &year);
    }
    while (year < 1900);

    PrintCalendarYear(year);
}
