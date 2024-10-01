#include <bits/stdc++.h>

using namespace std;

// Calculate the number of ways two knights can be placed on a K X K chessboard
// such that they do not attack each other
long calculateWays(int k) {
    // Total number of ways two knights can be placed on the chessboard
    long totalWays = ((long) k * k * (k * k - 1)) / 2;

    // Number of ways two knights can attack each other
    long attackingWays = 4 * (k - 1) * (k - 2);

    // Number of ways two knights can be placed without attacking each other
    return totalWays - attackingWays;
}

int main() {
    
    size_t n;
    cin >> n;

    // Iterate for all the K sized chessboard
    for (size_t k = 1; k <= n; ++k)
        cout << calculateWays(k) << ' ';

    return 0;
}