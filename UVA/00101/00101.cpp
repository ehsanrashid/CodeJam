#include <iostream>
#include <string>

using namespace std;

class stack
{
    int data[25],top;

public:

    void push(int n) { data[top++] = n; }

    int pop() { return (top > 0) ? data[--top] : -1; }

    void clear() { top = 0; }

    stack() { top = 0; }

    void show()
    {
        if (top == 0) return;
        int i;
        for (i=0; i < top; ++i)
        {
            cout<<" "<<data[i];
        }
    }
};

stack box[25], tmp;
int position[25];

void clear(int n)
{
    int i;
    while (true)
    {
        i=box[position[n]].pop();
        if (i==n)
        {
            box[position[n]].push(i);
            return;
        }
        else
        {
            box[i].push(i);
            position[i]=i;
        }
    }
}

void move(int a, int b)
{
    int i;
    tmp.clear();

    do
    {
        i=box[position[a]].pop();
        tmp.push(i);
    }
    while (i != a);

    i=tmp.pop();
    while(i!=-1)
    {
        box[position[b]].push(i);
        position[i]=position[b];
        i=tmp.pop();
    }
}

void show(int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        cout<<i<<":";
        box[i].show();
        cout<<endl;
    }
}

int main()
{
    int n,a,b,i;
    std::string str,str2;
    while(cin>>n)
    {
        for(i=0;i<n;i++)
        {
            box[i].clear();
            box[i].push(i);
            position[i]=i;
        }
        tmp.clear();

        while(cin >> str)
        {
            if(str=="quit") break;
            cin>>a>>str2>>b;

            if(position[a]==position[b]) continue;

            if(str=="move")  clear(a);
            if(str2=="onto") clear(b);

            move(a,b);
        }
        show(n);
    }
}
