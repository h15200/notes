- notes based on experience with code reviews, receiving code reviews,
  working with patterns in various languages and companies, and "Philosophy of
  Software Deisn" by John Ousterhout

## Interface vs Implementation

- an interface describes a module which could be any abstaction like a
  class, method, or function - only exposes what's necessary to use the logic like input/output
  types - when the interface itself does not suffice, additional comments are
  made to explain usage, edge cases, or code examples

## Bad modules

- A module is bad when:

  - it is depedent on many other modules. Changes here need to reflect in
    many other areas of the codebase
  - the interface does not explain the body of the abstraction and the dev
    needs to look into the implementation to understand the usage
  - when the module is shallow. The abstraction doesn't give you much in return

  ```
  // logUtil uses console.log to print a string and add newline
  const logUtil = (str: string) => {
          console.log(str)
      }
  ```

  - here the interface is longer than the actual code, `console.log`
  - it would be better to inline this without using a helper func
  - modules and abstractions should be deep, yet provide a simple interface to
    maximize efficiency
  - the design does not account for the majority of use cases, but an edge

  - less lines of code does not equate to more efficient
  - ordering of calling moduleA and moduleB should not matter. If it does,
    they should be consolidated into one module

## Good modules

- An module is good when:
  - the module has no or very little dependencies and is isolated. Changes
    to this module does not require changes elsewhere
  - the design takes the majority use case into account
  - the interface is clear in both design and documentation
  - unnecessary details only exist in the implementation and are hidden

## Don't over specialize modules

- modules are the deepest and most useful when it is _somewhat_ general
- to get the sweet spot, ask the question "what's the simplest interface for
  this current need", and "how often will this be used?"
