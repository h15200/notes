Binary search - pointer left, mid, right

always use iterative version as it takes up less space O(1)
while left is left of right represented by while (left <= right)
if target is on one side, move the pointer to the mid + 1 or mid - 1
else target IS mid

if out of while loop, target does not exist

- When something is a given value x 3 for example an array of only 1s, 2s, and 3s
  then it's usually solvable by 3 pointers
