## key in object syntax

- the inverse of `if (key in object)`needs to be parenthesized like so
  `if (!(key in object))`

## Property Descriptor

- All object properties (including accessors and methods) have a property descriptor object that shows 4 things

1. writable - can value be overwritten?
2. enumerable - will key/value show up in a for - in loop?
3. value - the value attached
4. configuarable - can property definition be changed?

- To access it in JS,

`Object.getOwnPropertyDescriptor(obj, key;`

- To CHANGE the property descriptor,

`Object.defineProperty(obj, key, { writable: false })`
// now you've changed the property such that its value can't be updated!

## YDKJS

- when using Object.create( <prototype to model after>, {additional props} }

- For the additional props, you must use another object with keyword ‘value’!

  { name:
  { value: ‘Patti },
  age:
  { value: 32 } }

Now the new object.name is equal to ‘Patti’

- Keyword “in” console.log( “prop/keyName” in obj) // will return true or false based on property

- Objects can hold functions simply by the function name as key and omitting : and the value if the function was declared before. - Ex. func whatever(){};
  let obj = {name:”Patti”, whatever} // whatever is the key and the function itself is the value attached

## this

- “this”binding is determined by HOW and WHERE the function was called, aka CALL-SITE
- Always used in a function.
- simply get the left hand of the . notation `[something].method` => `this` inside method refers to something object. If it's nested, only the DIRECT object will work. Otherwise, it will just refer to global window object
- Call-site - location in code where the function is CALLED (not declared! NOT lexical)

- 4 Rules of “this” and call-sites

  1.  Default Binding - If no other binding rules apply, this is the default. If a function is called in global, “this” in a function refers to the global scope. Does NOT WORK if function is declared in “strict mode”. Usually not used

  - ex

  ```function func() {
  console.log (this.a)
  }
  Var a = 4;
  func(); // bad usage of “this” , but would print “4” in non-strict mode.
  ```

  2.  Implicit Binding - if function call-site has a context object

  - works with bothdot or bracket notation. obj.func() OR obj [func]
  - ex

    ```
    function useThis() {
    console.log(this.a); }

    let obj = {a: 2, func: null};
    obj.func = useThis;

    obj.func();  // function useThis() call site. Indicates there IS context object - called via obj

        // prints 2 because “this.a” in this binding refers to obj.a
    ```

    - Only the most recent chain matters. obj1.obj2.obj3.obj4.func(); //”this” points to obj4

    - In order to implicitly (indirectly) bind “this”, you have to create and mutate an object and use the property function reference to call the function.

3.  Explicit Binding - Just like strings and arrays, functions also have methods that are built in.

    - function.name; // gets the original name when the function was declared
    - function.length; // gets number of parameters function calls for
    - function.toString(); // returns the function definition

    - function.call(someObj, arg1, arg2) //used to call the function AS A PROPERTY of the arg object
    - funciton.apply(someObj, [arg1, arg2]) // same as call but the args can be inside one array as the 2nd arg
    - function.bind(someObj) // creates a new function with the new binding of `this`

      - for bind, the args can also be added. uses the .call syntax so each one must be a separate arg
      - Hard Binding - if you set a function to use func.call(obj) and call the function, then the “this” will always be bound to that particular obj.

    - NOTE - “this” does not bind inside functions that are arrow functions. You can use function expressions (const a = function () {}) or declarations (function a() {}), but NOT arrow functions.

    - ex.

    ```
    function() { console.log(this.name);};
    const h = {name: "Hideaki", age: 37};
    func(); // would raise error as “this” is using default binding rule, and there is no var name
        in global, and we are in strict mode anyway so it wouldn’t work.

    func.call(h); // GOOD! (h) parameter specifies which object “this” should refer to. returns “Hideaki”

    ```

    - <invokeThisFunctionName>.call(<theObjectToBind”this”>, additional arguments);

    - You can also use function.bind(obj) which returns an updated function with the (obj) already explicitly bound to function.

    4. “New” binding

    - In JavaScript, there is no connection between using the word “new” and class-oriented functionality. In JS, constructors are just FUNCTIONS that are called with “new” in front of them and they are not attached to classes. There aren’t even constructor functions, technically. There are only constructor CALLS of functions.

    - When a function is invoked with “new” (aka constructor call), these things happen:

      - A new object is created out of thin air
      - The newly constructed object is [[Prototype]] linked
      - The newly constructed object is set as the “this” binding for that function call
      - Unless the function returns its own alternate obj, this constructor call will return the newly constructed object.

    - New binding takes precedence over explicit, then implicit.

    - Exception: returned arrow functions will bind “this” based on lexical scope of where it was called.

    - A LOT OF built in methods (for example, array methods) have a built in additional parameter to bind a certain obj to the “this” of the function.

```
function foo(el) {
console.log( el, this.id );
}

var obj = {
id: "awesome"
};

// when you pass in a second argument to forEach, it will bind the object to the function and allow “this” inside the function
[1, 2, 3].forEach( foo, obj ); // 1 awesome 2 awesome 3 awesome
```

## Lexical Scope VS Dynamic Scope

- Lexical is `authored` location. Used to determine VARIABLE and local execution context and closure
- Dynamic scope is the `call` location. Used to determine `this` context
- Historically, `this` being dynamically scoped while almost every other aspect of JS being lexically scoped has been confusing. Arrow functions will solve this issue by using lexical scoping instead

## bind() as function cloner, currying

- bind is primarily used to bind a new `this` context and return a function clone, but the cloning part is also useful for currying
- ex.

```
function multiply(a, b) {
    return a * b
};

const multiplyBy2 = multiply.bind(null, 2);  // since we're just using it to clone a function, the first arg doesn't matter since multiply doesn't even use `this`

// makes a clone with the "a" arg already filled out as 2

multiplyBy2(4) => returns 8
```

## OBJECTS

Objects - Built in objects such as numbers, boolean, string, object, function, array, date, regexp, error can all be used to construct a new instance of these

Objects come in 2 forms

Declarative (literal) form - let myObj = { key: value, etc …};
//Can make multiple key:value pairs in one statement

Constructed form - let myObj = new Object();
myObj.<key> = <value>
//highly unusual. Same is true for any of the built in objects like string, number, boolean, null, undefined

Simple Primitives - number, string, boolean, null, undefined are a subset of built in objects and actually NOT themselves objects as can be seen in typeof()

Objects aren’t really holding the values of keys. It is merely holding the pointers (keys) to where the values are stored in memory.

Dot notation is usually called “property access” and is prefered. Bracket notation is “key access”
Variables can only be used in bracket notation (without quotes)

Copying Objects
Object.assign( {}, <objectToCopy> ) // returns a new object with copy of 2nd parameter
Obj. Includes all Owned key:value (enumerable) pairs.

Property Descriptors

    Object.getOwnPropertyDescriptor( <objName>, <”key”>); // returns descriptors for that value attached to the property

    Descriptors include :  all with true or false values attached

Writable - the ability to change the value
Configurable - ability to change any descriptor. If false, the value can’t be deleted either
Enumerable - the property to show up in a for... in loop

If writable is true, Object.defineProperty() can change the properties of descriptors

Other Object Methods (parameter takes in Object)

Object.preventExtensions(); //prevents obj from having new properties
Object.seal() // calls preventExtensions() on obj AND configurable: false on all keys, so
you can’t reconfigure or delete any values (although you could modify values)
Object.freeze() // calls object.seal on everything and turns all value writable: false.

    Object Oriented Programming - refers to a certain form of code organization that deals with classes and inheritance. Data has associated behavior, so code should be designed to package the data and behavior together. Also called “Data Structure”

    In OOP, classes, inheritance, instantiation, and ideas of classification (behavior based on a parent class) are stressed.Polymorphism is the idea that a child class can override certain parent classes to give it more specifics.

In JS, OOP may not be the most ideal way of going about projects. It may not be a practical way to do projects in the modern age.

Classes don’t REALLY exist in JS, but there are fake class like programming patterns to allow users who are comfortable with class structures to use them.

Constructors - instances of a class is created by constructors. Constructors are just functions that are called in a special way, using keyword “new” before.

class Lady {
Lady () {}
}

    INSTANCES are copies of the class.

There is usually a function with the same name as the class inside the class object. The function is the thing that creates new instances.

let personOne = new Lady(); // the “new” keyword let’s the engine know that it’s a new class instance

Other classes can be inherited from a class. Remember, we are still talking about functions and not the instances of those classes.

class Vehicle {
engines = 1

    ignition() {
    	output( "Turning on my engine." )
    }

    drive() {
    	ignition()
    	output( "Steering and moving forward!" )
    }

}

class Car inherits Vehicle {
wheels = 4

    drive() {
    	inherited:drive()
    	output( "Rolling on all ", wheels, " wheels!" )
    }

}

class SpeedBoat inherits Vehicle {
engines = 2

    ignition() {
    	output( "Turning on my ", engines, " engines." )
    }

    pilot() {
    	inherited:drive()
    	output( "Speeding through the water with ease!" )
    }

}

More class stuff from codecademy. (maybe not important for JS)
Constructor functions will have something like

    function Dog(name, color){   //remember the new rule. If a new Dog() is called, “this” will bind
    this.name = name;			to that new object.

this.color = color; }

let golden = new Dog(“Mina”, “gold”); // creates new instance of dog

golden instanceof Dog // returns true

Also, all constructor instances are prototype relationships

Object.getPrototypeOf(golden) // returns Dog {}

Object.hasOwnOwnProperty(property) // returns true or false

If you’ve made a constructor function but want to add more later, use
<constructorFunc>.prototype.<newProp> = <newValue>;

This new value won’t appear inside any instances of the constructorFunc, but the instance.<newProp> will work because it will look up to the prototype for the property. For..in loops will also include this new property.

If you want to add many properties, make a new prototype object and stuff everything inside like:

    Bird.prototype = {       // see bottom for this blank space
    			numLegs:2,
    			chirp() { console.log “chirp chirp!”}
    			describe() {console.log`My name is ${this.name}  }
                                      };

When using this method, always re-attach the constructor to the prototype so the blank space should be constructor: Bird,

    <instanceObj>.constructor // returns the constructor of instance
    However, the constructor of an instance can be reassigned, so not as reliable as using <obj>.instanceOf()

Reviewing classes, prototypes, constructors

CLASSES are sort of fake. They are objects with constructor functions inside.

constructors are used to invoke new instances by keyword “new”.

ALL inticial “new” objects will have an instance-prototype relationship, and the constructor will be the class.

function Bird() {}

let yellowBird = new Bird;

console.log(Object.getPrototypeOf(yellowBird)); // Bird {}
console.log(yellowBird.constructor===Bird); // true
console.log(yellowBird instanceof Bird); // true

All objects in JS have a prototype, and the prototype itself is also an object which has its own prototype. This is called the prototype chain.

Instead of using a constructor and new, a better prototype-based way of object composition is..

function Animal() {}
Animal.prototype.numLegs = 4;

let dog = new Animal(); // Too hard to modify later. Class inheritance is rigid

Instead

let dog = Object.create(Animal.prototype);
//Animal is no longer the constructor of dog, but the prototype of Animal is inherited in prototype of dog.

Another way to do this is there is a super class Animal(), then an instance Dog() that are unrelated so far, Dog.prototype = Object.create(Animal.prototype);
If you do it this way, always make sure that Dog.prototype.constructor = Dog // so that all instances of Dog will inherit Dog.prototype and NOT Animal.prototype

Getters/Setters

    Remember that keyword get or set replaces function, but you still need () with parameters if necessary - usually only for setters and no params for getters.

set(num) { stuff… }

But to CALL getters or setters, you don’t know parens OR arguments. It is used like a reassignment. set <something> = 5; // 5 becomes the arg to setter(<here>)

A constructor’s prototype will include the constructor property pointing to the function itself.
Mixin syntax

let mixin = function (obj) {
obj.<funcName> = function (){

<body> }   };

Prototype: - possibly the prefered way to go about object composition in JS

    Most objects have an internal property, prototype, which is a reference to another object

When using dot notation, it is actually invoking a [[Get]] operation which looks for the key in the object that is before the dot, but if that does NOT exist, it will look up the chain and look for the key in the prototype object.

Object.create(<prototypeObj>) // returns an object based on another Obj. Will have a prototype relationship!

So let obj = {a:2};

let anotherObj = Object.create(obj);
console.log (anotherObj); // returns an empty object {}
console.log(anotherObj.a); // prints “2” because prototype of anotherObj, obj has property “a”

A for...in loop will also iterate the keys of the prototype (if enumerable property is true).

If you assign a key to obj.key = value;
The property look up goes to the actual object, and also through the prototype chain!

When there is NO lookup key in the object, one of these 3 things will happen:
If a normal data accessor (see Chapter 3) property named foo is found anywhere higher on the [[Prototype]]chain, and it's not marked as read-only (writable:false) then a new property called foo is added directly to myObject, resulting in a shadowed property.
If a foo is found higher on the [[Prototype]] chain, but it's marked as read-only (writable:false), then both the setting of that existing property as well as the creation of the shadowed property on myObject are disallowed. If the code is running in strict mode, an error will be thrown. Otherwise, the setting of the property value will silently be ignored. Either way, no shadowing occurs.
If a foo is found higher on the [[Prototype]] chain and it's a setter (see Chapter 3), then the setter will always be called. No foo will be added to (aka, shadowed on) myObject, nor will the foo setter be redefined.

Shadowing - having the same key on different levels of the prototype chain is more trouble than it’s worth and is best to be avoided

When you use

let objB = Object.create(objA)

You are making objB’s prototype point to objA.
Object.prototypeOf(objB) === objA // returns true

With “new” and constructors:

function Dog() {};
let a = new Dog;

You are linking such that the new Object a’s PROTOTYPE points to Dog’s prototype!

Classes DON’T really exist and Objects are NOT copied in JavaScript! They are merely linked via prototypes where one object can delegate property/function access to another.

    There are technically no such things as constructor functions. Any function can be called with keyword “new” before it, so there are only constructor CALLS of functions. The “new” func() call will invoke the function and as a side effect, create a new object.

The problem with THINKING that JS has constructors and copied objects is..

function Foo() { /_ .. _/ }

Foo.prototype = { /_ .. _/ }; // create a new prototype object

var a1 = new Foo();
a1.constructor === Foo; // false!
a1.constructor === Object; // true!

When you rewrite Foo.prototype, you are erasing the constructor key. When a1.constructor is looking for constructor, it looks in a1 // nothing, then a1.prototype (which is Foo.prototype)// finds nothing, then goes above to Object() and finds it there. It has nothing to do with which function it called “new” on!

The delegation model based around Object.create()
No constructors, no “new”, no parent or child classes
Use different names between the prototypes
Refer to a prototype when delegation is necessary
Flexible, composition based with nothing to do with “fake” classes

## Codesmith OOP lecture

const obj = {stuff} takes up too much local memory

better to store in dunder proto, `__proto__`

### Object.create()

```

const factory = {greet: () => 'hi'}
Object.create(factory); // returns an object that has a `__proto__` with the greet function

```

### using new with functions

functions can have prototypes that is used as ingredients to form `__proto__` upon being used with `new`

even better is to use a factory function.

```

function UserCreator(name, score) {
this.name = name;
}

UserCreator.prototype.greet = function () { 'hi' } // this CAN NOT BE an arrow function!

const user = new UserCreator;

// now user has `__proto__` based on prototype
user.greet // returns 'hi'

```

### using classes (syntax difference only)

```

class UserCreator {
constructor (name) {
this.name = name
}
greet () {
console.log('hi')
}
}

```

adding a method to a class is actually adding UserCreator.prototype.greet.

const user = new UserCreator;

```

```

```

```

```

```
