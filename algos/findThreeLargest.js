function findThreeLargestNumbers(array) {
  // Time O(n * m) m being the number of max items (three largest = 3)
  // Space O(m)

  const findLargestNumbers = (num) => {
    // make empty array of num x slots. initializes to undefined
    const output = new Array(num);
    // helper function shiftAndReplace to have reference to output

    // helper function
    const shiftAndReplace = (index, num) => {
      for (let i = 0; i < index; i++) {
        // [1,2,3,4,5] adding 6
        output[i] = output[i + 1];
      }
      output[index] = num;
    };

    array.forEach((current) => {
      // loop backwards on output array to see where it fits
      for (let i = output.length - 1; i >= 0; i--) {
        if (output[i] === undefined || current > output[i]) {
          console.log('index, current, output', i, current, output);
          shiftAndReplace(i, current);
          break;
        }
      }
    });
    return output;
  };

  return findLargestNumbers(3);
}

console.log(
  findThreeLargestNumbers([141, 1, 17, -7, -17, -27, 18, 541, 8, 7, 7])
);

// Do not edit the line below.
exports.findThreeLargestNumbers = findThreeLargestNumbers;
