// function nodeDepths2(root: BT) {
//   let total = 0;
//   (function counter(tree: BT | null, depth = 0) {
//     // edge case no tree
//     if (tree === null) return 0;
//     total += depth;
//     if (tree.left) counter(tree.left, depth + 1);
//     if (tree.right) counter(tree.right, depth + 1);
//   })(root);
//   return total;
// }

/* OHHHHHH   so the above needs to be used with closure and a separate function because 
unlike objects and arrays, depth and total are passed in by VALUE and not reference. So 
when a closure stack closes, the memory of the parent stack is used and not the updated value
if you MUST do it without a helper func, cheat like the following by using an index of an array,
but this is probably bad practice */

function nodeDepths2_noHelper(tree: BT, total = [0], depth = 0) {
  // edge case
  if (tree === null) return depth;

  // increment current depth
  total[0] += depth;

  // look left and look right
  if (tree.left) nodeDepths2_noHelper(tree.left, total, depth + 1);
  if (tree.right) nodeDepths2_noHelper(tree.right, total, depth + 1);
  return total[0];
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
// console.log(nodeDepths2(bst));
console.log(nodeDepths2_noHelper(bst));
