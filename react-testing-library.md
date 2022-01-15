# jest + rtl

- comes out of the box with Create react app

## screen

- in most cases you're only interested in the body of the document. for that, use the screen object

## seeing the dom

- screen.debug() to see the entire screen (the body)
- add args like this `screen.debug(screen.getByText('test'))` to debug one element

## types of queries

- it's crucial to use the correct type of query, as each use case is different

### getBy[...]()

- getBy queries are singular and will query if an element exists. If the element doesn't exist OR if there is more than one, it will throw an error, meaning the test itself won't work.

- use when there should be only one element

- getAllBy returns an array of all matching nodes, but throws and error if none are found

- there are different types of getBy queries. In order of what should be used:

  1. getByRole

  - query element exposed in the accessibiity tree.
  - screen.getByRole('button', {name: /enter/i})
  - this should work most of the time

  2. getByLabelText

  - query elements in forms based on label element names
  - screen.getByLabelText("Username");

  3. getByPlaceholderText]

  - query form input elements based on placeholder prop

  4. getByText

  - used to find non-interactive elements. divs, p

  5. getByDisplayValue

  - current form value

- if you want multiple matches, use `getAllBy`

### queryBy[...]

- used to assert that an element does NOT exist
- getBy can't assert a missing element as it will throw an error, while queryBy will return null
- if queryBy returns more than 1 match, it will throw an error
- `querryAllBy` returns an array of all matching nodes OR an EMPTY ARRAY if not found

### findBy[...]

- waits for 1 second and looks for element
- useful in certain cases where a framework has to do some logic before the page is rendered
- must use async syntax

## userEvent

- mimics user interactions
  - `userEvent.type(screen.getByLabel(\name\i)), "Patti"); ` // finds input with label "name" and enter the text "Patti"
- common pattern is to render a component, act using userEvents on nodes found with `getBy...`, then looking and testing the final state with the async `findBy`

## unit/integration tests

- one manageable user flow like filling out a form and submitting it can be considered an integration test
- a unit test is usually testing one piece of logic
- test() can have multiple expects or a single one.
- adding multiple expect() calls within a test should usually mean they are a part of one workflow ie integration test
