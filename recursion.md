Skipping the basics

4-14-20

Remember that when you need to do something recursively without returning anything like in the three types of binary depth-first searches, you need a reference point to get back to the original level node.

```
// pseudocode
basefunction() {
currentNode = initial

recursion(currentNode = nextNode)
currentNode.doSomethingMore

// after the above recursion is dones, our currentNode is NO LONGER initial, but the next node
}
```

a simple solution is

```
basefunction() {
currentNode = initial
referencePoint = currenNode

recursion(currentNode = nextNode)
referencePoint.doSomething

// now we have access back to initial
}
```

## regular recursion - O(n) LINEAR recursion

```
const factorial = (n) => {
  if (n===0) return 0;
  else return n * factorial(n-1)
}

```

## tail recursion (tail call optimization) Stack won't pop back up if you do it this way - Time complexity is still O(n) but Space complexity is O(1)

with tail recursion, we don't need the initial stacks for the return value, so the cpu is ONLY using one stack by reusing the first stack.

JS will evaluate the base case and if no other info is needed, it will trigger tail recursion automatically.

For tail recursion, you CARRY the return variable inside the params TO the recursive calls so that when you hit the base case, you don't need to go back.

```
const factorial = (n, product = 1) => {
  if (n ===0) return product;
  else return factorial(n-1, product * n);
};

```
