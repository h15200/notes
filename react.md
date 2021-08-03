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

## Basics

All react code is written in JSX (as of now, wasn't the case in the beginning)

```
class App extends React.Component {
render() {
   return (
      <div>
         <Welcome name="Richard" />
         <Welcome name="Dinesh" />
         <Welcome name = "Gilfoyle" />
      </div>
     );
   };
}

class Welcome extends React.Component {
render() {
   return <h1>Hello, {this.props.name}</h1>
   };
}

```

1. create a react component class
2. declare at LEAST a render method, which is a LIFE-CYCLE method!
3. Inside the return, also render another component, Welcome
4. Welcome takes in a JSX atrribute, "name"

Rendering a component with jsx is akin to instantiating a new object via `const component = new Component()`

## Making state (class componenet)

```
class App extends React.Component {
   constructor() {
      super()
      this.state = {
         cohortNumbers: [34,35,36]
      }
   }

   render(){
      return (
         <section>
            <Box number={this.state.cohortNumber[0]} />
            <Box number={this.state.cohortNumber[1] />
            <Box number={this.state.cohortNumber[2] />
         </section>

      )
   }
}

class Box extends React.Componenet {
   render() {
      return (
         <div>
         <p> Cohort {this.props.number} is awesome! </p>
         </div>
      )
   }
}
```

1. State is declared INSIDE the constructor of the top-level component.
2. ONLY the top level component has access to state via this.state.
3. For other components to use that state, it must be rendered as a child of the top level component as a prop.
4. Those child components do NOT have access to current state, just the form of the state when it was passed on to the child when it was rendered by the parent component

## JSX, js constrictions

Remember that render() runs when the component is being rendered, so you can have js logic BEFORE the return statement to use inside return.

## constructor()

Constructor method is ALSO a life cycle method

## Common pattern

Making an array before the return statement of render() like `const a = [<h1>hello</h1>, <div>hi</div> ]

then return {a} will render all of those as siblings

## Setting up React

The old old way pre 2015 - react was one library and it used React.render as well as React.create
Be aware of these, but don't worry about set up too much.

### Setting up via regular html and CDN directly into html (NO. doesn't work)

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

THERE IS A PROBLEM with this method as the babel script will block any import or require modules.

### using create-react-app

inside the named project root dir
`npx create-react-app . --use-npm`
. For current dir. will default to yarn otherwise

## React - changes from vanilla js

### Camel case most attributes

className
onClick

### Handler functions

for functions, do not CALL the function like in vanilla js
`onclick="function()"`

Just name the function

`onClick={thisFunction}`

or else it will run immediately on render

So if you want to pass an event or any other arg to the handler, you have the wrap the whole thing inside a default function

`onClick={ (e) => { onClickHandler(e) }}`

if you want to pass additional things on top of event

`onClick= { (e) => { onClickHandler(e, otherstuff) }}`

Nothing gets RETURNED from a handler in react, so you can't return false to stop a default function.
You also can't return jsx for rendering.

To render, you must add JS inside the component return like
{ someStateBooleon && <Redirect to="/anotherSection"> }

## life cycle methods!!!

1. constructor
2. render
3. componentDidMount
   render fires again!
4. componenetDidUpdate (after every state update)
   render fires
5. componenetWillUnmount (as the component closes)

### images

Sourcing direct from the project dir doesn't work as well as importing
`import apple from '.somepath'`
then `<img src={apple}/>`

### Router

Use react-router-dom npm
To have multiple pages, use BrowserRouter (as Router), Switch, Route
Put Routes components in the entry point of the ReactDOM render

```

cont Routes = () => {
return (
<Router>
<Switch>
<Route exact path="/" />
<IndexComponenet />
</Route>
<Route exact path="/about">
<AboutCompoenent />
</Route>
</Switch>
</Router>
)
}

```

If the layout is simple without any auth or other functions, you can just put it in the main App and use Link as a way to navigate

### JS inside JSX

Can't use if statements, so stick to conditional && renders
{ truthyValue && <componentToRender />}
or turnary
{ truhtyValue? <button> : <div>}

useState hooks will come in handy for these

### Form state

The react way to handle form value is to keep them in state as a controlled component
Set the value of a form to the state of react, and set a changeHandler that detects input value changes and stores them in the state hook.

### Rendering through functions

You can render additional components through functions inside jsx

```

const Component = () => {

const addElements = () => <div>more divs!</div>;

return (

   <div>
   </div>
   { addElements() }
)
}
```

To render multiple elements, use an array of elements and they will render in order!

### useEffect

useEffect is great for putting in fetch, but keep in mind that any setStates you call inside useEffect WILL work, but it will not be reflected inside useEffect through console.log or even setTimeout with a console.log.

put any logic to use that state outside the useEffect

## Don't setState in constructor

In class components, don't use this.setState inside the constructor as it might run BEFORE the state declaration itself.

Put any state changes inside componentDidMount, or inside an event, as an event will always run after the DOM is rendered

# HOOKS

## useEffect

- when fetching async, always subscribe and unsubscribe based on mount to avoid `can not set state on an unmounted component` error

```
  React.useEffect(() => {
    let isSubscribed = true
    fetchBananas().then( bananas => {
      if (isSubscribed) {
        setBananas(bananas)
      }
    })
    return () => isSubscribed = false
  }, []);
```

- Another reason for that same error can be duplicate useState calls by accident!
