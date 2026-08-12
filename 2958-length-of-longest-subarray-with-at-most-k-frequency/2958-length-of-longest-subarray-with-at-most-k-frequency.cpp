static const auto __ = []() { 
    std::ios_base::sync_with_stdio(false); 
    std::cin.tie(nullptr); 
    return 0; 
}();

class Solution {
public:
    int maxSubarrayLength(const std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freq;
        int left = 0, maxLength = 0;
        int n = nums.size();
        
        for (int right = 0; right < n; ++right) {
            freq[nums[right]]++;
            
            while (freq[nums[right]] > k) {
                freq[nums[left]]--;
                left++;
            }
            
            maxLength = std::max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};
