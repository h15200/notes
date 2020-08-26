/* even better way to make change is dynamically

 run the array each time with a coin
 is i >= coin? if so, the answer is arr[i] += arr[i - coinValue];
 do this for all coins
  */

const makeChangeDynamically = (n: number, denoms: number[]): number => {
  // this is an array of all make change possibilities. starts at 0 up to n
  const arr: number[] = new Array(n + 1);
  for (let i = 0; i < arr.length; i++) {
    if (i === 0) {
      arr[i] = 1;
      continue;
    }
    arr[i] = 0;
  }
  // you can make 0 only 1 way

  // loop through coins
  denoms.forEach((coin) => {
    for (let i = 1; i < arr.length; i++) {
      if (i >= coin) arr[i] += arr[i - coin];
    }
  });
  console.log(arr);
  return arr[n];
};

console.log(makeChangeDynamically(10, [1, 5, 10]));
