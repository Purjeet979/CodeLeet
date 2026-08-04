class Solution(object):
    def findDifferentBinaryString(self, nums):
        """
        :type nums: List[str]
        :rtype: str
        """
        ans = []

        for i in range(len(nums)):
            if nums[i][i] == '0':
                ans.append('1')
            else:
                ans.append('0')

        return "".join(ans)