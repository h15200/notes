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
