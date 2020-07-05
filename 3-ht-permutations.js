/*
  Let's say you flipped a coin multiple times, resulting in a given number of
  heads and tails. Return an array of strings representing all possible histories
  given those numbers of heads and tails. The strings can be in any order.

  Example

  htPermutations(2, 1) ->
  [
    'HHT',
    'HTH'
    'THH'
  ]

  htPermutations(2, 2) ->
  [
    'HHTT',
    'HTHT',
    'HTTH',
    'THHT',
    'THTH',
    'TTHH'
  ]

  htPermutations(0, 3) ->
  [
    'TTT'
  ]

  htPermutations(0, 0) ->
  [
    ''
  ]

*/

const htPermutations = (heads, tails) => {
  const output = [];

  (function generate(heads, tails, combo = '') {
    if (heads === 0 && tails === 0) {
      return output.push(combo);
    }

    // take heads
    if (heads > 0) {
      // combo += h , then passing in new combo DOES NOT work because it will change the global combo,
      // which means the take tails clause will now have an extra 'H'
      // console.log('combo in heads ->', combo + 'H');
      generate(heads - 1, tails, combo + 'H');
    }
    // take tails
    if (tails > 0) {
      // console.log('combo in tails ->', combo + 'T');
      generate(heads, tails - 1, combo + 'T');
    }
  })(heads, tails);
  return output;
};

/** Solution 1 */
// const htPermutations = (numOfHeads, numOfTails) => {
//   const results = [];

//   const recurse = (numOfHeads, numOfTails, HTStr = '') => {
//     // Base case: When both args are reduced to zero
//     if (numOfHeads === 0 && numOfTails === 0) {
//       return results.push(HTStr);
//     }

//     // Use H
//     if (numOfHeads > 0) {
//       recurse(numOfHeads - 1, numOfTails, HTStr + 'H');
//     }

//     // Use T
//     if (numOfTails > 0) {
//       recurse(numOfHeads, numOfTails - 1, HTStr + 'T');
//     }
//   }

//   recurse(numOfHeads, numOfTails);

//   return results;
// }

/** Solution 2 **/
// function htPermutations2 (heads, tails) {
//   const result = [];

//   (function generate(str = '', m = heads, n = tails) {
//     // base case of running out of coins
//     if (m === 0 && n === 0) return result.push(str);

//     // take head
//     if (m > 0) generate(str + 'H', m - 1, n);
//     // take tail
//     if (n > 0) generate(str + 'T', m, n - 1);
//     // the leave it scenarios happen as the call stack pops off
//   })();

//   return result;
// }

console.log(htPermutations(1, 1));
console.log(htPermutations(2, 1));
console.log(htPermutations(2, 2));
console.log(htPermutations(0, 0));
