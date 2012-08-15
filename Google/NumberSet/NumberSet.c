#include <STDIO.H>
#include <ALGORITHM>
//using namespace std;

typedef	unsigned __int32  uint;
typedef          __int64  ll;
typedef	unsigned __int64  ull;

ll *numSets;
ll *rank;

ll GCD(ll num1, ll num2)
{
    if (num1 < 0) num1 = -num1;
    if (num2 < 0) num2 = -num2;

    if (num2 == 0) return num1;
    if (num1 == num2) return num1;

    //---------------------------------

    //return num1 % num2 == 0 ? num2 : GCD(num2, num1 % num2);
    //---------------------------------

    while (num1 > 0 && num2 > 0)
    {
        if (num1 > num2)
        {
            num1 %= num2;
        }
        else
        {
            num2 %= num1;
        }
    }
    return num1 + num2;
    //---------------------------------
}

bool IsPrime(ll num)
{
    if (num < 0) num = -num;
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    for (int div = 3; div * div <= num; div += 2)
    {
        if (num % div == 0)
        {
            return false;
        }
    }
    return true;
}

ll MaxPrimeFactor(ll num)
{
    if (num < 0) num = -num;
    if (num > 3)
    {
        //for (ll div = 2; div * div <= num && num >= 1; ++div)
        //{
        //    if (num % div == 0)
        //    {
        //        while (num % div == 0)
        //        {
        //            num /= div;
        //        }
        //        if (num == 1)
        //        {
        //            return div;
        //        }
        //    }
        //}

        ll maxPrime = 0;
        for (ll div = 2; div * div <= num && num >= 1; ++div)
        {
            if (num % div == 0)
            {
                while (num % div == 0)
                {
                    num /= div;
                }
                maxPrime = std::max(div, maxPrime);
            }
        }
        //maxPrime = std::max(n, maxPrime);
        return maxPrime;
    }
    return num;
}

bool ShareMaxPrime(ll num1, ll num2, ll P)
{
    ll maxPrime = GCD(num1, num2);
    for (int div = 2; div < P && maxPrime >= P; ++div)
    {
        while (maxPrime % div == 0)
        {
            maxPrime /= div;
        }
    }
    return maxPrime >= P;
}

ll Root(ll x)
{
    if (numSets[x] != x)
    {
        numSets[x] = Root(numSets[x]);
    }
    return numSets[x];
}

void Unite(ll a, ll b)
{
    //while (numSets[a] != -1)
    //{
    //    a = numSets[a];
    //}
    //while (numSets[b] != -1)
    //{
    //    b = numSets[b];
    //}
    //if (a != b)
    //{
    //    numSets[a] = b;
    //}

    //a = Root(a);
    //b = Root(b);
    //if (a != b)
    //{
    //    numSets[a] = b;
    //}

    //----------------------------
    a = Root(a);
    b = Root(b);
    if (rank[a] < rank[b])
    {
        numSets[a] = b;
    }
    else
    {
        numSets[b] = a;
        if (rank[a] == rank[b])
        {
            ++rank[a];
        }
    }
}

ll NumSets(ll A, ll B, ll P)
{
    ll sets = 0;

    // ------------------------------------------------------------------------
    //numSets = new ll[(ull)(B + 1)];
    //rank = new ll[(ull)(B + 1)];

    // ------------------------------------------------------------------------
    //for (ll i = A; i <= B; ++i)
    //{
    //    //numSets[i] = -1;
    //    numSets[i] = i;
    //    rank[i] = 0;
    //}
    //for (ll i = A; i <= B; ++i)
    //{
    //    for (ll j = i+1; j <= B; ++j)
    //    {
    //        if (MaxPrimeFactor(GCD(i, j)) >= P)
    //        {
    //            Unite(i, j);
    //        }
    //    }
    //}
    //for (ll i = A; i <= B; ++i)
    //{
    //    //if (numSets[i] == -1)
    //    if (numSets[i] == i)
    //    {
    //        ++sets;
    //    }
    //}

    // ------------------------------------------------------------------------
    //ll interval = B - A + 1;
    //for (ll i = A; i <= B; ++i)
    //{
    //    numSets[i] = i;
    //    rank[i] = 0;
    //}
    //sets = B - A + 1;
    //for (ll prime = P; prime <= B; ++prime)
    //{
    //    if (!IsPrime(prime)) continue;
    //    ll last = -1;
    //    for (ll i = A; i <= B; ++i)
    //    {
    //        if (i % prime == 0)
    //        {
    //            if (last == -1)
    //            {
    //                last = i;
    //            }
    //            else
    //            {
    //                --sets;
    //                Unite(last, i);
    //            }
    //        }
    //    }
    //}
    ////for (ll i = A; i <= B; ++i)
    ////{
    ////    if (numSets[i] == i)
    ////    {
    ////        ++sets;
    ////    }
    ////}

    // ------------------------------------------------------------------------

    //ull interval = B - A + 1;
    //numSets = new ll[(ull) interval];
    //rank = new ll[(ull) interval];

    //for (ll i = 0; i < interval; ++i)
    //{
    //    numSets[i] = i;
    //    rank[i] = 0;
    //}

    //sets = interval;

    //for (ll prime = P; prime <= B; ++prime)
    //{
    //    if (!IsPrime(prime))
    //    {
    //        continue;
    //    }

    //    ll x = A / prime * prime;
    //    if (x < A)
    //    {
    //        x += prime;
    //    }

    //    x -= A; // 0 indexing
    //    for (ll y = x; y < interval; y += prime)
    //    {
    //        if (Root(x) != Root(y))
    //        {
    //            --sets;
    //            Unite(x, y);
    //        }
    //    }
    //}

    // ------------------------------------------------------------------------
    
    //delete[] numSets;
    //delete[] rank;
	
    // ------------------------------------------------------------------------

    ull interval = B - A + 1;
    numSets = new ll[(ull) interval];

    for (ll i = 0; i < interval; ++i)
    {
        numSets[i] = A + i;
    }
    sets = interval;
    for (ll i = 0; i < interval; ++i)
    {
        ll num1 = A + i;
        for (ll j = i + P; j < interval; ++j)
        {
            ll num2 = A + j;
            if (numSets[i] != numSets[j])
            {
                //if (MaxPrimeFactor(GCD(num1, num2)) >= P)
                if (ShareMaxPrime(num1, num2, P))
                {
                    ll pi = numSets[i], pj = numSets[j];
                    for (ll k = 0; k < interval; ++k)
                    {
                        if (numSets[k] == pi)
                        {
                            numSets[k] = pj;
                        }
                    }

                    --sets;
                }
            }
        }
    }

    delete[] numSets; numSets = NULL;
    
    // ------------------------------------------------------------------------

    return sets;
}

void main()
{
    freopen("NumberSet.in", "r", stdin);
    freopen("NumberSet.out", "w", stdout);

    int N;
    scanf(" %d", &N);
    for (int i = 1; i <= N; ++i)
    {
        ll A, B, P;
        scanf(" %lld %lld %lld", &A, &B, &P);
		
        ll numSets = NumSets(A, B, P);
        printf("%d: %lld\n", i, numSets);
    }
}