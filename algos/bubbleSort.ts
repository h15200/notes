function bubbleSort(array: number[]) {
  let sorted: boolean = false;
  let counter = 1;
  while (!sorted) {
    sorted = true;
    for (let i = 0; i < array.length - counter; i++) {
      if (array[i] > array[i + 1]) {
        sorted = false;
        [array[i], array[i + 1]] = [array[i + 1], array[i]];
      }
    }
    console.log('counter, array, sorted', counter, array, sorted);
    counter++;
  }

  return array;
}

console.log(bubbleSort([9, 8, 4, 2]));
