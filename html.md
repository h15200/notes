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

```

```
