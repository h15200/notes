Redux is a library that manages state as an alternative to using state in React components. Both methods tries to track changing data

## set up and overview

Follow first steps from create-react-app

npm i redux react-redux

If the store is complicated, make a seperate store.js
In index.js, import { createStore } from ‘redux’

2 boilerplate steps before calling createstore

Additional pre-step. Make a file in actions called types.js that just simply returns a string
Const SET_ALERT = ‘SET_ALERT’
Bring that into actions and use it instead of returning an object with strings, use the variables

Action(s) - seems stupid but a good idea for later. Just a function that returns { action: SOMETHING}

```
    const increment = () => {
      return { type: ‘INCREMENT’ }
  }
```

Reducer - pure func that takes in 2 args. One to set default state, and the action object
Usually a switch structure that’s set on action.type
action.type is CAP with \_ for spaces by convention

const counterReducer = (state = 0, action) => {
switch (action.type) {
case ‘INCREMENT’:
return state + 1
case ‘DECREMENT’:
return state - 1
default :
return state
}

make sure it’s let and not const. Call it with whatever reducer(s) you made above

let store = createStore(counterReducer)

## redux dev tools

GOOD IDEA to use chrome redux tool, so in createStore, add
use npm i redux-devtools-extension to simplify things
`window.__REDUX_DEVTOOLS_EXTENSION__**__()`
As a second arg after a comma

## The store has 3 apis

    	1.  store.getState()  - gets the current state
    	2. store.subscribe() - takes in a callback that runs upon every state change

Usually, react-redux is a better option but you can also just store redux state in local storage as well 3. Store.dispatch() - will call reducer based on action.type
It is called with { action: ‘SOMETHING’ } , which is usually returned from the action like:

    		store.dispatch(increment())

    			increment() will return { type: ‘INCREMENT’ } so same as
    			store.dispatch({ type: ‘INCREMENT’ }

Create src/reducers and src/actions
In reducers, make index.js (to combine all)
In src/reducers/index.js - import all reducers, { combineReducers } from ‘redux’
const allReducers = combineReducers( { anyName: reducer, anyName: reducer etc... } )
export default allReducers

Make individual reducers in files, export default.

    For individual reducer functions, might be a good idea to call it   nameReducer

In src/index.js
import { createStore, combineReducers } from ‘redux’  
 // you don’t need combineReducers if you only need one state, but you probably don’t need redux at all if you’re using only one state

    import allReducers from ./reducers/index.js

## FILE STRUCTURES:

Create src/reducers and src/actions

    In src/actions, break out all actions per reducer and export default
    	This only needs to be exported to the appropriate components in react. Does not need to be imported to src/index.js

    In reducers dir, make individual files per reducer function  and export default
    Good idea to use the naming  “whateverReducer” to be clear


    In src/reducers/index.js
    	import all reducers and import  { combineReducers } from ‘redux’
    	const allReducers = ( {  anyName: reducer, anyName: reducer etc...          } )
    	// you can name the reducer functions any name at this point
    	Export default allReducers

Now in src/index.js you can import { createStore, applyMiddleware, compose } from ‘redux’
And let store = createStore(allReducers) to have a store with all reducers

To use the dev tool with middleware,

    Let store = createStore (
             rootReducer,
            initialState,
           compose (
         applyMiddleware(...middleware),window.__REDUX_DEVTOOLS_EXTENSION__ && window.__REDUX_DEVTOOLS_EXTENSION__() )

);

## HOOKING IT UP TO REACT APP

In src/index.js
import { Provider } from ‘react-redux’ // Capital P

Wrap the entire react app with the Provider while passing the prop, store as store

So:

let store = createStore(reducers, window.**REDUX_DEVTOOLS_EXTENSION** && window.**REDUX_DEVTOOLS_EXTENSION**())

ReactDOM.render(
<Provider store={store}>
<App />
</Provider>,
document.getElementById(‘root’)
)

Now every stateless, functional components can import

{ useSelector } from ‘react-redux’ and have access to state!!

And Do something like

function App() {
const counter = useSelector(state => state.counter)
return (

<div className="App">
hello, {counter}
</div>
);
}

Notice the syntax of useSelector(state => state.nameOfState)

To CHANGE state, you still need to import actions from src/actions as well as { useDispatch } from react-redux

Make sure const dispatch = useDispatch() in the top level scope of the react function, then use the var dispatch inside handlers.

## Usage

```
import React from 'react';
import './App.css';
import { useSelector, useDispatch } from 'react-redux'
import { increment, decrement, signIn} from './actions/index'

function App() {

const counter = useSelector(state => state.counter)
const isLogged = useSelector(state => state.isLogged)
const dispatch = useDispatch()
const handleIncrement = () => {
dispatch(increment())
}
const handleDecrement = () => {
dispatch(decrement())
}
const handleSignIn = () => {
dispatch(signIn())
}

return (

<div>
<h1 className="App">
Counter: {counter}
</h1>
<button style={{fontSize:'2rem', margin:'0 2em'}} onClick={handleIncrement}>+</button>
<button style={{fontSize: '2rem', margin: '0 2em'}} onClick={handleDecrement}>-</button>
<button style={{fontSize: '2rem', margin: '0 2em'}} onClick={handleSignIn}>Sign In</button>
{isLogged && <h2>Secret Info that you need to be logged in for!</h2>}
</div>
);
}

export default App;
```

You can pass another parameter when calling the action like dispatch(increment(5))

And in the action which used to be this

const increment = () => {
return { type: ‘INCREMENT’}
}

Can also adapt so

const increment = (num) => {
Return {
type: ‘INCREMENT’,
payload: num}
}

And the payload can be used in the reducer to say, increment by 5 now

ASYNC actions

If you want to call dispatch on async actions like fetch(), the standard way is to use redux-thunk

To use it, you need to import { applyMiddleware } from ‘redux’

Reminder
Destructuring objects

const person = {
name: ‘Patti’,
age: ‘31’,
location: {
city: ‘NY’,
weather: ‘cold’
}
}

const {name,age} = person;

    // this is the same as const name = person.name AND const age = person.age

To go one level deeper in the nest, just change the right side of the assignment.

const {city, weather} = person.location;

    To rename,  (you can have one white space after the colon)

const {city: cityName , weather: currenWeather} = person.location;
// this will change the variable name WITHOUT changing the object itself

To have a default fallback, you can name it during destructuring like:
const {name = ‘Anonymous’} = person;
// if name doesn’t exist on object, ‘Anonymous’ will be used

Possible to do default and renaming on the same variable in one code:

    const {name: FullName = ‘Anonymous’ } = person.name;

Action Generators - Functions to be called inside store.dispatch();
This part is hard

// WHEN passing in an object to a function, you can use destructuring as if the param and the arg are connected by an = sign.

Example. If you are calling a function add( {a:1, b:10}) with an object
If you set up function param with its own curly braces like this:
const add = ( {a , b} ) => a + b;

That is the same as:
const numObj = {a:1, b:10}; // creates an object
const { a, b } = numObj; // assigns const a to 1, const b to 10;
When destructuring in functions, always remember to add an empty set as the default of the entire set because if you need to use any part of the object in the body of the function later, (you almost always will in action generators) and NO object is passed, it will throw an error of “Cannot get .type of UNDEFINED”

    so:

    const add = ( { a , b } = {} ) => a + b;

In addition, you should always set a default value to EACH new const declared by deconstruction in the function
So:
const add = ( { a = 0, b = 0 } = {} ) => a + b;
// if the function is called without any args, it will return 0.
// if the function is called with only {a = 3}, it will return 3;

Using this principle in action generators,

    const actionGen = ( {otherInfo = <default>, otherinfo =<default>, etc..  }= {} ) =>

({
type: <mainAction>, // this “type” needs to be there for sure
otherinfo : otherinfo, // set the other stuff to the arg passing in
otherinfo // can be shortened to just otherinfo in es6

});

And the other stuff is passed in the dispatch as
store.dispatch( actionGen({otherInfo: value}) );

And the store should have a way to deal with otherInfo.

These 3 elements must work together to form the core of redux

    createStore()  - must take a reducer function

Properties of a reducer:
Must be pure functions - everything except state should stay the same value
Never change state or action that’s passed in. Simply mutate the values by returning another object with the same key and new value.

To combine multiple reducers in a store, the arg is now combineReducers(). The arg of combineReducers is an object with a key-value pair of nameOFState:nameOfReducer

First set a default state const
const expensesReducerDefault = [];

const expensesReducer = (state = expensesReducerDefault, action) => {
switch (action.type) {
case ‘ADD_EXPENSE’:
return state.concat(action.expense);
// or even better, use return [ ...state, action.expense ];

more cases etc..

    default:
      return state;
    }
    };

const store = createStore(
combineReducers({
expenses: expensesReducer,
filters : filtersReducer
})
);

Set default state to a const
Set reducer as separate const
Use multiple reducers in combineReducer INSIDE createStore

store.dispatch() will return the action generator object.

// spread operators can now be used in objects as well to add

const P = { name: ‘Patti’,
age: 39 };

console.log ({...P, age: 31}) ; // will print { name: ‘Patti’, age: 31 } with the newer key-value will keeping the original const P pure.

    Reviewing the reducer in the expense project from udemy

To Add an account, pass in the info into the action generator as an argument object and return the action object {
type: ADD_EXPENSE,
expense: { // another object nested to expense
id: uuid() // a plugin id generator,
description, // this is the same as description: description
Otherstuff
}}

Expense reducer should have arg (state = [], action)
under the switch statement for case ‘ADD_EXPENSE’,
return [...state, action.expense]

For remove expense, simply return the id and on the reducer, use arr.filter() and return whatever that does NOT match that id:
return state.filter(({id})=> id !== action.id

- if you use the param with { }, you are destructuring the incoming object arg and creating a variable called id which is the VALUE of the key, ‘id’ of the incoming object. Then the filter is returning ALL objects where the id is NOT matching with action.id, which effectively is the same as deleting the one that matches it.

For edit expense, use the action generator should return the id and any updates.
In the reducer, use arr.map with a conditional for if the id matches, and if it does, return {...expense, ...action.updates} else return {expense}
This will go through the entire array of objects

    	Organization of React and Redux inside a project

Inside src, make directories:
actions - action generators
Make each JS file for each action category (usually same number as reducers) like expenses, or filters
reducers - reducers, obviously
selectors - query the data for store
store -
configureStore.js  
 Make a function that makes a store with createStore and combine reducers (if necessary), then return that store when called

Make sure to import all dependencies per file and export each component.

After that is set up, go back to the original src/app.js with the react code import hub
And import configureStore and call const store = configureStore();

To connect react to redux, you need to understand higher order components:
A component that renders another component
Reuse code
Hijack rendering
Prop manipulation
Abstract state

FIrst make a stateless functional component with props.
Make a regular const with a wrapper component that returns a FUNCTION that takes in props that returns jsx which INCLUDES the component above

    const higherOrderComponent = (WrappedComponent) =>

(props) => (

<div>
  { <theStatelessComp {...props} />     // {...props} same as   props.a = {props.a}, etc.. all keys
<div> );

    Installing react-redux library

yarn add react-redux

import { Provider } from ‘react-redux’ in app.js

    const store = configureStore();

    const jsx = (

<Provider store = {store}>
	<AppRouter />
</Provider>
);

ReactDOM.render(jsx, document.getElementById(‘app’));

Using momentsJS and airbnb datepicker

The built in JS dates function is terrible, so momentsJS is the gold standard for using dates/time.

yarn add moment react-dates

import moment from ‘moment’;

Usage:
const now = moment();
You have access to a lot of methods bound to now

now.format(‘MMM DD, YYYY”) // or whatever format you want
