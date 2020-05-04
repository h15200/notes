# socket.io

A server that's used alongside express

## set up

## server side

Get socket.io, express

In index.js of backend:

const http = require(‘http’)
const express = require(‘express’)
const socketio = require(‘socket.io’)

const app = express()
const server = http.createServer(app)
const io = socketio(server)

// set port in dev.env with env-cmd , publicDirPath,

server.listen(port, () => {
console.log(‘listening to server with socket.io’)}

## On the client side, they also need a socket dependency

    In the public index.html,

 <script src=”/socket.io/socket.io.js”></script>
<script src=”/js/chat.js”></script>

First script is the client side socket.io library
Second script is my file in vs, so i made another dir inside “public” called “js”, and chat.js inside that. This second js file was loaded in later, so it has access to the first script.

In chat.js, all you need is:

io()

But usually better to have

const socket = io() // so you can listen to emits from the server with socket.on

## Basic flow:

    Server

// the socket in the arg is to have access to the client that’s connected
io.on(‘connection’, (socket) => {
//stuff to do when you connect to the single client
socket.emit (‘event’, data) // will emit an event string and optionally data to client
})

Client chat.js

const socket = io() // socket is the server. .on is the listener. First arg is event, 2nd is function with what to do. The arg inside that function is the DATA

socket.on(‘event’, (data) => {

})

Clients will usually also emit through front end events like, say if the html file had a
<button id=”increment”>plus 1</button>

document.querySelector("#increment").addEventListener("click", () => {
console.log('clicked!')
socket.emit('increment') // now send an event to the server from the client
})

Then the server side will also have to listen with socket.on(‘increment’, () => {
// and here you can broadcast this to all clients with io.emit (io is what i named the server here) instead of socket.emit
io.emit(‘announcement’, data)

socket.broadcast.emit() will emit to everybody EXCEPT that client. Useful for sign in announcements

BASICALLY

Server => socket.emit(‘string’, data) must be paired with
=> Client socket.on (‘string’, (data)=> {} )

And vice versa
.emit() can have a third arg that is a function that runs when the event is received on the other end.

Connection sockets have socket.id, a unique id
