/*

Given an array of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets. Order does not matter.

Example:

Input: [1,7,4]
Output:
[
  [ 1, 7, 4 ],
  [ 1, 7 ],
  [ 1, 4 ],
  [ 1 ],
  [ 7, 4 ],
  [ 7 ],
  [ 4 ],
  []
]

*/

const allSubsets = (arr) => {
  const output = [];
  (function generate(index = 0, subset = []) {
    if (index === arr.length) {
      return output.push([...subset]);
    }

    // take it
    subset.push(arr[index]);
    generate(index + 1, subset);

    // leave it. Since this ALWAYS runs after take-it, you have to pop off the last element to undo the last add
    // index still needs to increment to push an element that is less than the length of arr
    subset.pop();
    generate(index + 1, subset);
  })();
  return output;
};

// const allSubsets = (arr) => {
//   const output = [];
//   const subset = [];
//   (function generate(index = 0) {
//     if (index === arr.length) {
//       return output.push([...subset]);
//     }

//     // take it
//     subset.push(arr[index]);
//     generate(index + 1);

//     // leave it. Since this ALWAYS runs after take-it, you have to pop off the last element to undo the last add
//     // index still needs to increment to push an element that is less than the length of arr
//     subset.pop();
//     generate(index + 1);
//   })();
//   return output;
// };

// const allSubsets = (arr, index = 0, temp = []) => {
//   const take = () => {
//     console.log('about to take. arr, index, temp', arr, index, temp);
//     temp.push(arr[index++]);
//     return allSubsets(arr, index, temp);
//   };

//   const leave = () => {
//     index++;
//     return allSubsets(arr, index, temp);
//   };

//   const output = [];
//   if ((index = arr.length)) {
//     output.push(temp);
//     temp = [];
//     return output[output.length - 1];
//   }
//   // take it
//   take();
//   // leave it
//   leave();

//   return output;
// };

// function allSubsets(nums) {
//   const result = [];
//   const current = [];

//   // function to recursively generate results
//   (function generate(index = 0) {
//     // base case
//     if (index === nums.length) return result.push([...current]);

//     // take it
//     current.push(nums[index]);
//     generate(index + 1);
//     // leave it
//     console.log('AFTER generate index, current ->', result, index, current);
//     current.pop();
//     console.log('AFTER pop result, index, current ->', result, index, current);
//     generate(index + 1);
//   })();

//   return result;
// }

console.log(allSubsets([1, 2, 3]));
