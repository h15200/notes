# Design Pattern

Repeatable <strong>object-oriented</strong> solutions to commonly occurring software problems.
They are REUSABLE designs and interactions of objects.

Major design patterns were accepted after being heavily vetted by the community and solves specific problems that are language agnostic.

a PROTO-pattern is an emergent pattern that is not standard rep
an ANTI-pattern is something that does NOT work. ex. - using vanilla js AND react at the same time

23 major types of design patterns as outlined by the gang of four.

## general terms and concepts

- `interface` just describes what something does without the implementation
  - ex. golang `interface` where methods with input/output is described but not
    the body of the method or java/typescript `abstract class`
- `implementation` describes what the method actual does in the body of the function
  - ex. golang `method` or typescript method override in a derivded class (A extends SomeAbstractClass)
- `concrete classes` have both interface and implementation
- `virtual classes` have interface and imple, but the imple can OPTIONALLY be overridden
- `abstract classes` only have interface and the derived class MUST implement the interface
- `derived class` from an abstract class or virtual class

- in an OOP language like `Java`, there are actual `virtual` and `abstract` classes.
- in `Javascript`, there are no abstract/virtual classes so you must add guardrails like
  throwing an error with message `This abstract class cannot be created, it must be extended`
  in the constructor
- `Typescript` doesn't have virtual classes and deals with `abstract` members and methods
  individually within abstract classes. In other words, an abstract class
  can have a mix of concrete members/methods (interface + impl) and abstract methods (impl only)

  - The abstract class needs both abstract members/methods.
    - concrete members are set in the constructor of the abstract class
    - abstract members are set in the derived class
    - concrete methods are implemented in abstract class and need not to be changed in derived class
    - abstract methods are overrideen/implemented in the derived class

  ```
  abstract class MyAbstractClass {
      name: string;
      abstract age: number; // does not set age in this class, but describes it

      constructor(name: string) {
          this.name = name; // constructor only deals with non abstract values
      }

      // display() has both interface and imple
      display(): void{
          console.log(this.name);
      }

      // find() only has interface and needs to be implemented in derived class
      abstract find(string): Person;
    }



   class MyDerivedClass extends MyAbstractClass{
        // any additional values
        color: string
        // constructor needs to take in all parameters for abstract parent class
        and this class
        constructor(color: string, age: number, color: string) {
            // call super to use the constructor in abstract class
            for only NON-abstract members
            super(name)
            this.age = age  // set the derived member from abstract class
            this.color = color // set the member from this derived class
            }

         // display() doesn't need to be defined or mentioned since we get
         that from the abstract class

        // find() needs to be overridden and implemented in the derived class
         find(name: string) {
             console.log(name)
             }
          }
  ```

- Golang
  - No concept of classes, so we don't use virtual or abstract
  - all interfaces act as abstract types and are implemented on the struct
    that it needs to be a part of
  - all design patterns apply, but the application in code is a lot easier
    since it's already composition based

## 3 Types of design patterns

### Structural Pattern

1. `Composite Pattern`

- create a root interface that governs all parts of a whole app
- the structure can be a primitive or an aggregate, but the client doesn't
  need to know. it usees the same interface
- useful for creating any tree like structure where each node is also the
  same interface as the parent
- ex. text editor. Text, Graphic, Line, Row, Col all need to have same methods
  - for aggregate types, there is an implementation
  - for primitive types, the imple for aggregate types can just return nil
- the individual members of an aggregate itself also is a type of the root
  interface

2.  `Adapter Pattern`

- takes two incompatible interfaces and creates a translator between so that
  the origin and target interfaces don't need to be modified

3. `Decorator Pattern`

- augments an object's behavior at runtime
- ex react-redux connect
- similar to `Strategy Pattern`, but here it always `augments` and in strategy
  it `changes` the implementation

4. `Proxy Pattern`

- A check is a proxy for cash. A representation of something.
- Same pattern with objects
- making an object with specific rules that hijacks usually pattern
- ex. - if a prop doesn't exist in an object, return 37

  ```
  // declare handler
  const handler = {
  get: function(obj, prop) {
           return prop in obj ? obj[prop] : 37;
       }
  }

  const proxy = new Proxy({}, handler);
  p.a = 1;
  p.b = undefined;

  console.log(p.a, p.b);
  // 1, undefined

  console.log('c' in p, p.c);
  // false, 37
  ```

### Creational Patterns

1. `Builder Pattern`

   - a class that holds various interfaces to add "parts" to itself. builder
     methods adds the feature, then returns itself
   - possibly easier to parse than `factory` patterns

   ```
   // make new builder
   myBugerBuilder = new(BugerBuilder).addTopping("tomatoes").addSauce().build()
   // chain the ingredients, then terminate with a method like build()

   ```

2. `Factory Pattern`

   - a method to create an object

3. `Abstract Factory Pattern`
   - an object or class to create a new factory

Differences:

- Use a factory to make multiple instances of whatever type you are making.
- Use abstract factory for different types of factories

3. Singleton Pattern

- everything points to ONE instance of an object.
- ex. postgres pool object is a singleton model so multiple connections are not made, also config files are made so that only 1 of a type can be made OR multiple ones will be combined into one.

### Behavioral patterns

1. `Strategy Pattern`

   - mainly to preserve "classes should be open for extensions but closed for modification"
   - a class should not have conditional logic that may need to be changed in the future
   - easier to modify without touching the actual class
   - easy to test
   - allows injecting objects at runtime by swapping implementation
   - similar to `dependency injection` but unlike DI, it is used to do
     different things depending on the runtime condition. In DI, you do a similar
     thing with a different implementation
   - in `Go`, this is just built in to the language. use an interface, Announcer
     which is any type that has the Announce() method.
   - to test the function that uses this logic, we just just pass in a mock
     Announcer and not test every condition
   - used for formatting, linting, payment methods, coupon discounts

   ```
   this is bad
   class Announce {
           if conditionA, announce A
           if conditionB, announce B

       }

   this is strategy pattern
   class Announce {
           // take in an object, Announcer
           announcer.Shout()
       }

     // to add a new type, we just need to create a new type of object
     with its own implementation of the announce method
   ```

2. `Observer Pattern`
   - event driven, pub sub model
