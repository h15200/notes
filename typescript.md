# Typescript

Use type systems to catch errors. Used during development only.

Type annotations are added in js to analyze code.

Typescript transpiles (compiling is going from human code to machine code) to regular js. It provides no performance optimization like C.

## Setup and compiling

To install typescript, `npm i -g typescript ts-node`
To see if you already have it, `tsc -v` which stands for typescrip compiler

Inside your project dir, make a projectName.ts file
After writing ts, remember it won't just with `node filename.js` like with regular js. You need to compile it first.

In the terminal, you can `tsc filename.ts` which creates a filename.js file in the same dir, and run `node filename.js`
OR
just simply use the ts-node package and `ts-node filename.ts` which will do both things with one command

## What is a type in js?

Anything that can be assigned to a variable.

number, string, function, array, object, Date.
All types have their own properties and methods built-in.

1. Primitive Types - number, boolean, string, null, undefined, symbol, void
2. Object Types - functions, classes, arrays, objects

## Type assignment in function parameters

`const print = (a: string, b: boolean) => console.log(a,b)`

Colon and data type after each parameter will specity the type of data coming into the function

## Interface

Interface will define the structure of a new Type

```
interface Todo {
  id: number;
  title: string;
  isDone: boolean;
}
```

Notice how each key-value pair ends with a SEMICOLON and not a comma like in regular objects.
tells what kind of data you will expect in each specified property.
It's fine to not define every property. If the todo Object had other properties, they will simply be ignored

Now any future objects can be treated as a Todo type
with the syntax `const a = obj as Todo;`

## Type Annotation & Type Inference

Type annotation is the coder telling TS what to look for
Type Inference is TS guessing what the type should be

### Type Annotation Overview

`const apples: number = 5;`
// annotating apples to the type apples

`const now: Date = new Date()`
// Note how Date type must be caplitalized

```
const arr: string[] = ['array', 'of', 'only', 'strings']
```

Array of strings

```
class Car {}

let toyota: Car = new Car();
```

You can use classes directly as a Type.

```
let point: { x: number; y: number } = {
  x: 10,
  y: 20,
};
```

// for objects, syntax is different from number[]. You put the stuff inside {} and separate with semicolons.

```
// Functions are the hardest in terms of syntax
// normal function
const logNumber = i => console.log(i);

// for typescript. THE LONG FORM IS
let logNumber :(i: number) => void = (i: number) => console.log(i);

// another example
let addFive :(i: number) => number = (i: number) => i + 5;

// This long form is used only if you plan to reassign the function later.
// notice you must use parens inside the function definition even if it's just one argument
// the void means the function returns nothing. Do not use undefined or null.
```

In reality, we will NOT be using annotations like this because of type inference.

### Type Inference

If there is no explicit type annotation in variable declarations, typescript will infer the type.
If a variable declaration and an initialization is on the same line like `let a = 4`, then the inference will be the type of the value

So, we will ONLY use type annotations when:

1. when a function returns an 'any' type
   for ex. JSON.parse() can return a boolean, number, or an object. You should annotate the return value with keys
2. we want to initialize a variable after a declaration
   ex - before loops
3. we want a variable to have a type that can't be inferred (objects with certain props)
   ex - if you want to assign a number OR a boolean depending on the outcome of running a function.
   `let numOrBool: number | boolean;`
   Notice that it's a SINGLE or operater |

## In depth FUNCTIONS and type annotation

Type annotation in FUNCTIONS tells TS what type of arguments the function will receive and what type it will output

Type inference in functions - TS will guess the return type of a value but will NOT guess anything about the args.
`const addOne:(n: number) => number = (n: number) => n + 1;`

There is a shorthand version of this that will be used most times

`const addOne = (n: number):number => n+1;`

for two args
`const twoNums = (a: number, b: number): number => a + b;`

Type inference on the RETURN value of functions is available, but NEVER USE IT!
Always annotate the return value to make debugging easier!

Using keyword function. Same syntax
`function divide(a: number, b:number):number { return a / b }`

Same for anonymous functions
`const multiply = function(a: number, b: number):number {return a * b }`

Function that takes in an object

```
const obj = { a: 2, b:3 };
const printObj = (input: { a: number; b: number}): void => console.log(obj.a, ob.b)

```

Destructuring with annotation is like this:

`const printObj = ( {a, b}: {a: number, b: number}): void => console.log(a, b)

### VOID

Annoting return value as void will accept undefined and null

### Edge Cases with Never

Annoting return value as never will mean the function will never reach the end.
ex.
`const throwErr = (message:string):never { throw new Error(message);};`

but in most cases you'll return something so 'never' is rarely used

## Annotating objects with destructuring

```
const profile = {
  name: 'Patti',
  age: 20,
  coords: {
    x: 30,
    y: 60,
  },
  // using method shorthand
  setAge(age: number): void {
    this.age = age;
  },
};

// if you want to annotate AND destructure at the same time
const { age }: { age: number } = profile;
```

To get the coords.x and coords.y with destructure WIHTOUT annotation,
`const { coords: { x, y } } = profile;`

To do both destructuring AND annotation.. quite nasty syntax
`const { coords: { x, y } }: { coords: { x: number; y: number }} = profile;`

## Arrays

### Typed Arrays

In TS, we USUALLY use typed arrays, which only containe ONE data type.

Type inference is useful when the array is initialized and declared in one line

`const arr = [1,2,3]` TS will infer correctly that this is an array of numbers

If you declare an empty set to initialize later, annotate accordingly.

`let arr; // not good`
`let arr: string[];`

For nested arrays, the syntax is INNER ARRAY first, then to outer level array(s)

so if you are planning to assign arr to [ [3], [3,5,2], [5,6]], which is an array of arrays of numbers,
`let arr:number[][];`

Type Inference will also be applied to extracting values from the array, which is very helpful!
for bracket access, arr[0] - type will be infered correctly
pop(), shift() , and other methods that return an item from an array will all have the correct inference.

Adding annotation in methods will solidify understanding of code

```
let arr = [1, 2, 3];
arr.forEach((item: number): void => {
  item++;
});

// since I'm not returning anything from the callback, return value is void
```

### Multiple Types in Arrays

It's possible to use multiple types.

If declared and initialized at the same time, inference will kick in if NO annotation
`const arr = [34, 'hello', 53];`  
// hovering over arr will say (number | string)[]

If annotating, do it like so
`const arr:(Date | boolean)[] = [new Date()];` // if you want to add boolean later
