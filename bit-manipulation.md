8 bits = 1 bytes

## binary

To get binary from a value, get the greediest power of 2 first

ex. 18 to binary

- double 2 until the highest divisible number. 2^0 = 1, 2^1 = 2, 2^2 = 4, 2^3 = 8, 2^4 = 16, stop
- put "1" as 18 / 16 = 1. `1` whie knowing that you have to fill out 4 more powers, so `1????`, more specifically, `1[how many 2^3?][how many 2^2?][how many 2^1?][how many 2^0?]`
- fill out the rest of the powers. we just need to fill 2, so that is 2^1 x 1, which now means `10010`

## binary -> hex

For large binaries with many digits, a hexidecimal representation is easier to count to avoid counting horizontally

ex. 100000101011111010

- first separate into 4s starting from RIGHT to left
  - `10` `0000` `1010` `1111` `1110`
  - add any missing 0s on the lefter most grouping of 4. (all others should be filled) `0010` `0000` `1010` `1111` `1110`
  - treat each set of 4 as a binary, convert to a num (will always be 0 - 15), then turn that into 0-9 + capital A - F
    - `0010` = 2
    - `0000` = 0
    - `1010` = 10 = A
    - `1111` = 15 = F (1111 is the highest binary possible)
    - `1110` = 13 = D
  - add those together `20afd` and prepend with `0x` to denote hexadecimal `0x20AFD`

## hex -> binary

- `0x3A1`
- take each hexadecimal and turn them into base 16 (0-9,A-F to a num 0-15)
  - `3` = 3, `A` = 10, `1` = 1
    - if you want to go straight to binary, do the math in powers of 16.
      16^2 x 3 + 16^1 x 10 + 16^0 x 1
- turn each of those into 4 digit binaries. fill out 0s (except on lefter most one)
  - `3` = `0011` (2^3 x 0, 2^2 x 0, 2^1 x 1, 2^0 x 1).
    since it's the lef most digit, get rid of 00s in front = `11`
  - `10` = `1010` (2^3 x 1, 2^2 x 0, 2^1 x 1, 2^0 x 0)
  - `1` = `0001`
- concat those to make `1110100001`

## js bit manipulation

- JS convert all operands to 32 bit signed integers, meaning the 32 bit (a binary with 32 digits or bits) will be negative after a certain point.
- as the binary gets bigger, it goes 0 => biggest postivie => biggest negative => smallest negative

0 => 0
the max is 2,147,483,647 (011111111111111111111111111111110) up to 31st bit
THE min is -2,147,483,647 (10000000000000000000000000000000) as you hit the last bit, turn sign from + to -
-1 => (11111111111111111111111111111111) all bits flipped "on" is -1

### JS Number type and binaries

specifically in terms of javascript arithmetic operations, converting from decimal => binary will include negative numbers.
To do this:

- decimal => binary conversion is exactly the same unless the 32nd bit exists as `1`
- on the 32nd bit (the last digit on the left), instead of increasing by another multiple of 2 (4 billion and chnage), just flip the previous bit (2 billion) to NEGATIVE 2 billion something
- if the 32nd bit exists, all other subsequent bits will be +(4 billion ish / 2)

ultimately this doensn't matter for vector arrays if you don't have to print out a given int

## Bitwise Operators

- OR `|` take two binaries, and all bits that have 1 OR 2 ones turn into one.
  ex. 25 | 4
  first convert to binaries and put them vertically
  compare each bit (digit) and if at least one of the two is a `1`, the new bit is also 1
  11001 |
  00100
  11101 = 29
- AND `&` if both bits are 1, then it's 1. otherwise 0
  ex. 25 & 4
  11001 &
  00100
  00000 = 0
- XOR `^` if only ONE bit is 1 and the other is 0, then 1
  ex. 25 ^ 21
  11001 ^
  10101
  01100 = 12
- NOT `~` inverts one binary based on its bits. all 32 bits are represented in this case (trailing 0s)
  because js uses 32 signed int, it will always be -(decimal number + 1)
  ex ~5 = -6
- Zero fill left shift `<< ${n}` add zeros on the left most bit, let left bit(s) fall off
  ex 5 << 2 = 20
  101 add two zeros on right
  10100 = 20
- signed right shift `>> ${n}` adds the same bit as the current left most bit to the left, let the right bit(s) fall off
  note! This will only be significant if the 32nd power bit is a `1`. if not, then it's the same as the next operation, `>>>` as it will just add zeros
  ex. -170 >> 2 = -43
  1000000000000000000000000000000000 (add `1` x 2 to the left digit, two `0`s fall off from the right) = 11100000000000000000000000000000 = -43
- zero fill right shift `>>> ${N}` adds zero on left, right falls off
  ex. -170 >>> 31 = 1
  10000000000000000000000000000000
  = 000...etc1 = 01 = 1

## common bit manipulation usage

- making a binary with only one `1` at a specific bit, `n`
  `1 << n`  
  1 << 0 = 0001 // set only 0th bit to 1
  1 << 1 = 0010 // set only 1st bit to 1
  1 << 2 = 0100
  helpful in doing other methods

- the inverse of the above, a binary with only one `0` is helpful as well

  - ex. 4th bit is 0, all other bits are 1 `~(1 << 4)` = `~(010000)` = `101111`

- SET a bit

  - use the tool above, `1 << n` and combine with 0 OR
    `0 | 1 << 2` - logic. find the right side of `|` first, which is 0001 => 0010, then OR with 0, which turns ON the 3rd bit from the right only
    0000 => 0100

- GET (find out in a given number if a specific bit is "on", or `1`)
  again, using `1 << n` this time with `&`

  - given number num, does the 2nd bit exist?
    first build the comporator, which is `1 << 2` (0100) on the target bit
    then compare to given num with AND operator
    `num & (1 << 2)`
    since the right side will be zeroes except ONE bit, (explicitly, 0000000000etc...0000100), then the return will be zero UNLESS that target bit is `1` for both, meaning
    if (num & (1 << 2)) is not 0, then the bit exists. If zero, then no

- DELETE

  - clearing all bits = looking at `&`, we see that setting any number & 0 = 0
  - setting any number `n` & 1111x32, also known as `~0` or the decimal value `-1` in js will just return the number `n` because

    - n 11001
    - ~0 11111
    - returns 11001 (same as original)
    - using the `~`, we can build a binary with exactly 1 `0` and `AND` it to a number to reset specific bit
    - ex. for given number n, clear just the 3rd bit.
      - make bit that looks like `1111111etc..0111` = `~(1 << 3)`
      - `AND` it with `n & (~(1 << 3))`

  - another good tool is the abiity to check if at MOST 1 bit is `1` and rest are 0
    - take a random binary, `0001000`
    - substract 1 `0001000 - 1` = `0000111` (all bits to the right flip to 1)
    - those two will NEVER coincide if there were only 1 bit to begin with `0001000` & `0000111` = 0
    - so if num & (num - 1) === 0, then num has only 1 bit. very useful for string algos with palindromes in conjuction with XOR

## bit vector (bit array)

- when you need to make a hash map or array of booleans say, for some string algo, you usually do something like:
  {a: true, b: false, c: true} (for arrays, [true, false, false])
  These will take up at least 1 byte (8 bits) per bucket
- if the total number of indicies are less or equal to 32, you can use a single variable as a bit vector and use bit manipulation to save space O(N) => O(1))
- simply `let bitVector = 0` and use the getter, setter, and clear with bit manipulation

## example algos

- given an array of numbers (can assume there is no overflow of 2.4billion +) that are all duplicated except one, return the unique number [3,3,5,5,6,99,99]

  - since anyNum `XOR` anyNum = 0, you can initialize a bitArray to 0 and simply keep XORing

  ```
    let bitArray = 0;
    for (let i = 0; i < arr.length, i++) {
      bitArray = bitArray ^ array[i] (or shorthand ^=)
    }
    return bitArray
  ```

- given a string (not cased), return true any chars are repeated more than once
  'abcdeff' -> true
  'bde' => false

  - this can be done with a vectorArray as the alphabet has less than 32 combintions

  ```
  // input string
  let bitArray = 0;
  for (let i = 0; i < string.length; i++) {
    // make 0 index
    const bitIndex = string.charCodeAt(i) - 'a'.charCodeAt(0); // a = 0, b = 1 etc..

    // add to bitArray using SET and GET bit methods. a = 0th bit, b = 1st bit etc..

    // if bit already exists, return true
    // if not, set the bit

    if (bitIndex & (1 << bitIndex) != 0) {
      return true;
    }
    bitIndex |= (1 << bitIndex)

  }
  return false;


  ```
