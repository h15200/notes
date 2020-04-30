# Cheatsheet

Interface - a type for objects
Type Guard - for multiple types, remind ts by writing if type of this value is something, then this

generics - `<T>` - args for classes and class methods
can be extended from an interface by `<T extends interfaceName>`
`<K extends keyof T>` - any of the keys of T

abstract classes - classes that can only be used as a parent class. Must be extended by a child class
class implements interfaceName - let's ts help you build a class that satisfies the interface

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

## Setting up a TS project JUST IN NODE

### tsconfig file

You have access to many options, including
outDir and rootDir useful for file structure. They should be next to each other and relatively close to the top of the options

uncomment and edit the rootDir to be `"./src"` and outDir to be `"./build"`

(This is not the BEST way) but, now all you need to do in the root project dir is `tsc -w` and it will -w WATCh all ts files in src, and compile into build.

Now you have an automatic ts complier that is running on save. Note that this does not run the newly built js file on save.

### File structure and tsconfig

For the tsconfig to apply correctly, you must call ts-node from within that same dir level! if you call ts-node somedir/somefile, then the file will be called as if there were no tsconfig files attached to it!!

### NODEMON and CONCURRENTLY

make sure there is an index.ts inside src

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

## Running typescript ON THE BROWSER the easy way with parcel

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

### Optional properties

```
interface User {
  name?: string;
  age?: age;
}
// it CAN have a name and it CAN have an age, but it doens't have to.
// what about empty objects? YES! so implement the logic so that it doesn't become a problem.
// for example, a setter should use something like Object.assign(thingToChange, interfaceObject) so that an empty set
// won't make any changes.
```

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

If you want to annotate a callback, syntax is <nameofcallback>: (argOfCallback) => {}

```
const someFunc = (number: number, callback: () => {}): number {
  return callback(number)
}
```

## Type Alias

You can use a type alias to create the callback annotation outside the function as well.
`type Callback = () => void`

Note how in the function body way, it's func: () => {}  
but in the alias, it's () => void
they both say a function that takes in no args and returns void

now `const someFunc = (number: number, callback:Callback) { return callback(number)}`

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

### Type annotation of objects where you DON'T know the name of the properties

ex. {a: 1, b:2 }

data: { [key: string]: number }
// data is an object with an unknown set of properties, but the properties are all strings and the values will all be numbers

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

## Using node apis inside typescript

Just like npm packages, TS needs type definition files for fs, http, os, and other node APIs.
You can NOT use the standard `const fs = require('fs')` as TS will not recognize the library.

For regular npm libraries, we searched for @types/{packageName} for type def files.

For node APIs, it is NOT the case. It is always the same file, @types/node
`npm i @types/node`

Now you can use `import fs from 'fs'`
As typescript can use es6 moduels.

You can also use the old `const fs = require('fs')` now

## Hiding Functionality

Using private and protected will hide functionality in the app to minimize breaking.

## Why you should always use interfaces

If you are dealing with multiple classes, say you make a method

`printProps (thing: Animal | Car):void {console.log(thing.name)};`

When you take in a constructor arg and set the TYPE to with a union (pipe | ), they will ONLY have access to common properties and disgard all other unique props inside those classes. It's better to take in one THING which is of a certain interface

If you use an interface on a function, it will FILTER out the requirements of classes.

```

interface Printable {
name: string
}
const printProps = (thing: Printable): void => console.log(thing.name);

```

## class IMPLEMENTS interface

if you exactly how a class instance will be used, you can use class implements interfaceName to let TS help you build the class.

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

## Abstract classes (often used with inheritance)

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

## Inheritance + Abstract + Geneerics

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

## Composition + interface + generics

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
area: ()=> state.height \* state.height
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
console.log(arr[0]\_)
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

## Type Alias with strings.

In TS, specific STRINGS can be their own type.

So, you can set up types as such.

`type TypeName = 'hello';`

All object keys are strings.
So object KEYS can also be their OWN type as well.

which leads to:

## Advanced Generic Contraints

### <K extends keyof T>

Example of situation.

You made a class that has a getInfo method that takes in an object in the constructor.
You don't want to make an interface for the arg because you want it to be a generic, universal model.

So you use

```
class printAnyValue<T> {
  constructor(public obj: T) {}
  get (key: string): void {
    return this.obj[key]
  }
}
```

But you don't know what to write in the return of the print() method because it could be ANY data type based on the incoming obj.

If you use a union |, it will be hard on the invoking end because

```
const testPrint = new printAnyValue({id: 3});
testPrint.get('id');  // this value can be anything and TS is confused

```

To solve this problem, extend the T object and create K, a key generic BASED on the T generic!

```
class printAnyValue<T> {
  constructor(public obj: T) {}
  get<K extends keyof T>(key: K): T[K] {
    return this.obj[key];
  }
}

// type of K must be one of the keys of T
// Create K just efore the method arg
// keyword 'keyof' will make a KEY of a Generic, T
// in the arg, key is now type annotated as a K
// the return value is the result of calling the value of T object with the key K

```

## Composition logic

Logic work flow

1. Make one mega class `class Window which has height, shape, weight`
2. Extract logic out by category into another class `WindowWeight class, a WindowShape class, a WindowHeight class`
3. Implement a way to connect the main class to those other classes DEPENDING ON THE PROJECT!
   Methods to connect classes (#3 option from above)

   1. You can add a contructor arg to the main class, which requires an instance of the task-class.

      ```
       // MainClass takes in TaskClass instance

      class MainClass {
        constructor (public dataToMakeMain, instanceOfTaskClass) {}
      }

       // First make an instance of TaskClass.
       // Then pass that instanceinto the Main on top of whatever constructors.

       const task = new TaskClass(dataToMakeTask)
       const main = new Main(dataToMakeMain, task)

      ```


           This is easy to read, but can be cumbersome if there are many taskClasses that need to be instantiated, then passed on to the MainClass. This method has the most flexibility if you want a vast variety of instances of TaskClass, as you have full control when you are making a new TaskClass

           This can be improved by using a default in the constructor like
           `constructor (public dataTomakeMain, instanceOfTaskClass = new TaskClass()) {}`
           So that an empty arg will automatically create the default new TaskClass and pass it in.


    2. Define a static class method (a method you can call on the class itself without creating an intance) to do boilerplating of method 1 internally. The static class is used to make a new instance INSTEAD of using new MainClass()

        ```
        // Inside MainClass, change the constructor to JUST taking in the task class
        // remember, although you can, the purpose now is to make a new instance of MainClass without calling new MainClass, but using MainClass.staticMethod(). So the constructor is there simply to be used by the static class.

        class MainClass {
        static staticMethod(dataForBothMainAndTask) {
          do stuff with dataForMain
          new TaskClass()
          make new MainClass(passInNewTaskClass)
          return the new MainClass
        }
        constructor (public instanceOfTaskClass) {}
        }

        Thie method is good if you are only planning to use 1 or 2 different instances of taskClass, as each would need to be a separate static method inside the main class. Saves lines of code so you don't have to write out many new classes.
        ```

    3. hard code class instances as props of main

      ```
      class Main {
        task: new TaskClass();

        constructor(public data: StuffForMain) {}
      }
      ```

      A new Main class automatically comes with the default class as a prop. Not flexible in terms of getting a variety of
      instances of taskClass, but if it's always the same one, the easiest to implement.

## Strict Mode - Optional Properties

When using an interface with optional properties `interface { thing?: number }`, using tsc --init and creating a tsconfig.json file will change the behavior as it will turn ON strict mode. Strict mode will check for number AND undefined.

Firstly, change target.
Defaults to ES5 syntax - set target in TSCONFIG to `es6`

Strict mode is usually a good thing, but you might need some additional type guards with things like

HTML elements - with false mode, accepts null OR element. If true, then you have to specify after each query

## Composition workflow

1. Make one big mega class with all the functionality for the app
2. Take out functions by type, and make them universal. Start using interfaces, generics, if necessary
3. In this last step, it may actually make sense to use inheritance to mix and match methods

## Pass through methods, shorthand

In composition, it's useful to make getters return the delegation function directly so you can call `user.get('id') instead of something like user.attributes.get('id')`

You can do that by having a getter inside user that returns user.attributes.get.

Usually it looks like this

```
get on() {
  return this.events.on;
}
```

But it can be shortened to
`on = this.events.on`

Notice how there is no parens, and no return keyword.
For getters, you don't even need to use () as it can NOT have an arg anyway

## Watch out when using shorthand getters

In TS (and maybe also in JS?) shorthand getters get compiled BEFORE constructor args.
If you are accessing delagate methods that uses the constructor

```
constructor(something:string) {
  this.something = something }
```

Or even just initializing a property. This also comes AFTER the getter

```
class Animal {
  shape = new Mammal()
}
```

,references to this WILL NOT WORK as the getter code will be set BEOFORE the constructor code.

However, if you sed the shorthand constructor method like
`constructor(public something: string) {}`

Then the constructor will run first!!

So code order is:

1. constructor shorthand
2. getter shorthand
3. constructor long hand, any other initialization
4. getter long hand

## Interfaces can be generics too

Just classes, interfaces can be generics too
Useful when making an inheritance model as well

## Multiple Generic Types

You can pass in more than one type

```
class Something<T, K> {

}
```

Second one is usually labeled `<K>`

## reminder type annotation for objects where you don't know the key

`{ [key: string] : number }` // an object where the keys are a string (obviously) and the values are numbers

## Syntax for nested generic classes

`export abstract class View<T extends Model<K>, K> {}`

Model is also an abstract class, so it needs an arg. The arg for model is K, which can be declared AFTER being used

## Typescript And Express

Because Classes were built in es6 in 2015, a lot of frameworks that existed before then don't work well with typescript.

TS and JS libs can be navigated in three ways

1. Use the lib normally, adding in basic annotation where possible. Avoid classes.
2. Use a TS adaptor that has helpers for your lib and use classes
3. Twist your lib to work with TS classes.

## Express with Typescript

We will skip method one - use the lib normally, adding in basic annotation as it is self explanatory. In the case of Express, it barely helps because what you need the most help with TS is req and res data. With method one, you can't type check anything inside those.

Set up with nodemon, concurrently and tsc -w (see above)

`npm i express @types/express` // don't forget typedef file
import {Reponse, Request} // interfaces built in type def

Why is typescript hard to implement with express?

Express is used on top of node to use middlewares to change the request/response data.
Then express will call next() to the next middleware, or if there are none, to what we wrote.

1. Typescript has no way of knowing what or how the middleware manipulated the req/res objects.

2. The typedef file will sometimes give the WRONG information.

For example, if you are using the body-parser middleware, the req object will now have a req.body property. This will NOT exist if you didn't use body-parser.

req.body should show an error in typescript if it wasn't accounting for ANY middleware. However, in the express typedef file, a body property IS defined, assuming that the user WILL use body-parser.

## Making tweaks to express typedef file

BAD IDEA! Never change the typedef file, even if it's not a great one!

A better if to define an interface at the top of your own file.
The interface should extend whatever object you want to improve with types.

Override the property that you want to modify.

You may have to use type guards after you have modified.

example with express and body-parser example would be

```
interface RequestWithBody extends Request {
  body: { [key: string]: string | undefined };
```

## Method two - use ts adaptor with classes and decorators

First, determine if it's worth it. Does this significantly enhance the development process? Do you get much better type safety as a result?

If you think yes...

### Refresher: vanilla JS constructors and prototypes

Remember there are no such thing as classes. They're all functions that's called with new thing(), which creates and object.

PROPERTIES refer to class properties that return a primitive type - string, number, boolean.
class properties are made in the CONSTRUCTOR, which is only ran upon instantiating a class.

Methods and accessors (getters) are stored in the PROTOTYPE of the class, which means the class itself without it even been instantiated.

Prototypes can be appended to a class AFTER it's already been instanticated, and that instance will also gain the new method when the class is changed.

1. A property on an object or class is a primitive type that can be assigned to a sting key.

Animal.age = 13

2. An Accessor is a getter function that doesn't require parens.

3. A method is a function that requires writing () to call.

## What are typescript decorators?

Decorators - are FUNCTIONS that can be used to modify different properties/methods inside a class.

JS decorators also exist, but TS decorators are different.

Used inside/on classes ONLY.

Understanding the order in which decorators are ran is key

They are experimental at this point in 2020.
You may need to `tsc --init` to make a `tsconfig.json` file and turn on `experiementalDecorators: true` as well as `emitDecoratorMetadata: true`

code example

```
// here inside boat he have a PROPERTY of color, an ACCESSOR formattedColor, and a METHOD, pilot.

class Boat {
  color: string = 'red';

  get formattedColor(): string {
    return `The boat color is ${this.color}`;
  }


  pilot(): void {
    console.log('swish');
  }
}

```

the decorator function

```
function testDecorator (target, key) : void{
console.log(target)
console.log(key)
}
```

APPLYING the decorator means simply add this code ABOVE the declaration of the property/method/accessor.

In this example, now we insert `@testDecorator` right above the pilot method.

```
class Boat {
  color: string = 'red';

  get formattedColor(): string {
    return `The boat color is ${this.color}`;
  }

@testDecorator
  pilot(): void {
    console.log('swish');
  }
}

// output is
Boat { formattedColor: [Getter], pilot: [Function]}
pilot
```

Notice how the decorator ran automatically on the class itself without having to create any new classes.

1st arg, target, will be the PROTOTYPE of the class
remember, the prototype only contains accessors and methods and NO properties, which is why color was not printed.

2nd arg, is the key of the property/accessor/method that we applied the decorator to,
in this case we applied it to ONLY the pilot method, we we get output 'pilot'

We didn't put in a third, but a 3rd arg is an object called the property descriptor.

The decorator is run ONLY once when the class is first defined.
It does not get run when an instance of the class is created.

All its doing is calling the decorator function ON what whatever method it's on top of, and the 1st arg is always the class prototype and the 2nd arg is key name of the prop/method/accessor.

### what is a property descriptor

usually shorhand `desc` and the type is `PropertyDescriptor`, available on default js
This is an object that has configuation options around a property defined on an object

propertyDescriptor is available on regular js

All object properties (including accessors and methods) have a property descriptor object that shows 4 thigns

1. writable - can value be overwritten?
2. enumerable - will key/value show up in a for - in loop?
3. value - the value attached
4. configuarable - can property definition be changed?

To access it in JS,

`Object.getOwnPropertyDescriptor(obj, key;`

To CHANGE the property descriptor,

`Object.defineProperty(obj, key, { writable: false })`
// now you've changed the property such that its value can't be updated!

### Using property descriptor inside a descriptor

Going back to the example above with the additional third argument, the desc (shorthand for property descriptor)

```

class Boat {
  color: string = 'red';

  get formattedColor(): string {
    return `The boat color is ${this.color}`;
  }

@myDecorator
  pilot(): void {
    throw new Error();
  }
}

funcion myDecorator(target: any, key: string, desc:PropertyDescriptor):void {

  // desc is the propertyDescriptor for the method, pilot
  // desc.value = someOther Function
  // will reassign another function to the method, pilot

  // now we have the power to modify the function with this, and still have reference to the original:

  const method = desc.value;   // store the original func

  desc.value = () => {
    try {
      method();
    }
    catch(e) {
      console.log('Oops we have an error')
    }
  }
}


```

A decorator can intercept a method or property or an accesso and modify it.

### Property Descriptor limit

Since property descriptors only applies to objects, putting that third arg of the descriptor on a property like a .color or size will not be valid. Only put in 2 args (target and key) for all descriptors that are applied to properties

### Decorator function invocation, factory decorators

When calling a decorator with the syntax `@decoratorName`, you can call it with args if the decorator is wrapped with another outside function.

```
function decoratorContainer (anyArgYouWant) {
 return actualDecorator(target, methodApplied, descriptorOfMethod) {
   stuff
 }
}

@decoratorContainer(anyArg)
```

Always remember to RETURN the inner function!

### Class properties

Since properties (as opposed to methods/accessors) are made in the constructor upon creating an INSTANCE of a class, you can't find properties inside the target arg of a decorator since decorators only run on the class DECLARATION without any instances.

As a result, decorators are usually pointless when applied to class properties.
It's usually applied on methods/accessors.

### other decorator usage - class decorators, arg decorators

Decorators can also be applied to the class itself, and also as an argument to a method inside the class.

when applied to the class itself, it only takes in one parameter, the CONSTRUCTOR of the class

When applied to a method arg, it takes in the target, string, and the index number of itself (in relaiton to the other args on the method)

The class decorator always runs LAST, after all the inside method and property decorators
This functionality is what we can manipulate to add route definitions in express.

## Making express work with typescrip in OOP using decorators.

1. node executes code
2. class definitions are read - decorators are executed immediately before the class being instantiated
3. decorators associate route configuration using METADATA (more below)
4. All method decorators run
5. class decorator of the controller runs last and reads metadata from each method and adds route definitionto router.

### Metadata

Proposed feature in js and ts.
Snippets of info that can be added to class properties, class methods, or the class definition itself
TS will optionally provide type information (that's usually lost at compile) as metadata
Read and written using the `reflect-metadata` npm package.

To use metadata, like decorators, you must
`tsc --init` to make a `tsconfig.json` file and turn on `experiementalDecorators: true` as well as `emitDecoratorMetadata: true`

You also need npm reflect-metadata

`npm init`
`npm i reflect-metadata`

simply
`import 'reflect-metadata'`

now you have a Reflect object inside your ts file.

### Reflect.defineMetadata, Reflect.getMetadata

Attaches metadata key and value pair to object
1st arg is key
2nd arg is arg 1's value
3rd arg is the object to attach
4th optional - key string -if available, this will assign the metadata to the SPECIFIC property IN that object

```
const plane = {
  color: red
}
Reflect.defineMetadata('note', 'hello!', plane);

// using 4th arg
Reflect.defineMetadata('anotherNote', 'hey there!', plane, 'color')
```

The metadata will not show up on console.log or on the object in dev console.
You can only retrieve it with
`console.log(Reflect.getMetadata('note', plane));`

for the 2nd example, also add the key of the particular prop
`console.log(Reflect.getMetadata('anotherNote', plane, 'color'));`

For get, just pass in the key and the object and the value will be returned.

### Back to decorators

Use decorators to add metadata to a CLASS now.

zoom out one more and use factory decorators so that you have even more control

## Typescript and react / redux - could be complicated, but documenting just in case you want to use it

Pros and Cons

Pros
Easy to debug incorrect action types (misspelling)
gives dev a better understanding of type of data flowing around
easier to refactor just about anything

Cons
Not the best type def files, especially for redux
A lot of generics
Tons of imports (action creator, action, reducer) for type annotation
Redux is inherently functional in nature, so tough integration with classes

## using create-react-app with typescript

go to project dir,
`create-react-app . --typescript` //also try adding --use-npm

You'll notice ts files are labeled as tsx.

Make a new App.tsx file in src and try to connect with a class component as you usually would

```
import React from 'react';
import ReactDOM from 'react-dom';

class App extends React.Component {
  render() {
    return <div>Hi There</div>;
  }
}

ReactDOM.render(<App />, document.getElementById('root'));
```

## TSX files

TSX files are used to use typescript + js + jsx

## Annotating props

All class componenets are generic classes, so you can make an interface for props and pass it in as a class arg.

Note how color is an optional property in case you DON'T want to pass on color as a prop.

```
import React from 'react';
import ReactDOM from 'react-dom';

interface AppProps {
  color?: string;
}

class App extends React.Component<AppProps> {
  render() {
    return <div>{this.props.color}</div>;
  }
}

ReactDOM.render(<App color="red" />, document.getElementById('root'));
```

### Defining state inside constructor vs property

```
class App extends React.Component<AppProps> {

   state = { counter: 0 };

  onIncrement = (): void => {
    this.setState({ counter: this.state.counter + 1 });
  };

  onDecrement = (): void => {
    this.setState({ counter: this.state.counter - 1 });
  };

  render() {
    return (
      <div>
        <button onClick={this.onIncrement}>Increment</button>
        <button onClick={this.onDecrement}>Decrement</button>
        {this.state.counter}
      </div>
    );
  }
}

ReactDOM.render(<App color="red" />, document.getElementById('root'));
```

The above is the same code as below in js

```
constructor(props: AppProps) {
    super(props);
    this.state = { counter: 0 };
  }

  // rest of stuff

```

But in typescript, since classes are generic classes, any time you want to use the constructor, you have to pass in two class arguments.

The first method is actually overriding the state object in the generic class, which is why it works.

To use the constructor method, make another interface for the state and pass it in like this

```
interface AppProps {
  color?: string;
}

interface AppState {
  counter: number;
}

class App extends React.Component<AppProps, AppState> {
  constructor(props: AppProps) {
    super(props);
    this.state = { counter: 0 };
  }

  // state = { counter: 0 };

  onIncrement = (): void => {
    this.setState({ counter: this.state.counter + 1 });
  };

  onDecrement = (): void => {
    this.setState({ counter: this.state.counter - 1 });
  };

  render() {
    return (
      <div>
        <button onClick={this.onIncrement}>Increment</button>
        <button onClick={this.onDecrement}>Decrement</button>
        {this.state.counter}
      </div>
    );
  }
}

ReactDOM.render(<App color="red" />, document.getElementById('root'));

```

Take the first approach by NOT using a constructor to assign state. Just understand that you are overriding the state type.

### for functional components

For functional components, we return jsx.
JSX.element is the correct type that comes with the typedef.

```
const App = (props: AppProps): JSX.Element => {
  return <div>{props.color}</div>;
};
```
