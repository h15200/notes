# Big O notation and Time Complexity

## Time Complexity

The time it takes for a function to finish depends on many thigns like computer memory, what programming language is being used, and input size.

Time Complexity is a way to describe the relationship between input size and runtime.

note log(16) is the same thing as 2** ? is 16? the answer is 4 as 2**4 is 16.
How many HALVING steps does it take to get to 1?

```
name             notation         ex                                    speed

Constant        `O(1)`            key look up                           FASTEST
Logarithmic     `O(log n)`        BST
Linear          `O(n)`            1 Level Looping
Quasilinear     `O(n log n)       Good stort(merge)
Quadratic       `O(n2)`          Nested loop (selection sort)
Exponential     `O(Cn)`          Recursive Backtracking: Subsets
Factorial       `O(n!)`          Generating permutations                SLOWEST

```

Exponential is the opposite of Logarithmic. One task creates TWO tasks

## Space Complexities - MEMORY

Space complexity is based on number of stacks called. Requires more cpu

Space and Time complexties have an inverse relationship.

You can buy more RAM, but not more time so ALWAYS prioritize time complexities

## BIG O Notation is simply a way to describe different time complexities

n is the size of the input

1. Linear Time = O(n) called "Big O of n" or "O of n"

The most common time complexity

2. Constant Time = O(1) "Big O of 1"

3. Quadratic Time = O(n2) "Big O of n squared"
   ex - nested for loops have O n2

## How to get the big O notation

If

T is time
n is the input size
a,b,c .. are single tasks

then most functions can be written as something like

T = an + b

All you need to do is taking the fastest growing term, then take away the coefficient

In this example, an is growing faster than b as input grows, so you take an, then get rid of the a, and you get O(n)
