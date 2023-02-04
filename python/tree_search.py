# 3 main ways to search a binary tree

# Definition for a binary tree node.
import typing


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxDepth(self, root: typing.Optional[TreeNode]) -> int:
        # method 1 recursive dfs
        # if not root:
        #     return 0

        # return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))

        # method 2 iterative bfs with queue
        # if not root:
        #     return 0

        # max_depth = 0
        # q = collections.deque([(root)])
        # while len(q):
        #     max_depth += 1
        #     new_q = collections.deque([])
        #     for tree in q:
        #         if tree.left:
        #             new_q.append(tree.left)
        #         if tree.right:
        #             new_q.append(tree.right)
        #     q = new_q

        # return max_depth

        # method 3 iterative dfs with stack
        if not root:
            return 0

        max_depth = 0
        stack = [(root, 1)]
        while len(stack):
            tree, depth = stack.pop()
            if tree:
                max_depth = max(max_depth, depth)
            if tree.left:
                stack.append((tree.left, depth + 1))
            if tree.right:
                stack.append((tree.right, depth + 1))
