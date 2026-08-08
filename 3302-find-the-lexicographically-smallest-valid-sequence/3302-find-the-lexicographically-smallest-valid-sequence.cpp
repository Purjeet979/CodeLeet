#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> validSequence(std::string word1, std::string word2) {
        int n = word1.size(), m = word2.size();
        std::vector<int> suffix(n + 1, 0);
        
        int j = m - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j]) {
                j--;
            }
            suffix[i] = m - 1 - j;
        }

        std::vector<int> res;
        bool changed = false;
        int curr_j = 0;
        
        for (int i = 0; i < n && curr_j < m; ++i) {
            if (word1[i] == word2[curr_j]) {
                res.push_back(i);
                curr_j++;
            } else if (!changed && (curr_j + 1 + suffix[i + 1] >= m)) {
                res.push_back(i);
                changed = true;
                curr_j++;
            }
        }

        return res.size() == m ? res : std::vector<int>();
    }
};
