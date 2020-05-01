# babel - main point is to be able to use import/export on the browser to use npm packages including react

# - unresolved. Couldn't figure out how to use import/export with babel. Use webpack for now as that works

In the grand scheme, it is more high-level than creating your own http server on node and connecting html/css/js via fs.readStream.pipe(res) - see vanillaNodeServer folder

but within the scope of being able to use import/export modules in the browser, pretty low-level compared to webpack or create-react-app or anything higher than that.

It is the lowest-level method that I know of right now to be able to use react on the browser.

## Setting up babel

set up git
`npm init`
`npm i -D live-server @babel/cli @babel/core @babel/preset-env @babel/preset-react`

file structure

/src index.js

/public
index.html
index.css
app.js

.gitignore
package-lock.json
package.json

The idea is to take index.js and transpile it to app.js

Go to package.json and add key and assign an object

Wire up html with `<link rel="stylesheet" type="text/css" href="index.css>`
and inside end of body `<script src="app.js" ></script>`

if you're using react, do the usual id root and reactDOM.render

```
"scripts": {
"serve": "live-server public/",
    "build": "npx babel src/index.js --out-file public/app.js --presets=@babel/preset-env,@babel/preset-react --watch"
},
```

You can also just make a .babelrc file and add presets in there, and leave them out in the script

the `npm run serve` command runs live-server on the entire public folder
`npm run build` will transpile index.js to app.js using the presets in watch mode
