// return an ordered array of arrays.

function threeNumberSum(array, targetSum) {
  // combination of sliding window and pointers O(n^2) T O(n) S
  // immeidately sort since O(n^3) is already worse than O(nlogn) + O(n^2)
  const output = [];
  array = array.sort((a, b) => a - b);
  // store i - 1, start for loop on i, go up to length - 1 (can't make triplet without 3 ele)

  for (let i = 1; i < array.length - 1; i++) {
    let firstNum = array[i - 1];
    let left = i;
    let right = array.length - 1;
    while (left < right) {
      const total = firstNum + array[left] + array[right];
      if (total === targetSum) {
        output.push([firstNum, array[left], array[right]]);
        left++;
      } else if (total < targetSum) left++;
      else right--;
    }
  }
  return output;
}

console.log(threeNumberSum([12, 3, 1, 2, -6, 5, 0, -8, -1, 6], 0));
