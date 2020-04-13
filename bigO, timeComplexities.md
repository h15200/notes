# Big O notation and Time Complexity

## Time Complexity

The time it takes for a function to finish depends on many thigns like computer memory, what programming language is being used, and input size.

Time Complexity is a way to describe the relationship between input size and runtime.

1. Linear Time - Time incerases at the same rate input size increases
   example might be adding up the total of an array
2. Constant Time - Time is the same regardless of input size.
   example - return first char of a string
3. Quadratic Time - Time inscreases quadratically, a lot steeper than linear time as input size increases. Least desirable.
   example - get the total of a 2 dimensional array.
4. Logarithmic Time - Could be half of linear time, or at worst, linear time.
   ex. binary search tree.

## BIG O Notation is simply a way to describe different time complexities

n is the size of the input

1. Linear Time = O(n) called "Big O of n" or "O of n"
2. Constant Time = O(1) "Big O of 1"
3. Quadratic Time = O(n2) "Big O of n squared"

## How to get the big O notation

If

T is time
n is the input size
a,b,c .. are single tasks

then most functions can be written as something like

T = an + b

All you need to do is taking the fastest growing term, then take away the coefficient

In this example, an is growing faster than b as input grows, so you take an, then get rid of the a, and you get O(n)
