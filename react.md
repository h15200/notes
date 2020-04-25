# JS vs React & JS

## Why do we need a front end framework?

If you're building a web app with js, css, and html, the work flow is usually.

1. build html structure first
2. Js somwhere.. either in the html file, or in another file(s)
3. add style

JS COULD be inline as a script tag but there are no rules about where they are stored.

The user interface is generally created in HTML on the SERVER first,
then sent to the browser.

In react, the html file might be minimal and most of the structure is in react js files and components, meaning
the user interface is defined on the BROWSER first as JSX, and ReactDOM will render that into the html file.
In react components, the structure and the JS code that manipulates that structure is in the SAME place.

In vanilla, it was very hard to figure out WHERE the js functionality existed in the file structure and what DOM elements they pertained to.

Main differences

1. Vanilla js stores data in the DOM as a value. To access it, you need to find the dom and get its .value.
2. Vanilla js has no "state" tracking/updating so you have to always access a value to see if it's changed based on the user input

```
addButton.addEventListener("click", function() {
  const input = document.getElementById("item-input");
  const list = document.getElementById("grocery-list");

  const listNode = document.createElement("li");
  const textNode = document.createTextNode(input.value);

  listNode.appendChild(textNode);
  list.appendChild(listNode);
});
```

1. React stores values in js variables
2. State tracks and updates specified values

```
function addItem() { setItems([...items, itemInput]); }
```

## Setting up React

The old old way pre 2015 - react was one library and it used React.render as well as React.create
Be aware of these, but don't worry about set up too much.

### Setting up via regular html and CDN directly into html

1. Make sure the target element has an id of 'app' or 'content' or whatever you want to call it for rendering later
2. set up jsx <script src="https://unpkg.com/babel-standalone@6/babel.min.js"></script>
   now jsx is available in all scripts when you add `type="text/babel"`
3. add core React and ReactDOM
   `<script crossorigin src="https://unpkg.com/react@16/umd/react.development.js"></script>`
   `<script crossorigin src="https://unpkg.com/react-dom@16/umd/react-dom.development.js"></script>`

These are dev versions. Production versions are different. Look for updates

4. add the js file with the babel jsx
   `<script src="app.js" type="text/babel"></script>`
5. now in app.js you can create a function, return jsx, and ReactDOM.render the component to the target element
