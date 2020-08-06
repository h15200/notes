// Combine the total of all bst depths on every node of a tree

// using breadth first with queues to save space
function nodeDepths(root) {
  const queue = [{ node: root, depth: 0 }];
  let total = 0;
  // look for current queue[0]'s left and right, add those to queue
  // shift() and do stuff with current
  // go into next head of queue
  while (queue.length) {
    // dequeue
    const current = queue.shift();
    // look for more nodes
    if (current.node.left) {
      queue.push({ node: current.node.left, depth: current.depth + 1 });
    }
    if (current.node.right) {
      queue.push({ node: current.node.right, depth: current.depth + 1 });
    }
    total += current.depth;
  }
  return total;
}

// This is the class of the input binary tree.
class BinaryTree {
  constructor(value) {
    this.value = value;
    this.left = null;
    this.right = null;
  }
}

const bst = new BinaryTree(1);
bst.left = new BinaryTree(2);
bst.left.left = new BinaryTree(4);
bst.left.right = new BinaryTree(5);
bst.left.left.left = new BinaryTree(8);
bst.left.left.right = new BinaryTree(9);
bst.right = new BinaryTree(3);
bst.right.left = new BinaryTree(6);
bst.right.right = new BinaryTree(7);

console.log(nodeDepths(bst));
