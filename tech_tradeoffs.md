## React VS Angular VS Vue

Angular is the most packaged including:
State management, routing, form validation/handling, http client

Vue has some built in features like:
State management, Routing

Then react is the most BASIC with core react which ONLY has UI / DOM manipulation
Routing has to be imported separately, (context hook is now considered state management)

Angular uses Typescript and separates template (HTML) with ts logic
Vue MOST OF THE TIME separates template (HTML) with js logic as well
React - ALL js because of jsx. Html templating lives inside a function or a class.

Most active community in the states, making it easy to find documentation.

Decoupling markup from logic is good for longer maintainability, so large components might look harder to comprehend in React. React, however, allows js engineers to use pure js to implement everything through jsx without learning new templating syntax.
NODE

## Redux

Pros using redux
Central store, any component can access any state from the store, there’s no need of passing props back and forth.
Another way to look at centralised store, it persists the state of a component even after the component has unmounted.
Prevents unnecessary re-renders, as when the state changes it returns new state which uses shallow copy.
Testing will be easy as UI and data management are separated.
History of state is maintained which helps in implementing features like undo very easily.
Cons using redux
No encapsulation. Any component can access the data which can cause security issues.
Boilerplate code. Restricted design.
As state is immutable in redux, the reducer updates the state by returning a new state every time which can cause excessive use of memory.

## Node

a JS runtime environment which allows infrastructure to build and run an app.

Build upon Google Chrome’s V8 runtime, written in C++.

Cross-platform dev possible like Electron or NW.js
Single-threaded, event-driven architecture allows it to handle multiple simultaneous connections efficiently. By NOT creating additional threads, RAM is not wasted

A light, scalable, and cross-platform way to execute code

- event-driven I/O model which makes it efficient and makes network app scaling possible
  Makes real-time apps (chat, gaming) very fast
  Makes coding in JS for both the client and server side possible, increasing dev efficiency
  Ever growing NPM choices and tooling
  Code executes faster than in any other language
  Perfect for micro services which are a popular architecture pattern

## EXPRESS vs KOA vs Meteor

A minimal framework that includes routing, serving static files, and middlewares that doesn’t jeopardize the I/O performance superiority of Node.
Non-opinionated so can use any model like MVC. Requires self-implementation and design prior to starting a project with a team

KOA is also minimal and very similar to Express, but it has no middlewares, which are helpful
Meteor is a FULL STACK framework that opinionated and automated but it takes away performance when the app scales

## NO SQL / SQL

SQL - structured, ACID compliant, joins to get data
NoSQL - flexible, fast, ease of use to get data

## JEST / MOCHA

Jest - auto mocking is helpful but slow
Defaults to using Jasmine 2 for test runner, assertions, and mocks under the hood

Mocha - faster as mocking is needs to be done manually
Flexible choice of assertions and mocking (chai, Sinon.js) and mix and match
