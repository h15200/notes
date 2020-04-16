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
