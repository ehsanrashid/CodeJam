#include <STDIO.H>
#include <STRING.H>

#define MAX 1000000

void main()
{
    bool p[MAX];
    //memset(p, 1, sizeof(p));
    memset(p, true, sizeof(p));    
    
    int k = 1000;
    for (int i = 4; i < MAX; i += 2) 
    {
        p[i] = false;
    }

    int c = 1;
    for (int i = 3; i < 1001; i += 2)
    {
        if (p[i])
        {
            ++c;
            for(int j = i * i; j < MAX; j += i)
            { 
                p[j] = false;
            }
        }
    }

    while (c < 10001)
    { 
        c += p[++k];
    }

    printf("Answer: %d\n", k);
}
