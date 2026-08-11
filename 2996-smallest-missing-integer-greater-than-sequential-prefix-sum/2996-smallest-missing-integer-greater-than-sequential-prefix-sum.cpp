static const auto __ = []() { std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr); return 0; }();

class Solution {
public:
    int missingInteger(const std::vector<int>& nums) {
        int n = nums.size();
        int sum = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] == nums[i - 1] + 1) {
                sum += nums[i];
            } else {
                break;
            }
        }
        
        // Use a boolean array for O(1) lookup since constraints are small (nums[i] <= 50)
        // If constraints were larger, use std::unordered_set<int>
        bool present[2001] = {false};
        for (int x : nums) {
            if (x <= 2000) present[x] = true;
        }
        
        while (present[sum]) {
            sum++;
        }
        
        return sum;
    }
};
