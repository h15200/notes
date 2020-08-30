// find max total of substring in an array of numbers

const maxSubstring = (arr: number[]): number => {
  // kadane's algo states that you can find the max substring total of each index
  // that ends with the index (must use index)
  // this will reset new num if the left side is useless and the max item of this dpArray
  // will be the correct answer

  // make dynamic programming array, initializing with 1st item
  const dpArr: number[] = [arr[0]];
  // start array starting on 2nd element
  for (let i = 1; i < arr.length; i++) {
    // compare index 1 to max(arr[0]) + 1
    dpArr[i - 1] + arr[i] > arr[i]
      ? (dpArr[i] = dpArr[i - 1] + arr[i])
      : (dpArr[i] = arr[i]);
  }
  // console.log(dpArr);
  return Math.max(...dpArr);
};

console.log(maxSubstring([3, 5, -9, 1, 3, -2, 3, 4, 7, 2, -9, 6, 3, 1, -5, 4]));
