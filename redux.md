Redux is a library that manages state as an alternative to using state in React components. Both methods tries to track changing data

The cons of component states
All components must be on the same tree with one parent to control all data
Components are bound to each other with states and props so are not really reusable
Very hard to track multiple states in code

With redux, the goal is to make components with no props and can be rendered anywhere. State, instead, is managed by the global redux store.

    Keep in mind, when there is a situation where a parent needs to pass data to the child, using props is still feasible and recommended. If you are passing data over 2 levels just to get it to another element, it is recommended to use redux instead of props.

    The createStore parameters include

Callback function (reducer)
action
Usually, a switch statement is set to action.type

Action types are usually ALL CAPS by convention separated by underscores

Store Methods

store.dispatch( {type: someActionType} or an actionGenerator function );

    Actions objects can be manually inserted, but usually a better idea to have an action generator function to avoid typos. If manually inserted, typos won’t register in the store and code will be hard to debug

store.getState(); // current state
store.subscribe(callback) ;  
// gets called automatically on state change. callback is usually related to store.getState() like logging it
The return value of store.subscribe(); is a function that acts like unsubscribe.

    So const func = store.subscribe(()=console.log(store.getState));
    func() ;    //   now you have unsubscribed

Everytime store.dispatch( {actionObject} ) is called, createStore is run.

REMEMBER, the redux store itself is not a class, so it refers to its state as state and NOT this.state.

When setting action types, simply return an state object
return {count: state.count+1}

store.subscribe(); takes in a function that gets called every time the state changes

All actions MUST have a “type” key but it could also have additional ones

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
