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

Notice that a promise object runs immediately, and the baz() is treated like regular code despite it being INSIDE the promise object

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

foo()

// prints
'foo'
'baz'
'should be right after baz'
'bar'

```

### Async / Await

ECMA2017 way of dealing with asynchronicity in JS.
Just syntactical sugar over Promises to make them more readable (no callback / chained .thens)

Like promises, the resolved value will end up in the micro task queue, ahead of the callback queue.

```
const hi = async () => {
  const hello = await new Promise((resolve, reject) => {
    resolve('I'm still a promise but resolved using async await')
  })
  console.log(hello);
}

```

## ways in which async / promises might show up in interviews

```
let num = 0;
async function increment() {
  num += await 2;
  console.log(num);
}
increment();
num += 1;
console.log(num);
```

// what order will the console logs be?

// answer 1, 2
// not 1, 3 because line 78 num += await 2 will resolve to 2 and that is set before running line 82.

// an async function is a regular function UNTIL you hit a line with await, or any variables that refer to an awaited value

//
let num = 0;
const test = async() => {
console.log('num before await', num);
num += await 2; // now it will skip to num++ and finish main thread until it comes back to next line
console.log('num after await', num);
console.log('num at this point', num);
}
test();
num++;
console.log('num last line', num)

prints

'num before await', 0
'num last line', 1
'num after await', 2
'num at this point' 2
//

// solution to "promise all"

```
const promiseAll = new Promise((resolve, reject) => {
  const n = promiseis.length;
  const returnedPromise = new Promise((resolve, reject) => {
  // dec var to keep track of promises
  let completed = 0;
  // declare array with same length of the promise one passed in
  // set every value to null
  const results = new Array(n).fill(null);
  // iterate through the arr
  promises.forEach((promise, i) => {
    // on each iteration use .then method to write logic for when teh promise resolves
    promise.then(result => {
      // each time result is resolved increment completed by one
      completed++
      // reassign the curr idx of our results arr to be the resolved rsult
      results[i] = result;
      // check if the number of completed promise is equal to the length
      if (completed === n)
      resolve(results);
    })
    .catch(err => {
      // if there is an error at any point
      reject(err);
    })
  })
  return returnedPromise
})
```
