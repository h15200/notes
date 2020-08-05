// given a sorted array of integers, remove duplicates in-place
// and return the new length

// input [1,1,1,2,2,3] -> output length = 2

const removeDuplicates = function (arr) {
  // start 2 pointers on second element, set stored to first element
  let left = 1;
  let right = 1;
  let stored = arr[0];
  // loop through entire array
  while (right < arr.length) {
    // if right index value is different from what's stored,
    if (arr[right] !== stored) {
      // replace left pointer value to right pointer value, make that the new stored and increment both
      arr[left] = arr[right];
      stored = arr[right];
      left++;
      right++;
    } // if right index value is the same as what's stored, just increment right
    else right++;
  }
  // at this point the first x (x being the value of left) indexes are all unique
  // slice the beginning up to the left index and that's the new arr
  return arr.slice(0, left).length;
};
const myArr = [1, 1, 1, 1, 2, 2, 3];
console.log(removeDuplicates(myArr));
