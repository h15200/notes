from types import List


class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        # 2 pointers for left and right, and have them cave in per iteration
        # don't overthink the grids. Use left and right as boundaries first, then do the offset math

        # use pointers to set outer boundaries. have them cave in per iteration
        start, end = 0, len(matrix[0]) - 1
        while start < end:
            # do inner rotation end - start times
            for i in range(end - start):
                # topLeft matrix[start][start]
                # topRight matrix[start][end]
                # bottomRight matrix[end][end]
                # bottomLeft matrix[end][start]

                # now, try to figure out offset logic with {i}
                # topLeft matrix[start][start + i]
                # topRight matrix[start + i][end]
                # bottomRight matrix[end][end - i]
                # bottomLeft matrix[end - i][start]

                # rotate three times
                matrix[start][start + i], matrix[start + i][end] = matrix[start + i][end], matrix[start][start + i]
                matrix[start][start + i], matrix[end][end - i] = matrix[end][end - i], matrix[start][start + i]
                matrix[start][start + i], matrix[end - i][start] = matrix[end - i][start], matrix[start][start + i]
                # print('matrix', matrix)
            # shrink box
            start += 1
            end -= 1
