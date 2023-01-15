import collections
from typing import List


class Solution:
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        # O(n) * 81 * 3 (not good)
        # validate row, then col, then 1 horizontal

        # row
        # for row in board:
        #     cache = {}
        #     for num in row:
        #         if num in cache:
        #             return False
        #         elif num != ".":
        #             cache[num] = True

        # # col
        # for x in range(len(board)):
        #     cache = {}
        #     for y in range(len(board)):
        #         num = board[y][x]
        #         if num in cache:
        #             return False
        #         elif num != ".":
        #             cache[num] = True

        # # check sub grids
        # for grid in range(9):
        #     y_start = grid % 3 * 3 # 0 or 3 or 6
        #     x_start = grid // 3 * 3
        #     cache = {}
        #     for y in range(y_start, y_start + 3):
        #         for x in range(x_start, x_start + 3):
        #             num = board[y][x]
        #             if num in cache:
        #                 return False
        #             elif num != ".":
        #                 cache[num] = True

        # return True

        # O(n) only 1 pass using 27 hashes (9 for row, 9 for col, 9 for sub gris)at the same time
        row = collections.defaultdict(list)
        col = collections.defaultdict(list)
        grid = collections.defaultdict(list)

        # grid math (0,0 0,1, 0,2 1,1, 1,2, 2,1, 2,2) -> 0
        # x // 3 add by 1
        # y // 3 add by 3

        def is_duplicate(r: int, c: int) -> bool:
            # print('checking r, c', r, c)
            num = board[r][c]
            g = (r // 3) * 1 + (c // 3) * 3
            return num in row[r] or num in col[c] or num in grid[g]

        for r in range(9):
            for c in range(9):
                num = board[r][c]
                if num == ".":
                    continue
                if is_duplicate(r, c):
                    return False
                row[r].append(num)
                col[c].append(num)
                grid[(r // 3) * 1 + (c // 3) * 3].append(num)

        return True
