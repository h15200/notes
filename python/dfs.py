from typing import List

# an algo you should just memorize the pattern for. most graph algos will be a variation of this
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        # just memorize a dfs and bfs graph func
        # always add to visited right BEFORE looking through 4 paths, then delete after
        ROW, COL = len(board), len(board[0])
        visited = {}

        def dfs(y: int, x: int, i: int) -> bool:
            # out of bounds, visited, wrong word
            if y < 0 or x < 0 or y >= ROW or x >= COL or (y, x) in visited or board[y][x] != word[i]:
                return False
            if i == len(word) - 1:
                return True
            # at this point the char is a match
            # print('is match', y, x, visited)
            visited[(y, x)] = True
            res = dfs(y - 1, x, i + 1) or dfs(y + 1, x, i + 1) or dfs(y, x + 1, i + 1) or dfs(y, x - 1, i + 1)
            del visited[(y, x)]
            return res

        for y in range(ROW):
            for x in range(COL):
                res = dfs(y, x, 0)
                if res:
                    return True
        return False


board_1 = ([["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]],)
word_1 = "ABCB"
print(Solution().exist(board_1, word_1))  # -> should return False

board_2 = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]]
word_2 = "SEE"
print(Solution().exist(board_2, word_2))  # -> should return True
