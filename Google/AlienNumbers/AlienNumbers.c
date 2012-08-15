#include <STDIO.H>
#include <ASSERT.H>

#include <STRING>
using namespace std;

typedef unsigned int  uint;
typedef long long     ll;

ll ToValue(string nm, string d1);
string FromValue(ll n, string d2);

string AlienNumber(string nm, string d1, string d2);

ll ToValue(string nm, string d1)
{
    ll n = 0;

    int base_d1 = d1.size();
    assert(2 <= base_d1 && base_d1 <= 94);

    // --------------------------------------
    //ll pos = 1;
    //for (int i = nm.size()-1; i >= 0; --i)
    //{
    //    //char digit = nm[ i ];
    //    //int value = d1.find(digit);
    //    //n += pos*value;
    //    n += pos*d1.find(nm[ i ]);
    //    assert(n <= 1000000000);
    //    pos *= base_d1;
    //}

    // --------------------------------------
    for (uint i = 0; i < nm.size(); ++i)
    {
        //n *= base_d1;
        //int value = d1.find(nm[ i ]);
        //n += value;
        n = n*base_d1 + d1.find(nm[ i ]);
        assert(n <= 1000000000);
    }
    // --------------------------------------

    return n;
}

string FromValue(ll n, string d2)
{
    string r;
    int base_d2 = d2.size();
    assert(2 <= base_d2 && base_d2 <= 94);
    do
    {
        //int value = n%base_d2;
        //char digit = d2[ value ];
        //r += digit;
        r += d2[ n%base_d2 ];
        n /= base_d2;
    }
    while (n != 0);

    reverse(r.begin(), r.end());

    return r;
}

string AlienNumber(string nm, string d1, string d2)
{
    string r;
    // ------------------------
    //int l_nm = nm.size();
    //int base_d1 = d1.size();
    //int base_d2 = d2.size();

    //assert(2 <= base_d1 && base_d1 <= 94);
    //assert(2 <= base_d2 && base_d2 <= 94);
    //
    //int val[256];
    //memset(val, -1, sizeof(val));
    //for (int i = 0; i < base_d1; ++i)
    //    val[ d1[ i ] ] = i;
    //
    //ll n = 0;
    //for (int i = 0; i < l_nm; ++i)
    //{
    //    n = n*base_d1 + val[ nm[ i ] ];
    //    assert(n <= 1000000000);
    //}
    //do 
    //{
    //    r += d2[ n%base_d2 ];
    //    n /= base_d2;
    //}
    //while (n != 0);
    //reverse(r.begin(), r.end());

    // ------------------------

    ll n = ToValue(nm, d1);
    r = FromValue(n, d2);
    // ------------------------

    return r;
}

void main()
{
    FILE* file = freopen("AlienNumbers.in", "r", stdin);
    if (file != NULL)
    {
        freopen("AlienNumbers.out", "w", stdout);

        int N;
        scanf(" %d", &N);
        assert(1 <= N && N <= 100);

        for (int i = 1; i <= N; ++i)
        {
            char nm[50], d1[100], d2[100];
            scanf(" %49s %99s %99s", nm, d1, d2);

            string r = AlienNumber(nm, d1, d2);
            printf("%d: %s\n", i, r.c_str());
        }
    }
}