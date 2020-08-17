// Do not edit the class below except for
// the insert, contains, and remove methods.
// Feel free to add new properties and methods
// to the class.
class BST {
  constructor(value) {
    this.value = value;
    this.left = null;
    this.right = null;
  }

  insert(value) {
    // if value is less than current tree
    if (value < this.value) {
      // if no left child, this is the left child
      this.left ? this.left.insert(value) : (this.left = new BST(value));
    }

    if (value >= this.value) {
      this.right ? this.right.insert(value) : (this.right = new BST(value));
    }

    // Do not edit the return statement of this method.
    return this;
  }

  contains(value) {
    if (value === this.value) return true;
    if (value < this.value) {
      return this.left ? this.left.contains(value) : false;
    }
    if (value > this.value) {
      return this.right ? this.right.contains(value) : false;
    }
  }

  remove(value) {
    // edge case value doesn't exist
    if (!this.contains(value)) return this;

    // helper func - finds the swap parent, the swap node, and possible children, and
    // will change the target value and nullify the swap based on child availability

    const handleTwoChildren = (target) => {
      // takes in the target node (that has 2 children), finds swapParent
      let parent = target;
      let swapNode = parent.right;
      let next = swapNode.left;
      while (next) {
        parent = swapNode;
        swapNode = swapNode.left;
        next = next.left;
      }

      // first reassign the target value to swap value
      target.value = swapNode.value;

      // get direction from parent to swapNode
      let direction;
      swapNode.value < parent.value
        ? (direction = 'left')
        : (direction = 'right');

      // does the swapNode have a child
      if (!swapNode.right && !swapNode.left) parent[direction] = null;
      else if (swapNode.right) parent[direction] = parent[direction].right;
      else if (swapNode.left) parent[direction] = parent[direction].left;
    };

    // edge case - target is the only node. head boolean true for first time only
    if (this.value === value) {
      // if it's the only node, cancel
      if (!this.left && !this.right) return this;
      // if only left child, head is left cheld
      else if (this.left && !this.right) {
        this.value = this.left.value;
        this.left = this.left.left;
      } else if (this.right && !this.left) {
        this.value = this.right.value;
        this.right = this.right.right;
      }
      // if both children,
      else return handleTwoChildren(this);
      return this;
    }

    // find  target (definitely not the head of the tree)
    let parent;
    let current = this;
    while (!parent) {
      if (
        (current.left && current.left.value === value) ||
        (current.right && current.right.value === value)
      )
        parent = current;
      if (value > current.value) current = current.right;
      else if (value < current.value) current = current.left;
    }
    // at this point, parent is valid node

    // if target is smaller than parent, target is parent.left and vice versa
    let direction;
    value < parent.value ? (direction = 'left') : (direction = 'right');

    // parent.direction is target
    // check children of target
    // 3 cases - target has 0 child, 1 child, 2 children
    // if 0 children, make the target node null
    if (!parent[direction].left && !parent[direction].right)
      parent[direction] = null;
    // 1 children
    else if (!parent[direction].left)
      parent[direction] = parent[direction].right;
    else if (!parent[direction].right)
      parent[direction] = parent[direction].left;
    // 2 children
    else handleTwoChildren(parent[direction]);
    // Do not edit the return statement of this method.
    return this;
  }
}

const bst = new BST(10);
bst.insert(20);
bst.insert(5);

bst.remove(10);

console.log(bst);
