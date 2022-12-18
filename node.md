# Node

Node is javascript that runs on your computer rather than on the browser.
You don't have access to document or window, but you have access to process and the ability to create files, make changes to your system, and listen to network traffic.

## how to run quickly

- run `node` in terminal for interactive mode
- to quit, `.exit`

## Difference between browser js

JS in the browser uses the event loop to sort the stack and callback queue. Web apis are pushed to the callback queue (promises have high priority) and the callback queue is not cleared until the main stack is clear.

Node uses the LibUV library which works similary to the event loop but it communicates with C++ to handle the node equivalent event loop, callback queue (event quque) and background I/O operations.

Node has no Web API, no window, document, navigator, XMLHttpRequest, or any other browser-specific objects.

Instead it has **dirname, **filename, and process

## Module

modules are used to share information between files and keep your namespace clean.
Modules allow us to expose only the parts of your program you want exposed, sort of like a closure.

By default, module.exports is an OBJECT.

When you write code to import a file, `const stuff = require('someBuiltInModule');`
We are assigning the module.exports object of the someJsFile to the variable, stuff.

If someJsFile is empty, it will be an empty object

In the exporting file, you can refer to the exporting object with the full name, `module.exports`
OR the shorthand, `exports`

### Why it's like closure

```
counter.js

let i = 0;
function counter() {
  console.log(i);
  return i++;
}

modules.exports = counter;


index.js

const counter = require('./counter.js');

console.log(counter()); // in console: 0;
console.log(counter()); // in console: 1;
console.log(i); // error
```

the function counter has access to i from counter.js. index.js can CALL counter and have indirect access through the return statement, but not as a variable.

## Overriding module.exports

Though it is an object, you can ovveride the object by making it a function

`module.exports = function() { console.log('module.exports is now this function!)}`

Now if you require this file, `const stuff = require('pathToFile');`
you can just call with `stuff()`
Some libraries have this pattern, some keep module.exports as an object.

## npm - node package manager

npm uses the same module technology to share files from libraries. installing a package makes a node_modules folder in your system, and importing it in a file does not require the path like with files you made yourself.

## FS - path

File System api's usually ask for the direct path from the ROOT dir of the project. Don't use relative path './'

Don't forget to encode it so that you don't get a buffer, but a string when you read a file
Pass in an options object with encoding: 'utf-8'

```
fs.readFileSync('project.csv', {
  encoding: 'utf-8'
})
```

## Server

Using the built in http library, a server can be set up in node

```
const http = require('http');

const server = http.createServer((request, response) => {
  console.log('got a request!')
  response.write('hello');
});

const PORT = 3000;

server.listen(PORT, () => {
  console.log(`server is listening on port ${PORT}`)
});
```

## Node vs Express

What's the difference between vanilla node and express?

Express is very bare bones and only adds a few things to node, but those are essential.

Express manipulates the request (info coming into the serrver) and response (info going to the browser) such that middlewares can be run. When all (if any) maddlewares are done parsing through those, then they finally go to what we wrote in inside the route.

node can't use middlewares

The boilerplating of Node is a little verbose. Connecting html, css, and frontend js to the server can be a lot of code.

<strong>See vanillaNodeServer folder for more details</strong>

## Sessions and Cookies cookie-session

Web app servers are generally stateless. Each HTTP request is independent and a server can't tell if 2 requests came from the same browser. Servers can't persist information unless it is coded to store in memory, on disk, or on a database.

The workaround to this is when a request comes in to the server for the first time, the server responds with a cookie, which is just a name-value pair. How every time the same browser makes a req to the server, the server can implement SESSIONS, which means it understands that it's the same user from before via the cookie

A common way to set this up in express is using the npm pacakge, cookie-session as a middleware

If you add cookie-session as a middleware, the request now has res.session attached which is an object that you can pass back and forth.

## process.env

For server package.json scripts,

"start" : "NODE_ENV=production node server.js",
"dev" : "NODE_ENV=development nodemon server.js"

process.env.NODE_ENV inside the server script will be set to "development" or "production" based on script

## FS streams

Streams are used to get data gradually
You need to add event listeners on the stream to put the chunk buffers together
You need to add event listener on 'end' for all function to run after the stream is done

```
// initiates the stream
const stream = fs.createReadStream(<pathToFile>)
stream.on('data', (chunk)= {
  // do something with the chunk of data
})
stream.on('end' () = {
  // logic for what to do when the stream is done
})

```

## Under the hood

`http.createServer((request, response) => { })`
is EXACTLY the same thing as making a server, and creating an event listener for 'request' as the server itself is also an EventEmitter!

```
const http = require('http');

const server = http.createServer((request, response) => {

});
```

Is the SAME as

```
const server = http.createServer();
server.on('request', (request, response) => {
});
```

All incoming body data through POST or PUT are read in chunks as buffers.
All stream event have 'data' and 'end' which you'll have to attach as listeners.

If the data is a string, the easiest way to parse the chunks is to make an array and Buffer.concat and toString();

```
let body = [];
request.on('data', (chunk) => {
  body.push(chunk);
}).on('end', () => {
  body = Buffer.concat(body).toString();
  // at this point, `body` has the entire request body stored in it as a string
});
```

All requests AND reponse objects should have error handling on the Node side via .on('error', callback)

```
request.on('error', (err) => {
  // This prints the error message and stack trace to `stderr`.
  console.error(err.stack);
});
```

Usually the .listen is chained to the end of the createServer() function along with a callback of logging `listening on port ${PORT}`

## PIPE!

Pipe is very powerful. if you are reading a stream and writing to a stream, remember that request objects are readableStreams and response objects are writableStreams so you can skip chunking and Buffer.concat and even response.end() if you pipe. Pipe will implicitly call response.end() when the last chunk is read and written.

```
const http = require('http');

http.createServer((request, response) => {
  request.on('error', (err) => {
    console.error(err);
    response.statusCode = 400;
    response.end();
  });
  response.on('error', (err) => {
    console.error(err);
  });
  if (request.method === 'POST' && request.url === '/echo') {
    request.pipe(response);
  } else {
    response.statusCode = 404;
    response.end();
  }
}).listen(8080);
```
