import math
import heapq
from typing import List
import collections


class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, k: int) -> int:
        # do shortest path k times, return min
        res = math.inf
        graph = collections.defaultdict(set)
        for orig, dest, edge in flights:
            graph[orig].add(edge, dest)
        heap = []
        heapq.heappush(heap, (0, src))
        visited = set()
        while heap:
            if k < 0:
                return res
            curr_dist, curr_node = heapq.heappop(heap)
            if curr_node in visited:
                continue
            if curr_node == dst:
                return min(res, curr_dist)
            visited.add(curr_node)
            for nei_d, nei_node in graph[curr_node]:
                heap.heappush((curr_dist + nei_d, nei_node))
            k -= 1
