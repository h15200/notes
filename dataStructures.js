// // Using typed arrays
// // regular
// const regularArr = [1, 2, 3]
// console.log(regularArr.byteLength) // prints undefined

// // typed array with shorthand
// const i8 = new Int16Array(3)
// console.log(i8.byteLength) // prints 6  since each Int16Array item has 2 bytes, adding '3' will make it 6

// // typed array with doing your own byte math

// const buffer = new ArrayBuffer(6) // assign 6 bytes to buffer
// const i8View = new Int16Array(buffer)
// console.log(i8View.byteLength) // also returns 6

// const newInt32 = new Int32Array(1)
// console.log(newInt32.byteLength)

// const set1 = new Set([1, 3, 'a', 'b', true, 1, 'b', undefined, null]);
// console.log(set1.has(1));

// no length method, but you can use size. Size does not seem to count undefined or null
// console.log(set1.size);

// console.log(set1);
// set1.add(3);

// const set2 = new Set([2, 3, 457, 23, 35]);

// you CAN NOT add multiple items with the .add() method with an array or another set inside the parens.
// but you can use the spread operator on a set to turn it into an array

// get a binary tree max height

// function Node(value) {
//   this.value = value;
//   this.left = null;
//   this.right = null;
// }

// function BinarySearchTree() {
//   this.findMaxHeight = function (
//     currentArr = [this.root],
//     nextArr = [],
//     height = 0,
//     isNextHeight = false
//   ) {
//     if (!this.root) {
//       return -1;
//     }
//     console.log(
//       `height is ${height} and currentArr is ${JSON.stringify(currentArr)}`
//     );
//     for (let node of currentArr) {
//       if (node.left) {
//         console.log('here');
//         isNextHeight = true;
//         nextArr.push(node.left);
//       }
//       if (node.right) {
//         isNextHeight = true;
//         nextArr.push(node.right);
//       }
//     } // end of for loop
//     console.log('end of loop. is');
//     if (!isNextHeight) {
//       return height;
//     }

//     return this.findMaxHeight(
//       (currentArr = [...nextArr]),
//       (nextArr = []),
//       (height += 1),
//       (isNextHeight = false)
//     );
//   };
// }
// const test = new BinarySearchTree();
// test.root = new Node(10);
// test.root.left = new Node(9);
// console.log(test.findMaxHeight());

// Depth-First binary searches - three methods

var displayTree = (tree) => console.log(JSON.stringify(tree, null, 2)); // just to print tree
function Node(value) {
  // to add nodes to tree from root
  this.value = value;
  this.left = null;
  this.right = null;
}
function BinarySearchTree() {
  this.root = null;
  // change code below this line

  this.inorderOutput = []; // to have storage one level higher than methods

  this.inorder = function (currentNode = this.root) {
    const isDone = (node) =>
      node === null || this.inorderOutput.includes(node.value); // helper
    if (!this.root) {
      return null;
    } // exception. if tree is empty
    // base case - if left node is done
    let savedCurrentNode = currentNode;
    while (!isDone(currentNode.left)) {
      this.inorder((currentNode = currentNode.left));
    }
    this.inorderOutput.push(savedCurrentNode.value);
    while (!isDone(savedCurrentNode.right)) {
      this.inorder((currentNode = savedCurrentNode.right));
    }
    if (isDone(this.root) && isDone(this.root.right)) {
      return this.inorderOutput;
    }
  }; // end of inorder()

  this.preorderOutput = [];
  this.preorder = function (currentNode = this.root) {
    const isDone = (node) =>
      node === null || this.preorderOutput.includes(node.value); // helper
    if (!this.root) {
      return null;
    }
    // root exists
    this.preorderOutput.push(currentNode.value); // push value
    let referenceNode = currentNode;
    while (!isDone(currentNode.left)) {
      this.preorder((currentNode = currentNode.left));
    }
    while (!isDone(referenceNode.right)) {
      this.preorder((currentNode = referenceNode.right));
    }
    if (isDone(this.root.right)) {
      // if the right subtree is done, it's all done
      return this.preorderOutput;
    }
  };

  this.postorderOutput = [];

  this.postorder = function (currentNode = this.root) {
    const isDone = (node) =>
      node === null || this.postorderOutput.includes(node.value); // helper
    if (!this.root) {
      return null;
    }
    let referenceNode = currentNode;
    while (!isDone(referenceNode.left)) {
      this.postorder((currentNode = referenceNode.left));
    }
    while (!isDone(referenceNode.right)) {
      this.postorder((currentNode = referenceNode.right));
    }
    if (isDone(referenceNode.left) && isDone(referenceNode.right)) {
      this.postorderOutput.push(referenceNode.value);
    }

    if (this.postorderOutput.includes(this.root.value)) {
      return this.postorderOutput;
    }
  };
}

const test = new BinarySearchTree();

test.root = new Node(1);
test.root.left = new Node(2);
test.root.right = new Node(3);
test.root.left.left = new Node(4);
test.root.left.right = new Node(5);
console.log(test.inorder());
console.log(test.preorder());
console.log(test.postorder());
