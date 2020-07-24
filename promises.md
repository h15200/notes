High level view of promises

## ways to accomplish asynchronicity in JS

### Callback Pattern

Reply on event loop and callback queue in order to get any delayed functionality back.

example: `setTimeout(() => console.log('done!'), 2000)`

Thread of execution is always single threaded.

A circular system of:

check the call stack -> check the microtask queue (promises) -> callback queue (fetch, setTieout) -> back to call stack

For the example, setTimeout will check the callback Queue every few micro seconds, and when it hits 2000, the console.log goes to the CALLBACK queue. The callback queue will call the functions in the order it came in.

### Promises

the same non-blocking task execution occurs and we get an object IMMEDIATELY returned to us in JS as a Promise object.

Microtasks are responsible for promise callbacks.
A resolve of a promise will go to the microtask queue INSTEAD of the callback queue.

Microtasks are prioritized immediately after the end of the current main thread task. If a function is waiting on the microtask queue, it will run before any other tasks in the callback queue.

## Differences between macro and micro tasks

```
const bar = () => console.log('bar');
const baz = () => console.log('baz');

const foo = () => {
  console.log('foo');
  setTimeout(bar, 0);
  new Promise((resolve, reject) => {
    resolve('should be right after baz, before bar')

  }).then(resolve => console.log(resolve))
  baz()
}

// prints
'foo'
'baz'
'should be right after baz'
'bar'

```

### Async / Await

ECMA2017 way of dealing with asynchronicity in JS.
Just syntactical sugar over Promises to make them more readable (no callback / chained .thens)

## ways in which async / promises might show up in interviews
