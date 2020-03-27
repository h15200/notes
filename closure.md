---
dateWritten: '3/27/20'
author: 'H'
subject: 'js closure'
---

# Closure

## Main Concept

- An outer function that returns an inner function creates a lexical scope when the inner function is assigned.

```
const outer = () => {
  let counter = 0

  const inner = () => {
    return counter++   // return current counter and then increment by 1
  }
  return inner
}

const activeClosure = outer()   // this execution creates the function inner with closure over the counter variable in lexical scope that remains in memory

console.log(activeClosure())
console.log(activeClosure())
console.log(activeClosure())

```
}

## You can do things like run a function only once, keep things in memory, etc.. For callbacks, remember that the number of params for the inner function is undertermined. Use ...args!

```
const createClosure = arr => {

  const innerFunc = str => {
    arr.forEach( (i) => {
      console.log(str + ' ' + i)
    })
  }
  return innerFunc
}

const newFunction = createClosure(['bob', 'patti'])

newFunction('hi')   

// this is fine. This prints 'hi bob' and 'hi patti'  but if newFunction is called with more than 1 arg, everything after the first will be ignored


```

```
const createClosure = arr => {

  const innerFunc = (...arg) => {
    arr.forEach( (i) => {
      console.log(...arg + ' ' + i)
    })
  }
  return innerFunc
}

const newFunction = createClosure(['bob', 'patti'])

newFunction('hi')
newFunction('hi', 'hello')

// This is better as it can handle any number of args! Notice how for arrow functions, ...arg must be in parens as it counts as more than one param.


```