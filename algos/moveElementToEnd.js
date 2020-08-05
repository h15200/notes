/* moveElementToEnd

Input:  arr: int[], target:int
Output: arr: int[] with all target ints at the end of the array
All non-target ints stay the same

Unordered input

[4,6,7,8,3,5,5,3] target = 3
[4,6,7,8,5,5,3,3]
 
*/

// O(n) T/ O(n) S

// const moveElementToEnd = function (arr, target) {
//   const nonTarget = [];
//   const targetArr = [];
//   for (item of arr) {
//     if (item === target) targetArr.push(item);
//     else nonTarget.push(item);
//   }
//   return [...nonTarget, ...targetArr];
// };

// Now do the same in O(1) SPACE and O(n) Time
// O(1) space implies that you are not using additional arrays
// also applies pointers are probably involved

const moveElementToEnd = (arr, target) => {
  let targetIndex = 0;
  let currentIndex = 0;
  while (currentIndex < arr.length) {
    console.log('arr', arr);
    // if neither are target, and the indicies are identical, move both
    if (arr[currentIndex] !== target && currentIndex === targetIndex) {
      targetIndex++;
      currentIndex++;
    } // if current is target, just increment current
    else if (arr[currentIndex] === target) {
      currentIndex++;
    }
    // if the current is not target but the targetIndex IS, reassign targetIndex value
    // then increment current by 1, then target until the next target
    else if (arr[currentIndex] !== target) {
      arr[targetIndex] = arr[currentIndex];
      currentIndex++;
      targetIndex++;
    }
  }
  // at this point targetIndex to arr.length - 1 and reassign everything to target
  // if necessary
  while (targetIndex < arr.length) {
    if (arr[targetIndex] !== target) arr[targetIndex] = target;
    targetIndex++;
  }
  return arr;
};
console.log(moveElementToEnd([1, 2, 3, 4, 3, 7, 5], 3));

// 1, 2, 3, 3, 3, 4, 3, 5

// is current a target?
//   if not and indicies are the same, move both
//   if not and indicies are different, reassign targetIndex to current and move target
//   if yes, just move the current
