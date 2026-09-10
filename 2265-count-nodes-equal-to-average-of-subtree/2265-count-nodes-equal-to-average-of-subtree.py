class Solution:
    def averageOfSubtree(self, root: TreeNode) -> int:
        self.result = 0

        def traverse(node):

            if not node:
                return 0, 0

            left_sum, left_count = traverse(node.left)
            right_sum, right_count = traverse(node.right)
            
            curr_sum = node.val + left_sum + right_sum
            curr_count = 1 + left_count + right_count

            if curr_sum // curr_count == node.val:
                self.result += 1

            return curr_sum, curr_count

        traverse(root)

        return self.result