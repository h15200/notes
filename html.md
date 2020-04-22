## Rendering additional html from js

`<template>` elements can render strings like `<div>hi</div>`
Can be used to render elements dynamically

## Typescript built in type, 'DocumentFragment'

A DocumentFragement type is the .content of a DOM, like a template BEFORE it gets rendered.
So

```
const templateElement = document.createElement('template');
    templateElement.innerHTML = `
    <div>
      <h1 class="header-primary">Hi</h1>
    </div>
    `;

    templateElement.content    // this is of type, DocumentFragment

```
