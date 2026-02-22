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
  ```
  ROW, COL = 5, 4     # 5 rows, 4 cols
  matrix = [["init_val" for _ in range(COL)] for _ in range(ROW)]
  ```
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
  - usually use 2 pointers (left index in while loop, right pointer for loop), pinning l = 0 and manually incrementing
    l for unhappy path. Note that left will often go above r.
  - 2 general patterns. When a problem asks to get a MAXIMUM window, you want to shrink the window from left while condition NOT met
  - if it asks for a MINIMUM window, you need to shrink from the left while condition met
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

#### Construct tree from level ordered values with BFS (generally much easier than iterative DFS below)

- used in Serialize and Deserialize Binary tree
- when serializing, make sure to also push "None" nodes
- when deserializing, use a simple pointer that increments every time left and right is assigned. the queue should
  only contain the latest node

```
class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        if not root:
            return ""
        # level ordered nodes from left to right
        q = deque([root])
        res_l: List[str] = []
        while q:
            node = q.pop()
            if not node:
                res_l.append("None")
            else:
                res_l.append(str(node.val))
                q.appendleft(node.left)
                q.appendleft(node.right)

        return ",".join(res_l)







    def deserialize(self, data):

        data = data.split(",")
        # data is a list of strings including "none" and digits that denote node values
        root = TreeNode(int(data[0]))
        q = deque([root])
        idx = 1

        while q and idx < len(data):
            node = q.pop()
            if data[idx] != 'None':
                node.left = TreeNode(int(data[idx]))
            idx += 1

            if data[idx] != 'None':
                node.right = TreeNode(int(data[idx]))
            idx += 1
            if node.left:
                q.appendleft(node.left)
            if node.right:
                q.appendleft(node.right)

        return root
```

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
Controlled iterative InOrder

curr = root
stack = []
while curr:
    stack.append(curr)
    curr = curr.left

# adds all left side nodes to stack initially

# helper function

node = stack.pop()

# get the right side of this node
curr = node.right
while curr:
    stack.append(curr)
    curr = curr.left



return node

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

[1
