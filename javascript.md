# Javascript

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

## Weird things about forEach

You can pass in a second arg to the callback of forEach for index.
However, you can not STOP a forEach method with return, as that only returns the value from the forEach loop and the loop continues to run. `break` doesn't work and is a syntax error.

To use a breakable loop, use the for or while loops

## .flat() will flatten arrays once without an arg. You can add levels with arg

## Dom inside backticks

You can assign html elements inside backticks like so

```
const html = `
<div>
  <h1>This actually works!</h1>
</div>
`
```

## Object.assign()

target first, then the additional (or overwrite) props starting 2nd arg. Can be multiple.

If an empty obj is the 2nd arg, nothing will change in the target

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
