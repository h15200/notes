function numberOfWaysToMakeChange(n: number, denoms: number[]): number {
  // helper function to check to see

  // edge case n doesn't exist or is 0
  if (n === undefined || n < 0) return -1;
  if (n === 0) return 1;

  // initialize cache like this {  1: 0, 5: 0, 10: 0 }
  const cache: Object = {};
  denoms.forEach((coin) => (cache[String(coin)] = 0));

  // helper function to compare objects
  const compareCoins = (obj1, obj2) => {
    for (const key in obj1) if (obj1[key] !== obj2[key]) return false;
    for (const key in obj2) if (obj2[key] !== obj1[key]) return false;
    return true;
  };
  let ways: number = 0;
  const recorded: Object[] = [];
  // n is bigger than 0
  (function generateCombo(balance: number, coinsUsed: Object = cache): void {
    // recorded is a list of objects representing existing combos of coins
    // base case - if balance is 0
    if (balance === 0) {
      // compare against recorded
      if (recorded.every((cached) => !compareCoins(cached, coinsUsed))) {
        console.log('hit. coins is', coinsUsed);
        ways++;
        recorded.push(coinsUsed);
        return;
      }
    }

    for (let coin of denoms) {
      if (balance >= coin) {
        generateCombo(balance - coin, {
          ...coinsUsed,
          [coin]: coinsUsed[coin] + 1,
        });
      }
    }
  })(n);
  console.log(recorded);
  return ways;
}

console.log(numberOfWaysToMakeChange(10, [10, 5, 2]));
