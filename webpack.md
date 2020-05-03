# Wepack

- used to separate components into file while organizing the entire project. Multiple components should not live in one file for scalability.

Used to load babel comppiler. As of now, the simplest way to make a light-weight react app. crr is a lot more bulky

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
