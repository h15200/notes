/*

  You are given a positive integer target.

  Return an array of all arrays of ordered (ascending) positive integers that
  sum up to the target.

  The arrays can be provided in any order.

  Example:

  partitionNumber(3) ->
  [
    [1, 1, 1],
    [1, 2],
    [3]
  ]

  partitionNumber(4) ->
  [
    [1, 1, 1, 1],
    [1, 1, 2],
    [1, 3],
    [2, 2],
    [4]
  ]

  The inner arrays must have ascending numbers, but can be provided in any order.

*/

// Input ==> an integer, "target"
// Output ==> an array of arrays

const partitionNumber = (target) => {
  const output = [];
  (function generate(target, num = 1, combo = []) {
    // base case target is 0
    if (target === 0) return output.push([...combo]);
    if (target < 0 || num > target) return;

    // take it
    combo.push(num);
    generate(target - num, num, combo);
    // leave it
    combo.pop();
    generate(target, num + 1, combo);
  })(target);

  return output;
};

// /** SOLUTION 1 **/
// const partitionNumber = (target) => {
//   const results = [];

//   (function recurse(i = 1, sum = 0, combo = []) {
//     // BASE CASES:
//     // Success case: When sum equals target
//     if (sum === target) return results.push(combo);

//     // Fail case: When sum exceeds target, or when i reaches target
//     if (sum > target || i > target) return;

//     // RECURSIVE CASE:
//     // Take it (ie. add curr i to sum; don't skip to next i)
//     recurse(i, sum + i, combo.concat(i));

//     // Leave it (ie. don't add curr i to sum)
//     recurse(i + 1, sum, combo);
//   })();

//   return results;
// }

// /** SOLUTION 2 **/
// function partitionNumber2(num) {
//   const result = [];
//   const current = [];

//   // recursive function to generate results
//   (function generate(count = 1, target = num) {
//     // base cases
//     // found valid partition
//     if (target === 0) {
//       return result.push(current.slice());
//     }
//     // not valid path
//     if (target < count) {
//       return;
//     }

//     // take it
//     current.push(count);
//     generate(count, target - count);

//     //leave it
//     current.pop();
//     generate(count + 1, target);
//   })();

//   return result;
// }

console.log(partitionNumber(3));
console.log(partitionNumber(4));
