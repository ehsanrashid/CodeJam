#include<iostream>
#include<stdlib.h>
using namespace std;

const short int dom[12]={31,28,31,30,31,30,31,31,30,31,30,31};

bool valid(int,int,int);

int main()
{
    cout << atoi("21/22/2009") << endl;
    short int d1,d2,ddif,m1,mdif,m2,y1,y2,ydif;

    cin>>d1>>m1>>y1;
    cin>>d2>>m2>>y2;
    bool neg=false;
    if ((y1<y2)||(y1==y2 && m1<m2)||(y1==y2 && m1==m2 && d1<d2))
    {
        swap(d1,d2);
        swap(m1,m2);
        swap(y1,y2);
        neg=true;
    }

    if (d1<d2)
    {
        if(m1==2 && y1%4==0)
            d1+=29;
        else
            d1+=dom[m1-1];
        m1--;
    }
    ddif=d1-d2;
    if (m1<m2)
    {
        m1+=12;
        y1--;
    }
    mdif=m1-m2;
    ydif=y1-y2;
    if (neg==true)
        cout<<ddif<<'/'<<mdif<<'/'<<ydif<<" (Negetive)"<<endl;
    else
        cout<<ddif<<'/'<<mdif<<'/'<<ydif<<endl;
    system("pause");
    return 0;
}      
