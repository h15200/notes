Use npm react-router-dom

NOT react-router

Client-side rendering vs server side rendering.
Client side Javascript rendering can be done on one page and is faster because you only have to communicate with the server once in the initial loadin.

React Router is used to implement client side rendering.

To start a project, make a new project folder, , quit current dev-server and cd into the same folder, yarn run dev-server againl.

    Find the documentation
    	In teminal, yarn add react-router-dom

    In app.js,   import { BrowserRoute as Router, Link, NavLink, Route, Switch }from ‘react-router-dom’;

    <Router>
      <div>

 	    <Route path=”/” component={Home} />
	    <Route path=”/contact” component={Contact} />
	  </div>
	</Router>

Like in jsx, the router element can only have 1 child below so multiple <Route> tags need to be under another <div>

In development with webpack, make sure to first go to webpack.config.js and to

devServer: {
//add
historyApiFail: true
}

Then close and re-run dev-server in console.

Using keyword exact will only match exact path names. For example, “/” will also match “/ANYTHING” without the keyword exact

<Route exact path =”/”

If a <Route> does not have a path, it will match with everything and render the component.

    Setting up 404 error - use SWITCH

First, import it. Now, replace where the <div> inside <Router> will be with <switch>

<Router>
  <div>
   <Route exact path=”something” component={something} />
   <Route same as above />
   <Route component={component for 404 message} />
  </div>
<Router />

Now switch will try to match exclusively to each path, and when nothing matches, the last one without any path will run correctly

If you want a header that shows up every page, include it BEFORE switch

    Linking Routes

If you use an <a> anchor wtih an href to “/”, you are still using server side rendering. To avoid this and use browser side javascript, add event listeners via <Link> and keyword to that tells the browser NOT to render it via server.
Use exact before to just like in Router to avoid “/” and “/create” matching

    <Link to=”/”>Back Home</Link>
    For Header Components with a nav bar, use Nav-Link
    	2 special properties called activeClassName and activeStyle
    	<NavLink to=”/” activeClassName=”home” activeStyle= {{color:red}}

activeClassName attaches a class directly to NavLink - recommended
activeStyle uses a javascript object to style directly - quick fixes

Workflow

Make a folder in src called routers
Inside, make AppRouter.js where the <AppRouter> lives
-Break up all pages into js files under components - import necessary React, routes

- import routes into AppRouter.js

Imports -
regular app.js doesn’t need any router
AppRouter.js will import React from ‘react’
{ BrowserRouter as Router, Link, NavLink, Route, Switch} from “react-router-dom”
Import AppRouter from ‘./router/AppRouter’;
Along with the other router components

- create a stateless const AppRouter = (
  <Router>
  <div>
  <header> THIS is for a header that renders on every page of the app </header>
  <Switch>
  <Route exact path=”/urlPath” component={JSX to render} />
  <Route  More of the above>
  </Switch>
  </div>
  </Router>
  );

const Header = () => (

<div>
  <NavLink exact to=”/STUFF” exact=”true”>Name of Link</Link>
  <NavLink></Link> etc..
<div>
);

ReactDOM.render ( <TheRouterComponent>, document.getElementById(‘app’));

Dynamic url

React Router is passing in info when using <Router> and <Route>. If you pass props into a component and console log to chrome dev tool, you will see a lot of properties.

One useful one - if you pass <Route exact path=”/whatever/:id” in AppRouter.js, you can now access the website/whatever/<number> and the props.match.params.id will be that number.

    If you want a bunch of things to path to /gallery/1  and /gallery/2

You can just do exact path=”/gallery/:id” Note that this will not match with “/gallery” so you’ll need two different components, one for the gallery page and one for gallery items in that page
