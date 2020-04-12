# Typescript

Use type systems to catch errors. Used during development only.

Type annotations are added in js to analyze code.

Typescript transpiles (compiling is going from human code to machine code) to regular js. It provides no performance optimization like C.

## The whole point is to reduce API surface area using class modifiers AND using reusable interfaces that interact with classes

## Setup and compiling

To install typescript, `npm i -g typescript ts-node`
To see if you already have it, `tsc -v` which stands for typescrip compiler

Inside your project dir, make a projectName.ts file
After writing ts, remember it won't just with `node filename.js` like with regular js. You need to compile it first.

In the terminal, you can `tsc filename.ts` to create a filename.js file in the same dir
OR
use `ts-node filename.ts` which compile the typescript file into js, then run it

## Running typescript on the browser the easy way with parcel

npm -g i parcel-bundler

make an index.html with a script tag that reads from index.ts inside src dir

```
<body>
  <script src="./src/index.ts"></script>
</body>
```

then feed the html into parcel from terminal

```
parcel index.html
```

usually the port is localhost:1234

## What is a type in js?

Anything that can be assigned to a variable.

number, string, function, array, object, Date.
All types have their own properties and methods built-in.

1. Primitive Types - number, boolean, string, null, undefined, symbol, void
2. Object Types - functions, classes, arrays, objects

## Type assignment in function parameters

`const print = (a: string, b: boolean) => console.log(a,b)`

Colon and data type after each parameter will specity the type of data coming into the function

## Interface - more in depth below

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

## Turning arrays into tuples.

Tuples are an array like object that has to be ordered in a certain way. You can use typescript to tell the order of each data type.

Tuples can't be made in JS, but you can in typescript.

For a one time annotation:
`const pepsiTuple: [string, boolean, number] = ['brown', true, 40];`

For using it more times

```
type Drink = [string, boolean, number];
const coke:Drink = ['brown', false, 30];
```

## Interfaces

The backbone of TS is interfaces + classes to have reusable code.

Inteface - Creates a new type which describes the property names and value TYPES of an object

Why? For working with objects (especially when calling a function with an object arg), the annotation gets quite long.

```
const printVehicle = (vehicle: { name: string; year: number; broken: boolean }): void => {
  console.log(`Name: ${vehicle.name} \n Year: ${vehicle.year} \n Broken? ${vehicle.broken}`)
}
```

The argument would need to be repeated every time another function calls the vehicle object.

To avoid this, you can set an interface to a type once, then after that simply call vehicle: Nameoftype

```
interface Vehicle {
  name: string;
  year: number;
  broken: boolean;
}

const civic = {
  name; 'honda civic';
  year: 2000;
  broken: true;
}

// now you can call the same function with this new type
const printVehicle = (vehicle: Vehicle): void => console.log(vehicle.year)
```

interface can also define the type of a return value of a method

`interface Vehicle { honk(): void; } // all Vehicle types must have a .honk method that returns void`

Basic idea is that an interface acts as the gatekeeper to functions. Functions take in arguments that are interface types.

## Classes

Classes - blueprint to create an object with keys and methods to represent a "thing"

### Methods Only (easier than working with fields and values)

Refresher for class syntax - method declaration short hand is func() {}

```
class Vehicle {
  drive(): void { console.log('chugachuga') }
}

class Car extends Vehicle {
  drive(): void { console.log('vroom') }
}
const car = new Car()
car.drive() // prints 'vroom'
```

You can extend a class into a child which has the same methods. The methods can be overridden by another declaration in the child.

### Modifiers

In TS, you can add modifiers to class METHODS

public - (default) method can be called any where, any time
private - can only be called by OTHER methods in THIS class, not child classes, meaning another method has to call this function.
protected - can be called by other methods in this class OR by other methods in child classes (that was created with extends)

These modifiers are added before each method declaration

A child class can NOT override the MODIFIER of a method that was inherited from a super class.

### Adding fields

In regular es6 if you are just setting a default prop, color

```
class Vehicle {
  color = 'red';
  year = 2001;
  drive() { console.log('vroom')}
}

```

If you need to take in args (still regular es6)

```
class Vehicle {
constructor(color) {
this.color = color;
}
// methods go here, outside the constructor
}

```

In typescript, you need to declare the Type FIRST before the constructor AND inside the parens

```
class Vehicle {
color: string;
constructor(color: string) {
  this.color = color;
}
// methods
}
```

But there is a shorthand for the above. You can add the modifier public in the arg

```
class Vehicle {
  // omit this line now
  constructor(public color: string) {
// omit this too
  }
}

// This will add the field, color of type string and is the same thing as the previous code example
```

You can add private or protected if you don't want direct access to Vehicle.color.
Notice how in fields, public IS NOT default. You must explicitly write it

If a child class that extends Vehicle in the above example does NOT have a constructor function, it will call the
constructor of the super class automatically.

If you want additional args for the child class, you must call the parent constructor method manually by super()

```
// let's say only the child class Car asks for wheels

class Car extends Vehicle {
  constructor(public wheels: number, color: string) { // since color belongs to the parent class, do NOT add public here again
    super(color);
  }
}
```

## Interfaces AND Classes

Using both interfaces AND classes is the basis of making good, reusable code in TS.

## Design Patterns in TS

Projects are usually structured into THINGS which are classes. Each of those classes are in separate files
and exported to the index.ts file, which is rendered in the html through parcel.
Convention is to use capital first letter like User.ts for classes

## NPM Package imports in Typescript

If you do the usual es6 syntax , import { thing } from 'npmPackageName'; ,
TS will throw an error, `Could not find a declaration file for module 'npmPackageName'`

All libraries being used in typescript needs a Type definition file which is like an adaptor to use JS libs in TS.
In some cases, type definition files are automatically downloaded when you npm i (like Axios)
Others, iike the faker module, does NOT include a type definition file in the install.

The error above means that you need to make a type definition file.
The majority of libraries already have type definition files available.
The project is called

            Definitely Typed

         Definitely Typed Naming Scheme

           Usually -   @types/{libraryName}
           specific ex. @types/faker
          google @types/faker npm to see if it exists and if it was made by credible source like Definitely Typed
          if so, simply `npm i @types/faker` on the project root dir

After getting the type definition files, you can command+click on the import statement to see the file itself, which serves as good documentation for the package!

If there is still a problem, try typing this INCLUDING the triple slashes at the top of the file.

`/// <reference types="@types/faker" />` or whatever the Definitely Typed Package was

If the module was default exported, you may see `This module is declared with using 'export =', and can only be used with a default import when using the 'esModuleInterop' flag.`

Simply, `import * as faker from 'faker';` to do the trick, OR just pull out the sub modules you need
`import { name, address } from 'faker';`

## import / export convention

In typescript files are USUALLY as regular export, even if there is only 1. Import files need curlies.
Note how in react, every component is usually exported with default so imports don't require curly braces.

## Type definition files

Make a habit of looking inside type def files as the documentation.

Often helpful to use command palette "fold 2" to only show methods and props

Usually, you make a new instance of a class with some args.
Also good to search keyword "required" if something isn't working in case you are missing some args.

## Hiding Functionality

Using private and protected will hide functionality in the app to minimize breaking.

## Why you always use interfaces

If you are dealing with multiple classes, say you make a method

`printProps (thing: Animal | Car):void {console.log(thing.name)};`

When you use the pipe | or operater on classes, they will ONLY have access to common properties and disgard all other unique props inside those classes.

If you use an interface on a function, it will FILTER out the requirements of classes.

```
interface Printable {
  name: string
}
const printProps = (thing: Printable): void => console.log(thing.name);
```

It is even better to export the interface to the class declaration files and add

## class IMPLEMENTS interface

`class Person implements Printable {}` adding keyword 'implements' and the interface name in the class declaration will
let ts know that the class SHOULD satisfy the interface requirements.
