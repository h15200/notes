# Data Structures

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
1. making a buffer from that byte size.
1. plug that into the parens of new Int16Array().

the function, new ArrayBuffer() takes in the memory size in bytes as arg and returns a buffer
A buffer is an all purpose object that carries data that can't be accessed directly without a view.

```
var buffer = new ArrayBuffer(6) // since each item of an Int16Array requires 2 bytes, this number has to be a multiple of 2 bytes
var i8View = new Int16Array(buffer)


i8View.byteLength // returns 6

// You can assign the arrays like before i8View[0] = 42. // [42,0,0]
// but you can't use some methods like .pop, .push, Array.isArray().
```

## Sets

ES6 object object is like an array but it can't have duplicate values.
It can have different types of data as long as they are unique.

Sets can be created like this
`const set1 = new Set([1,1,2,3,3,4]) // set1 is [1,2,3,4]`

The .has method checks for items
`set1.has(1) // true set1.has(5) // false`

and a .add method to add items.
`set1.add(5)`
.add will do nothing if the item you're trying to add is already in the set

.size method does <strong>NOT</strong> use parens similar to length
`set1.size`  
note that .size will not count undefined or null
NO length, so no forloops based on length

for of loops will work

`set1.delete(value)`
To remove an item from the set

you can't add multiple unique items in the form of an array or a set, but the spread operator will turn a set into an array.

You can combine any sets or arrays into a new Set like this!

```
const setA = new Set([1,2,3,4,5])
// now you realize you want to make a new set but combine with arrayX to get unique items from both

setA.add([arrayX]) //WILL NOT WORK because setA will simply add one more item which is an array of everything in arrayX

// so, we turn setA back into an array and combine two arrays to make a new Set like so:
const combinedSet = new Set([...setA, ...arrayX])

```

## Tuple

A tuple is an array-like object that stores information about ONE thing. It is usually a mixed data type

// Apartment - number of bathrooms, number of bedrooms, basement exists

[ 2, 3, true]

Tuples have a fixed order of values because the number of bathrooms must match the first element.

## Map

A map stores a key-value pair. In JS, maps are avilable as objects but there are certain limitations,
the main one being the order of insertion is not specified.

In ES6, maps are available as another value-pair data structure with useful methods not available to objects.

Map has no prototypes that interfere and can be used as a purer storage than js objects.
It can also use any type for the key, not just strings!

Map methods. The last two are especially useful

.has(key) - returns boolean
.get(key) - returns the value associated with key
.set(key, value) - inserts a new key value pair
.delete(key) - removes key along with its value
.clear() - removes all keys and values
.entries() - returns an array of all keys in INSERTION ORDER!
.values() - returns an array of all values in INSERTION ORDER!

```
const myMap = new Map();
myMap.set('Patti', 'Awesome');
```

## Hash Table

A tash table is an array of data where the index of the data is built in to the key.
Ex- database of users. User's first name as ASCI values added up, then modulo by a number might return the index.
Since it's relatively easy to get the index, it is considered constant time O(1) and very efficient.

Sometimes two users might end up in the same index (collision) but you can add it as a linked list to the same index.
A simpler way to implement is to add both key-value pairs.

So the concept without thinking about collision is..

empty array []. Let's say we want to use 100 slots
you want to add a key value pair "color", "blue"  
since the key is color, have a hashing algorithm like converting to ascii, adding them up, and modulo by the array length, 100
"color" ends up being a number, that ends up being the index of the array, so array[hash of key] contains [key, value]

If you need to think about collision, then you have to consider if somebody else adds the same key, "color", you'll end up with the
same index.

So it might be better if you just store an object at index [hash('color')] of the array so it's more like
[ {}, {}, {}, {color: 'blue', anotherKey: 'hello' }]

## Linked List

Is a linear collection of nodes that go in one direction.
Each node contains 2 pieces of information - its own value, and the pointer to the next linked list.
It can hold any type of data.

The next element of a node is initialized to null until it's set.

The first item is called the head

Implementation - to add a new node, you have to recursively look for a node where the next value is null and assign the new node to that. You can't use indexes, you must always start at the head and continue calling next until the next value is 'null', which means it's the end of the linked list

to remove an element, you have to start at the head, and rather than deleting that node, you simply link the previous node to the node 2 links in front and exclude the current.

```
function LinkedList() {
  var length = 0;
  var head = null;

  var Node = function(element){
    this.element = element;
    this.next = null;
  };

  this.size = function(){
    return length;
  };

  this.head = function(){
    return head;
  };

  this.add = function(element){
    var node = new Node(element);
    if(head === null){
        head = node;
    } else {
        var currentNode = head;

        while(currentNode.next){
            currentNode  = currentNode.next;
        }
        currentNode.next = node;
    }
    length++;
  };

  this.remove = function(element, previous = head, current = head.next ){
  if (element === head.element) {
    head = head.next;
    length--;
  }
  else if (element === current.element) {
    previous.next = current.next;
   length--;
  }
  else if (current.next === null) {
    return null
  }
  else {
    this.remove(element, previous = previous.next, current = current.next)
  }
  };
}
```

### Doubly linked lists

A Doubly Linked List has a next AND a previous element stored in each node.
It allows both way travel but takes up more memory.

often notated like this

null -> head/node -> node -> tail/node -> null

## Tree

Starts with a root node up top and splits into children.

A subtree refers to all the descendants of a specified node.
Branches may be referred to as edges
Leaves are nodes that don't have children

Types include binary trees and tries.

### Binary Tree (Binary Search Tree in particular)

Unlike a linked list which has Nodes, a BST should only have ONE class. Every leaf IS a BST

A binary tree can only have 2 branches per node
The branches of a binary tree are ordered such that the left branch has a smaller value than the parent,
and the right branch has a greater value than the parent node

Logarithmic Time comlexity - Means at best, the time can be halved. The binary tree will be travesing based on
the value of the current node, so it has a CHANCE of doing everything in half the time.

If the tree is unbalanced, at worst, it could still take linear time.

In strict computer science, an empty binary tree that has a root of null is still a valid binary tree

### Binary Tree height (sometimes called depth)

Maximum height is the largest distance between a root and a leaf
Minimum height is the smallest distance between a root and a leaf.

In a balanced tree, the max and min height will vary at most by 1.

The algorithm I came up with to find the height was to build an array of nodes for every height, loop through the array and send all available left and right branches to the next arr, determine if leaf or not and call the next array with the same function recursively.

### Tree Search Methods (Depth first, Breadth first

In a depth-first search, a given subtree is explored as deeply as possible before starting a search on another subtree.

Three Types of depth-first searches. All of these use recursive algorithms

```
                1
           2         3
        4     5          6
```

1. In order - Begin at left subtree(2), go deeper if there is another subtree (node with more branches). Get left node, root, then right node. Back up to root (of the subtree you were on) return that, then the right subtree of that root.
   ex from top- 4, 2, 5, 1, 3, 6
2. Pre order - Return values from the root and end in the leaf

ex - 1, 2, 4, 5, 3, 6

3. Post order - Return values from the leaf and end in the root for each subtree
   ex - 4, 5, 6, 2, 3, 1

### Breadth first search

NOTE!!

Breadth first searches can be solved using a queue in MOST cases!!

Get all the nodes in a certain depth first by having a queue that keeps track and loops through everything

Left to right - for above example would be 1,2,3,4,5,6
Right to Left - for above would be 1, 3, 2, 6, 5, 4

### Deleting from a tree

Deletion is difficult because of the links before and after.

One of three things will happen.

1. If deletion target is a leaf node, delete the node, and nullify parent's left or right.. wherever the target was
2. Target has one child - Target is removed, the parent target link is relinked to the single child of the deletion.
3. Target has two children - Target is removed, then you have to figure out how to link the two children.

Removing a node with two Children is the most difficult process out of the three.

there are two possible methods.

You can either get the lowest value in the right subtree of the target and replace with target
Or
Get the highest value in the left subtree of the target and replace with target

Here's an example using the 1st method of finding the replacement node in the right subtree which has the lowest value

                10
          5                 20
                         15     30
                   12
                      13

If target is value 10, the root, you must go through the entire subtree that starts with value 20.
from there, you'll see that 12 is the lowest.
Note that the replacement node will at MOST have 1 child. If it had two nodes, it wouldn't be the smallest value
root 10 becomes root 12
the new root, 12.right is still 20 as before
We must now delete where 12 was
12's old parent, 15 will either be null (if 12 was a leaf) or take on 12's child as it's child that used to be 12

new structure is

             12
    5                   20
                    15         30
                13

## Merge Sort Time complexity

A merge sort is O(NlogN) because if you break down the tree into halves,
you get levels of N, N/2, N/4, N/8 and on each level, you are "stitching" them. Stitching each level have different amounts of items to sort (only 2 at the bottom level, the entire N at the top level) but average out to N. Since you're stitching on every level of the tree, there are logN levels of the tree, so it's N on each logN level.

## Trie

A Trie is another type of tree
Ordered search tree commonly used to hold strings
They are good at storing sets of data when many keys will have overlapping prefixes, like words in a dictionary.
Unlike binary trees, nodes are not associated with values but the storage method is the PATH we take to make that string.

For example, to store "patti" in a trie, you must travel to nodes p, a, t, t, and i. The path is then stored
Each node can store many children as well as the

Implementation:

all nodes have a keys collection which is an object or a map with key-value pair of char, and another node.
all nodes have an isEnd boolean to signify a word

a tree will have a root that is a node which doesn't have a value but with a key and isEnd to false.

add function ('hi') will first look through the keys of the root, if 'h' doesn't exist, make one, and then now look into that 'h' node, and its keys, and add 'i' if it doesn't exist along with the isEnd true on the i node.

a search function will look through keys to see if a word exists

## Binary Heap

An implementation of a priority queue. Array which represents a nearly complete binary tree. Binary (not binary SEARCH tree)

The heap property - Specifies a relationship between a parent and child node
Max heap = all parent nodes are greater than OR equal to their child nodes
Min heap = all parent nodes are less than OR equal to their child nodes

The left and right children don't have to relate to each other in any way, as long as they satisfy the value relatiopnship with the parent node.

Although it's a tree and can be represented like this
ex of Binary Min Heap Tree

```
            10
      20        25
  29     37     40      29
```

It is much better to represent nodes as an array
`[10, 20, 25, 29, 37, 40, 29]`

This is because you can always figure out the index of each node and the parent.
since index 0 is the root, index 1 is always the left child of the root. index 2 is the right child of the root.

More generally, if you refactor the math,

indexOfParent _ 2 + 1 = left child
indexOfParent _ 2 + 2 = right child

And you can reverse the math to get a parent from the child with:
`Math.floor(indexOfChild / 2)`

We can make the math work even easier if you add a null item in the array
`[null, 10, 20, 25, 29, 37, 40, 29]`

NOW, an element's left child is always `i * 2`
and right child is `i * 2 + 1`

An element's parent is `Math.floor(i / 2)`

This array with the null in the top BEFORE the root is often how a max heap or min heap is represented!

### time complexity

MAKING a max or min-heap from an array is O(n) because you start from n/2 (all n/2 + 1 to n-1 have no children). At the lowest branch level (with children), it's constant time swapping because you only compare against direct children and there are no more grandchildren. At the highest level n, you have logN levels to compare to children, grandchildren, grandgrandchildren etc...

When you count each row, this adds up to linear time mathmatically.

To finish the sort, we extract min from a min-heap N times

Finding the min is constant time
Swapping min to end is constant time
Dropping the last node is constant time

After the drop, re-shaping the heap again is O(logN) as you swap from the head down each level.

Total time is O(nLogn), the same as merge sort

### Sift up/ Sift down

Important to understand and implmement siftUp / siftDown methods.
siftDown is what's used in makeHeap, as well as remove(). You compare from the current to the children, swap if necessary, then check the swapped node.

In siftUp, it is used in insertion. You add to the END of the heap,then look to the parent to see if the tree is valid. If not, swap, and look the new parent etc..

### Inserting into a max heap

During insertion, it is important to always maintain the heap property. For a max heap this means the root element should always have the greatest value in the tree and all parent nodes should be greater than their children. For an array implementation of a heap, this is typically accomplished in three steps:

Add the new element to the end of the array.

If the element is larger than its parents, switch them.

Continue switching until the new element is either smaller than its parent or you reach the root of the tree.

### Removing from a max heap

Very similar logic to inserting into a max heap

To remove from a max heap, you usually remove the greatest value, which is the root.

1. Remove the root
2. The last element in the heap becomes the root
3. check the root against its children. If child is greater, swap biggest child with root.
4. check the children of that swapped child. Repeat same process

### Heap Sort

A heap sort uses a min heap, which means the root is always the smallest number.

Heap sort takes an unsorted array, adding each item in the array into a min heap, then extracting every item out of the min heap into another array. The min heap structure will insure that the new array is in least to greatest value, and is O(nlog(n)), making it one of the most efficient sorting algorithms.

## Note; What's interesting is that the array version of a min heap is NOT in least to greatest order

[null, 2, 4, 34, 10 ] is a valid min heap because in tree form,

```
        2
   4          34
10
```

Every child is bigger than the parent.

It is the REMOVE method of the min heap that allows for all items coming OUT of the heap to be in exact order from least to greatest.

## Graph

A graph is usually used to show a network.

Consists of nodes and edges. Nodes connect to other nodes via edges.

## Adjacency List

One way to represent a graph.
A bulleted list where the left represents the current node and the right is all the connected nodes

```
Node1: Node2, Node3
Node2: Node1
Node3: Node1
```

This, in js, can be represented as an object

```
const graph = {
  Node1: ["Node2", "Node3"],
  Node2: ["Node1"],
  Node3: ["Node1"]
}
```

That is sometimes shortened to an array with an assumed index if there are no key string values

```
// index 0 is node0, index 1 is node1
const graph = [
  [1,2],
  [0],
  [0]
]
```

Notice how the above nodes are connected to each other on both ends.
1 to 2, 2 to 1
1 to 3, 3 to 1

This makes that particular adjency list an `undirected graph`

A `directed graph` will have a directional edge that only goes one way

## Adjencency Matrix

Another way to represent a graph in a 2D array

The rows and columns represent nodes. the value 0-1 means no edge, or an edge exists

The same example from above would be represented like so:

```

   1 2 3
   -----
1  0 1 1
2  1 0 0
3  1 0 0
```

This can represent both directed and undirected graphs. This one above is undirected, as the relationship is reciprocal.

Unlike adjency lists, you must have the same number of rows and columns to represent nodes.

In js, this is represented with a nested array

```
const adjacencyMatrix = [
  [0,1,0],
  [0,0,1],
  [0,0,0]
]

```

Notice how that one above is a directed graph as node0 has an edge to node1, but node1 doesn't point back to node0

### Weights

Graphs can have different weights on their edges.
When there are more than 0 and 1 representing edges, they represent weights of each edge.

## Incidence Matrix

Another graph represenatation type

In an incidence matrix, the Rows are nodes and the Columns are edges
The rows and columns can be different lengths
A '1' represents yes and '0' no
Can represented both undirected and directed graphs

```
    1 2 3
--
1   1 0 1
2   0 1 0
3   1 1 0
4   0 0 1
// 4 nodes, 3 edges. node 1 - 3, 2 - 3, 1-5. Look on each column for matching pair
```

It's easy to get confused.. remember, the ROW is a particular EDGE, so seeing one '1' doesn't tell you about the destinatino of that edge. It just means that edge EXISTS. You go down the same column to find another '1' to find WHERE that edge is connecting to.

In js, it is again an array of arrays
The "labels" of row and column are assumed

```

const incidenceMatrix = [
[ 1, 0, 1 ],
[ 0, 1, 0 ],
[ 1, 1, 0 ],
[ 0, 0, 1],
]

```

A directed matrix will show the in and outs with 1 and -1. [-1] means LEAVING that node and [1] means entering. Each edge should have a [1], [-1] pair

```

const incidenceMatrixDirected = [
[ -1, 0, 1],
[ 0, 1, 0],
[ 1, -1, 0],
[ 0, 0, -1]
]

```

A number greater than 1 represents weight

## Graph searches (breadth-first, depth-first)

A search on a graph structure is used to get the distance between ALL nodes and an input node.
If not reachable, it defaults to Infinity
A breath first search will explore the root and all of its neighbor roots, and then those neighbors
A depth first search will explore one neighbor all the way until it reaches a leaf

// breadthFirst(graph, 1) - what is the distance form this root to all nodes in this graph
// returns something like { 0:1, 1:0, 2:infinity, 3:3 }

## Breath first graph search

Tools for keeping track

1. a queue which initializes as the first node you're visiting. It doesn't matter which
2. a doneList which has the nodes that are 'done'

Steps

1. Queue starts off as one node. Base case is queue length 0
2. Do whatever you need to do at queue[0], then check it's neighbor edges. If those edge nodes do NOT exist in the
   doneList, push() them to the queue
3. After you've added all neighbor nodes, shift() the queue INTO the doneList
4. Recursively go into the new queue[0]

## Sorts

### Bubble sort - just keep swapping and iterating

to optimize, use a didSwap boolean and only run it if the previous iteration had a swap

### Insertion sort - use pointer,

loop left to right, but for every time something is unsorted, sort that element ALL the way to the left using pointer j. Same time complexity as bubble sort, but can be done in one loop

## Getting the midpoint of a linked list

The most efficient way is to make two pointers

```
let i = this.head
let j = this.head
while (j !== null && j.next !==null) {
  i = i.next;
  j = j.next.next;
}
return i;
```

Basically have the second pointer tragerse twice as fast.
