In C, you have to declare the data type in a variable to allocate the right amount of bytes depending on the type

signed char, unsigned char, int, long int, unsigned int, float, long float, etc...


When an array is declared with 4 elements, it creates 4 consecutive bytes in memory. When an additional item is needed, you have to reassign a brand new array in a different, 5 consecutive byte location in memory. In JS, this is all happening under the hood when you push a new element to an existing array.

## TYPED ARRAYS - You can declare arrays with exact bytes like in C

Int16Array needs 2 bytes (16 bits) of memory PER item.

1. `var i8 = new Int16Array(3); i8.byteLength // returns 6 since 2 bytes x 3`
// array elements are initialized to 0 for Int16Arrays.
 // i8 is [0,0,0]

 // byteLength will return the amount of bytes in a typed array. Will return undefined for regular (const a = [1,2,3]) arrays.

  i8 can be any variable name and the num inside the parens can be changed for the number of elements
  The number 3 here will tell JS to do the math to figure out how many bytes it needs to store 3 of the dataType, in this case Int16, in the array.


2. The more low level way to do this is 
  1. declaring your own byteSize (multiple of whatever data type yo need in array), 
  2. making a buffer from that byte size. 
  3. plug that into the parens of new Int16Array(). 

  the function, new ArrayBuffer() takes in the memory size in bytes as arg and returns a buffer
  A buffer is an all purpose object that carries data that can't be accessed directly without a view.

``` 
var buffer = new ArrayBuffer(6) // since each item of an Int16Array requires 2 bytes, this number has to be a multiple of 2 bytes
var i8View = new Int16Array(buffer)


i8View.byteLength // returns 6

// You can assign the arrays like before i8View[0] = 42. // [42,0,0] 
// but you can't use some methods like .pop, .push, Array.isArray().
```