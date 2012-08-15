#include <STDIO.H>
#include <ASSERT.H>
#include <STRING.H>
#include <VECTOR>
#include <QUEUE>
using namespace std;

vector<string> Tokenize(string str, string ch)
{
    vector<string> vecS;
    int beg = 0;
    while (beg < str.size()) 
    {
        int end = str.find_first_of(ch, beg);
        if (end == -1)
        {
            end = str.size();
        }
        if (end > beg)
        {
            vecS.push_back(str.substr(beg, end-beg));
        }
        beg = end+1;
    }
    return vecS;
}

vector<int> TokenizeInt(string str, string ch) 
{
    vector<int> vecI;

    //vector<string> vecS = Tokenize(str, ch);
    //for (int i = 0; i < vecS.size(); ++i)
    //    vecI.push_back(atoi(vecS[i].c_str()));
    // -------------------------------------------

    int beg = 0;
    while (beg < str.size()) 
    {
        int end = str.find_first_of(ch, beg);
        if (end == -1)
        {
            end = str.size();
        }
        if (end > beg)
        {
            vecI.push_back(atoi(str.substr(beg, end-beg).c_str()));
        }
        beg = end+1;
    }

    return vecI;
}

const int LimitS = 75;
int S;

#pragma region 1

//int BipartiteMatch(const vector<vector<int>> &m)
//{
//    int V = 2*(m.size() + 1);
//    vector<vector<int>> d(V, vector<int>(V, 1000000000));
//
//    for (int i = 0; i < S; ++i) d[V-2][i] = 0;
//    for (int i = 0; i < S; ++i) d[i+S][V-1] = 0;
//    
//    for (int i = 0; i < S; ++i)
//    {
//        for (int j = 0; j < S; ++j)
//        {
//            d[i][j+S] = m[i][j];
//        }
//    }
//
//    int ret = 0;
//    for (int i = 0; i < S; ++i)
//    {
//        vector<int> dist(V, 1000000000), prev(V, 1000000000);
//        
//        dist[V-2] = 0;
//        
//        bool change;
//        do
//        {
//            change = false;
//            for (int x = 0; x < S*2+2; ++x)
//            {
//                for (int y = 0; y < S*2+2; ++y)
//                {
//                    if (d[x][y] < 1000000000)
//                    {
//                        if (dist[x] + d[x][y] < dist[y]) 
//                        {
//                            dist[y] = dist[x] + d[x][y];
//                            prev[y] = x;
//                            change = true;
//                        }
//                    }
//                }
//            }
//        }
//        while (change);
//
//        ret += dist[V-1];
//        for (int x = V-1; x != V-2; x = prev[x]) 
//        {
//            d[x][prev[x]] = -d[prev[x]][x];
//            d[prev[x]][x] = 1000000000;
//        }
//    }
//    return ret;
//}
//
//int HexagonSolution(vector<int> pos, vector<int> cost)
//{
//    int b[LimitS][LimitS];
//    memset(b, 0, sizeof(b));
//
//    int cnt = 1;
//    for (int y = 1; y <= (S+1)/2; ++y)
//        for (int x = 1; x <= y + S/2; ++x)
//            b[y][x] = cnt++;
//    for (int y = 1; y < (S+1)/2; ++y)
//        for (int x = y+1; x <= S; ++x)
//            b[y + (S+1)/2][x] = cnt++;
//
//    vector<vector<int>> d1, d2, d3;
//    d1 = d2 = d3 = vector<vector<int>>(S, vector<int>(S));
//
//    for (int i = 0; i < S; ++i)
//    {
//        int y, x;
//        for (y = 1; y <= S; ++y)
//        {
//            for (x = 1; x <= S; ++x)
//            {
//                if (b[y][x] == pos[i])
//                    goto found;
//            }
//        }
//found:
//        bool seen[LimitS][LimitS];
//        memset(seen, 0, sizeof(seen));
//
//        vector<pair<int, int>> que;
//        que.push_back(make_pair(x, y));
//
//        int dist = 0;
//        while (!que.empty()) 
//        {
//            vector<pair<int, int>> newque;
//            while (!que.empty())
//            {
//                x = que.back().first;
//                y = que.back().second;
//                que.pop_back();
//
//                if (seen[y][x] || b[y][x] == 0) continue;
//                seen[y][x] = true;
//
//                if (y == (S+1)/2) d1[i][x-1] = dist * cost[i];
//                if (x == (S+1)/2) d2[i][y-1] = dist * cost[i];
//                if (x == y)       d3[i][x-1] = dist * cost[i];
//
//                newque.push_back(make_pair(x+1, y+0));
//                newque.push_back(make_pair(x-1, y+0));
//                newque.push_back(make_pair(x+0, y+1));
//                newque.push_back(make_pair(x+0, y-1));
//                newque.push_back(make_pair(x+1, y+1));
//                newque.push_back(make_pair(x-1, y-1));
//            }
//            que.swap(newque);
//            ++dist;
//        }
//    }
//
//    int md1 = BipartiteMatch(d1);
//    int md2 = BipartiteMatch(d2);
//    int md3 = BipartiteMatch(d3);
//
//    int md = min(min(md1, md2), md3);
//    return md;
//}

#pragma endregion

//#pragma region 2

const int maxn=110;
int ar[maxn],ac[maxn];
int vx[maxn],vy[maxn],xy[maxn],yx[maxn];

bool dotry(const vector<vector<int>> &scores, int x)
{
    if (vx[x] != 0) return false;
    vx[x] = 1;

    int y;
    for (y = 0; y < S; ++y)
    {
        if (scores[x][y] + ar[x] + ac[y] == 0)
        {
            vy[y] = 1;
        }
    }
    for (y = 0; y < S; ++y)
    {
        if (scores[x][y] + ar[x] + ac[y] == 0 && yx[y] == 0)
        {
            xy[x] = y;
            yx[y] = x;
            return true;
        }
    }
    for (y = 0; y < S; ++y)
    {
        if (scores[x][y] + ar[x] + ac[y] == 0 && dotry(scores, yx[y]))
        {
            xy[x] = y;
            yx[y] = x;
            return true;
        }
    }
    return false;
}

void Hungary(const vector<vector<int>> &scores)
{
    for (int i = 0; i < S; ++i)
    {
        int k = INT_MAX;
        for (int j = 0; j < S; ++j)
        {
            k = min(k, scores[i][j]);
        }
        ar[i] = -k;
    }
    for (int j = 0; j < S; ++j)
    {
        int k = INT_MAX;
        for (int i = 0; i < S; ++i)
        {
            k = min(k, scores[i][j] + ar[i]);
        }
        ac[j] = -k;
    }

    memset(&xy, 0, sizeof(xy));
    memset(&yx, 0, sizeof(yx));

    int c = 0;
    while (c < S)
    {
        memset(&vx, 0, sizeof(vx));
        memset(&vy, 0, sizeof(vy));

        int k=0;
        for (int i = 0; i < S; ++i)
        {
            if (xy[i] == 0)
            {
                if (dotry(scores, i))
                {
                    ++k;
                }
            }
        }

        c += k;

        if (k == 0)
        {
            int z = INT_MAX;
            for (int i = 0; i < S; ++i)
            {
                if (vx[i] == 1)
                {
                    for (int j = 0; j < S; ++j)
                    {
                        if (vy[j] == 0)
                        {
                            z = min(z, scores[i][j] + ar[i] + ac[j]);
                        }
                    }
                }
            }

            for (int i = 0; i < S; ++i)
            {
                if (vx[i] == 1)
                {
                    ar[i] -= z;
                }
                if (vy[i] == 1)
                {
                    ac[i] += z;
                }
            }
        }
    }
}

vector<vector<int>> BFS(pair<int, int> s)
{
    vector<vector<int>> dist(S);

    for (int i = 0; i < S; ++i)
    {
        int size = i < (S+1)/2 ? (S+1)/2 + i : S+S/2 - i; 
        dist[i].resize(size);
        for (int j = 0; j < size; ++j)
        {
            dist[i][j] = -1;
        }
    }

    int si = s.first;
    int sj = s.second;
    dist[si][sj] = 0;

    queue<pair<int, int>> que;
    que.push(make_pair(si, sj));

    while (!que.empty())
    {
        pair<int, int> cell = que.front(); que.pop();

        int ci = cell.first;
        int cj = cell.second;

        int di[] = { 0, 0, -1, 1, -1, 1 };
        int dj[] = { -1, 1, 0, 0, 0, 0 };

        if (ci-1 >= 0)
        {
            dj[4] = dist[ci-1].size() < dist[ci].size() ? -1 : 1;
        }

        if (ci+1 < S)
        {
            dj[5] = dist[ci+1].size() < dist[ci].size() ? -1 : 1;
        }

        for (int d = 0; d < 6; ++d)
        {
            int ni = ci + di[d];
            int nj = cj + dj[d];
            if (0 <= ni && ni < S               &&
                0 <= nj && nj < dist[ni].size())
            {
                if (dist[ni][nj] == -1)
                {
                    dist[ni][nj] = dist[ci][cj] + 1;
                    que.push(make_pair(ni, nj));
                }
            }
        }
    }
    return dist;
}

int HexagonSolution(const vector<int> &pos, const vector<int> &cost)
{
    int score = INT_MAX;

    vector<vector<int>> hexagon(S);

    int cnt = 0;
    int row = 0;
    for (int sizeHexRow = (S+1)/2; sizeHexRow <= S; ++row, ++sizeHexRow)
    {
        for (int r = 0; r < sizeHexRow; ++r)
        {
            hexagon[row].push_back(++cnt);
        }
    }
    for (int sizeHexRow = (S-1); sizeHexRow >= (S+1)/2; ++row, --sizeHexRow)
    {
        for (int r = 0; r < sizeHexRow; ++r)
        {
            hexagon[row].push_back(++cnt);
        }
    }

    vector<pair<int, int>> hexPos(S);
    for (int idx = 0; idx < S; ++idx)
    {
        for (int i = 0; i < S; ++i)
        {
            int sizeHexRow = hexagon[i].size();
            for (int j = 0; j < sizeHexRow; ++j)
            {
                if (pos[idx] == hexagon[i][j])
                {
                    hexPos[idx] = make_pair(i, j);
                }
            }
        }
    }

    vector<vector<int>> scores(S);
    {
        for (int i = 0; i < S; ++i)
        {
            scores[i].clear();
            scores[i].resize(S);
            vector<vector<int>> dist = BFS(hexPos[i]);
            for (int j = 0; j < S; ++j)
            {
                scores[i][j] = cost[i]*dist[(S+1)/2-1][j];
            }
        }
        Hungary(scores);

        int cscore = 0;
        for (int i = 0; i < S; ++i)
        {
            cscore += scores[i][xy[i]];
        }
        score = min(score, cscore);
    }
    {
        for (int i = 0; i < S; ++i)
        {
            scores[i].clear();
            scores[i].resize(S);
            vector<vector<int>> dist = BFS(hexPos[i]);
            for (int j = 0; j < S; ++j)
            {
                scores[i][j] = cost[i]*dist[j][min((S+1)/2-1, S-1-j)];
            }
        }
        Hungary(scores);

        int cscore = 0;
        for (int i = 0; i < S; ++i)
        {
            cscore += scores[i][xy[i]];
        }
        score = min(score, cscore);
    }
    {
        for (int i = 0; i < S; ++i)
        {
            scores[i].clear();
            scores[i].resize(S);
            vector<vector<int>> dist = BFS(hexPos[i]);
            for (int j = 0; j < S; ++j)
            {
                scores[i][j] = cost[i]*dist[j][min((S+1)/2-1, j)];
            }
        }
        Hungary(scores);

        int cscore = 0;
        for (int i = 0; i < S; ++i)
        {
            cscore += scores[i][xy[i]];
        }
        score = min(score, cscore);

    }

    return score;
}

//#pragma endregion

void main()
{
    freopen("HexagonGame.in", "r", stdin);
    freopen("HexagonGame.out", "w", stdout);

    int N;
    scanf(" %d", &N);
    assert(1 <= N && N <= 100);

    char line[3*LimitS];
    for (int c = 1; c <= N; ++c)
    {
        scanf(" %[^\n]", line);
        vector<int> pos = TokenizeInt(line, " ");
        S = pos.size();
        assert(S <= LimitS);

        scanf(" %[^\n]", line);
        vector<int> cost = TokenizeInt(line, " ");
        S = cost.size();
        assert(S <= LimitS);

        int md = HexagonSolution(pos, cost);
        printf("%d: %d\n", c, md);
    }
}



//
//#include <map>
//#include <set>
//#include <cmath>
//#include <queue>
//#include <vector>
//#include <string>
//#include <cstdio>
//#include <cstdlib>
//#include <cstring>
//#include <cassert>
//#include <numeric>
//#include <algorithm>
//#include <iostream>
//#include <sstream>
//#include <ctime>
//using namespace std;
//
//typedef long long int64;
//typedef vector<int> vi;
//typedef vector<string> vs;
//typedef vector<double> vd;
//
//#define for (i,a,b) for (int i(a),_b(b); i <= _b; ++i)
//#define Ford(i,a,b) for (int i(a),_b(b); i >= _b; --i)
//#define Rep(i,n) for (int i(0),_n(n); i < _n; ++i)
//#define Repd(i,n) for (int i((n)-1); i >= 0; --i)
//#define Fill(a,c) memset(&a, c, sizeof(a))
//#define MP(x, y) make_pair((x), (y))
//#define All(v) (v).begin(), (v).end()
//
//template<typename T, typename S> T cast(S s) {
//    stringstream ss;
//    ss << s;
//    T res;
//    ss >> res;
//    return res;
//}
//
//template<typename T> inline T sqr(T a) { return a*a; }
//template<typename T> inline int Size(const T& c) { return (int)c.size(); }
//template<typename T> inline void checkMin(T& a, T b) { if (b < a) a = b; }
//template<typename T> inline void checkMax(T& a, T b) { if (b > a) a = b; }
//template<typename T> inline bool isSet(T number, int bit) { return (number&(T(1)<<bit)) != 0; }
//
//const int maxn=110;
//const int INF = 1000000000;
//int n;
//int a[maxn][maxn];
//int ar[maxn],ac[maxn];
//int vx[maxn],vy[maxn],xy[maxn],yx[maxn];
//
//bool dotry(int x)
//{
//    if (vx[x]) return false;
//    vx[x]=1;
//    int y;
//    for (y,1,n) 
//        if (a[x][y]+ar[x]+ac[y]==0) vy[y]=1;
//    for (y,1,n)
//        if (a[x][y]+ar[x]+ac[y]==0 && yx[y]==0)
//        {
//            xy[x]=y;
//            yx[y]=x;
//            return true;
//        }
//        for (y,1,n)
//            if (a[x][y]+ar[x]+ac[y]==0 && dotry(yx[y]))
//            {
//                xy[x]=y;
//                yx[y]=x;
//                return true;
//            }
//            return false;
//}
//
//void hungary()
//{
//    int k,z,c;
//    for (i,1,n)
//    {
//        k=INF;
//        for (j,1,n) k=min(k,a[i][j]);
//        ar[i]=-k;
//    }
//    for (j,1,n)
//    {
//        k=INF;
//        for (i,1,n) k=min(k,a[i][j]+ar[i]);
//        ac[j]=-k;
//    }
//    Fill(xy,0);
//    Fill(yx,0);
//    for (c=0; c<n;)
//    {
//        Fill(vx,0);
//        Fill(vy,0);
//        k=0;
//        for (i,1,n) if (xy[i]==0)
//            if (dotry(i)) ++k;
//        c+=k;
//        if (k==0)
//        {
//            z=INF;
//            for (i,1,n) if (vx[i]==1)
//                for (j,1,n) if (vy[j]==0)
//                z=min(z,a[i][j]+ar[i]+ac[j]);
//            for (i,1,n) 
//            {
//                if (vx[i]==1) ar[i]-=z;
//                if (vy[i]==1) ac[i]+=z;
//            }
//        }
//    }
//}
//
//char buf[1024*1024];
//int s;
//int pos[75], cost[75], r[75], c[75];
//vector<vector<int> > num;
//
//vector<vector<int> > bfs(int si, int sj) {
//    vector<vector<int> > res = num;
//    Rep(i, Size(res)) Rep(j, Size(res[i]))
//        res[i][j] = -1;
//    res[si][sj] = 0;
//    queue<int> que;
//    que.push(si); que.push(sj);
//    while (!que.empty()) {
//        int ci = que.front(); que.pop();
//        int cj = que.front(); que.pop();
//        int di[] = {0,0,-1,1,-1,1};
//        int dj[] = {-1,1,0,0,0,0};
//        if (ci-1 >= 0)
//            if (Size(res[ci-1]) < Size(res[ci]))
//                dj[4] = -1;
//            else
//                dj[4] = 1;
//        if (ci+1 < Size(res))
//            if (Size(res[ci+1]) < Size(res[ci]))
//                dj[5] = -1;
//            else
//                dj[5] = 1;
//        Rep(dir, 6) {
//            int ni = ci+di[dir], nj = cj+dj[dir];
//            if (ni >= 0 && ni < Size(res) && nj >= 0 && nj < Size(res[ni])) {
//                if (res[ni][nj] == -1) {
//                    res[ni][nj] = res[ci][cj]+1;
//                    que.push(ni);
//                    que.push(nj);
//                }
//            }
//        }
//    }
//    return res;
//}
//
//int solve() {
//    num.clear();
//    int cnt = 0;
//    for (i, (s+1)/2, s) {
//        num.push_back(vector<int>());
//        Rep(j, i)
//            num.back().push_back(++cnt);
//    }
//    Ford(i, s-1, (s+1)/2) {
//        num.push_back(vector<int>());
//        Rep(j, i)
//            num.back().push_back(++cnt);
//    }
//    Rep(i, Size(num)) Rep(j, Size(num[i])) Rep(k, s) {
//        if (num[i][j] == pos[k]) {
//            r[k] = i;
//            c[k] = j;
//        }
//    }
//
//    int res = INF;
//    n = s;
//    Rep(i, n) {
//        vector<vector<int> > dist = bfs(r[i], c[i]);
//        Rep(j, n)
//            a[i+1][j+1] = cost[i]*dist[(n+1)/2-1][j];
//    }
//
//    //todo::
//    hungary();
//    int cur = 0;
//    for (i, 1, n)
//        cur += a[i][xy[i]];
//    checkMin(res, cur);
//    Rep(i, n) {
//        vector<vector<int> > dist = bfs(r[i], c[i]);
//        Rep(j, n)
//            a[i+1][j+1] = cost[i]*dist[j][min((n+1)/2-1, n-1-j)];
//    }
//    hungary();
//    cur = 0;
//    for (i, 1, n)
//        cur += a[i][xy[i]];
//    checkMin(res, cur);
//    Rep(i, n) {
//        vector<vector<int> > dist = bfs(r[i], c[i]);
//        Rep(j, n)
//            a[i+1][j+1] = cost[i]*dist[j][min((n+1)/2-1, j)];
//    }
//    hungary();
//    cur = 0;
//    for (i, 1, n)
//        cur += a[i][xy[i]];
//    checkMin(res, cur);
//    return res;
//}
//
//void main() 
//{
//    freopen("HexagonGame.in", "rt", stdin);
//    freopen("HexagonGame.out", "wt", stdout);
//
//    int n;
//    scanf("%d", &n);
//    for (test, 1, n) 
//    {
//        scanf(" ");
//        gets(buf);
//        string st(buf);
//        istringstream iss(st);
//        s = 0;
//        int x;
//        while (iss >> x) 
//            pos[s++] = x;
//        Rep(i, s)
//            scanf("%d", &cost[i]);
//        printf("Case #%d: %d\n", test, solve());
//    }
//}
