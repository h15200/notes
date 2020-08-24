// In a heap structure implmentation, it is VERY useful to add siftUP and siftDown.

// build and remove will use siftDow
// insert will use siftUp
class MinHeap {
  constructor(array) {
    this.heap = this.buildHeap(array);
  }

  buildHeap(array) {
    // copy original
    const minHeap = [...array];

    // 0, 1, 2, 3, 4, 5, 6
    // parent = Math.floor(i + 1 / 2) - 1. if 0, null
    // left child = (i + 1) * 2 - 1
    // right child = (i + 1) * 2

    // helper functions hasChild returns boolean
    // const hasChild = (index) => minHeap[(index + 1) * 2 - 1] !== undefined;
    // helper function will swap values with children
    const heapify = (index) => {
      const left = (index + 1) * 2 - 1;
      const right = (index + 1) * 2;
      // if both nodes exists
      if (minHeap[left] !== undefined && minHeap[right] !== undefined) {
        // console.log('checking children for current value', minHeap[index]);
        let smallerIndex;
        minHeap[left] <= minHeap[right]
          ? (smallerIndex = left)
          : (smallerIndex = right);
        // swap if smaller
        if (minHeap[smallerIndex] < minHeap[index])
          [minHeap[index], minHeap[smallerIndex]] = [
            minHeap[smallerIndex],
            minHeap[index],
          ];
        // call recursively on new child index
        heapify(smallerIndex);
      } // if only left exists AND it's smaller than index
      else if (minHeap[left] !== undefined && minHeap[left] < minHeap[index]) {
        // swap
        [minHeap[index], minHeap[left]] = [minHeap[left], minHeap[index]];
        // call recursively on the new left
        heapify(left);
      }
    };
    // start at (i - 1) / 2 to i

    for (let i = Math.floor(minHeap.length / 2); i >= 0; i--) {
      heapify(i);
    }
    return minHeap;
  }

  siftDown() {
    // Write your code here.
  }

  siftUp() {
    // Write your code here.
  }

  peek() {
    return this.heap[0];
  }

  remove() {
    // swap 0 with last
    [this.heap[0], this.heap[this.heap.length - 1]] = [
      this.heap[this.heap.length - 1],
      this.heap[0],
    ];
    // pop last
    this.heap.pop();
    let current = 0;
    // while there is at least one child
    while (this.heap[(current + 1) * 2 - 1] !== undefined) {
      console.log('current is', current);
      const left = (current + 1) * 2 - 1;
      const right = (current + 1) * 2;
      // if both
      if (this.heap[left] !== undefined && this.heap[right] !== undefined) {
        // get smaller
        let smaller;
        this.heap[left] < this.heap[right]
          ? (smaller = left)
          : (smaller = right);
        // if smaller is smaller than index, swap
        if (this.heap[smaller] < this.heap[current]) {
          [this.heap[smaller], this.heap[current]] = [
            this.heap[current],
            this.heap[smaller],
          ];
          // look at the child of the swapped child
          current = smaller;
          continue;
        }
      } // if only one child
      else if (this.heap[right] === undefined) {
        // check and swap with left
        if (this.heap[left] < this.heap[current]) {
          [this.heap[current], this.heap[left]] = [
            this.heap[left],
            this.heap[current],
          ];
          // check new child
          current = left;
        }
      }
      // if none of these apply, it's done early
      return this.heap;
    }
    return this.heap;
  }

  insert(value) {
    // make copy
    const newHeap = [...this.heap];
    // push value to end of current heap
    newHeap.push(value);
    // while current is more than 0
    let current = newHeap.length - 1;
    while (current > 0) {
      const parent = Math.floor((current + 1) / 2) - 1;
      // check to see if it's bigger than parent
      if (newHeap[current] < newHeap[parent])
        [newHeap[current], newHeap[parent]] = [
          newHeap[parent],
          newHeap[current],
        ];
      // current is now the parent
      current = parent;
    }
    this.heap = newHeap;
    return this.heap;
  }
}

const minHeap = new MinHeap([4, 34, 74, 12, 5647, 98, 465, 32, 54, 67, 78]);
console.log('minheap is', minHeap.heap);
// console.log('peek at smallest', minHeap.peek());
// console.log('insert. new heap is,', minHeap.insert(0));
console.log('remove. new heap is', minHeap.remove());

const minHeap2 = new MinHeap([12, 78, 74, 32, 67, 98, 465, 34, 54, 5647]);
console.log('should be the same', minHeap2.heap);
