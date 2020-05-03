# Express setup

In root

```
npm init
mkdir config src views
touch src/index.js config/dev.env
npm i env-cmd nodemon  --save-dev
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
