static const auto __ = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

class Solution {
public:
    int stoneGameII(const vector<int>& piles) {
        int n = piles.size();
        vector<int> suffixSum = piles;
        for (int i = n - 2; i >= 0; --i) suffixSum[i] += suffixSum[i + 1];
        
        // dp[i][m] stores max stones current player can get from index i with limit m
        // M can reach up to n, so size (n+1)x(n+1) is sufficient
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for (int i = n - 1; i >= 0; --i) {
            for (int m = 1; m <= n; ++m) {
                if (i + 2 * m >= n) {
                    dp[i][m] = suffixSum[i];
                } else {
                    for (int x = 1; x <= 2 * m; ++x) {
                        dp[i][m] = max(dp[i][m], suffixSum[i] - dp[i + x][max(m, x)]);
                    }
                }
            }
        }
        return dp[0][1];
    }
};
