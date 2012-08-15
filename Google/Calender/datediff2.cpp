#include<iostream>
#include<stdlib.h>
using namespace std;

const int dom[12]={31,28,31,30,31,30,31,31,30,31,30,31};

void datesplit(char*,int*,int*,int*);
int valid(char*);
void diff(char*,char*,int*,int*,int*);

int main()
{
    char* date1;
    char* date2;
    date1=new char;
    date2=new char;
    int ddif,mdif,ydif;
    do
    {
        cin>>(date1);
        //if (valid(date1)==0)
        //cout<<"Invalid date. Enter again"<<endl;
    }
    while (valid(date1)==0);
    //cout<<date1<<endl;
    do
    {
        cin>>(date2);
        //if (valid(date2)==0)
        //cout<<"Invalid date. Enter again"<<endl;
    }
    while (valid(date2)==0);
    diff(date1,date2,&ddif,&mdif,&ydif);
    cout<<ddif<<"/"<<mdif<<"/"<<ydif<<endl;
    system("pause");
    return 0;
}      

void datesplit(char* date,int* d,int* m,int* y)
{
    *d=atoi(date);
    while (date[0]>47 && date[0]<58)
        for (int i=0;i<strlen(date);i++) 
            date[i]=date[i+1];
    
    for (int i=0;i<strlen(date);i++) 
        date[i]=date[i+1];
    
    *m=atoi(date);

    while (date[0]>47 && date[0]<58)
        for (int i=0;i<strlen(date);i++)
            date[i]=date[i+1];
    
    for (int i=0;i<strlen(date);i++) 
        date[i]=date[i+1];
    
    *y=atoi(date);      
}

int valid(char* date)
{
    int val=1;
    int d,m,y; 
    datesplit(date,&d,&m,&y);
    if (d<1 || m<1 ||m>12 || y<0)
        val=0;
    if (y%4==0 && m==2 && d>29)
        val=0;
    else if (d>dom[m-1])
        val=0;
    return val;
}

void diff(char*date1,char*date2,int *ddif,int*mdif,int*ydif)
{
    int d1,d2,m1,m2,y1,y2;

    datesplit(date1,&d1,&m1,&y1);

    datesplit(date2,&d2,&m2,&y2);
    //cin>>d1>>m1>>y1;
    //cin>>d2>>m2>>y2;

    if ((y1<y2)
        || (y1==y2 && m1<m2)
        || (y1==y2 && m1==m2 && d1<d2))
    {
        swap(d1,d2);
        swap(m1,m2);
        swap(y1,y2);
    }

    if (d1<d2)
    {
        if (m1==2 && y1%4==0)
            d1+=29;
        else
            d1+=dom[m1-1];
        m1--;
    }

    *ddif=d1-d2;
    if (m1<m2)
    {
        m1+=12;
        y1--;
    }
    *mdif=m1-m2;
    *ydif=y1-y2;
}
