# Express

## Express is a node framework

aims to be fast, un-opinionated, and minimal
The most used Node framework for the web

Other frameworks include Hapi and Koa. Hapi was very opinionated, Kao was not.
Kao was developed by TJ Holowaychuk, who also created Express.

## Abstractions

Express will handle all stream events. No need to parse buffers and add event listeners.
Express' request and response objects wrap the vanilla node request and response objects with extra functionality.
The middleware design pattern is implemented

## middleware

express middleware is simply a function that takes on 3 args (third is optional)

1. req object
2. res object
3. next function

You simply apply the current middleware, then run the next function

app.get('/', middleWare1, middleWare2);

// middleWare1 will need a next function but not middleWare2

Stuff that you write with (req, res) => {} is also considered middleware!!

### Middleware data `Res.locals`

Data will persist across middleware chains.

Convention to use `res.locals.<variablenName> = dataToPersistAcrossMiddlewareChain`

ex

```
app.get('/', middleWare1, middleWare2)

func middleWare1() {
  const res.locals.name = 'patti';
  return next();
}

func middleWare2() {
  res.send(res.locals.name)
}

```

As soon as the res is sent, the res.locals data will be gone.

## usage

In root

```

npm init
mkdir config src views
touch src/index.js config/dev.env
npm i env-cmd nodemon --save-dev
npm i express (and other middlewares like body-parser)

```

Package.json script
`“dev”: “env-cmd -f ./config/dev.env nodemon -e js, html, (other endings to file types as necessary) src/index.js`

App.js

```

const express = require ('express');
const app = express();
app.use(middleware)

probably set up routes in another page, then import here

const PORT = process.env.PORT || 3000 (or any port)

    At bottom, app.listen(PORT, () => { console.log(“server is up and listening to PORT”)}

```

To serve html or other engines, `app.use(express.static(path)`
the path must be an absolute path, so require path and for example going into html of a public folder would be
`const pathToHtml = path.join(__dirname, '../public/index.html')`

path.join will make an absolute path out of the current director and the relative path

## Full stack app with a db

Start with backend
Set up mongoAtlas cluster, get connection string
In vscode, make a .gitignore, git init, npm init (make entry point ‘server.js’)
Install regular dependencies (express, middlewares)
Install dev dependencies (nodemon, eslint etc.)
Setup script for nodemon server.js

in server.js

```

import express,
const app = express()
const PORT = process.env.PORT || 3000
app.listen(PORT, () => console.log (`listening on port \${PORT}’)
Do a test with a get request to index that sends back “test”, check w Postman
(see postman setup)

```

Don’t forget app.use(express.json()) in the server to parse requests!

Db
Use library ‘config’ to store values
Make a dir config, and a file default.json inside
Save db uri, jtw token password, etc.. inside json file (remember the { } at the top of file and double quotes for both key/value
Make another file inside config called db.js
require mongoose, config
const db = config.get(‘mongoURI’) // or whatever you named it inside default.json

```

const connectDB = async () => {
Try {
await mongoose.connect(db)
} console.log(‘db connected!’)
catch (e) {
console.log(e)
}
}

module.exports = connectDB

```

Require it inside server.js, run it to check

Routes folder
Api folder

    If there are server rendered html or templates, make pages dir
    If not, just make api dir and inside, break up files into resources
    Inside individual route resources (users.js, posts.js, profile.js, auth.js, etc…)
    These will all become /thing so plan accordingly  website/users, website/posts
    	Bring in express, const router = express.Router()

router.get( ‘/’, (req, res) bla bla and test // remember this root / is whatever we set it later in server.js in app.use

    	module.exports = router

    Then in server.js import all, use app.use(‘/api/users’, require(‘./pathtothatFile’)
    // good convention to add /api before any actual api endpoints

Models folder
Add schema

Helpful libraries
Config - to store mongoURI, jwt secret
Express-validator - error handling for server requests
Gravitar - hooks up global avatar. Use String type and add option ‘mm’ in default
Bcrypt - hash passwords before it gets saved in database
jwt - use objectID to define payload, secret string, pass in expiresIn, and a callback
Make custom middleware to use jwt

## CONNECTING TO FRONT END:

npx create-react-app client --use-npm
Make new script using concurrently which should be installed as a dev dep
"scripts": {
"start": "node server.js",
"server": "nodemon server.js",
"client": "npm start --prefix client",
"dev": "concurrently \"npm run server\" \"npm run client\" "
},

    On the root project, npm run dev should run nodemon on server AND create-react-app at the same time

Delete create-react-app’s git as you should have your own from the root
In client, manually delete readme and .gitignore
In terminal OF CLIENT folder, rm -rf .git
// -r is remove dir and contents, -f is to force without confirmation

// npm init was already made through create-react-app
In the client folder, npm i
axios, react-router-dom, redux, redux-react, redux-thunk, redux-devtools-extension moment react-moment
npm i --save-dev eslint eslint-config-airbnb eslint-plugin-html eslint-plugin-import eslint-plugin-jsx-a11y eslint-plugin-react eslint-plugin-react-hooks

Make a proxy in the CLIENT’s package.json
Below dev dependencies,
“proxy”: “http://localhost:5000”
Add client .eslintrc.js and node_modules into .gitignore of root project

    REMEMBER, in this first case, we made an html / scss -> css  file structure as a separate project that we’re connecting to the  back end. Usually, you would make the scss file structure inside a scss folder, and the compiled css will go in the public or dist folder along with other html files.

Add libraries in public/index.html header (like font awesome)

Do usual clean up in cra
Delete in client/src/ service workers, index.css logo, test, imports, replace div with react fragment, copy css into app.css,

Make src/img for any images used in css

THINK:
In html files, you use <a> and href to point links to specific html files. In react, all html code is written inside components and components are assigned to routes like “/” and “/login” via react-router-dom

In app.js, import { BrowserRouter as Router, Route, Link, Switch } from ‘react-router-dom’

Wrap Entire fragment with Router
Wrap Routes with Switch, use Route to connect web routes to components

CONCEPTUALLY, the switch component is a conditional if -> then rendering of the components. ALL previous component is rendered for all routes inside the switch.

Once switch routes are set, you can use <Link> to replace href in navbars and other components

You connect the backend to the frontend when you make axios requests to the database!
Example:

```
const newUser = {
name: formData.name,
email: formData.email,
password: formData.password
}
try {
const config = {
headers: {
'Content-Type': 'application/json'
}
}

        const body = JSON.stringify(newUser)
        const response = await axios.post('/api/users', body, config)
        console.log(response)
      } catch (err) {
        console.log(err)
      }

```

## MVC with express

In express, the controller in MVC refers to a group of related middlewares.

## Router

articleRouter.js

```
const router = express.Router();

router.get('/', () => {
  //stuff
  })

router.post('/', () => {
  // stuff
})

module.exports = router;
```

index.js

```
const express = require('express');
const app = express();
const PORT = 3000;
const articleRouter = require('./articleRouter.js');

app.use('/article', articleRouter);

```

## app.use()

When you use app.use() with a router, it is functioning like an else if.

```
app.use('/articles', middleware);
app.use('/', mw);

// this next one will ONLY active for ALL routes that are not in ./articles or ./
app.use('*', mw)
```

## Global error handling

THE ONLY thing you pass into next() inside middleware is error.
The global error handler will count these errors.

To get them, you simply make an app.use() with FOUR args. First one is error

```
app.use(err, req, res, next) => {
  res.localsmessage = err.message;
  console.log('ERROR: ', err);
  const errorStatus = err.status || 500;
  return res.status(errorStatus).send(res.locals.message)
}
```
