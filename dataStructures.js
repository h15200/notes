// // Using typed arrays
// // regular
// const regularArr = [1, 2, 3]
// console.log(regularArr.byteLength) // prints undefined

// // typed array with shorthand
// const i8 = new Int16Array(3)
// console.log(i8.byteLength) // prints 6  since each Int16Array item has 2 bytes, adding '3' will make it 6

// // typed array with doing your own byte math

// const buffer = new ArrayBuffer(6) // assign 6 bytes to buffer
// const i8View = new Int16Array(buffer)
// console.log(i8View.byteLength) // also returns 6

// const newInt32 = new Int32Array(1)
// console.log(newInt32.byteLength)

const set1 = new Set([1, 3, 'a', 'b', true, 1, 'b', undefined, null]);
// console.log(set1.has(1));

// no length method, but you can use size. Size does not seem to count undefined or null
// console.log(set1.size);

console.log(set1);
set1.add(3);

const set2 = new Set([2, 3, 457, 23, 35]);

// you CAN NOT add multiple items with the .add() method with an array or another set inside the parens.
// but you can use the spread operator on a set to turn it into an array
