# combination algorithms using recursion

## given an array of numbers and a target, return a boolean if any combination (addition) of the numbers can total the target

[4, -1, 2], 5

since adding all three returns 5, return true

for each element, there are

```
const subsetSum (nums, target, index = 0) {
  // base case

  // if element is found
  if (target ===0) return true;

  // if done with entire array
  if (index === num.length) return false;

// first part of OR is if you ADDED the current index, second part is NOT taking the current index as part of the total.
// if true, end immediately.
  return (subsetSum(nums, target - nums[index], index + 1) || subsetSum(nums, target, index + 1))
}
```

## given an array of distinct integers, nums, return all possible subsets

Do not contain duplicate subsets. Order does not matter

ex. input: [1,7,4]
output:
[
[1,7,4], [1,7], [1,4], [7,4], [1,], [7], [4], []
]

```
const allSubsets = (nums) => {
  const result = [];
  const current = [];

// helper
(function generate(index) {

  // base case
  if (index === nums.length) return result.push(current.slice());

  // take the value
  current.push(nums[index]);
  generate(index + 1);

  // leave it alone
  current.pop();
  generate(index + 1);
})(0)

return result;
}
```

## htPermutation - return an array of strings representing all possible histories of a coin flipt given the numbers of heads and tails. Any order

// 2 heads and 1 tail
htPermutations(2, 1) -> [ 'HHT', 'HTH', 'THH']

similar concept as the previous algos. the pool changes as you take an element

```
const htPermutations = (numHeads, numTails) => {
  const results = [];
  const recurse = (numOfHeads, numOfTails, HTStr = '') => {
    // base case no more args
    if (numOfHeads === 0 && numOfTails === 0) {
      return results.push(HTStr);
    }

    // use H
    if (numOfHeads > 0) {
      recurse(numOfHeads - 1, numOfTails, HTStr + 'H');
    }

    // use T
    if (numOfTails > 0) {
      recurse(numOfHeads, numOfTails - 1, HTStr + 'T');
    }
  }

  recurse(numOfHeads, numOfTails);

  return results;
}

```

## partitionNumber

given a positive integer target, return an array of all arrays of ordered (ascending) positive integers that sum up to the target

partitionNumber(3) -> [
[1,1,1],
[1,2],
[3]
]

partitionNumber(4) -> [
[1,1,1,1,],
[1,1,2],
[1,3],
[2,2],
[4]
]

```
const paritionNumber = (target) => {
  const result = [];

  (function recurse(i = 1, sum = 0, combo = []) {
    // base cases:
    // success case: when sum equals target
    if (sum === target) return results.push(combo);

    // fail case: sum exceeds target, or when i reaches target
    if (sum > target || i > target) return;

    // recursive case:
    // take it (add curr i to sum, don't skip to next i)
    recurse(i, sum + i, combo.concat(i));

    // leave it (DON'T add curr i to sum)
    recurse(i + 1, sum, combo);
  })();

  return results;

}
```
