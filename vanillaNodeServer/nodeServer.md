# This is an example of how to set up a full stack app with a vanilla node.js server without express

## File structure

backend is usually a node named something like server.js

frontend is all in a folder named 'public', as it's something the end user would be able to see. Put an index.html file in there and link the css and script the frontend js by

Inside the head - css
`<link rel="stylesheet" type="text/css" href="index.css">`

At the end of the body - js
`<script src="index.js"></script>`

## Node server

use modules http, path, and fs

http.createServer() takes in a callback function with req and res

You can use an if (and else if) statement for '/', '/index.css', and '/index.js'

The css and js files that were added to the html will need to be read by the server as a path.

## fs.readFile()

Inside the server, you'll need to call fs.readFile() which takes in the path and a callback with an error and content args.

the path module was needed to get the absolute path for the first arg
The callback inside the readFile is used for error handling.

```
const server = http.createServer((req, res) => {
  if (req.url === '/') {
    fs.readFile(
      path.join(__dirname, 'public', 'index.html'),
      (error, content) => {
        if (error) {
          throw error;
        }
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(content);
      }
    ); // end of readFile for root
  }
```

## res.writeHead and res.end

writeHead is used to write the head of a response.
the first arg is the status code and the second arg is an object that is usually used to specify key 'Content-Type' which is the Mime type

res.end() is used to end the response so that the network doesn't hang, but you can send data as an arg before ending.

In these examples of html, css, and js, we need to get the data from the files so we need to set the header, and write and end (write and end are both in res.end()).

There is no res.send() in core node. Just express

## Mime type or Content Type

html is 'text/html'
css is 'text/css'
js is 'text/javascript'

JSON data is 'application/json'

## Alternative

The above method of using fs, path, and http is the standard, but there is an alternate method available if the paths are simple and available

Instead of using path.join and fs.readFile, use fs.createReadStream

fs.createReadStream takes in a path as the first arg and the file type as a second arg.
Then instead of res.end(), you can use the <yourstream>.pipe(res).
.pipe() will call .end() as soon as the stream is finished reading, so it does the same thing as above method but with one less core module

```
const myCss = fs.createReadStream(__dirname + '/index.css', 'utf8');
     res.writeHead(200, { 'Content-Type': 'text/css' });
     myCss.pipe(res);
```

## api

You can easily make an api by pushing JSON as a reponse into a path

```
else if (req.url === '/api/users') {
    data = JSON.stringify({ cat: 'Lady', person: 'Patti' });
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(data);
  }
```

## using a readStream is BETTER

Better practice to use a stream instead of using readFileSync or readFile as streams will make things more efficient. When given a choice, use a stream
