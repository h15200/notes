function nodeDepths2(root: BT) {
  let total = 0;
  (function counter(tree: BT | null, depth = 0) {
    // edge case no tree
    if (tree === null) return 0;
    total += depth;
    if (tree.left) counter(tree.left, depth + 1);
    if (tree.right) counter(tree.right, depth + 1);
  })(root);
  return total;
}

// This is the class of the input binary tree.
class BT {
  value: number;
  left: BT | null;
  right: BT | null;

  constructor(value: number) {
    this.value = value;
    this.left = null;
    this.right = null;
  }
}

const bst = new BT(1);
bst.left = new BT(2);
bst.right = new BT(3);
bst.left.left = new BT(4);
console.log(nodeDepths2(bst));
