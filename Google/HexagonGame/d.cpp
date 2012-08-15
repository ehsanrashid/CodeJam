
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;

typedef long long int64;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<double> vd;

#define For(i,a,b) for (int i(a),_b(b); i <= _b; ++i)
#define Ford(i,a,b) for (int i(a),_b(b); i >= _b; --i)
#define Rep(i,n) for (int i(0),_n(n); i < _n; ++i)
#define Repd(i,n) for (int i((n)-1); i >= 0; --i)
#define Fill(a,c) memset(&a, c, sizeof(a))
#define MP(x, y) make_pair((x), (y))
#define All(v) (v).begin(), (v).end()

template<typename T, typename S> T cast(S s) {
    stringstream ss;
    ss << s;
    T res;
    ss >> res;
    return res;
}

template<typename T> inline T sqr(T a) { return a*a; }
template<typename T> inline int Size(const T& c) { return (int)c.size(); }
template<typename T> inline void checkMin(T& a, T b) { if (b < a) a = b; }
template<typename T> inline void checkMax(T& a, T b) { if (b > a) a = b; }
template<typename T> inline bool isSet(T number, int bit) { return (number&(T(1)<<bit)) != 0; }

const int maxn=110;
const int INF = 1000000000;
int n;
int a[maxn][maxn];
int ar[maxn],ac[maxn];
int vx[maxn],vy[maxn],xy[maxn],yx[maxn];

bool dotry(int x)
{
    if(vx[x]) return false;
    vx[x]=1;
    int y;
    For(y,1,n) 
        if(a[x][y]+ar[x]+ac[y]==0) vy[y]=1;
    For(y,1,n)
        if(a[x][y]+ar[x]+ac[y]==0 && yx[y]==0)
        {
            xy[x]=y;
            yx[y]=x;
            return true;
        }
        For(y,1,n)
            if(a[x][y]+ar[x]+ac[y]==0 && dotry(yx[y]))
            {
                xy[x]=y;
                yx[y]=x;
                return true;
            }
            return false;
}

void hungary()
{
    int k,z,c;
    For(i,1,n)
    {
        k=INF;
        For(j,1,n) k=min(k,a[i][j]);
        ar[i]=-k;
    }
    For(j,1,n)
    {
        k=INF;
        For(i,1,n) k=min(k,a[i][j]+ar[i]);
        ac[j]=-k;
    }
    Fill(xy,0);
    Fill(yx,0);
    for(c=0; c<n; )
    {
        Fill(vx,0);
        Fill(vy,0);
        k=0;
        For(i,1,n) if(xy[i]==0)
            if(dotry(i)) ++k;
        c+=k;
        if(k==0)
        {
            z=INF;
            For(i,1,n) if(vx[i]==1)
                For(j,1,n) if(vy[j]==0)
                z=min(z,a[i][j]+ar[i]+ac[j]);
            For(i,1,n) 
            {
                if(vx[i]==1) ar[i]-=z;
                if(vy[i]==1) ac[i]+=z;
            }
        }
    }
}

char buf[1024*1024];
int s;
int pos[75], cost[75], r[75], c[75];
vector<vector<int> > num;

vector<vector<int> > bfs(int si, int sj) {
    vector<vector<int> > res = num;
    Rep(i, Size(res)) Rep(j, Size(res[i]))
        res[i][j] = -1;
    res[si][sj] = 0;
    queue<int> que;
    que.push(si); que.push(sj);
    while (!que.empty()) {
        int ci = que.front(); que.pop();
        int cj = que.front(); que.pop();
        int di[] = {0,0,-1,1,-1,1};
        int dj[] = {-1,1,0,0,0,0};
        if (ci-1 >= 0)
            if (Size(res[ci-1]) < Size(res[ci]))
                dj[4] = -1;
            else
                dj[4] = 1;
        if (ci+1 < Size(res))
            if (Size(res[ci+1]) < Size(res[ci]))
                dj[5] = -1;
            else
                dj[5] = 1;
        Rep(dir, 6) {
            int ni = ci+di[dir], nj = cj+dj[dir];
            if (ni >= 0 && ni < Size(res) && nj >= 0 && nj < Size(res[ni])) {
                if (res[ni][nj] == -1) {
                    res[ni][nj] = res[ci][cj]+1;
                    que.push(ni);
                    que.push(nj);
                }
            }
        }
    }
    return res;
}

int solve() {
    num.clear();
    int cnt = 0;
    For(i, (s+1)/2, s) {
        num.push_back(vector<int>());
        Rep(j, i)
            num.back().push_back(++cnt);
    }
    Ford(i, s-1, (s+1)/2) {
        num.push_back(vector<int>());
        Rep(j, i)
            num.back().push_back(++cnt);
    }
    Rep(i, Size(num)) Rep(j, Size(num[i])) Rep(k, s) {
        if (num[i][j] == pos[k]) {
            r[k] = i;
            c[k] = j;
        }
    }

    int res = INF;
    n = s;
    Rep(i, n) {
        vector<vector<int> > dist = bfs(r[i], c[i]);
        Rep(j, n)
            a[i+1][j+1] = cost[i]*dist[(n+1)/2-1][j];
    }
    hungary();
    int cur = 0;
    For(i, 1, n)
        cur += a[i][xy[i]];
    checkMin(res, cur);
    // ----------
    Rep(i, n) {
        vector<vector<int> > dist = bfs(r[i], c[i]);
        Rep(j, n)
            a[i+1][j+1] = cost[i]*dist[j][min((n+1)/2-1, n-1-j)];
    }

    hungary();
    cur = 0;
    For(i, 1, n)
        cur += a[i][xy[i]];
    checkMin(res, cur);
    // ----------
    Rep(i, n) {
        vector<vector<int> > dist = bfs(r[i], c[i]);
        Rep(j, n)
            a[i+1][j+1] = cost[i]*dist[j][min((n+1)/2-1, j)];
    }
    hungary();
    cur = 0;
    For(i, 1, n)
        cur += a[i][xy[i]];
    checkMin(res, cur);
    return res;
}

int main() 
{
    freopen("HexagonGame.in", "rt", stdin);
    freopen("HexagonGame.out", "wt", stdout);

    int n;
    scanf("%d", &n);
    For(test, 1, n) {
        scanf(" ");
        gets(buf);
        string st(buf);
        istringstream iss(st);
        s = 0;
        int x;
        while (iss >> x) 
            pos[s++] = x;
        Rep(i, s)
            scanf("%d", &cost[i]);
        printf("Case #%d: %d\n", test, solve());
    }

    exit(0);
}
