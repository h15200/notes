# create-react-app

More heavyweight than webpack, but the wiring is done so good for big projects

## set up

in project root
`npx create-react-app . --use-npm` // will default to yarn otherwise

make
/src/components

You might want to delete these for a small setup

Index.css,
Logo.svg,
serviceWorker.js
app.test.js

Inside src/index.js file
Delete import css
Delete import serviceworker, service.worker.unregister()
Delete import logo

Inside src/app.js
Delete import logo
Delete body of component, make it rafcp, replace div with Fragment (which you need to import from react so import react, { Fragment } from ‘react’ )

Otherwise, keep them and modify them

```
import React, { Fragment } from 'react';
import './App.css';

const App = () =>
<>
  <h1>App</h1>
  <div>Hi</div>
</>

export default App
```

App.css - rewrite to something like:

- {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
  transition: all ease-in-out 250 ms;
  }

body {
font-family: whatever;
Font-weight:
font-size;
line-height: 1.4 ish
}

img {
max-width : 100%; (avoid expanding image)
display: block; (inline block images behave weird)
}

a {
color: #333;
text-decoration: none;
}

```

```
