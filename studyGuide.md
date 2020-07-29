# Daily Routine

1. Algos
2. Review front/back/SDI
3. Work on take home
4. Learn a new concept
5. Apply/Paperwork

## Algos

1. 14 Coding patterns
2. whiteboard practice

## Concepts

### General

1. How does the browser work?
   DNS look up to covert to IP address, server get request, html is served, additional assets are served through html (css, maybe js based on server-side or client-side rendering), user interfaces lead to more requests to various servers of micro services, each with their own load balancers and db management (sharding, cloning)

2. Hoisting
   PRE es6 `vars` were hoisted and not block scoped. function declarations (not function expressions) are also hoisted
   POST es6 let and consts are block scoped, making sure variable contamination doesn't occur in for loops. function declarations are still hoisted.

3. How does the event loop work?

What is a callback? A callback itself is simply just a function definition as a parameter inside a function. With browser APIs like event listeners, setTimeout, the callback function is ran asynchronously and put in an EVENT QUEUE instead of the call stack. Nothing in the Event queue runs UNTIL the call stack is cleared.

PROMISES - microtask Queue has priority OVER event queue.

### React

1. React life-cycles and useEffect counterpart
   useEffect with a callback as 1st arg and an array as 2nd. If array is empty, it is onMount. If it has variables, it is dependent on those (willUpdate), and if the callback returns a function, it is a willUnmount function call.

   If there is no second arg (dependency array) available, then the function will run EVERY render. If there is an array, and it's empty, it will only run ONCE. If there is a variable in there, then the function will only run if that variable was changed.

2. React v. 16 fiber
   React fiber is a new core architecture, an algorithm that optimizes the monitoring and possible updating of the virtual Dom. Because JS is single threaded, virtual DOM change buffers a small frame drop when dealing with animations. React fiber optimizes the virtual DOM change process

3. React Class components vs functional components

4. What is jsx? A JS object that compiles to html.

5. What is ReactDOM and Create? ReactDOM libarary in charge of rendering html and pushing it to an html file from the algorithm in memory that React made. React only makes the virtual DOM. In react native, instead of HTML, the virtual DOM is compiled into IOS and Android code.

### Node

1. How does node modules and import/export work? When you import a module, the entire file is wrapped in a function and ran immediately. When you say `import React from 'react'`, you are running the React FUNCTION and storing the result to a variable named React. Since this is all wrapped in a function, you have access to React via closure.

### RESEARCH

- How does History API and react router work?
  ck function is used to write asynchronous code. This was the case before Promises.
