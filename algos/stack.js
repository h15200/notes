// make a stack (size, add, remove) without any built-in js methods

// es5

function Stack() {
  this.collection = [];
  this.lastIndex = 0;
}

Stack.prototype.size = function () {
  return this.collection.length;
};

Stack.prototype.add = function (item) {
  this.collection[this.lastIndex++] = item;
  return item;
};

Stack.prototype.remove = function () {
  // if no item to remove
  if (!this.collection.length) return null;
  // if only one current item
  if (this.collection.length === 1) {
    const removed = this.collection[0];
    this.collection = [];
    this.lastIndex = 0;
    return removed;
  }
  // otherwise, build a new array without last element
  const output = [];
  for (let i = 0; i < this.collection.length - 1; i++) {
    output[i] = this.collection[i];
  }
  this.lastIndex--;
  this.collection = output;
  return output;
};

// remember, only use THIS if you need to assign a property through the constructor
class StackClass {
  collection = [];
  lastIndex = 0;
  size() {
    return this.collection.length;
  }

  add(item) {
    this.collection[this.lastIndex++] = item;
    return item;
  }

  remove() {
    // if no item to remove
    if (!this.collection.length) return null;
    // if only one current item
    if (this.collection.length === 1) {
      const removed = this.collection[0];
      this.collection = [];
      this.lastIndex = 0;
      return removed;
    }
    // otherwise, build a new array without last element
    const output = [];
    for (let i = 0; i < this.collection.length - 1; i++) {
      output[i] = this.collection[i];
    }
    this.lastIndex--;
    this.collection = output;
    return output;
  }
}

// const stack = new Stack();
// stack.add(5);
// stack.add(6);
// stack.add(7);
// console.log(stack.remove());
// console.log(stack);

const stackClass = new StackClass();
console.log(stackClass.size());
stackClass.add(1);
stackClass.add(2);
stackClass.add(3);
stackClass.add(4);
stackClass.add(5);
console.log(stackClass);

stackClass.remove();
stackClass.remove();
console.log(stackClass);
