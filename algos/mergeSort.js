const mergeSort = (array) => {
  if (array.length <= 1) return array;

  const mid = Math.floor(array.length / 2);
  const left = mergeSort(array.slice(0, mid));
  const right = mergeSort(array.slice(mid));

  // here left and right are both length 1 or 0
  const output = [];
  // left and right pointers each pointing to left array and right array
  let lp = 0;
  let rp = 0;
  while (output.length < left.length + right.length) {
    if (left[lp] === undefined) output.push(right[rp++]);
    else if (right[rp] === undefined) output.push(left[lp++]);
    // if both numbers exist, push smaller of the two
    else
      left[lp] < right[rp] ? output.push(left[lp++]) : output.push(right[rp++]);
  }
  return output;
};

console.log(mergeSort([1, 4, 2, 6, 11]));
