# Data Structures

In C, you have to declare the data type in a variable to allocate the right amount of bytes depending on the type

signed char, unsigned char, int, long int, unsigned int, float, long float, etc...

When an array is declared with 4 elements, it creates 4 consecutive bytes in memory. When an additional item is needed, you have to reassign a brand new array in a different, 5 consecutive byte location in memory. In JS, this is all happening under the hood when you push a new element to an existing array.

## strings

- `ASCII` (either 128 for standard, or 256 for extended) which is mapped to an int and only includes english alphabet and special chars. Uses 1 byte (8 bits) to store

- `Unicode` is a superset of ASCII, so the first 128 chars correspond one-to-one with ASCII.
  - UTF (8, 16, 32) refers to Unicode Encoding.
    - UTF-8 will use 1 - 4 bytes
    - UTF-16 2 - 4 bytes
    - UTF-32 will always use 4 bytes
  - The vast majority uses Utf-8, meaning it uses 8 bits (1 bytes) for encoding. about 97% of chars used on the web are utf-8 encoded.
  - utf-8 encoding is compatible with ASCII, so ascii chars are technically also utf-8.

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

## Sets - subset of hashtable

- since it's implmented with a hashtable, get, set, add operations are all O(1)

ES6 object object is like an array but it can't have duplicate values.
It can have different types of data as long as they are unique.

Sets can be created like this
`const set1 = new Set([1,1,2,3,3,4]) // set1 is [1,2,3,4]`

The .has method checks for items
`set1.has(1) // true set1.has(5) // false`

and a .add method to add items.
`set1.add(5)`
.add will do nothing if the item you're trying to add is already in the set

.size method is a getter and does <strong>NOT</strong> use parens. follows similar syntax to array.length
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

```

// [ 0: [[], [],], 1 [[key, val], [key, val] ]]

class Hash<T> {
  size = 53;
  table: [string, T][][] = new Array(this.size);
  protected hash(key: string) {
    let total = 0;
    for (let i = 0; i < Math.min(key.length, 100); i++) {
      const salt = 13;
      total = (total + key.charCodeAt(i) * salt) % this.size;
    }
    return total;
  }
  set(key: string, val:T): void {
    // console.log('this.table', this.table)
    const idx = this.hash(key);
    // console.log('hash is', idx)
    // console.log('this.table[idx]', this.table[idx])
    this.table[idx] ? this.table[idx].push([key, val]) : this.table[idx] = [[key, val]] ;
    console.log('this.table', this.table)

  }


  get(key: string): T | null {

    const hash = this.hash(key);
    for (const [itemKey, itemVal] of this.table[hash]) {
      if (itemKey === key) return itemVal;
    }
    return null;
}

keys(): string[]{
  const output = new Set();
  for (let i = 0; i < this.table.length; i++) {
    if (this.table[i]) {
    for (let j = 0; j < this.table[i].length; j++) {
      output.add(this.table[i][j][0])
    }

    }
  }
  return Array.from(output as Set<string>);
}

values(): T[] {
    const output = new Set();
  for (let i = 0; i < this.table.length; i++) {
    if (this.table[i]) {
    for (let j = 0; j < this.table[i].length; j++) {
      output.add(this.table[i][j][1])
    }

    }
  }
  return Array.from(output as Set<T>);
}

}


const hash = new Hash();
hash.set("pink", "23409234")

hash.set("orange", "539482")
console.log(hash.values())
```

## Linked List

Is a linear collection of nodes that go in one direction.
Each node contains 2 pieces of information - its own value, and the pointer to the next linked list.
It can hold any type of data.

The next element of a node is initialized to null until it's set.

The first item is called the head

Implementation - to add a new node, you can interatively look for a node where the next value is null and assign the new node to that. You can't use indexes, you must always start at the head and continue calling next until the next value is 'null', which means it's the end of the linked list

to remove an element, you have to start at the head, and rather than deleting that node, you simply link the previous node to the node 2 links in front and exclude the current.

- common algo tool. Use recursion to count the size (go to end, return -1 or 0, then add 1). As a side effect of that function, return or delete the node

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

```
class MaxHeap {
  heap: number[] = [];
  add(val: number): void {
    // add to first available (last of array)
    // if added node is bigger than parent, swap
    this.heap.push(val);
    let newIndex = this.heap.length - 1; // intitialize i of new node
    let parentIndex = Math.floor((newIndex - 1) / 2 ); // initialize parent of new node
    // edge case if len is 1, do nothing
    while (parentIndex >= 0 && parentIndex !== newIndex) {
      if (this.heap[parentIndex] < this.heap[newIndex]) {
        [this.heap[parentIndex], this.heap[newIndex]] = [this.heap[newIndex], this.heap[parentIndex]];
        newIndex = parentIndex;
        parentIndex = Math.floor(newIndex / 2);
      }
    }
  }
  remove(): number | null {
    if (!this.heap.length) return null;
    const removed = this.heap[0];
    if (this.heap.length === 1) return removed; // don't do anything if 1 index as it will pop and push the same ele
    // swap first and last, then remove last
    [this.heap[0], this.heap[this.heap.length - 1]] = [this.heap[this.heap.length - 1], this.heap[0]]
    this.heap.pop();
    // compare curr (1st index) with children. if any are bigger than curr, swap with bigger child. repeat
    let currIndex = 0;
    let leftChild = currIndex * 2 + 1;
    let rightChild = currIndex * 2 + 2;
    while (currIndex < this.heap.length && (this.heap[rightChild] || this.heap[leftChild])) {
      if (this.heap[currIndex] < Math.max(this.heap[leftChild], this.heap[rightChild])) {
        if (this.heap[leftChild] > this.heap[rightChild]) {
          // swap with leftChild
          [this.heap[currIndex], this.heap[leftChild]] = [this.heap[leftChild],this.heap[currIndex]]
          currIndex = leftChild;
          leftChild = currIndex * 2 + 1;
          rightChild = currIndex * 2 + 2;
        } else {
          // swap with rightChild
             [this.heap[currIndex], this.heap[rightChild]] = [this.heap[rightChild],this.heap[currIndex]]
          currIndex = rightChild;
          leftChild = currIndex * 2 + 1;
          rightChild = currIndex * 2 + 2;
        }
      }
    }
    return removed;
  }
}

const heap = new MaxHeap();
heap.add(5);
console.log(heap.heap)
heap.add(6);
console.log(heap.heap)
heap.add(7);
console.log(heap.heap)
heap.add(10);
console.log(heap.heap)
heap.remove();
console.log(heap.heap)

  // [5] => [6, 5] => [7, 5, 6] => [10, 7, 6, 5] => [7,5,6]
```

- a priority queue is implemented WITH a heap. It's basically the same code as above, but instead of using the `value` as the parameter, it will take another data structure like node which will have a value and priority (or weight). the logic will just use `node.priority` and make a minHeap based on priority (if priority 0 is considered greatest) or maxHeap (if higher weight means higher priority)

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

- depth first can be done recursively or iteratively with a stack. these two methods will have different ordering of visited vertices, but will both be valid depth first searches.

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

- code implmentation example

```
class Graph {
  adjacencyList: {[key: string]: string[]}  = {};
  // O(1)
  addVertex(vertex: string): null | void {
    // if vertex already exists, null
    if (this.adjacencyList[vertex] !== undefined) return null;
    this.adjacencyList[vertex] = [];
  }
  // O(1)
  addEdge(vertexA: string, vertexB: string): null | {[key: string]: string[]} {
    // not found
    if (this.adjacencyList[vertexA] === undefined || this.adjacencyList[vertexB] === undefined) return null;
    if (!this.adjacencyList[vertexA].includes(vertexB)) this.adjacencyList[vertexA].push(vertexB);
    if (!this.adjacencyList[vertexB].includes(vertexA)) this.adjacencyList[vertexB].push(vertexA);
    return this.adjacencyList;
  }
  // O(E) for splice
  removeEdge(vertexA: string, vertexB: string): null | void {
    if (this.adjacencyList[vertexA] === undefined && this.adjacencyList[vertexB] === undefined) return null;
    if (this.adjacencyList[vertexA]) this.adjacencyList[vertexA] = this.adjacencyList[vertexA].filter(edge => edge !== vertexB)
    if (this.adjacencyList[vertexB]) this.adjacencyList[vertexB] = this.adjacencyList[vertexB].filter(edge => edge !== vertexA)
  }
  // O(1) for removing hash key, O(V + E) for deleting edge
  removeVertex(deleteVertex: string): boolean {
    // not found
    if (this.adjacencyList[deleteVertex] === undefined) return false;
    // loop through the delete vertex for all edges (works only for undirected graphs) OR just loop through entire graph like here
    for (const vertex in this.adjacencyList) {
      if (this.adjacencyList[vertex].includes(deleteVertex)) this.removeEdge(vertex, deleteVertex)
      }
    delete this.adjacencyList[deleteVertex];
    return true;
  }

  // dfs in graph - checkout the node, then all of it's neighbors
  dfsRecursive(vertex: string): null | string[] {
    if (!vertex) return null; // edge case
    const visitHash:{[key: string]: boolean} = {};
    // for this dummy logic just store all the vertex vals
    const valuesList: string[] = [];
    recurse(vertex, this.adjacencyList);
      function recurse(vertex:string, list:{[key: string]: string[]}):void {
        valuesList.push(vertex);
        visitHash[vertex] = true;
        list[vertex].forEach((neighbor: string) => {
          if (!visitHash[neighbor]) recurse(neighbor, list)
        })
      }
  return valuesList;
  }
  // use a stack and collect data backwards for each neighbor
  dfsIterative(vertex: string): null | string[] {
    if (!vertex) return null;
    const visitHash: {[key: string]: boolean} = {};
    const valuesList: string[] = [];
    const stack: string[] = [vertex];

  while (stack.length) {
    const curr = stack.pop();
    // curr will always exist, so use post !
    valuesList.push(curr!);
    visitHash[curr!] = true;
    for (let i = this.adjacencyList[curr!].length - 1; i >= 0; i--) {
      if (!visitHash[this.adjacencyList[curr!][i]]) {
        visitHash[this.adjacencyList[curr!][i]] = true;;
        stack.push(this.adjacencyList[curr!][i]);
      }
    }
  }
  return valuesList;
  }
// only iterative for breadth first
  bfs(vertex: string): null | string[] {
    if (!vertex) return null;
    const visitHash: {[key: string]: boolean} = {[vertex]: true};
    const valuesList: string[] = [];
    const queue: string[] = [vertex]; // shorthand queue. pretend shift is O(1)
    while (queue.length) {
      const curr = queue.shift();
      valuesList.push(curr!); // ! after value means value definitely exists
      this.adjacencyList[curr!].forEach(neighbor => {
        if (!visitHash[neighbor]) {
          visitHash[neighbor] = true;
          queue.push(neighbor);
        }
      })

    }
    return valuesList;
  }
}

const graph = new Graph;
graph.addVertex("a");
graph.addVertex("b");
graph.addVertex("c");
graph.addVertex("d");
graph.addVertex("e");
graph.addVertex("f");
graph.addEdge("a", "b");
graph.addEdge("a", "c");
graph.addEdge("b", "d");
graph.addEdge("c", "e");
graph.addEdge("d", "e");
graph.addEdge("e", "f");

      /*

              a
            /   \
          b       c
          |       |
          d   -   e
           \     /
              f
      */


console.log(graph.dfsRecursive("a"))
console.log(graph.dfsIterative("a"))
console.log(graph.bfs("a"))


```

### Dijkstra shortests path

- make 3 storages for isVisited, shortestPath, and previousVertex
- initiate shortestPath to 0 for starting node

- pick the node that has the shortest path to visit AND is not visited yet
  - in that node, see if the neighbors are visited
  - if not, check the new shortest distance using current node's shortest and add new edge
    - if this is a new shortest path, update it and also update previousVertex
  - once all neighbors are visited, mark this node as visited
- when the node with the shortest path IS the destination, break out of loop

- shortestPath data structure should be some kind of min heap priority queue

```
class N {
  connections: N[] = [];
  constructor(public value: string) {}
}

class Graph {
  collection: {[key: string]: {node: string, weight: number}[]} = {};

  addVertex(val: string): void {
    this.collection[val] = [];
  }

  addEdge(nodeA: string, nodeB: string, weight: number): void {
    if (this.collection[nodeA] && this.collection[nodeB]) {
      this.collection[nodeA].push({node: nodeB, weight});
      this.collection[nodeB].push({node: nodeA, weight})
    }
  }
}

const graph = new Graph();
graph.addVertex("a")
graph.addVertex("b")
graph.addVertex("c")
graph.addVertex("d")
graph.addVertex("e")
graph.addVertex("f")
graph.addEdge("a", "b", 4)
graph.addEdge("a", "c", 2)
graph.addEdge("b", "e", 3)
graph.addEdge("c", "d", 2)
graph.addEdge("c", "f", 4)
graph.addEdge("d", "e", 3)
graph.addEdge("d", "f", 1)
graph.addEdge("e", "f", 1)

console.log(dijkstraShortest('a', "e", graph))

function dijkstraShortest(startVal: string, endVal: string, graph: Graph): string[] {
  // initiate three objects
  const isVisited: {[key: string]: boolean} = {};
  const shortestPath: {[key: string]: number} = {}
  const previousNode: {[key: string]: string} = {};

  for (const key in graph.collection) {
    if (key === startVal) {
      shortestPath[key] = 0; // starting point will have distance of 0
    } else {
    shortestPath[key] = Infinity;
    }
  }

  /*
  - pick the node with shortestDistance to visit first
    - for each of this node's neighbor (that's not visited yet), see if the shortestPath can be updated
      - if yes, also update the previous table
    - add to isVisitedNode, repeat by choosing new node to visit based on shortestDistance
  - stop when the smallest unvisited node in shortestDistance is the destination
  */

  while (true) {
    let nodeToVisit: string;
    let minDist = Infinity;
    for (const key in shortestPath) {
      if (!isVisited[key] && shortestPath[key] < minDist) { // make sure they are unvisited
        minDist = shortestPath[key];
        nodeToVisit = key;
      }
    }
    if (nodeToVisit! === endVal) {
      break;
    }
    for (const {node, weight} of graph.collection[nodeToVisit!]) {
      // if not visited, measure the neighbors
      !isVisited[node] && measureAndUpdate(nodeToVisit!, node, weight);
    }
    isVisited[nodeToVisit!] = true;
  }
    // return a shortest path
    const path = [endVal];
    let prev = previousNode[endVal]
    while (prev) {
    path.push(prev);
    prev = previousNode[prev];
    }
    return path.reverse();



  function measureAndUpdate(originNode: string, destinationNode: string, weight: number): void {
    if (weight + shortestPath[originNode] < shortestPath[destinationNode]) {
      shortestPath[destinationNode] = weight + shortestPath[originNode];
      previousNode[destinationNode] = originNode;
    }
  }
}
```

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

## Sorts

### Bubble sort - just keep swapping and iterating T: O(N^2), S: O(1)

to optimize, use a didSwap boolean and only run it if the previous iteration had a swap

### Insertion sort - use pointer, T: O(N^2), S: O(1)

loop left to right, but for every time something is unsorted, sort that element ALL the way to the left using pointer j. Same time complexity as bubble sort, but can be done in one loop

- note how this will be optimal to sort data that keeps adding to an already sorted data. Selection sort will not have this advantage as the whole thing needs to run every time a new element is introduced.

Basically have the second pointer tragerse twice as fast.

### Selection sort T: O(N^2), S: O(1)

- get the min of entire array, swap with first index. repeat for 2nd index

### Merge Sort T: O(n logn), S: O(n) for extra array

A merge sort is O(NlogN) because if you break down the tree into halves,
you get levels of N, N/2, N/4, N/8 and on each level, you are "stitching" them. Stitching each level have different amounts of items to sort (only 2 at the bottom level, the entire N at the top level) but average out to N. Since you're stitching on every level of the tree, there are logN levels of the tree, so it's N on each logN level.

### Quick sort T: O(n logn), S: O(log n)

- best case TIME is nLogn but worst case is n^2 since pivot point can yield no left or right subarray
- in the same logic, best case SPACE is O(logN) for recursion stack but could be O(n) if pivot is unbalanced

- like merge sort, usually implemented with recursion
- same base case.. if arr.len is <= 1, it's sorted
- pick a random pivot point (usually at index 0). put all numbers less than pivot such that the array is
  [...all nums below pivot, pivot, ...all nums above pivot]
- key! Do it in PLACE for O(1) space. keep track of pivotIndex
- return the concat array of 1. recurse(arr.slice(0, pivotIndex)), 2. arr[pivotIndex] (this is in place) 3. recurse(arr.slice(pivotIndex + 1))

ex- logic is good, but space is O(n) since we are passing in different arrays in each stack

```
function quickSort(arr: number[]): number[] {

    if (arr.length <= 1) return arr;
    // order the array IN PLACE so it's [less than pivot unordered, pivot, greater than pivot unordered]
    // then split that into left [less than pivot], arr[pivotIndex] (this is sorted!), [greater than pivot] and run recursively on both and add

    // [3, 4, 6, 1] keep track of pivot index, 0;

    const pivotVal = arr[0];
    let pivotIndex = 0;
    for (let i = 1; i < arr.length; i++) {
      if (arr[i] < pivotVal) {
        let curr = i;
        while (curr !== pivotIndex) {
          // if a num is less than pivotIndex (3 in this case), swap until the element is ONE left of current pivot (the curr pivotIndex position), increase pivotIndex
          [arr[curr], arr[curr - 1]] = [arr[curr - 1], arr[curr]]
          curr--;
        }
        pivotIndex++;
      }
    }

    return [...quickSort([...arr.slice(0, pivotIndex)]), arr[pivotIndex],...quickSort([...arr.slice(pivotIndex + 1)])]
}

console.log(quickSort([5,17,1,7,0, 3, -3]))
```

- better optimization to just use indices. now the space complexity will just be (logN) at best to account for the recursive call stack

```
function quickSort(arr: number[], left: number = 0, right: number = arr.length - 1): number[] {
  // same as before, but now only pass in indices to make space O(1)
    if (left < right) {
      const pivotVal = arr[left];
      let pivotIndex = left;
      for (let i = left + 1; i <= right; i++) {
        if (arr[i] < pivotVal) {
          let curr = i;
          while (curr !== pivotIndex) {
            [arr[curr], arr[curr - 1]] = [arr[curr - 1], arr[curr]]
            curr--;
          }
          pivotIndex++;
        }
      }
      console.log('left', left, 'pi', pivotIndex)
      quickSort(arr, left, pivotIndex -1); // not a return statement. just mutating left side
      quickSort(arr, pivotIndex + 1, right);
    }
    return arr; // because of top level conditional, this will only run after all arrays have been sorted

}

console.log(quickSort([5,17,1,7,0, 3, -1]))
```

## Radix Sort T: O(n + k (length of numbers)), S: O(n + k)

- All of the previous sorts (bubble, insertion, selection, merge, quick) are grouped under `Comparison Sorts` Comparison Sorts will at best have a time complexity of O(n Log(n)). In THEORY, can be faster although under the hood it may not be an improvement on quick sort.

- if bound by certain contrainsts (only integars), other sorting algorithms can be faster by using an alternate method and NOT comparing values

- in a radix sort, you just repeatedly do O(n + k) operations.

  - first, make 10 buckets from 0 - 9
  - go to the righter most bit (digit), and place then in buckets of queues
  - dequeue items out of the buckets in order to re-order array
  - do the same for 2nd digit (10's column), putting all single digit numbers in the 0 bucket
  - repeat until highest digit is sorted

- it never makes a value to value comparison, but simply hashes them into buckets per pass, making it digits x n time complexity, and O(1) space (10 buckets is a constant, so slash to 1)
