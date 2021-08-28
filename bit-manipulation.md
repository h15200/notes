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

## Bitwise Operators
