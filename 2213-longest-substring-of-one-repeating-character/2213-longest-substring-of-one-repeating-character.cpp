static const auto __ = []() { std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); return 0; }();

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        set<pair<int, int>> intervals;
        multiset<int> lengths;

        int start = 0;
        for (int i = 1; i <= n; ++i) {
            if (i == n || s[i] != s[start]) {
                intervals.insert({start, i - 1});
                lengths.insert(i - start);
                start = i;
            }
        }

        vector<int> res;
        res.reserve(queryIndices.size());

        for (int i = 0; i < queryIndices.size(); ++i) {
            int idx = queryIndices[i];
            char new_c = queryCharacters[i];
            if (s[idx] == new_c) {
                res.push_back(*lengths.rbegin());
                continue;
            }

            auto it = intervals.upper_bound({idx, n});
            --it;
            int l = it->first, r = it->second;
            intervals.erase(it);
            lengths.erase(lengths.find(r - l + 1));

            if (l < idx) {
                intervals.insert({l, idx - 1});
                lengths.insert(idx - l);
            }
            if (idx < r) {
                intervals.insert({idx + 1, r});
                lengths.insert(r - idx);
            }
            intervals.insert({idx, idx});
            lengths.insert(1);
            s[idx] = new_c;

            auto curr = intervals.find({idx, idx});
            
            if (curr != intervals.begin()) {
                auto prev = std::prev(curr);
                if (s[prev->second] == s[idx]) {
                    int l1 = prev->first, r1 = prev->second;
                    int l2 = curr->first, r2 = curr->second;
                    intervals.erase(prev);
                    intervals.erase(curr);
                    lengths.erase(lengths.find(r1 - l1 + 1));
                    lengths.erase(lengths.find(r2 - l2 + 1));
                    curr = intervals.insert({l1, r2}).first;
                    lengths.insert(r2 - l1 + 1);
                }
            }
            
            auto next = std::next(curr);
            if (next != intervals.end() && s[next->first] == s[idx]) {
                int l1 = curr->first, r1 = curr->second;
                int l2 = next->first, r2 = next->second;
                intervals.erase(curr);
                intervals.erase(next);
                lengths.erase(lengths.find(r1 - l1 + 1));
                lengths.erase(lengths.find(r2 - l2 + 1));
                intervals.insert({l1, r2});
                lengths.insert(r2 - l1 + 1);
            }
            res.push_back(*lengths.rbegin());
        }
        return res;
    }
};
