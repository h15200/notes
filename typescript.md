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
use `ts-node filename.ts` which skips building index.js and just runss the ts

Best practice to have a src dir with the ts file (which you write)
and a build dir with the compiled js file (which tsc biulds automatically which you don't touch)

To do so, make a tsconfig.file by running on the terminal
`tsc --init` inside the ROOT dir, not the src or build subdirs.

### tsconfig file

You have access to many options, including
outDir and rootDir useful for file structure. They should be next to each other and relatively close to the top of the options

uncomment and edit the rootDir to be `"./src"` and outDir to be `"./build"`

(This is not the BEST way) but, now all you need to do in the root project dir is `tsc -w` and it will -w WATCh all ts files in src, and compile into build.

Now you have an automatic ts complier that is running on save. Note that this does not run the newly built js file on save.

### NODEMON and CONCURRENTLY

The watch process is useful, but we still need a way to run the new js file.
You COULD just open a new integrated terminal window and hit node build/index.js, but there is an even better way!

npm init -y in root, then npm i nodemon concurrently
nodemon will run a js file anytime the file is changed. This will be used on the build js file
concurrently allows us to run multiple scripts at the same time. one for starting tsc, and one for nodemon at the same time

package.json file scrypt should look something like this:

```
"start:build": "tsc -w",
"start:run": "nodemon build/index.js",
"start": "concurrently npm:start:*"
```

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

## Why you should always use interfaces

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

## class IMPLEMENTS interface

It is even better to export the interface to the class declaration files and add

`class Person implements Printable {}` adding keyword 'implements' and the interface name in the class declaration will
let ts know that the class SHOULD satisfy the interface requirements.

## Type Guard

Allows to tell typescript which data type you are dealing with at certain points of the code.
Remember, an annotation with union | will limit syntax and method to one that's common to all data types unioned, which is bad.

for strings, numbers, booleans, symbols and ALL other primitive types
`if (typeof thing === 'string') {} // don't forget that the type check is a string. 'number', 'string', 'boolean', etc..`

syntax for objects, Date, arrays, classes, anything with a constructor function
`if (thing instanceof Array) {}`
wrap all code that applies with curly braces

## Advanced work flow. ex. sorting

The main issue with classes ONLY approach is that you want reusable code. You always start with a class that has methods.
When you think about what type the class takes in the constructor, you run into problems as you want a wide range of data types, but
using union operator | makes everything an inner join which is bad, and even use type guards makes the code very long and hard to read.

The solution is to always have the generic main class take in an INTERFACE which can take in a wide range of data types as long as the minimum requirements are present.

1. Usually start with a main class that contains a method with the logic only.
   Looks almost like pseudocode

Sorter.ts (capitalized for class)

```
class Sorter {
  sort() {
    for () // short hand for example. In reality, you would implement two for loops for a bubble sort.
    for()
    if (this.collection.compare()) {
      this.collection.swap()
    }
  }
}
// sorter will not have access to numbers directly. It will only deal with NumbersCollection.
```

2. Make an interface Sortable that says, anything with a length, a sort, and a swap can be plugged in into sort.

3. Make classes by data type that satisfies the interface, and does the logic for figuring out length/sort/swap for that data type.

NumbersCollection.ts (just for arrays of number)

```
class NumbersCollection implements Sortable{
  data: number[];
  swap (i, j);
  compare(i, j);
  length: number

}
```

4. Now you can plug in any data type into the first function as long as it satisfies the interface!

## Type annotation for functions with edge cases

If you want to write edge cases for functions, do not allow the function to return null.
Instead, throw errors.

For example, let's say you want to return the index

```
// bad example:

at(index:number): number | null{
  if (index < 0 ) {
    return null
  }
  else return arr[index]
}
```

```
// better
at(index: number); number {
  if (index < 0 ) {
    throw new Error('input is out of bounds')
  }
  else return arr[index]
}
```

## Abstract classes

In TS, classes that never get called directly to make a new object is useful.
Abstract classes puts restrictions on a class so that it can only be a parent class (called by extends)

Since it's always being extended in another class, it can contain references to "this" that may not make sense on its own, but works in the context of the child class.

ex

```
class Print {
  print(): void {
    console.log(this.age)
  }
}
// here this.age doesn't exist, and would trigger an error, but it makes sense in the next scenario.

class Child extends Print {
  constructor(public age: number) {}
  // now this.age exists
}
```

Above is the perfect use case for abstract classes so that typescript doesn't triggter errors.

The syntax looks like this. Make sure you include the abstract promises in the body

```
abstract class Print {
  abstract age: number;
  print(0: void {
    console.log(this.age)
  }
}
// this abstract class PROMISES that the child class will have a property called age, which is a number, which can be accessed with this.age
```

## Interfaces vs Inheritance / Abstract Classes

Interfaces

1. Sets up a contract between different classes
2. Use when you have different objects that we want to work together
3. Loose coupling

Abstract Classes / Inheritance

1. Sets up a contract between different classes
2. Use when we are trying to build up a definition of an object
3. Strongly couples classes together

## Using node apis inside typescript

Just like npm packages, TS needs type definition files for fs, http, os, and other node APIs.
You can NOT use the standard `const fs = require('fs')` as TS will not recognize the library.

For regular npm libraries, we searched for @types/{packageName} for type def files.

For node APIs, it is NOT the case. It is always the same file, @types/node
`npm i @types/node`

Now you can use `import fs from 'fs'`
As typescript can use es6 moduels.

You can also use the old `const fs = require('fs')` now

## enum (enumeration)

Also used in databases
Enums set a parameter for accepted values.

The main usage is to let the dev team know that these are the possible values for this topic.

Convention to use capital leter for the enum type as well as each value
Syntax - notice how the value of each type is assigned by an equal sign and not a semi colon.

```
enum MatchResult {
  HomeWin = 'H',
  AwayWin = 'A',
  Draw = 'D'
}
```

This also creates a type inside typescript. Values are accessible by MatchResult.HomeWin
Syntax for calling values are the same as objects.

It is possible to create an enum without assigning any values.

When compiled to JS, enums are turned into JS objects.

Enums should be used for a KNOWN, SMALL set of data that doesn't change over time.

### enum type assertion

After declaring enum, you can assert the type of 'H', 'A', or 'D' with keyword as.

```
let char = 'H';

let x = char as MatchResult
// char is still a string
// x is type MatchResult and not a string
```

## 2 Main concepts of making reusable code

1. Inheritance - Abstract classes to make a class CREATOR through extending the template class. Add placehold generics for the exact type that the creator class reads. This is defined in the child class.

Inheritance = Is a relationship. One class IS an instance of another class.

2. Composition - Make an interface for the adaptor to plug into classes. Usually will involve making 2 classes that work with each other.

Composition = Has a relationship. One class has a relationship with another, but it is not an intance.

## Inheritance + Geneerics

Like function arguments, but for types in class/function definnitions
Allows us to define the type of a property/argument/return value at a FUTURE point
Used heavily for reusable code.

syntax:

```
class HoldNumber {
  data: number
}
 const holdNum = new HoldNumber;
holdNum.data = 5;

class HoldString {
  data: string
}
const holdStr = new HoldString;
holdStr.data = 'hello!'

// a better way to do both above using generics is:

// much like function arguments, this promises the new key word declaration to have a TYPE generic
class HoldAnything<TypeOfData> {
  data: TypeOfData;
}

const holdNumber = new HoldAnything<number>(); // this created HoldNumber

Now for the class instance, holdNumber, everything inside the class where it said <TypeOfData> is replaced by string!
```

Generics are even more powerful when used with abstract classes
By convention, `<TypeOfData>` is usually abbreviated to just `<T>`

```
export abstract class CsvFileReader<T> {
  data: T[] = []; // empty strings can be valid for a string of tuples.
  constructor(public fileName: string) {} // assigns input to this.fileName
  abstract mapRow(row: string[]): T;

  read(): void {
    this.data = fs
      .readFileSync(this.fileName, {
        encoding: 'utf-8',
      })
      .split('\n')
      .map((row: string): string[] => row.split(','))
      .map(this.mapRow); // to array of strings
  }
}

// another file with the child class
import { CsvFileReader } from './CsvFileReader';
import { MatchResult } from './MatchResult';
import { dateStringToDate } from './utils';

type MatchData = [Date, string, string, number, number, MatchResult, string];
// tuple type

export class MatchReader extends CsvFileReader<MatchData> {
  mapRow(row: string[]): MatchData {
    return [
      dateStringToDate(row[0]),
      row[1],
      row[2],
      parseInt(row[3]),
      parseInt(row[4]),
      row[5] as MatchResult,
      row[6],
    ];
  }
}

// with the child class MatchReader, now class CsvReader will replace <TypeOfResult> to MatchData, which is a tuple - [Data, string, string, number, number, MatchResult, string];
// const newMatch = new MatchReader(fileName);
```

REMEMBER once T is declared in the beginning of the class <T>, the following references will just be T without <>

## Composition + interface

```
export class CsvFileReader {
  data: string[][] = []; // empty strings can be valid
  constructor(public fileName: string) {} // assigns input to this.fileName
  read(): void {
    this.data = fs
      .readFileSync(this.fileName, {
        encoding: 'utf-8',
      })
      .split('\n')
      .map((row: string): string[] => row.split(',')); // to array of strings
  }
}

// then in another file

import { dateStringToDate } from './utils';
import { MatchResult } from './MatchResult';

type MatchData = [Date, string, string, number, number, MatchResult, string];
// tuple type

interface DataReader {
  read(): void;
  data: string[][]; // this can initially be empty array
}

// MatchReader is constructed with a DataReader type, which contains a read() method and data
export class MatchReader {
  matches: MatchData[] = [];
  constructor(public reader: DataReader) {}

  load(): void {
    this.reader.read();
    this.matches = this.reader.data.map(
      (row: string[]): MatchData => {
        return [
          dateStringToDate(row[0]),
          row[1],
          row[2],
          parseInt(row[3]),
          parseInt(row[4]),
          row[5] as MatchResult,
          row[6],
        ];
      }
    );
  }
}
```

## Current trend, Misconception of composition

Composition vs Inheritiance is valid discussion, but the definition of composition is mostly incorrect in the js community.

Composition involves DELAGATION, which means a class has reference to another intance of a class rather than being another class.

```
const rectangular = state => {
  return {
    area: ()=> state.height * state.height
}
}

const openable = state => {
  return {
    toggleOpen: () => { state.open = !state.open}
  }
}

const buildRectangleWindow = state => {
  return Object.assign(state, rectangular(state), openable(state))
}

This is just another version of INHERITANCE and NOT composition
```

## other tips

As a reminder, an interface is a type for objects and instances of types that's used to feed to the constructor method when invoking a new class (usually)

When using multiple compositions, you may notice that you want to call a function through the class WITHOUT creating an instance of it. Youc an use static functions that can be called by the class ITSELF (as opposed to an instance of a class). Static methods are written with the keyword static before the constructor. Remember, the constructor info is not available for static methods as those are only present in instances of that class

Using static classes will make the code much less verbose, but it may not be clear to other devs what the implementation are without going inside each class declaration files

## More advanced generics

```
class ArrayOfAnything<T> {
  constructor(public collection: T[]) {}
  get(index: number): T {
    return this.collection[index];
  }
}

const test = new ArrayOfAnything<boolean>([true, false, false]);

// however, type inference will kick in so you don't even need to specify <> when calling an intance

// this is ok
const test = new ArrayofAnything([true,false,false])
```

This is type inference around generics for classes.
Although it's useful, it is better to always put in <type> in the invokation to check for errors

## Generics with Functions

syntax for regular declarations

```
function printFirstElementOfArrOfAnything<T>(arr: T[]): void {
  console.log(arr[0])
}

printFirstElementOfArrOfAnything<string>(['hi', 'there'])
// again, instead of relying on type inference for generics, always best practice to specify <type>
```

For es6

```
const printFirstElementOfArrOfAnything = <T>(arr: T[]): void => {
  console.log(arr[0]_)
};
```

## Generic Contraints in functions

Sometimes, you need something specific from a generic for future use, like a method on that.
To do that, you must put a contrainst on the generic with an interface and extending.

```
// generic constrains
// what if it's an array of objects with print methods inside?

class Car {
  print() {
    console.log('I am a car');
  }
}

class House {
  print() {
    console.log('I am a house');
  }
}

// returns error since TS doesn't know that T will have a prop of print without interface
// solution is to make an interface and have T extend an interface

interface Printable {
  print(): void;
}

const printCarOrHouse = <T extends Printable>(arr: T[]): void => {
  for (let i = 0; i < arr.length; i++) {
    arr[i].print();
  }
};

printCarOrHouse<Printable>([new Car(), new House()]);
```
