# Testing

Why Test?

To verify the correctness of our code in an organized way
Adding a new feature can have unintended side effects.
Over time, code bases can become too large to hold in your mind at once
Testing is essential to maintain a codebase.

## Testing Methodology

TDD - Test-Driven Development is an AGILE development process in which code is iterated upon quickly to add new features.
Each new feature involves writing tests BEFORE adding new code.
Many argue that test-driven development results in more maintainable, readable, modular code.
As the code base grows, this coding style influences the architecture of the project in a way that can be more easily refactored, tested, and iterated.

## TDD steps

1. Start by writing a test
2. Run the tests to confirm that they are FAILING since there is no code available.
3. Write the minimum amount of code required to make the test pass
4. Run the tests to check the new test passes
5. Refactor and optimize your code while making sure they still pass the tests.

## Types of Tests and scope

- Unit tests: focuses on a single, small piece of code. a function in an object, or module. Unit tests are isolated from other pieces.

- Integration tests: multiple parts tested together. ex when I hit a route, does that send me back what I need? This is testing multiple controllers/middlewares/functions at once.

- End-to-end (acceptance) tests: Test of a large part or entirety of application.

The most common test writing architecture is to have A LOT of unit tests (smaller tests), some integration tests, and even fewer end-to-end tests.

## Features of a testing framework

1. Coordination: Running 100 - 1000 tests requires coordination. We want to be able to independently run tests and parallelize them.
2. Assertion: Testing our expectations cleanly.
3. Isolation: Failure should be clearly isolated and meaningful. <em>Mocking</em> and <em>dependency injection</em> help us make failures independent.

## jest

Industry leader for testing alongside mocha.

Install as a dev depency
`npm i --save-dev jest` or `npm i -D jest`

    Jest Config

inside script, `"test": "jest --verbose file.test.js"`

Good idea to always use `--verbose`

For more complex configuration using .env files, use something like

`“test”:” env-cmd ./config/test.env jest --watch”`
--watch will run the tests on change on git, --watchAll will run all test files, see below for env-cmd explanation

### test file format

must end in `.test.js`

### dir format

name the testing folder -> `__test__`

On the test script, add a flag to watch
"test": "jest --watch",

Make a `someName.test.js` file

to run, simply `npm test` no need to add `run`

### writing the test

Inside the `.test.js` file, first import or require the js file you are testing depending on front/back end
No need to import jest

```
test( <name of test> , () => {
expect(<something>).toBe (something)
})
```

### syntax

Top level - describe()

Inside describe, beforeEach(), and a bunch of it()

toBe() or is() checks for strict equality (===)
toEqual() is loose equality (==)

expect()

to check for a returning object
expect(object).toHaveProperty('key', value)

.toBeTruthy()

.not.toBe() // bang operator

### Testing end-to-end or 'acceptance' testing in the browser

We want the most realistic environment possible, ie a real browser. We can automate these tests with a headless browser or browser automator.

Headless browsers: Puppeteer, PhantomJS, JSDOM
Browser automators: Puppeteer, Selenium, Cypress.io

We use a headless browser to run front end tests when we don't have a DOM provider by an actual browser

These are intentionally light weight and just supply the DOM.

Browser automators provide full browser functionality, which actually paints out the DOM but they are heavier and slower.

### Testing react

React testing involves tests on the DOM and virtual DOM. These require no browser environment.

Test Utilities (Facebook)

1. Virtual DOM tests with shallow rendering
2. Actual DOM tests with renderIntoDocument

Snapshots (jest): Records DOM render so we can catch unexpected changes

Enzyme - Airbnb's solution for testing React.

### Enzyme

Better than facebook and jest's solution to testing react.

Three approaches

1. shallow: lightweight mock wrapper for unit tests
2. mount: Used to mount a component to a DOM node and inspect its behavior
3. render: renders to static HTML and tests the result

NOTE: babel-jest is automatically installed when installing Jest and will automatcially transform files if a babel configuration exists in your project. To AVOID this behavior, you can explicitly reset the transform configuration option.

Babel will transpile React JSX to React.createElement calls.

inside jest

// runs once before every test
beforeAll() - do something like let wrapper = shallow(<ReactComp> {...props})

now wrapper is a shallw copy of a react comp without
wrapper.find('h1').toHaveLength(1); // there is ONE h1 element inside

mount(anotherReactComponent) - now it will find nested children

### jest config

Usually a good idea to make a jest config in json file with both globalSetup and globalTeardown (one async function that runs before the test suite, and one after to simulate a test group)

In package.json, add

“jest” : { “testEnvironment“ : “node” } // default is browser-environment. Do this only if you need to test for backend

Jest installs test() as a global, so you don’t need to require it.
In the file, call test() - 1st arg string, 2nd arg function
If the function runs without throwing and error, the test passes

### ENV

Jest must have the same env variables to test the routes properly
To do so:

Make another env file ‘test.env’ in your config dir
Copy everything the same except:

Possibly change the PORT to 3001 or something different
Definitely change the DATABASE_URL to from ‘...app-name’ to ‘...app-name-test’

Now use env-cmd (or whatever package you used in the main app)
And put the command before the test script

### mocking

Fake calls to simulate an action

To avoid packages like sendgrid firing off emails for every test,

create a directory called `__mocks__` in ‘tests’

Then depending on the module… for example, sendgrid is
require(‘@sendgrid/mail’)

So the first part is ANOTHER folder inside `__mocks__` and the name after the / is the file name.

So, make another dir inside `__mocks__` called @sendgrid, then create a file, mail.js inside THAT

`tests/__mocks__/@sendgrid/mail.js`

Then in mail.js module.exports { anyMethodsfromThisPackageYouUsed }
And set them up usually as an empty function UNLESS you are using the return values i

- Stub: the fake result that's returned from a mock
- Spy: recording metadata for a test subject function
- fake timer: freeze time, increment time, etc...

### Making testable code

- Pure functions (stateless): functions always produce the same output, so makes testing easier

- Dependency Injection ... in rare cases. Will make code messy

### Server testing with supertest and superagent

To test your server, you need supertest and superagent frameworks on top of jest

Supertest - high-level abstraction for testing HTTP routes
Sueragent - Underlying http request library used in supertest

Like jest, save as a dev dependency

npm i supertest --save-dev

Does not need to be connected to server to test routes, so you don’t want app.listen() to be called.

To do this, it’s best practice to have an app.js that imports express, routers, sets the port, etc.. with everything EXCEPT app.listen, module.exports = app

and have another file like index.js import that, and just call listen.

This way testing can be done on app.js before app.listen is called

```
describe('GET /user', () => {
	it('responds with json', async () => {
		const res = await request(app).get('/user).set('Accept, 'application/json');


		expect(res.header['content-type').toMatch(/application\/json/);
		expect(res.statusCode).toEqual(200);
	})
});
```

### process.env.NODE_ENV

jest will automatically change process.env.NODE_ENV to 'test' when it's running!

### Supertest async-await

await the request
res object will have statusCode
For headers, do
`expect(res.headers['content-type']).toMatch(/text\/html/)`;

## Jest vs Moccha

Moccha does not include mocking feature out of the box.
Must download chai for that.

Jest has a wider built-in feature set: assertions, data mocking, clearer console output
Jest automatically runs tests in parallel, making testing faster
Jest provide other tools like fake timers, spies, etc. without an additional library
