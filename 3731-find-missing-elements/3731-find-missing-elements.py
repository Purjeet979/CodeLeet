class Solution(object):
    def findMissingElements(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        s = set(nums)
        ans = []

        for x in range(min(nums), max(nums) + 1):
            if x not in s:
                ans.append(x)

        return ans