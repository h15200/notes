# DOM is a tree

```
              Window

              Document

              <Html>
      <Head>              <Body>
<meta> <title> <link>     <header> <main> <footer> <scrypt>


```

ALL things in the dom are basically objects with built-in methods

## steps

1. HTML page loads, browser creats a Document Object Model
2. DOM is exposed to javascript via `document`
3. Browser loads the js script LAST

## selecting a dom element

- generally, best to just use `document.querySelector("div")`
- it is versatile and can be used for classes `document.querySelector(".header_1")` and ids as well `document.querySelector("#top")`

## creating

- `document.createElement('div')`

## deleting

- 2 main ways to delete

1. get element, then just that element.remove()
2. from parent, parent.removeChild(childEle)

- select the element

## Rendering additional html from js

`<template>` elements can render strings like `<div>hi</div>`
Can be used to render elements dynamically

## Make sure js runs after DOM is loaded

```
document.addEventListener("DOMContentLoaded", () => {

// put ALL js code inside here



})
```

## form

You can set a regex to attribute pattern
`input type="text" pattern="/\d+/"` // must be 0 or more digits

## Form, button, preventing default submit action

action="/someRoute"
method="post"

Forms can ONLY make 'get' or 'post' requests!

You can handle form submit in two ways

1. On the form itself as a `onsubmit` attribute
2. On the button as a `onclick` attribute

I prefer on the button.

In vanilla js, you always need to call the function.

`<form onsubmit="formSubmitHandler()">`
`<button onclick="clickHandler()>`

When writing the function in js, you usually have to STOP the default submit action (going to another page through a get method).

You can do this in 2 ways as well. You should implement BOTH methods as a fail safe

1. event.preventDefault()
   first, pass in an event on the html side - `<form onsubmit="formSubmitHandler(event)>`

```
js file

const formSubmitHandler = (event) => {
  if (document.findElementById('password').value !== 'good password') {
    event.preventDefault();
    alert('wrong password');
  }
}
```

2. in the callback inside the html, write keyword return
   `<button onclick="return clickHandler()>`

if false if returned in js, then the submit will not go through

```
js file

const clickHandler = () => {
  if bad validation...
   return false
}
```

Again, it's best to DO BOTH

`<button onclick="return clickHandler(event)">`

```
const clickHandler = (event) => {
  if something fails,
  event.preventDefault();
  alert('wrong password');
  return false;
}
```

## Typescript built in type, 'DocumentFragment'

A DocumentFragement type is the .content of a DOM, like a template BEFORE it gets rendered.
So

```

const templateElement = document.createElement('template');
templateElement.innerHTML = `<div> <h1 class="header-primary">Hi</h1> </div>`;

    templateElement.content    // this is of type, DocumentFragment

```

## fetch()

Remember it's async and that you need to use response.json() (not json.parse), which is also sync

## Geolocation API

To get the lat/long of user, use the API on the browser.

First see if `navigator.geolocation` exists on the user browser. If not, it is not supported. If yes, run the method .getCUrrentPosition() which takes in a success callback and an error.

```
const sucessCB = (position) => {
  // position is the name of the incoming data. there is a coords property that contains the location

  const { coords } = position;
  console.log(`lat is ${coords.latitude}, long is ${coords.longitude} `);
  // do other stuff with this data
};

const errorCB = (error) => {
  console.log(error);
  // means geolocation is supported but there was some kind of error in getting the location
};

if (navigator.geolocation) {
  navigator.geolocation.getCurrentPosition(sucessCB, errorCB);
} else {
  alert('Gelolocation is not supported by this browser');
}
```

## rendering symbols

In html, you can use `&lt;`
but if you want to render it through javascript on an event, use hexcode.

## get / set / delete attributes

- if there is a <div id="hi">Hi</div>

- ways to get the attribute:

  - `const div = document.querySelector("span")`
    `div.getAttribute("id");`
  - also you can get it directly `div.id`

- If you want to dynamically change the src of an image tag

```
const img = document.querySelector("img");
img.setAttribute("src", "123");

OR JUST
img.src = "123";


```

- removing an attribute
  - `ele.removeAttribute("src");`

## data set

- you can add any custom attribute to dom elements with name `data-[anything]`
- <div data-my-age="40"></div>
- this can be accessed by `dataset` in js `myEle.dataset` => {
  myAge: 40
  }
- you can remove/add/edit like any other attribute
  - `myEle.dataset.newName = "Patti"; (automatically converts from camelcase to hyphen case)

## classes

- given <div class="h1"></div>'
  - ele.classList.add('new-class');
  - ele.classList.remove('h1');
- you can use `classList.toggle` to either remove it if it already exists, or add if it's missing
  - ele.classList.toggle('show');

## directly modifying styles

- use camelCase in js for the css equivalent
- span.style.backgroundColor = "red"

## NodeList is NOT a JS array

When getting multiple nodes back with document.querySelectorAll(), you get back a NODELIST which is NOT an array.

Nodelist methods do NOT share all array methods.

`NodeList.item()`
Returns an item in the list by its index, or null if the index is out-of-bounds.
An alternative to accessing nodeList[i] (which instead returns undefined when i is out-of-bounds). This is mostly useful for non-JavaScript DOM implementations.
`NodeList.entries()`
Returns an iterator, allowing code to go through all key/value pairs contained in the collection. (In this case, the keys are numbers starting from 0 and the values are nodes.)
`NodeList.forEach()`
Executes a provided function once per NodeList element, passing the element as an argument to the function.
`NodeList.keys()`
Returns an iterator, allowing code to go through all the keys of the key/value pairs contained in the collection. (In this case, the keys are numbers starting from 0.)
`NodeList.values()`
Returns an iterator allowing code to go through all values (nodes) of the key/value pairs contained in the collection.

## Event listeners

- always remove to avoid memory leaks

## STOP PROPAGATION

Stop the event from going up the DOM tree. For example, if a btn is inside a div and they both have onclick functions that outputs a message, you will ONLY get “div was clicked” even when you click on the button. This is because the event will propagate UP the dom tree and “button was clicked” will be immediately overridden by “div was clicked”. To prevent this, add `stopPropagation()` on the event.

const nestedBtnClick = event => {
document.querySelector(message).textContent=”button clicked!”
event.stopPropagation()
}

## Node.replaceChild()

syntax is

`parentNode.replaceChild(newChild, oldChild)`

If the newChild ALREADY exists in the DOM, it is first removed from that original position!

## error handling

For ex, if a src is not valid on an image tag

USE onerror attribute!

html
`<img src="whatever" onerror="callbackFunc()"></img>`

react
`return <img src={props.src} onError={someFuncToRunIfThereIsError}></img>`
