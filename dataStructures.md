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

## Tree

Starts with a root node up top and splits into children.

A subtree refers to all the descendants of a specified node.
Branches may be referred to as edges
Leaves are nodes that don't have children

Types include binary trees and tries.

### Binary Tree (Binary Search Tree in particular)

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

1. In-order - Begin at left subtree(2), go deeper if there is another subtree (node with more branches). Get left node, root, then right node. Back up to root (of the subtree you were on) return that, then the right subtree of that root.
   ex from top- 4, 2, 5, 1, 3, 6
2. Pre-order - Return values from the root and end in the leaf

ex - 1, 2, 4, 5, 3, 6

3. Post-order - Return values from the leaf and end in the root for each subtree
   ex - 4, 5, 6, 2, 3, 1

### Breath first search

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
