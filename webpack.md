# Wepack

Webpack is a module bundler tool

Overview

- why are build tools necessary
- intro
- bundling (review of modules in Node and in the browser)
- Features include transpilation, minification/uglification, css, images.
- Webpack-dev-server, live reloading
- Other bundlers and task-runners

## Why do we need build tools

1. Modularity: Devs want to modularize their code for maintainablility. Separate files for separate tasks
   Code bundlers allow us to bundle up these modularized source code files in to one JS file for our browser to work with.
   Remember, the browser can ultimately only read ONE js file, plain .css, .jpg and .png but not much else.

2. Source code typically isn't code that can be run in the browser - TS, JSX, CofeeScript, SASS, ES6
   Build tools allow us to transpile these languages into browser readable code with uglyfying and minifying to optimize performance.
   (minifying deletes whitespace and comments, uglyfying will replace human readable variables with short vars)

   BEFORE webpack, multiple script tags were used inside HTML files with defer options.
   Each script was a separate GET request. bad for speed
   Polluted the global namespace.

## Modules Review for backend and frontend

### Backend = Common.js = module.exports and require()

- Common.js is what we use in Node - module.exports
  Each file is module
  Each module exports a variable called module.exports `module.exports = whateverToExport`
  Other modules are imported with const `anyVariable = require('/somePath')`
  Encompasses built-in modules fs, path, process, etc.. as well as community node_modules from npm: express, mongoose, pg
  For npm modules, they are stored in the node_modules folder so we don't need a relative path and can just use the package name `const express = require('express')`

### Frontend = No native modules until recently (2020)

Must use webpack.

2 main choices - CommonJS and ES6 modules

CommonJS is the same as node as above
ES6 modules - import, export, default etc.. allows tree-shaking (selecting specific export pieces)

ES6 Modules are BETTER OPTIMIZED because you can ONLY import the thing you need from that particular file.
This is called `tree-shaking`

ES 6 Module review

```
export default Apple = (props) => {};
export const Banana = props => {};
export const Cherry = props => {};
```

```
import Apple from '/fruits';                // will only import the default Apple. no access to banana or cherry.
import Apple, * as myModule from '/fruits'  // will import Apple as the default, myModule as the object of everything else. myModule.Banana , myModule.Cherry
import Apple, { Cherry } from '/fruits';    // will import Apple as the default and Cherry as the destructured value from the object. no a access to banana

```

### Modern Browsers

Lastest versions of Chrome, Firefox, and Edge do support ES6 by using the module tag, but you still can't use NPM, still requests each file, and can't transpile or uglify other file types. This may change in the future, but we still need webpack.

## Loaders

Webpack enables use of loaders to preprocess files.
Loaders are usually defined in `webpack.config.js`, then we set up a script and run webpack.
Example of babel-loaders

ES6+ to ES5 (for IE)
JSX to React.createElement
TypeScript to JS

Various css-loaders allow modularized CSS to allow import an individual CSS file into a JS file
SASS and LESS usage

## Plug-ins

webpack plugins perform logic that a loader can't do to optimize
Minifying, uglyfying
If `mode: production`, webpack will uglify code

## Webpack dev-server (& proxy server)

Primary way to use Webpack for dev purposes.

- For production, JS needs to be uglified, and CSS/images need to be separate from the main bundle.js rather than inlined. Performance matters the most
- For development, more important to see the code changes reflected immediately.

webpack dev-server allows live-reloading of bundle.js and refresh of the page upon save
wds can ONLY serve static FILES!
spawns a localhost server under the hood that watches for file system changes. browser has a websocket connection to the dev-server so that it knows to live-reload
Does NOT write a bundle.js file to the file system. It keeps the bundle in memory and updates it on file system change events.

### Full stack web architecture

In <em>production</em>, we utilize one sever:
The single server is our express server that handles everything (DB logic, express sever, static files). Hosted on AWS/google cloud / etc..
When a request comes in, it has everything it needs to make a response.

In <em>development</em>, for a full-stack React/Node app, we use two servers

One for node backend - usually local:3000 handles API backend routes to retrieve/store data, business logic
One for webpack-dev-server - usually localhost:8080. Serves .html, .css, .js stored in RAM

When a request comes in, the dev server doesn't have the information needed to make a response. It will make ANOTHER request to the node backend, then get the info. This is the PROXY server.

## What is HMR, codesplitting

## Alternatives to webpack

- gulp
- grunt
- browserfy
- parcel
- bit-bundler
- broccoli.js
- rollup.js

grunt and gulp are older task runners, not module bundlers. They do not have the capability of efficiently combining modules. They're used to RUN module bundlers

## Setup

Structure

/public - index.html, also destination for bundle.js

1. if using react, make a div with id root inside body.
2. and right outside body `<script src="./dist/bundle.js"></script>` or wherever the bundle.js is
   /src App.js , maybe another folder called components, etc..
   make sure you import react and react-react into all components in /src

/src - index.js or App.js for react, any other components

`npm init -y`
`npm i -D webpack webpack-cli webpack-dev-server @babel/core babel-loader @babel/preset-env @babel/preset-react css-loader style-loader sass-loader node-sass`
optionally npm i react react-dom

webpack and webpack-cli is part of webpack
webpack server is a dev server
core is just babel
the loader is how webpack communicates with babel
the env preset is for es5 to es6 (modules)
env react is for react and jsx

make and fill out `webpack.config.js` for the file transpiling

dist or public or whatever you're using

```
module.exports = {
  entry: './src/index.js',
  output: {
    path: __dirname + '/public',
    publicPath: '/',
    filename: 'bundle.js'
  },
  devServer: {
    contentBase: './public',
  },
  module: {
    rules: [
    {
      test: /\.(js|jsx)$/,
      exclude: /node_modules/,
      use: ['babel-loader']
    },
    {
        test: /\.css$/,
        use: ['style-loader', 'css-loader']
      }
    ]
  },
  devtool : ‘cheap-module-source-map’
};
```

// if using sass, replace rule with

```{
test: /\.scss$/,
      use: ['style-loader', 'css-loader', 'sass-loader']
    }
```

inside package.json add a script

```

"scripts": {
"start": "webpack-dev-server --mode development",
},

make a script inside package.json for
"build" : "webpack -w"

```

then finally, `.babelrc`

```

{
"presets": [
"@babel/preset-env",
"@babel/preset-react"
]
}

```

npm start to run the dev server
