const http = require('http');
const path = require('path');
const fs = require('fs');

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
  } else if (req.url === '/index.css') {
    fs.readFile(
      path.join(__dirname, 'public', 'index.css'),
      (error, content) => {
        if (error) {
          throw error;
        }
        res.writeHead(200, { 'Content-Type': 'text/css' });
        res.end(content);
      }
    );
  } else if (req.url === '/index.js') {
    fs.readFile(
      path.join(__dirname, 'public', 'index.js'),
      (error, content) => {
        if (error) {
          throw error;
        }
        res.writeHead(200, { 'Content-Type': 'text/javascript' });
        res.end(content);
      }
    );
  } else if (req.url === '/api/users') {
    const data = JSON.stringify({ cat: 'Lady', person: 'Patti' });
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(data);
  }
});

const PORT = process.env.PORT || 3000;

server.listen(PORT, () => {
  console.log(`server is listening on port ${PORT}`);
});
