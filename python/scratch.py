from typing import List
import math


class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        # brute force keep trying a number until it works
        # min is 1 max is max(piles)

        l, r = 1, max(piles)
        res = max(piles)

        while l <= r:
            mid = (l + r) // 2
            hours = 0
            for p in piles:
                hours += math.ceil(p / mid)
            if hours <= h:
                res = min(res, mid)
                r = mid - 1
            else:
                l = mid + 1
        return res
