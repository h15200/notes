# Node

Node is javascript that runs on your computer rather than on the browser.
You don't have access to document or window, but you have access to process and the ability to create files, make changes to your system, and listen to network traffic.

## Module

modules are used to share information between files.

By default, module.exports is an OBJECT.

When you write code to import a file, `const stuff = require('someJsFile');`
We are assigning the module.exports object of the someJsFile to the variable, stuff.

If someJsFile is empty, it will be an empty object

In the exporting file, you can refer to the exporting object with the full name, `module.exports`
OR the shorthand, `exports`

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
  console.log('server is listening on port ${PORT})
});
```

## Node vs Express

What's the difference between vanilla node and express?

Express is very bare bones and only adds a few things to node, but those are essential.

Express manipulates the request (info coming into the serrver) and response (info going to the browser) such that middlewares can be run. When all (if any) maddlewares are done parsing through those, then they finally go to what we wrote in inside the route.

node can't use middlewares

## Sessions and Cookies cookie-session

Web app servers are generally stateless. Each HTTP request is independent and a server can't tell if 2 requests came from the same browser. Servers can't persist information unless it is coded to store in memory, on disk, or on a database.

The workaround to this is when a request comes in to the server for the first time, the server responds with a cookie, which is just a name-value pair. How every time the same browser makes a req to the server, the server can implement SESSIONS, which means it understands that it's the same user from before via the cookie

A common way to set this up in express is using the npm pacakge, cookie-session as a middleware

If you add cookie-session as a middleware, the request now has res.session attached which is an object that you can pass back and forth.
