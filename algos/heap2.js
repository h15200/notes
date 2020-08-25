// use sift helper functions
class MinHeap {
  constructor(array) {
    this.heap = this.buildHeap(array);
  }

  buildHeap(array) {
    // starting i can be tweaked with a google lookup for first non-leaf node
    for (let i = Math.floor(array.length / 2) - 1; i >= 0; i--) {
      this.siftDown(i, array);
    }
    return array;
  }

  siftDown(index, array) {
    // check index against children, swap, and their children
    let current = index;
    // while left child of current exists
    while (array[current * 2 + 1] !== undefined) {
      const left = current * 2 + 1;
      const right = current * 2 + 2;
      let smaller;
      // if right child also exists, find smaller index
      if (array[right] !== undefined)
        array[left] <= array[right] ? (smaller = left) : (smaller = right);

      // if smaller exists, compare against that. if not, compare against left only
      if (smaller !== undefined && array[smaller] < array[current]) {
        [array[current], array[smaller]] = [array[smaller], array[current]];
        current = smaller;
      } else if (smaller === undefined && array[left] < array[current]) {
        [array[current], array[left]] = [array[left], array[current]];
        current = left;
      } else {
        return;
      }
      // increment current
    }
  }

  siftUp(index) {
    // parent = floor(i-1) / 2
    let current = index;
    while (this.heap[Math.floor((current - 1) / 2)] !== undefined) {
      let parent = Math.floor((current - 1) / 2);
      if (this.heap[current] < this.heap[parent]) {
        [this.heap[current], this.heap[parent]] = [
          this.heap[parent],
          this.heap[current],
        ];
        current = parent;
      } else return;
    }
  }

  peek() {
    return this.heap[0];
  }

  remove() {
    // swap head with tail
    [this.heap[0], this.heap[this.heap.length - 1]] = [
      this.heap[this.heap.length - 1],
      this.heap[0],
    ];
    // remove last
    const removed = this.heap.pop();
    this.siftDown(0, this.heap);
    return removed;
  }

  insert(value) {
    this.heap.push(value);
    this.siftUp(this.heap.length - 1);
  }
}

const heap = new MinHeap([
  -7,
  2,
  3,
  8,
  -10,
  4,
  -6,
  -10,
  -2,
  -7,
  10,
  5,
  2,
  9,
  -9,
  -5,
  3,
  8,
]);
console.log(heap);
console.log(heap.insert(-8));
console.log(heap);
