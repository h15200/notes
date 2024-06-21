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

2.  Adapter Pattern

- heart of the structural pattern

3. Decorator

- extneds an object's behavior dynamically. The ability to add behavior at runtime is accomplished with an object which 'wraps itself' around another
- ex react-redux connect

4. Proxy Pattern

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

1.  Abstract Factory Pattern

- Use a factory to make multiple instances of whatever type you are making.

2. Singleton Pattern

- everything points to ONE instance of an object.
- ex. postgres pool object is a singleton model so multiple connections are not made, also config files are made so that only 1 of a type can be made OR multiple ones will be combined into one.

### Behavioral patterns

1. Mediator Pattern

2. Observer Pattern

- subscription model
