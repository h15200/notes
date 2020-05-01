# import export

## NOT SUPPORTED Natively!

The most important thing to note is that export/import statements are NOT supported curently by the browser OR node.

The only thing that works without any libraries or transpilers is inside node,

```
// js file

const a = 3;
cont b = 5;
module.exports = b
```

```
another js file

const b = require('./pathToFirstFile')
 // const b is now 5;
```

And require and module.exports is NOT supported by the browser either.

So

Vanilla Browser - no import/export, no require/modules object
Node - require and modules are GOOD, but no import/export

The ONLY way to use import/export module is through a transpiler like babel, webpack, create-react-app!
If you need an npm library on the front end, the way to do it is through a transpiler- import the library in node, then do whatever you need to do, then use the bundler as the connection to the html file to display it on the browser.
