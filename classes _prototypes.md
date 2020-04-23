# Classes are fake

Classes don't exist in js. The keyword class is just syntactical sugar to make things easier.
In reality making a class and calling new SomeClass() is the same as calling a new function.

When making a new function (or class), primitive types can be stored as a variable.

Animal.age // num
Animal.color // string
Animal.isFriendly //boolean

but functions need to be inside a prototype.

Animal.prototype.greet = function () { console.log('hi'))}

This implementation on es5 is done automatically in es6 when using classes like so

```
class Animal {
  age: 13
  name: 'Lady'
  greet() {

  }
}
```
