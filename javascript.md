# Javascript

## Infinity

Infinity
-Inifinity

are valid number assignments

## Array.isArray()

```
let a = [2,3]
a.isArray() // returns true
```

Object.isObject() does NOT exist.
best just to use `typeof(x) === 'Object'`

## For of loop indexing

To get the index in a for of loop (and for in loop)

it's possible with array destructuring, but not worth it

you have to turn the array into an object with indexes, then assign them to index and value through destructuring

```
for (const [i, v] of ['a', 'b', 'c'].entries()) {
  console.log(i, v)
}
```

## types

7 Built in Types in JS

null
boolean
undefined
number
string
object
symbol

All of these EXCEPT objects are “primitives”

All of these can be defined correctly by typeof except null, which returns Object bc of a bug

Because of the nature of null being falsy And returning “object”, you must check for it this way:

var a = null;

(!a && typeof a === "object"); // then it must be null

typeof will also identify “function” but not array despite both of them being subsets of objects

"undefined" and "undeclared" in JavaScript are quite different. undefined is a value that a declared variable can hold. "Undeclared" means a variable has never been declared.
JavaScript unfortunately conflates these two terms, not only in its error messages ("ReferenceError: a is not defined") but also in the return values of typeof, which is "undefined" for both cases.
However, the safety guard (preventing an error) on typeof when used against an undeclared variable can be helpful in certain cases.

    Values

Arrays are also objects, so keys can be added arr.<key> = <value> in either dot or bracket notation without changing the array or arr.length. Don’t use anything that could be coerced into numbers because that will actually add indexes to the array.

## ASCII comparison

“A” > “a” // false because lower cases have a higher ascii value
“aa” < “Aaa” // still false because the 1st char a is bigger than A
“aa” < “aaA” // true . third char is bigger than “nothing”

## loop breaking

You can pass in a second arg to the callback of forEach for index.
However, you can not STOP a forEach method with return, as that only returns the value from the forEach loop and the loop continues to run. `break` doesn't work and is a syntax error.

To use a breakable loop, use the for or while loops

## .flat() will flatten arrays once without an arg. You can add levels with arg

- passing in Infinity will flatten to 1 level

## Dom inside backticks

You can assign html elements inside backticks like so

```
const html = `
<div>
  <h1>This actually works!</h1>
</div>
`
```

## array destructuring swapping

let a = 1;
let b = 2;
[b, a] = [a, b];
// a is 2 and b is 1

## Object.assign()

- target to copy as first arg, then an optios object as the 2nd arg for additional (or overwrite) values.

- If an empty obj is the 2nd arg, nothing will change in the target

## Class method syntax and 'this' binding reminder

```
class Person {
  name: 'Patti';

  greet() {
    console.log(this.name)
  // this is a function declaration es5 style, but short hand
  }

  greet2 = () => {
    console.log(this.name)
// this is es6 arrow function
  }
}

// remember, 'this' is bound to the call site   whatever.greet().  The whatever is 'this' in the first example.
// in the arrow function version, this is bound to the Person class no matter where the call site was
```

For this reason, you should always choose to write arrow functions methods ALL THE TIME even though it's slightly more verbose than the shorthand function declaration.

## Alternate array creation

const arrayOfThreeHellos = Array(3).fill('hello');

## Dates

Probably looking for this one which takes in a Date Object and returns a human readable string

(DateObject).toDateString()

## array.concat()

Very cool property that's not in the spread operator is:

let a = [1,2,3]
let b = [4]
let c = 4

a.concat(b) AND a.concat(b) will give the same output, [1,2,3,4]

This can be used to flatten arrays!!

## .contructor === String, Object, Array, Function

for type checking

## sort() comparator is weird

Often, sort comparators are abbreviated as they still work. Depending on the browser(?) it may behave differently so be safe and be explicit
and always return 0, -1, and 1!

For alphabetical order increasing,

```
(a, b) => {
  if (a < b) {
    return -1;
  }
  if (a > b) {
    return 1;
  }
  return 0;
}
```

## eval()

evaluates a string as math operation IF valid

str = '4+4'
eval(str) // returns the number 8

DO NOT include the equal sign

## str.repeat() !!!

## Use array destructuring to swap items in an array like

[item[i], item[i+1]] = [item[i+1], item[i]]

## Using POINTERS to keep reference to do stuff inside a for loop.

let j = i, swap things to the left for ex. insertion sorts

## != null

checks for BOTH null AND undefined

## one line if returns are good

cleaner code to have

`if (input > 0) return null`

## When using a cache for tallying

you can increment to the current value or 0 by doing something like

`tally[val] = (tally[val] || 0) + 1`

## IIFE and npm modules

- older npm libraries like jQuery was just a script that ran one huge IIFE. This was to avoid contaminating the global namespace

- the following code just creates a global object, `hideaki` which contains all library methods. This way calling `hideaki.fetch()` does not collide with the normal fetch web api

```
const hideaki = (() => {
    function test () {
console.log('npm test');
    }

function slice() {
console.log('my slice!');
}

function fetch() {
console.log('fetch me a pizza, please!')
}

return {
  test,
slice,
fetch
}
})()
```

## 2 pillars of js

- `closure` and `prototypes` give javascript unique functionality
- a closure is an exception to garbage collecting when a function is using a variable from a parent scope. In this case, the parent stack is popped off but any variables being used in the inner function stays in the heap.
- closures can keep data private, persist info in memory, and memoize

- all js data inherits all properties based on its `__proto__`.
- you can manually change the proto by doing something like this snippet below, but DON'T EVER DO THIS! bad performance, bad practice, etc.. use classes or `Object.create(obj_to_inherit)`

```
const car = {
  color: "blue",
  getColor: function () {
    return this.color
  },
}

const myCar = {
  color: "red";
}

myCar.__proto__ = car;

myCar.getColor() // returns "red"

```

- the `class` keyword was added so you can manuever around prototypal inheritance as if they were class inheritance
- `[someObj].hasOwnProperty(propName)` will check if the property is on the actual object as opposed to the prototype object. It will exclude prototype props.

- all js data has a `.__proto__` property which eventually leads to the "base" object. If you ask for the `__proto__` of that base obj, it will return null as it's the base prototype

### WEIRD Proto stuff

- all js data types have a `__proto__` property
- ONLY FUNCTIONS have `prototype`
- since classes are functions, built-in JS objects with capital letters `Date`, `String`, `Object` ARE functions since they are constructors.
- you can add built-in prototype like

```
Array.prototype.sayHiPerArrItem = function () {
  for (let i = 0; i < this.length; i++) {
    console.log('hi');
  }
}
```

### difference between `__proto__` and prototype in function

- `__proto__` is the reference of what a child used to inherit from the parent. It's the parent's properties
- `prototype` is the object that's used to inherit for a CHILD of the current object. What's going to be passed down

  - if `const someClassInstance = new Someclass()`, then `someCLassInstance.__proto__ === Someclass.prototype`

- code example:

```
class Car {
  color = 'red'
  getColor() {
    return this.color;
  }
}

const myCar = new Car();

myCar.__proto__ === Car.prototype // true
```

## functional vs OOP

- in js, functions are 1st class citizens. Under the hood, functions are objects.

## ecma 2020

- nullish coalesce: `const thing = obj?.prop1 ?? "no prop"`
- it is similar to `||` which tests for truthy / falsey, but `??` tests only for if data is `undefined / null`. If the left hand side of `??` is EITHER null or undefined, it will use the right hand side option

## Map

- maps are ordered, so they can be helpful in certain algos
- syntax is more c++ esque with iterators

- `const orderedMap = new Map()`
- orderedMap.set('myKey', 'myVal');
- orderedMap.get('myKey') // returns val
- orderedMap.delete('myKey') // deletes and returns bool
- const iterator = orderedMap.keys();
  iterator.next().value // returns the key of the first key value. if ran again, the 2nd item

## OOP vs Functional Programming

- the 2 main paradigms of how to organize code
- current trend (2021) leans slightly towards FP

- the main philosophical difference is in OOP, the data and behaviors are packaged into one object, or class
- in FP, the behavior is separated from the data

### OOP

- two main ways of having an OOP paradigm

1. class based (c++)
2. prototype based (js)

- prototype checking is tricky. better to use `thingA instanceof thingB` to check for instantiated classes

- 4 pillars of OOP

1. Encapsulation - both members and methods are in one place
2. Abstraction - controlling complexity at the appropriate data level. Devs don't need to know about the inner works
3. Inheritance - Avoiding memory space and redundant coding
4. Polymorphism - Ability to overload methods inside subclass implementation

### Functional Programming (FP)

- functional programming concepts work well in a distributed system
- relevant concepts include HOF, closure, memoization, currying
- data and functions are SEPARATED (as opposed to OOP classes where it's combined)
- goals are the same as OOP. clear, maintainable, well performing, non repetitive coding

- `HOF` higher order functions either:

  1. takes in a function as an arg
  2. returns a function

- `currying` technique of turning a function with multiple params into separate functions which all take exactly 1 param.

  - similar to OOP classes. Used as a factory function

- `Partial Application` is an adjacent technique to `currying`. In partial application, you pre-fill some of the multiple params using the bind method

  - ex.

  ```
    function addThree(a, b, c) {
    return a + b + c;
    }

  // Partial Application
  const partialAdd = addThree.bind(null, 10); // a defaults to 10
  partialAdd(1, 2) // -> 13
  ```

- basic idea of pure functions (immutable, no side-effects, no shared state, does one thing, returns something)
- idea of same input always having the same output = `Referential Transparency`

- pure functions are predictable and easy to test

- in OOP, data is privatized by the keyword `private` and public getters. In FP, it's done with closure

- currying, composition is used in FP. It's best to have a low `arity` (number of args) of pure funcs chained together

## imperative vs declaritive

- machines require imperative code. step-by-step
- declarative is more human. "get me this"
  ex. of Imperative code (for loops, vanilla js)
  ex. of Declarative code (array methods like forEach, react)

- declarative code needs to be compiled down to more imperative, machine code eventually

## Inheritance vs Composition

- in fp, composition and piping is used

  - composition and piping is the same concept, but just ordered differently
  - compose(func1, func2, func3) means you're running in the order 3,2,1
  - piping is the opposite. goes func1, 2, 3

  ```
  function compose = (func1, func2) {
    return function (data) {
      return func1(func2(data))
    }
  }

  function pipe = (func1, func2) {
    return function (data) {
      return func2(func1(data))
    }
  }
  ```

- OOP is great when data relationships are clear in the planning stages.
- FP is great if there are no tight couplings between data structures

## Promise.all() es9

- Promise.all allows a pseudo-parallel or concurrent resolution waiting for multiple Promises.

- Promise.all will ONLY work if all promises resolve. If there is even 1 reject value, it will throw

- if given 3 Promises, it starts to resolve Promise[0], then if it's time intensive, will move on and start Promise[1], etc..

- as a parameter, takes in an array of PROMISES! Not callbacks (functions), but actual function invocations in the case of fetch, as the function fetch itself is just a function the return of fetch() is a promise.

- promise syntax ex

- remember, Promises use .then and .catch which both take a callback. In async await try/catch, the catch itself is `try (e) { // actions }`

```
const urls = ['https://jsonplaceholder.typicode.com/users', url2, url3 ];

async function myFetch(url) {
  try {
    const res = await fetch(url);
    if (!res.ok) throw Error;
    return await res.json();
  } catch(e) {
    throw Error(e);
  }
}

Promise.all(urls.map(url => {
  return myFetch(url);
})).then(dataArr => {
  console.log(dataArr[0])
  console.log(dataArr[1])
}).catch(e => console.log(e))

// the urls.map is building 3 fetch requests


```

- same thing above with async/await IIFE
- promiseAll gets very

```
const urls = [url1, url2, url3];

async function myFetch(url) {
  try {
    const res = await fetch(url);
    if (!res.ok) throw Error;
    return await res.json();
  } catch(e) {
    throw Error(e);
  }
}
// IIFE
(async function () {
 let dataArr;
  try {
  dataArr = await Promise.all(urls.map(url => asyncFetch(url)))
} catch(e) {console.log(e)}
console.log(dataArr[0]);
console.log(dataArr[1]);

})()
```

## await for (NOT an alternative to Promise.all, but just sequential syntax)

- a newer way to do `SEQUENTIAL` async calls
- `for await` if a for of loop for promise arrays, which is the param of a Promise.all
  1. create an async func
  2. inside, make an arr of promises (remember, not functions but function returns from a promise)
  3. for await (const var of promiseArr) {
     // make await calls with try/catch
     }

```
// IIFE

const urls = [url1, url2, ...];

(async function() {
  const promiseArr = urls.map(url => fetch(url))
  for await (const res of promiseArr) {
    if (!res.ok) throw Error;
    try {
    const data =  await res.json();
    console.log(data);
}  catch(e) {
  console.log('error', e);
}


}
})()
```

## asyc pseudo-parallel (or concurrent) VS sequential,

- when resolving multiple promises, the slowest way is to do them sequentially while blocking each action

  - if you await code, it is blocking so it's running in `sequence`. ex

  ```
  const a = await fetch(a);
  // fetch a (connect via http), get the result, then finally start fetching b
  const b = await fetch(b);
  // same
  const c = await fetch(b);

  ```

- `for await` calls are also sequential because you can have logic for each finished promise in the order of the array, but ONLY in the order of the array. You usually don't know which promise will settle first, so this still does not control or execute in the order that a promise was settled

- `await Promise.all([...promises])` will return only when all promises have settled, but all promises are working in `pseudo-parallel` or `concurrently`. If a promise isn't resolved, it can move on to the next Promise and start evaluating. In fetch, this is possible because you can have multiple http connections to endpoints, so you can fetch[0], and while waiting for the reuslt, start fetch[1], etc.. This is faster than awaiting each call

## Promise.race()

- when you need to return ONLY the 1st Promise that settles out of an array, use Promise.race();
- `await Promise.race()` takes in an array of Promises, but will return the resolve of ONLY the 1st promise that finishes.

```
return dataOfFirstPromiseResolve = await Promise.race([fetch[urla], fetch[urlb]]);

// will return as soon as EITHER urlA or urlB data is received
```

## Promise.allSettled() es2020

- `Promise.all` is most useful when you know all Promises in the array will resolve. If any one of them rejects, then it will short circuit. For example, in a promiseArray [promiseA, promiseB, promiseC] and calling await Promise.all([...array]), if promiseC rejects, you will NOT see the resolve values of promiseA or promiseB.

- `Promise.allSettled()` is a variation on Promise.all. It will return an array of both resolved AND rejected values.

- use Promise.all if the application needs the data from all Promises to continue.

- if even one Promise can fail and still be "normal", use Promise.allSettled()

## module history

1. When js files were directly attached to the html, devs just attached one file.

- when multiple files became necessary as apps got bigger, variable collision became an issue.
- Solution -> `module pattern` or `module scope`

2. Module scope was created using an IIFE so that instead of a global var, each script had a script1.variable that was different from script2.variable

- used by libraries like jQuery
- pros: all scripts can refer to each other IF it was imported AFTER
- cons: global space is still being polluted by the module name. Script ordering can be hard to track if there are hundreds of them

- solution -> `CommonJS` and `AMD` (asynchronous module)

3. CommonJS, AMD

- each NODE (not browser) file in commonJS just uses keyword `require` to import/export
  - `const thing = require(./someOtherFile.js);`
  - `module.exports = { exportedThing: someFunc}`
- also became possible to share node modules with other people through npm

- pros: files can refer to each other in NODE
- cons: it was a synchronous operation. Not available on browser

- as commonJS got popular, there was a desire for the browser to also use import/export syntax. solution -> `browserify`

- AMD was another browser-side solution to handle imports/exports. Was used by the RequireJS package (which confusingly did not use CommonJS, but AMD)

4. Browserify

- the first bundler. Took js scripts with commonJS and bundled it into ONE js file so the ordering of the script import does not matter
- handled variable collusion
- lead to the development of rollup, parcel, webpack etc..

- con: still an external package that is handling browser moduling.
  solution -> the first native browser module system, `es6 modules`

5. native ES6 modules

- if importing in an html file, you must indicate `type="module"` (instead of the old type="text/javascript") and open in a server
- import/export statements
- browsers can now just read import/export statements from multiple js files
- pros: global namespace is no longer polluted. The modules will just now run, but there will be no additional properties or methods inside the window object
- as of node 13, ES6 modules are supported server side as well

## Error handling

### throw

- the `throw` keyword will stop the current execution.
- you can throw anything `throw true`, `throw 'hi'`, not just errors
- the error must be handled by the next call stack execution with a catch block
- if the error is not inside a catch block, it is an `uncaughtException`

### instances of Error constructor function

- properties include:
  - `.stack` -> prints current func where error was thrown
  - `.name` , `.message`
    - note that Error methods are all getters so no need to wrap with `()`
- can create specific errors like `new SyntaxError`, `new ReferenceError`

### try catch

- a catch can be a catch block (in async await or syncronous code) or a catch method (in promise chaining)

- NOTE that going into the catch block does not STOP the execution context. it will keep going. Best to return in the catch block

```
function fail() {
  try {
    conSAWL.log('good') // syntax error
  } catch (error) {
    console.log('error found!');
  }
}

fail() -> will log the error. the error was caught, which is good

```

### finally {}

- if you need code to run even after a caught exception, use a finally block. Sort of weird because you don't need a finally as this is the default behavior
- note that NO code will run AFTER a finally block

- in async code, it is crucial to catch errors with a .catch method or a try catch block in async await

### extending errors

- you can create your own custom errros based on the built-in error constructor function

```
class MyNewError extends Error {
  constructor(message) {
    super(message);
    this.name="My Error";
  }
}

throw new MyNewError('test');
```

### reduce with array of objects

- when reducing nested values like `const arr = [{num:1}, {num:2}, {num:3}], think about the accumulator data structure.

- this will NOT WORK
  `arr.reduce((a, b) => a.num + b.num)` because the in the 1st iteration, it's fine but in the 2nd, `a` is a number and not an object. number.num is not a property, and will return `nan`

- 3 ways to fix:

  1. map it, then reduce it `arr.map(obj => obj.num).reduce((a, b) => a + b)`;
  2. add a starting value, and just evaluate the nested val (better than option 1). BEST option
     `arr.reduce((a, b) => a + b.num, 0)`
  3. reduce as an object. works, but hard to reed11

  ```
  const obj = arr.reduce((a, b) => {
    return ({
      num: a.num + b.num1
    })
  })

  // obj.num is total
  ```
