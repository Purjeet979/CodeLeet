class Solution {
public:
    int minimumPushes(string word) {
        int n = word.length();
        int totalPresses = 0;
        for (int i = 0; i < n; ++i) {
            totalPresses += (i / 8) + 1;
        }
        return totalPresses;
    }
};
