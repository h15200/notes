# Data Structures and Algorithm

- generally, array inputs will result in pointers and/or a map table
- while loops with pointers are safest when it's checked against being out-of-bounds
  - ex. leftPointers should stop when they hit array.length, rightPointers when they hit index -1

LATEST stupid discovery

- When using recursion, make sure to remind yourself that primitive values are passed in by VALUE so does not update through all the recursion stacks, but arrays and objects WILL update. This means primitive answers like a number or boolean will usually use closure and need a 2nd IIFE to generate something

What is a data structure and algorithm and how do they relate?
An algorithm is a set of instructions to solve a problem with logic.
Data structure is a way to organize data, utilized inside algos.

# basic operation costs

## Arrays

Time complexities:

Init => O(n)
Get => O(1)
Set => O(1)
Delete => O(n)
Traverse => O(n) ex. loop
Copy => O(n)
Insert at end (appending) => O(n) for static arrays. O(1) even for dynamic arrays as the frequency amortized is still O(1) even though re-allocation is technically O(n)
Pop (remove last ele) => O(1)

any insert not at the end / any pop not at the end => O(n)

## Linked Lists

Getting, Setting in LLs aren't efficient since the idea of indices isn't a ting
Init => O(n)
Get => O(i) i being the index
Set => O(i)
Copy => O(n)
Traverse => O(n)

Insert at beginning => O(1) Faster than arrays because no need to re-index
Insert anywhere else => O(i) for traversal, then O(1) for insertion itself.
Delete => O(i) for finding the node, but O(1) for deleting

## Hash Tables

A key value pair. Uses a dynamic array of linked lists for collision:

example -

```
[
  0: (value1, key1) => null // no collision
  1: (value2, key2) => (value3, key3) // collision dealt by linked list
]
```

Set => O(1)
Find (if key is known) => O(1)
Delete => O(1)

if it's an exceptionally bad hashing algorithm, it will be O(n) because it'll just have one bucket with a long linked-list.

## Stacks

Insert / Delete is O(1) ST

basically a dynamic array that only adds/deletes at the end of the array with pop() and push()

## Queues

Insert / Delete is O(1) ST

Implemented with a linked list so enqueue will add a node and move the head, dequeue will remove tail and move the tail back one node

In an algo problem that uses a queue, you can probably just do `const queue = []` and use shift() and unshift() as shorthand

## Strings

Stored as integers via ASCII

traverse => O(n)
copy => O(n)
get => (1)
insert Immutable in js, so impossible. Must copy first, then append

string += "3" => this is O(n), NOT O(1)
so if you have to add something more than 2 times, it is actually better to .split(), make a bunch of constant mutations, and .join()

## Graphs

Vertices (Nodes)
Edges - the path between
Direction - if directed, it's one way. If undirected, it goes both ways
Cycle - 3+ vertices that can be revisited
Connected / Unconnected - is a set of vertices visitable

Creation - Space O(v + e) where v is number of vertices and e is number of edges
Traversal - O(v + e) for both breadth-first and depth-first
Insertion/Deletion is specific to the circumstance and there is no general blanket T or S complexity value

## Algorithmic thinking, fundamental tools in (Python)

### NUMBERS

- In python, division is weird. Must do int(x / y) instead of // when negative
- use `abs(my_num)` and do negative conditional after main logic
- num % 10 to get first digit on right
  - e.g Leetcode "Plus One"
- num // 10 to cut off digit on right
- to add numbers by digit, curr \*= 10, then curr += digit
- adding digits with carry logic
- merge intervals `[[1,2], [2,3], [3,5]]`
  - use a temp to store the merged version and keep comparing to the next range.
    After loop, merge the temp one more time
- create a matrix with nested list comprehension
  - matrix = [[0 for _ in range(COL)] for i in range(ROW)]
- Calculator
  - use reusable nums trick like a visited set with _= 10, += trick.
    On each new sign, compute the OLD sign by adding, adding -(num),
    popping and adding if _ or /. Sum of stack
- prefix array
  - for any arithmetic operation, you can pre-compute.
    For addition, just one pass left to right and get array of sum.
    To use, arr[R] - arr[L - 1] unless L is 0, in which case just arr[R]
  - for things that say "excluding self", make 2 arrays for going left and
    going right, and the usage is arrR[i + 1] and arrL[i - 1]
- peak

  - in algos, a peak will usually exist to the right of in increasing sequence,
    or to the left of a decreasing sequence if curr is not valid

- bonus
  - cumulative sum (LC 2381 :shifting letters ii)
  - when adding/subtracting to a range, only add the markers at start and end

### STRINGS

- `"".join(my*list)` to make a string from an array of chars
- `list(my_str)` to make an array of strings
- `str.isdigit()`, `str.isalpha()`, `str.isalnum()`
- Only non mutable types can be a key for a dict.
  - For anagram grouping, use a tuple of list with each char [0] \* 26
- you can fprint via. `print(f"{}")`
- a palindrome validation based on char counter.
  first odd is a bonus, 2nd odd is not part of palindrome
- shorthand to exclude chars `if char in "+-/\_"`

### SLIDING WINDOW

- general idea
  - usually use 2 pointers (l while + for loop), pinning l = 0 and manually incrementing
    l for unhappy path
  - When "happy", just continue. If not, while loop with Left pointer logic
    until condition is happy again. often easier to while loop until bad
    condition is removed than the other way around
- MATRIX
  - For spiral type algos, use a variation of sliding window by shrinking the
    existing y and x borders. Remember to + 1 to end when incrementing and -1 to
    end AND adding -1 as 3rd arg in decrem.
  - To check for vertical / horizontal/ diagonals in a large board for
    N-Queens, cache existing queens and compare if y's are equal, x's
    are equal, or the abs(y_diff) == abs(x_diff)

### SORTS

- partitioning two numbers (one low, one high)
  - use one left pointer while and for loop for right. if t
  - num is the low one, leave left pointer alone.
  - otherwise, always flip. similar to sliding window
- quick sort
  - use the last ele as the pivot_val and first val as pivot_i.
  - for range loop and if less OR EQUAL the val, switch with pivot_i and
    increment.
  - At the end, one more swap between pivot_i and last idx
- quick select
  - getting only 1 particular idx sorted.
  - add conditional for final pivot_i to see if it's done

### BINARY SEARCH

- binary search
  - with variations, keep updating the best val when condition met and move
    direction. else, the other way without updating

#### Iterative DFS

- use a stack and visit twice with a set
- first time, add the nodes in reverse order
- second time, execute the business logic
- as an exception to the rule, preorder doesn't require a 2nd visit

```
in-order

class Solution:
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        stack = [root]
        res = []
        visited = set()
        curr = root

        while stack:
            top = stack.pop()
            if top not in visited:
                if top.right:
                    stack.append(top.right)
                stack.append(top)
                if top.left:
                    stack.append(top.left)
                visited.add(top)
            else:
                res.append(top.val)

        return res
```

```
post-order

class Solution:
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        visited = set()
        res = []
        curr = root
        stack = [root]

        while stack:
            top = stack.pop()
            if top not in visited:
                stack.append(top)
                if top.right:
                    stack.append(top.right)
                if top.left:
                    stack.append(top.left)
                visited.add(top)
            else:
                res.append(top.val)

        return res

```

```
pre-order is exceptional in that it doesn't need to be visited twice!

class Solution:
    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        if not root:
            return []
        stack = [root]
        res = []
        curr = root

        while stack:
            top = stack.pop()
            res.append(top.val)
            if top.right:
                stack.append(top.right)
            if top.left:
                stack.append(top.left)

        return res
```

### HEAP NAVIGATION

- when you need to travel through a key in a dict in order,
  make the dict first, then add all keys to an `idx_min_heap`

### LL

- review Reversing
- Getting midpoint
  - either left or right of mid by setting while loop to either
    "while fast and fast.next" or "while fast and fast.next and fast.next.next"
- Merging zigzag in place
  - switch off first and second references while second exists
- Merging two ordered lists
  - use a dummy node, then pick first or second while both exists.
    once out, just add the rest of the other
- Using pre during midpoint logic to get the node before slow.
  - in while loop, pre = slow. slow = slow.next etc..

### BINARY TREES

- None tree is True
- Use max and min to validate
- Level-Order traversal is the same as BFS with queue
- 1 + DFS() for height
- Iterative DFS with stack and visited set when you want to terminate early
  - kth smallest element in bst
- possible to build a tree entirely with pre-order (self, left, right) list
- Technique to use DFS to bring up a target node all the way up.
  - Return Optional[tree] so that it's either None or a new Node.
    Useful for closest ancestor
- Turn a tree into an undirected graph with DFS for some problems,
  then do BFS starting from some node

### GRAPH

- dfs recursive
  - usually needs a visited set, but can get away with mutating the original
    input depending on algo.
- DFS iterative with stack
  - visited logic is necessary, but can get away with mutating the original.
  - Unlike BFS queue, no need to have added set if mutating state
- BFS
  - use a queue and no visited set since there's no need to detect recursive
    visited but needs an "added" set before appending.
  - Logic should be done one previous level
- topological sort
  - used in directed graphs to order from leaves by checking for no neighbors.
  - two sets of sets (`done`, and `in_cycle`)
- clone graph
  - make a dict of all already cloned graphs, and always check to see if
    one exists before appending to neighbors.
- union find
  - helper `getRootParent`
  - rank defaults to 1, parents default to self
  - always add to the higher rank of the root parent and increment root parent rank
- MST
  - minimum spanning tree.
- Prim's Algo
  - a variation of Dijkstra. Don't forget that every heap has the possibility
    to be already visited
- midpoint of a graph has the maximum height. There could only be 1 or 2
  midpoints in a graph. use BFS to delete leaf nodes (indegree = 1) while
  deleting edges until graph len is 2 or less
- Dijkstra's shortest path
  - optimization on WEIGHTED graphs BFS make adj of node: [edge, node],
    make visited set, make minHeap which becomes the queue (dist, node)
    then pop, check visited, then check its neighbors and push that with
    the curr dist + edge

### BIT WISE

- add ints using both XOR and AND
- in Python, negative numbers have unlimited leading 0s.
  use mask if possible use a dist cache and update with min for every heappush
  n & n - 1 will remove the right most "1" . ex. 10111 n & n - 1 -> 1011

### Backtracking

- Subsets, Subsets II
  - To avoid duplicates, sort then increment for the "not take" path until a new value
- Permutation ii
  - hash the nums and loop over keys which are unique.
    Update hash while looping.
    Same trick for (3 x quarters, 2 x pennies get all permutations)

### DP

- dfs to get combinations
  - to get only uniques, in the leave-decision, skip idx until next val. sort first
    usually starts with a decision tree that is 2 \*\* n -> memoized to reduce
    some work -> dp array using same logic
- Unbounded Knapsack is usually easier with one dp array going forward
- Bounded Knapsack will require recursion with memoization, or using dp set
  brute force to get every combination starting with {0},
  then adding val to every existing, OR going backwards
- A square is often a DP problem. Imagine each grid being the top left of
  a square, and fill in the bottom and right edges. Usually calculate with
  right, bottom, and bottom-right

## other example algos

### balanced parens

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

### merge sort

return all array length 1 or less

separate into left and right

make a helper merge

return merge(recursive(left), recursive(right))

### Kadane's algo

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

Notice how at index 7, we cut off all possibilities from the left hand side as it was determined that nothing in the left is useful.

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

    " given an array of positive integers,

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

### permutations

- this first way works, but takes more time `O(n * n * n!)`

```
export function getPermutations(array: number[]): number[][] {
	if (!array.length) return [];
	return recurse(array);
	// helper recursion
	function recurse(array: number[]): number[][] {
		if (array.length === 1) return [array]; // [[4]]
		const head = array[0];
		const perms = recurse(array.slice(1));
		const output: number[][] = [];
		// loop for outer
		for (const perm of perms) {
			// loop inner item length + 1
			for (let i = 0; i <= perm.length; i++) {
				// perm is [3] for ex.
				const rest = [...perm];
				rest.splice(i, 0, head);
				output.push(rest);
			}
		}
		return output;
	}
}
```

- better method
- backtracking! (unswap to restore original state)
- swapping instead of array methods will shave off time and space to `O(n * n!)` from `O(n * n * n!)`

```
export function getPermutations(array: number[]) {
  if (!array.length) return [];
	const output: number[][] = [];
	helper(0, array)
  return output;
	function helper(swapCount: number, array: number[]): void {
		if (swapCount === array.length - 1) output.push([...array]);
		// if swapping is done, push the image
		else {
			// swapcount starts at 0.
			for (let i = swapCount; i < array.length; i++) {
				// swap
				[array[swapCount], array[i]] = [array[i], array[swapCount]]
				// call with i + 1 and new array
				helper(swapCount + 1, array);
				// swap back
				[array[swapCount], array[i]] = [array[i], array[swapCount]]
			}
		}
	}
}
```

walk through

[1,2,3] swapCount = 0

first, swap swapCount with i. The first iteration is a no-op, as they are equal to each other
[1,2,3] (no swap), but increment swapCount to 1
next, same but increment again swapCount to 2
[1,2,3] now that swapCount is len - 1, push that copy as a permutation

backtrack ONE level to count = 1 and image [1,2,3]
now we can swap to [1,3,2] , increment 1 and save image
backtrack to the UNSWAP, [1,2,3] again
backtrack to first level, now swap to [2,1,3] count is 1
[2,1,3] do the first swap (doesn't change) and count is 2, save
[2,3,1] now do a swap, save, and unswap [2,1,3]
back to 1st level, unswap again to original [1,2,3] .. now do final swap between 1 and 3 and repeat

### Quick Sort

```
export function quickSort(array: number[]) {
  // using LAST index as pivot is usually the simplest logic


	return pivot(array, 0, array.length - 1);


	function pivot(array: number[], start: number, end: number): number[] {
		if (start >= end) return array; // baseline - no need to change anything

		const pivotVal = array[end];
		let pivotIdx = start
		for (let i = start; i < end; i++) { // don't loop to last element
			if (array[i] <= pivotVal]) {
				// swap
				[array[i], array[pivotIdx]] = [array[pivotIdx], array[i]]
				pivotIdx++
			}
		}
		// the right most element has been chilling the whole time. The current pivotIdx is pointing to the first
		// element that is NOT correct, so swap those 2 and the pivot point will be in the correct final position
		[array[pivotIdx], array[end]] = [array[end], array[pivotIdx]];

		// now repeat for the 2 left and right arrays NOT including the pivot point itself
		pivot(array, start, pivotIdx - 1)
		pivot(array, pivotIdx + 1, end);
		return array;
	}
}

```

### Trie (let curr)

```
// EXERCISE in Merging Objects

interface TrieNode {
  [key: string]: TrieNode | boolean;
}

// Do not edit the class below except for the
// populateSuffixTrieFrom and contains methods.
// Feel free to add new properties and methods
// to the class.
export class SuffixTrie {
  private root: TrieNode;
  private endSymbol: string;

  constructor(string: string) {
    this.root = {};
    this.endSymbol = '*';
    this.populateSuffixTrieFrom(string);
  }

  private populateSuffixTrieFrom(string: string): void {
    for (let i = 0; i < string.length; i++) {
			this.insertToTrie(i, string);
		}
  }

	private insertToTrie(index: number, string: string): void {
		let curr: TrieNode = this.root;
		for (let i = index; i < string.length; i++) {
			const char = string[i]
			if (!(char in curr)) {
				curr[char] = {};
			}
			curr = curr[char] as TrieNode;
		}
		curr[this.endSymbol] = true;
	}

  public contains(string: string): boolean {
    let node: TrieNode = this.root;
		for (let i = 0; i < string.length; i++) {
			const char = string[i];
			if (!(char in node)) return false;
			node = node[char] as TrieNode;
		}
    return (this.endSymbol in node) && node[this.endSymbol] === true;
  }
}

```

### get digit value (Radix Sort)

- this is the meat of the radix sort
- to start the logic, remember that mod 10 will ALWAYS give you the one's column. To get the other columns, you must first divide and floor by a divider, which is `10 ** {whateverDigit}`

```
let num = 1234;

let divider = 10 ** digit
// digit here is 0 for 1s column, 1 for 10s, 2 for 100s

const digitValue = Math.floor(num / divider) % 10;

```

### quick sort

- remember to use the first index as the pivot, then lp which is pivot + 1 and rp which is end
- recursive will pass in startIdx and EndIdx using the same array repeatedly
- the pivot will swap with the right index at the end of the while loop

```
export function quickSort(array: number[]) {
  // using index 0 as pivot is usually the simplest
	  // otherwise you need one extra flip to position the pivot pointer to 0

	return pivot(array, 0, array.length - 1);


	function pivot(array: number[], start: number, end: number): number[] {
		if (start >= end) return array;
		const pivotIdx = start;
		let leftIdx = pivotIdx + 1;
		let rightIdx = end;
		while (leftIdx <= rightIdx) {
			if (array[leftIdx] < array[pivotIdx]) {
				leftIdx++;
			}
			else {
				if (array[rightIdx] < array[pivotIdx]) {
					[array[leftIdx], array[rightIdx]] = [array[rightIdx], array[leftIdx]];
					leftIdx++;
					rightIdx--;
				}
				else {
					rightIdx--;
				}
			}
		}
		[array[pivotIdx], array[rightIdx]] = [array[rightIdx], array[pivotIdx]];
		pivot(array, start, rightIdx - 1)
		pivot(array, rightIdx + 1, end);
		return array;
	}
}
```

### merge range

- in most range stitching logic, first make ONE list of things based on first value`[1, 3], [2, 4], [2, 3], [4, 2]`
- make a new stack
- loop through the 1 sorted array. If stack is empty, push and increment. Otherwise get top of stack, compare if the currStart is in range, and merge by getting the max of two ends or just push a new value to stack

### time math

- with time and other non mod 10 numbering systems, take the greatest common value (minutes or seconds) instead of trying to separate hours and minutes and seconds.
