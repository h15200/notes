class LinkedList {
  value: number;
  next: null | LinkedList;
  constructor(value: number) {
    this.value = value;
    this.next = null;
  }
  append(value: number): void {
    let node: LinkedList = this;
    while (node.next !== null) {
      node = node.next;
    }
    node.next = new LinkedList(value);
  }
}

const ll = new LinkedList(0);
ll.append(3);
ll.append(5);
console.log(ll);
