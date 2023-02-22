# when moving a value, memorize this pattern

from typing import List


def moveZeroes(self, nums: List[int]) -> None:
    """
    Do not return anything, modify nums in-place instead.
    """
    # two pointers. right finds non zeros, left stays at zero after found
    zero_idx = 0
    for i in range(len(nums)):
        if nums[i] != 0:
            nums[i], nums[zero_idx] = nums[zero_idx], nums[i]
            zero_idx += 1


# 3, 6, 0, 2, 5, 6, 0
# R  swap with self, does nothing
# L

#    R swap self
#    L
#       R
#       L   now L stays

#          R
#       L     SWAP

# 3, 6, 2, 0, 5, 6, 0
#          L  R   SWAP etc..
