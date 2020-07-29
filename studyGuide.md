# Daily Routine

1. Algos
2. Review front/back/SDI
3. Work on take home
4. Learn a new concept
5. Apply/Paperwork

## Concepts

1. How does the browser work?
   DNS look up to covert to IP address, server get request, html is served, additional assets are served through html (css, maybe js based on server-side or client-side rendering), user interfaces lead to more requests to various servers of micro services, each with their own load balancers and db management (sharding, cloning)

2. React life-cycles and useEffect counterpart
   useEffect with a callback as 1st arg and an array as 2nd. If array is empty, it is onMount. If it has variables, it is dependent on those (willUpdate), and if the callback returns a function, it is a willUnmount function call.

3. React v. 16 fiber
   React fiber is a new core architecture, an algorithm that optimizes the monitoring and possible updating of the virtual Dom. Because JS is single threaded, virtual DOM change buffers a small frame drop when dealing with animations. React fiber optimizes the virtual DOM change process

4. Hoisting
   PRE es6 `vars` were hoisted and not block scoped. function declarations (not function expressions) are also hoisted

POST let and consts are block scoped, making sure variable contamination doesn't occur in for loops. function declarations are still hoisted.
