from typing import List

# best to pivot on the LAST element

# 1. set the last element as pivot point, and first idx as p_idx
# 2. loop from index 0 to index len - 1. if num is <= to pivot, swap with pivot point and increment p_idx
# it's ok if i is the same as the p_idx and you swap with yourself. this logic needs to be included
# 3. after loop is done, swap the last element that wasn't touched with current p_idx
# 4. now p_idx is in the correct position. recursively repeat with all other segments (start, p_idx -1) and (p_idx + 1 , end)
def quick_sort(nums: List[int]) -> List[int]:
    def partition(start: int, end: int) -> None:
        if start < end:
            pivot_val = nums[end]
            pivot_idx = start
            for i in range(start, end):  # loop to end - 1
                if nums[i] <= pivot_val:
                    # swap
                    nums[i], nums[pivot_idx] = nums[pivot_idx], nums[i]
                    pivot_idx += 1
            # swap last element with current pivot_idx as the last element was not altered during loop
            nums[pivot_idx], nums[end] = nums[end], nums[pivot_idx]
            partition(start, pivot_idx - 1)
            partition(pivot_idx + 1, end)

    partition(0, len(nums) - 1)
    return nums


print(quick_sort([3, 1, 5, 6, 3, 123, -234234, 144, 4]))
