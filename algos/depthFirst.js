// Do not edit the class below except
// for the depthFirstSearch method.
// Feel free to add new properties
// and methods to the class.
class Node {
  constructor(name) {
    this.name = name;
    this.children = [];
  }

  addChild(name) {
    this.children.push(new Node(name));
    return this;
  }

  // first attempt - it works but totally unnecessary
  // depthFirstSearch(array = []) {
  //   // make helper func and immediately call
  //   const node = this;
  //   (function generate(current = node) {
  //     // first, push the current node name to array
  //     array.push(current.name);
  //     // if current has no children, return
  //     if (current.children.length === 0) return;
  //     else {
  //       // if current has children, loop through each child and call func
  //       for (let child of current.children) {
  //         generate(child);
  //       }
  //     }
  //   })();
  //   return array;
  // }
  // since we are not actually returning the recursive call, only the top level return will truly return
  // depthFirstSearch(array = [], current = this) {
  //   // push value first
  //   array.push(current.name);
  //   // loop and push all children
  //   for (const child of current.children) {
  //     this.depthFirstSearch(array, child);
  //   }
  //   return array;
  // }

  // third attempt. Even use less space by calling recursively in the child method
  depthFirstSearch(array = []) {
    // only reference "this"
    array.push(this.name);
    // loop and push all children
    for (const child of this.children) {
      child.depthFirstSearch(array);
    }
    return array;
  }
}

const graph = new Node('A');
graph.addChild('B');
graph.addChild('C');
graph.addChild('D');
graph.children[0].addChild('E');
graph.children[0].addChild('F');
graph.children[0].children[1].addChild('I');
graph.children[0].children[1].addChild('J');

graph.children[2].addChild('G');
graph.children[2].addChild('H');
graph.children[2].children[0].addChild('K');

console.log(graph.depthFirstSearch());
