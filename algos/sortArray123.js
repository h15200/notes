// sort an array of only 1's, 2's and 3's

// generic merge sort would be O(nLogn) T, O(n) space

const sort123 = (array) => {
  // do it in place O(1) space
  // and linear time O(n)

  // this is linear time because original initialization + incrementing current all adds up to n,
  // and all comparisons and swapping is constant time and constant space (probably 1 for temp under the hood)

  // make 3 pointers
  // left is the first element that is not 1. everything to the left of left is 1, so sorted
  let left = 0;
  while (array[left] === 1) left++;
  // same for right. keep moving left until it's not a 3. everything to the right of right is sorted
  let right = array.length - 1;
  while (array[right] === 3) right--;
  // initialize current to left
  let current = left;
  // when current overlaps right, everything is sorted
  while (current < right) {
    if (array[current] === 1) {
      // swap with left
      [array[left], array[current]] = [array[current], array[left]];
      left++;
      // because current is starting from left, we only need to increment by 1
    } else if (array[current] === 3) {
      // swap with right
      [array[current], array[right]] = [array[right], array[current]];
      // it's possible the next few on the left are all 3s, so keep decrementing until a non-3
      while (array[right] === 3) right--;
      // ignore 2s
    } else current++;
  }
  return array;
};

console.log(sort123([1, 1, 2, 2, 2, 1, 3, 2, 3, 1, 2, 3, 2, 1, 3, 2]));
