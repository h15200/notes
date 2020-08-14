// sort an array of only 1's, 2's and 3's

// generic merge sort would be O(nLogn) T, O(n) space

const sort123 = (array) => {
  // do it in place O(1) space
  // and linear time O(n)

  // basic idea - left keeps all 1's to the left, current keeps all 2s to the left, right keeps all 3s to right
  // when current is on the right side of right, it's done

  // this is linear time because original initialization + incrementing current all adds up to n,
  // and all comparisons and swapping is constant time and constant space (probably 1 for temp under the hood)

  // make 2 pointers
  // left is the first element that is not 1. everything to the left of left is 1, so sorted
  let left = 0;
  let right = array.length - 1;
  let current = left;
  // when current overlaps right, everything is sorted
  while (current <= right) {
    // move right in case there are consecutive 3s
    while (array[right] === 3) right--;
    // if current is 1, swap with left value
    if (array[current] === 1) {
      [array[left], array[current]] = [array[current], array[left]];
      // since current is following from left to right, we know that left pointer can be incremented by 1 to hit a non-1 number
      left++;
    }
    // same on 3 and right
    else if (array[current] === 3)
      [array[current], array[right]] = [array[right], array[current]];
    else current++;
  }
  return array;
};

// console.log(sort123([1, 3, 2, 2, 3, 1, 3]));
console.log(sort123([3, 1, 2, 3, 3, 2, 2, 3, 1, 2, 2, 2, 2]));
