const firstMissing = (array, expected = 1) => {
  // base case 1 if everything is in order
  if (array[0] === 1 && array[array.length - 1] === array.length)
    return array.length + 1;
  // base case 2
  if (array.length <= 2) {
    return array[0] === expected ? expected + 1 : expected;
  }
  // divide until problem segment is reached
  let midpoint = Math.floor(array.length / 2);
  // if start to midpoint matches up to expected, recursively go to second half
  if (array[0] === expected && array[midpoint] === expected + midpoint) {
    return firstMissing(array.slice(midpoint), midpoint + 1);
  } else return firstMissing(array.slice(0, midpoint + 1), 1);
};
