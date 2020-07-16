# Testing

## Selenium WebDriver

like puppeteer, writes tests that control a web browser from a user's perspective.
useful for integration testing as it goes beyond unit tests
Is language agnostic

To USE Selenium, you need to wrap Selenium in your language driver

## WebdriverIO

JS driver that wraps Selenium with a nice JS API

## Spectron

Yet another wrapper around Webdriver that allows devs to use WebdriverIO with Electron apps. This is necessary as electron apps often have more power over regular browser apps

Can technically use any task runner, but the recommended one is mocha since all the docs are written in mocha (and chai if you like it)

### Usage

WebdriverIO takes care of controlling Selenium WebDriver on our behalf.

You don't really need to think about the line between Spectron and WebdriverIO, but just know that certain methods are governed by each. Some methods belong to Spectron itself, and some methods are delegated to WebdriverIO.

Spectron - Primary way to use is to create an `Application` instance which includes a number of child objects that allow us to access different parts of our application

### Children of Application

app. +

1. client - the underlying WebdriverIO instance. used for DOM, and triggering events like click
2. electron - Electron's Renderer Process API. Anything available when using `require('electron')` in the renderer process is available here. You can use `electron.remote` to access the main process in the same manner as you would in the renderer process (ALTHOUGH BAD PRACTICE!)
3. browserWindow - alias for current focused browser window. same as `electron.remote.getCurrent-Window()`. `browserWindow.capturePage()` is useful when you want to take a screenshot of the current window and save to desktop! If you want to focus on an alternate window, `app.client.windowByIndex()`
4. webContents -alias to Electrons's WebContents API. same as `electron.remote.getCurrentWebContents()`. The same method used to load HTML file into a BrowserWindow in main.js. This API provides access to browser funcationality like the forward and back buttons, printing, reloading. It emits events as the browser loads that can be useful for testing. Also provides the `webContents.savePage()` method saves the currently loaded page as an HTML file on your fs.
5. mainProcess - alias to Node's process object in the Main process. Same as `electron.remote.process`. useful if you need access to environment variables or args passed to Electron when it was started. Note that `main-Process` is something different and NOT an alias to Electron's main process API, but it can be accessed using `electron.remote`.
6. rendererProcess - similar to `mainProcess` and provides access to the renderer process's `global.process` object. Node's process object in the Renderer process. if you need Electron's renderer process APIs, use `electron` instead.

CLIENT and ELECTRON are the main functions
3, 4, 5, and 6 are simply SHORTCUTS to functions within client and electron.

Details below

### app.client

Client has Electron-specific methods but a lot of it are delegated to WebdriverIO.

app.client. +

getMainProcessLogs() - returns a promise that resolves to an array of messages
getRenderProcessLogs() - same as above
getSelectedText()
getWindowCount() - returns a promise that resolves to an integer
waitUntilTextExists(selector, text, optional milliseconds to wait before giving up)
waitUntilWindowLoaded()
windowByIndex(index)

### Reference sample tests

https://github.com/electron-userland/spectron/blob/master/test/application-test.js#L219

### SYNTAX

Spectron versions (which are governed by Electron version) often use different versions of webDriver, which means there are syntax differences so always double check.

For testing mode, turn off contextIsolation and sandbox and make electronRequire = require (see preload of swell5.0)
