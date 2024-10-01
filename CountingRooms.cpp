#include <bits/stdc++.h>

using namespace std;

constexpr char FLOOR = '.';
constexpr char WALL  = '#';

class Building final {
public:
    Building(const vector<vector<char>>& map) noexcept : 
        n(map.size()), m(map[0].size()), map(map) {}
    
    
    size_t countRooms() noexcept {
        
        size_t rooms = 0;

        vector<vector<bool>> visited(n, vector<bool>(m));
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < m; ++j)
            {
                if (map[i][j] == FLOOR && !visited[i][j])
                {
                    DFS(i, j, visited);
                    ++rooms;
                }
            }
        }
        return rooms;
    }
    
private:

    bool isValid(int y, int x) {
        return !(y < 0 || x < 0 || y >= n || x >= m || map[y][x] == WALL);
    }

    void DFS(int y, int x, vector<vector<bool>>& visited) {
        visited[y][x] = true;
        for (size_t i = 0; i < 4; ++i)
        {
            int newX = x + dX[i];
            int newY = y + dY[i];
            if (isValid(newY, newX) && !visited[newY][newX])
                DFS(newY, newX, visited);
        }
    }

    const int dX[4]{0, 0, 1, -1};
    const int dY[4]{1, -1, 0, 0};
    
    size_t n, m;
    vector<vector<char>> map;
    
};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    vector<vector<char>> map(n, vector<char>(m));
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            cin >> map[i][j];

    Building building(map);
    cout << building.countRooms() << '\n';

    return 0;
}
