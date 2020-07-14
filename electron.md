# Electron

A way to build desktop apps with js
Electron has access to node, unlike a browser which is sandboxed and does not have access to system processes

## Security issues

ONE Main process
Many Renderer Process

The old way of doing things using REMOTE

main process

```
global.thing = {
  color: blue
  greet: () => { something }
}

```

renderer process

```
const proxyObject = remote.getGlobal('thing') // makes a proxy object that acts like the same object inside main
// now proxyObject acts like global.thing and the renderer has access to it
```

This is BAD.

1. slow
2. the proxying process can create race conditions
3. The object is not really the same object. Prototyping, handling of NaN and Infinity will break code
4. The power of the main process will breach into any compromised renderer process.

remote should <em>NOT</em> be used

## How to fix an existing code base that uses remote

1. When possible, minimize the usage of IPC (inter process communication) in general
   If you need to communicate between multiple windows in the same origin, you can use `window.open()` and script them synchronously as you would on the Web

For communicating between windows in different origins, there's `postMessage`

2. When you NEED to call a function in the main from the renderer, use `ipcRenderer.invoke()` (available from Electron v. 7.0) which is asynchronous and does not block other things in the renderer.

## example

BAD, with remote module

```
// Main
global.api = {
  loadFile(path, cb) {
    if (!pathIsOK(path)) return cb("forbidden", null)
    fs.readFile(path, cb)
  }
}


// Renderer
const api = remote.getGlobal('api')
api.loadFile('/path/to/file', (err, data) => {
  // ... do something with data ...
})
```

After, with ipcRednerer.invoke

```
// Main
ipcMain.handle('read-file', async (event, path) => {
  if (!pathIsOK(path)) throw new Error('forbidden')
  const buf = await fs.promises.readFile(path)
  return buf
})
// Renderer
const data = await ipcRenderer.invoke('read-file', '/path/to/file')
// ... do something with data ...
```

Notice that the Main process is now re-written as an event handler with a 2nd arg which is an ASYNC function

That way the renderer can set a variable to AWAIT ipcRenderer.invoke() which uses 1st arg as the event, and 2nd arg is the path to the main process file

## preload details

if turning off nodeIntegration, use a preload script.

```
const { ipcRenderer, contextBridge } = require("electron");

contextBridge.exposeInMainWorld("api", {
  send: (channel, ...data) => {
    // allowlist channels
    const allowedChannels = [
      "toMain",
    "other-events-from-renderer"
    ];
    if (allowedChannels.includes(channel)) {
      ipcRenderer.send(channel, ...data);
    }
  },
  receive: (channel, cb) => {
    console.log("listening on channel : ", channel);
    // allowlist channels
    const allowedChannels = [
      "fromMain",
      "other-events-TO-renderer"
    ];
    if (allowedChannels.includes(channel)) {
      ipcRenderer.on(channel, (event, ...args) => cb(...args));
    }
  },
});
```

renderer process will declare `const { api } = window`
and have access to window.send and window.receive

main will use `mainWindow.webContents.send('channel');` if inside main

to keep main small, use a module by

main_grpcController.js

```
const { ipcMain } = require('electron');
require other core node modules

some functions

then at bottom

module.exports = () => {
  ipcMain.on('channel-name', (event, data) => {
    someFuncInThisFile(event, data)
  })
}

```

main

```
require("./main_grpcController.js")()
```

## electron-builder

Leverages the OS of the machine you are building with, so some errors can be related to os versions or node versions

the "build" key inside package.json acts as the config
