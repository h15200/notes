# Data Structures and Algorithm

- generally, array inputs will result in pointers and/or a map table
- while loops with pointers are safest when it's checked against being out-of-bounds
  - ex. leftPointers should stop when they hit array.length, rightPointers when they hit index -1

LATEST stupid discovery

- When using recursion, make sure to remind yourself that primitive values are passed in by VALUE so does not update through all the recursion stacks, but arrays and objects WILL update. This means primitive answers like a number or boolean will usually use closure and need a 2nd IIFE to generate something

What is a data structure and algorithm and how do they relate?
An algorithm is a set of instructions to solve a problem with logic.
Data structure is a way to organize data, utilized inside algos.

## Algorithmic thinking, Peak Finding

## solve 24 solve24('1234') // "(1+2+3)\*4"

See code. The hardest one so far to date (4-30-20)!

## balanced parens

use a Stack to keep track of most recent open brackets.

Strategy

make a bracket pair cache like
{
'{' : '}',
'(' : ')'
}

Stack can be used as a simple array but using push and pop (last one in, first one out)

loop through string and IF opening brackets, push to stack.
Else if closing brackets, check to see if the POP value of the stack matches.
If not, return false

After loop, if there are any items inside the stack, it was never closed

## merge sort

return all array length 1 or less

separate into left and right

make a helper merge

return merge(recursive(left), recursive(right))

## Kadane's algo

max subset

brute force- get the max of ALL subsets

ex [1,-4,3]

let leftPointer = 0
let rightPointer = 0
const allSubMax = [];

start at left, push arr[left] alone to array (1)
move right, push arr[left] plus arr[right] to array (1 + -4)  
move right, (1 + -4 + 3)

now move left,
add -4
add -4 + 3

Now move left

add 3 alone

Now you have ALL possible combinations in O(n^2) time, and you just get the max out of those

Kadane's algo says you can at least get the max substring of each index linearly if you definitely HAVE to use that index. Compare previous index max + itself VS itself alone and the bigger one is the max for that substring

[1, 3, -5, 7 ,-3]
1 4 -1 7 4

first index is 1 because that is the max by default
second index 1 + 3 is bigger than 3, so 4
third index. remember you MUST use the index element, so the choice is either 4 + -5 or -5 alone. answer is -1
fourth index - 7 alone is bigger
last index 4

Notice how at index 7, we cut off all possibilites from the left hand side as it was determined that nothing in the left is useful.

As a last step, you must get the highest out of the new dp array for the max

### two sum

the brute force is O(n^2)
using a cache is O(n) T O(n) S
if prioritizing S over time, sort and using shrinking window with O(nlogn) T , O(1) S

left to 0
right to length - 1

if total === target, that's the pair
if total is smaller than target, left++
if not, right--

This sliding window is extremely useful in threeNumberSum as it is optimal for space AND time

### buy and sell

Best Time to Buy and Sell Stock "Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

### reverse linked list

Reverse Linked List Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL

Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?

### merge intervals

Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

### max depth bst

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

```
    3
   / \
  9  20
    /  \
   15   7
```

return its depth = 3.

### palindromic substring

Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:

Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:

Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

### reorder list

Given a singly linked list: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.

### Number of Islands

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1

Example 2:

Input:
11000
11000
00100
00011

Output: 3

### set matrix zeroes

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in-place.

Example 1:

Input:
[
[1,1,1],
[1,0,1],
[1,1,1]
]
Output:
[
[1,0,1],
[0,0,0],
[1,0,1]
]
Example 2:

Input:
[
[0,1,2,0],
[3,4,5,2],
[1,3,1,5]
]
Output:
[
[0,0,0,0],
[0,4,5,0],
[0,3,1,0]
]
Follow up:

A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?"

### longest substring w/o repeating characters

Given a string, find the length of the longest substring without repeating characters.

Example 1:

Input: "abcabcbb"
Output: 3
Explanation: The answer is ""abc"", with the length of 3.
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is ""b"", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Note that the answer must be a substring, ""pwke"" is a subsequence and not a substring.

### valid parens

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true"

### invert binary tree

"Invert a binary tree.

Example:

Input:

```
     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

### Valid BST

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.

Example 1:

```
    2
   / \
  1   3
```

Input: [2,1,3]
Output: true
Example 2:

```
    5
   / \
  1   4
     / \
    3   6
```

Input: [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4."

### 3sum

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
[-1, 0, 1],
[-1, -1, 2]
]

### coin sum

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:

Input: coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Note:
You may assume that you have an infinite number of each kind of coin.

### circularLinkedList

"Given a circular linked list, implement an algorithm which returns the node at the beginning of a loop.
Example: A -> B -> C -> D -> E -> C (answer is C)"

### checkBalancedBinaryTree

Given a binary tree, check if it is balanced (ie the heights of the two subtrees of any node never differ by more than one.

### makeMinBinaryTree

Given a sorted array, find a way to make a binary tree with minimal height

### longestWord

"Given a list of words, write a program to find the longest word made of other words in the list.
Example: ['dog', 'cat', 'walker', 'dogwalker'] -> 'dogwalker'"

### findInSortedArray

You are given a sorted array and you want to find the number N. How do you do the search as quickly as possible

### stackToQueue

Implement a stack using queues as the underlying data structure

### changeWord

    "Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

1.Only one letter can be changed at a time
2.Each intermediate word must exist in the word list"

### excelColumn

"Given a column title as appear in an Excel sheet, return its corresponding column number.
Example: (A -> 1, B -> 2, AA -> 27, AB -> 28)"

### storeAlphabet

"Write a function that takes three arguments, two strings and an alphabet. Write a function that returns the word that comes first in the alphabet. What data structure would you use to store the alphabet?
For example: a given 4 letter ordered alphabet “zgac” how do you decide what word comes alphabetically first “aggd” vs. “aggz”"

### findZero

    " given an array of positive intergers,

each integer represents how many times to the left or right
you can move in the array, no out of bound moves.
Given a starting index, return true if you can reach 0
in the array, otherwise return false.

ex:
input: arr = [1, 3, 2, 0, 4, 2, 1]
startIdx = 1
output: false"

### noDuplicates

given an array of integers return an array with the duplicates removed [1,2,3,3,4,5,6,1,1] ==> [1,2,3,4,5,6]

### invertBinaryTree

given a binary tree, reverse all of the nodes {8}->{5}{10}-> {2}{6}{7}{12} ==>{8}->{10}{5}-> {12}{7}{6}{2}
