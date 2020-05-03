## Rendering additional html from js

`<template>` elements can render strings like `<div>hi</div>`
Can be used to render elements dynamically

## Form, button, preventing default submit action

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

## DOM

You need to go to the parent to remove a node, as the only way to do it is to remove the child
removeChild() needs to be called with the element so the syntax is

`parentElement.removeChild(theChildToRemove)`

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

## to set attributes

If you want to dynamically change the src of an image tag
