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

Semicolon and data type after each parameter will specity the type of data coming into the function

## Interface

Interface will define the structure of a new Type

```
interface Todo {
  id: number;
  title: string;
  isDone: boolean;
}
```

Notice how each statement ends with a SEMICOLON and not a comma like in regular objects.
tells what kind of data you will expect in each specified property.
It's fine to not define every property. If the todo Object had other properties, they will simply be ignored

Now any future objects can be treated as a Todo type
with the syntax `const a = obj as Todo;`
