#include <STDIO.H>
#include <ASSERT.H>
#include <STRING>
using namespace std;

typedef unsigned __int32 uint;

uint Square(int x)
{
    return x*x;
}

struct Point
{
    int x, y;

    void Input()
    {
        scanf(" %d %d", &x, &y);
    }
    void Output()
    {
        printf(" %d %d", x, y);
    }
};

bool IsEqual(Point P1, Point P2)
{
    return P1.x == P2.x && P1.y == P2.y;
}

bool IsCollinear(Point P1, Point P2, Point P3)
{
    //return (P1.x*P2.y + P2.x*P3.y + P3.x*P1.y) == (P1.x*P3.y + P2.x*P1.y + P3.x*P2.y);
    return (P2.x - P1.x)*(P3.y - P1.y) == (P3.x - P1.x)*(P2.y - P1.y);
}

uint DistanceSquare(Point P1, Point P2)
{
    return Square(P2.x - P1.x) + Square(P2.y - P1.y);
}

string TriangleTrilemma( Point P1, Point P2, Point P3 )
{
    if (IsEqual(P1, P2) ||
        IsEqual(P2, P3) ||
        IsEqual(P3, P1))
    {
        return "no";
    }

    if (IsCollinear(P1, P2, P3)) return "no";

    string triangle;

    uint d1 = DistanceSquare(P2, P3);
    uint d2 = DistanceSquare(P3, P1);
    uint d3 = DistanceSquare(P1, P2);

    //if (d1 == d2 && d2 == d3 && d3 == d1)
    //    triangle = "equilateral";
    //else
    if (d1 == d2 || d2 == d3 || d3 == d1)
        triangle = "isosceles";
    else
        triangle = "scalene";


    if (d3 < d1) swap(d3, d1);
    if (d3 < d2) swap(d3, d2);

    if (d3 == d1 + d2)
        triangle += " right";
    else if (d3 > d1 + d2)
        triangle += " obtuse";
    else
        triangle += " acute";

    return triangle;
}

void main()
{
    FILE* file = freopen("TriangleTrilemma.in", "r", stdin);
    if (file != NULL)
    {
        freopen("TriangleTrilemma.out", "w", stdout);

        int N;
        scanf(" %d", &N);
        assert(1 <= N && N <= 100);

        for (int i = 1; i <= N; ++i)
        {
            Point P1, P2, P3;
            P1.Input(); P2.Input(); P3.Input();

            //P1.Output(); P2.Output(); P3.Output();
            printf("%d: %s triangle\n", i, TriangleTrilemma(P1, P2, P3).c_str());
        }
    }
}