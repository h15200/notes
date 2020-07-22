# Design Pattern

Repeatable <strong>object-oriented</strong> solutions to commonly occurring software problems.
They are REUSABLE designs and interactions of objects.

Major design patterns were accepted after being heavily vetted by the community and solves specific problems that are language agnostic.

a PROTO-pattern is an emergent pattern that is not standard rep
an ANTI-pattern is something that does NOT work. ex. - using vanilla js AND react at the same time

23 major types of design patterns as outlined by the gang of four.

## 3 Types of design patterns

creational, structural, and behavioral patterns

### Creational Pattern nexamples

#### Abstract Factory Pattern

- Use a factory to make multiple instances of whatever type you are making.

#### Singleton Pattern

- everything points to ONE instance of an object.
- ex. postgres pool object is a singleton model so multiple connections are not made, also config files are made so that only 1 of a type can be made OR multiple ones will be combined into one.

### Structural Pattern examples

#### Adapter Pattern

The heart of the structural pattern.

#### Decorator

extneds an object's behavior dynamically. The ability to add behavior at runtime is accomplished with an object which 'wraps itself' around another

ex react-redux connect

#### Proxy Pattern

A check is a proxy for cash. A representation of something.
Same pattern with objects

making an object with specific rules that hijacks usually pattern

ex. - if a prop doesn't exist in an object, return 37

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

### examples of behavioral patterns

#### Mediator Pattern

#### Observer Pattern

subscription model
