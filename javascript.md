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

Many developers will assume "undefined" and "undeclared" are roughly the same thing, but in JavaScript, they're quite different. undefined is a value that a declared variable can hold. "Undeclared" means a variable has never been declared.
JavaScript unfortunately conflates these two terms, not only in its error messages ("ReferenceError: a is not defined") but also in the return values of typeof, which is "undefined" for both cases.
However, the safety guard (preventing an error) on typeof when used against an undeclared variable can be helpful in certain cases.

    Values

Arrays are also objects, so keys can be added arr.<key> = <value> in either dot or bracket notation without changing the array or arr.length. Don’t use anything that could be coerced into numbers because that will actually add indexes to the array.

## ASCII comparison

“A” > “a” // false because lower cases have a higher ascii value
“aa” < “Aaa” // still false because the 1st char a is bigger than A
“aa” < “aaA” // true . third char is bigger than “nothing”

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

## array destructuring swapping

let a = 1;
let b = 2;
[b, a] = [a, b];
// a is 2 and b is 1

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
