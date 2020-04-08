// Using typed arrays
// regular
const regularArr = [1, 2, 3]
console.log(regularArr.byteLength) // prints undefined

// typed array with shorthand
const i8 = new Int16Array(3)
console.log(i8.byteLength) // prints 6  since each Int16Array item has 2 bytes, adding '3' will make it 6

// typed array with doing your own byte math

const buffer = new ArrayBuffer(6) // assign 6 bytes to buffer
const i8View = new Int16Array(buffer)
console.log(i8View.byteLength) // also returns 6

const newInt32 = new Int32Array(1)
console.log(newInt32.byteLength)
