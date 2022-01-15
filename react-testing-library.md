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

- use one .test (or .test.tsx) file per component. ex - `UserForm.test.tsx` and only test that one component in each file

- one manageable user flow like filling out a form and submitting it can be considered an integration test
- a unit test is usually testing one piece of logic
- test() can have multiple expects or a single one.
- adding multiple expect() calls within a test should usually mean they are a part of one workflow ie integration test

## inputs

- inputs are tricky as there are multiple ways of querying them. Make sure it is accessible in the source to start. All inputs should have an associated label, and the label must link to the input with any of these methods:

the most common way is,label ele BEFORE input ele, htmlFor attribute set to the id that's set in the input

```
<label htmlFor="firstname">First Name</label>
<input
  id="firstname"
  type="text"

/>

```

- method 1 input can be queried by `const inputEle = screen.getByLabelText(/firstname/i);`

-using `screen.getByRoles("textbox", {name: /something/i})` will require specific aria labels

### example

```
import React from "react";
import { render, screen, waitFor } from "@testing-library/react";
import userEvent from "@testing-library/user-event";
import { Practice } from "./practice/Practice";

// getBy... use to assert one singular, returns element or error if no match
// getAllBy... use to assert multiple, returns list of elements or error if no match

// queryBy... use to assert element doesn't exist. returns null or error if match
// queryAllBy... use to assert multiple elements don't exist. returns array with elements or empty array

// findBy... async positive assertion like getBy
// findAllBy... async multiple positive assertions like getAllBy
test("Practice Component should not render any article", () => {
  render(<Practice />);
  // check for all article elements and make sure none exist
  const linkElements = screen.queryAllByRole("article");
  expect(linkElements.length).toBe(0);
});

test("Practice Component should render 1 increment button", () => {
  render(<Practice />);
  // check for exactly 1 button named /increment/i
  const buttonElement = screen.getByRole("button", { name: /increment/i });
  expect(buttonElement).toBeInTheDocument();
});

test("Practice Component should render several list items after fetching", async () => {
  render(<Practice />);

  // ol, ul, are both just "list" roles
  await waitFor(() => {
    expect(screen.getAllByRole("list")).toHaveLength(10);
  });

  // lines 31-33 can also be replaced by next two lines as another option

  // const listItemElements = await screen.findAllByRole("list");
  // expect(listItemElements).toHaveLength(10);
});

test("Clicking on increment button will change num counter", () => {
  render(<Practice />);
  expect(screen.getByText(0)).toBeInTheDocument();
  const buttonElement = screen.getByRole("button", { name: /increment/i });
  userEvent.click(buttonElement);

  expect(screen.queryByText(0)).not.toBeInTheDocument();
  expect(screen.getByText(1)).toBeInTheDocument();
  userEvent.click(buttonElement);
  userEvent.click(buttonElement);
  userEvent.click(buttonElement);
  expect(screen.getByText(4)).toBeInTheDocument();
});

test("Input element should display what's being typed", () => {
  render(<Practice />);
  const inputElement = screen.getByLabelText(/italics/i);
  expect(inputElement).toBeInTheDocument();

  userEvent.type(inputElement, "hi");
  expect(screen.getByDisplayValue("hi")).toBeInTheDocument();

  userEvent.type(inputElement, ", there!");
  expect(screen.getByDisplayValue("hi, there!")).toBeInTheDocument();
});

```

### react-testing-library is used to test logic, not css styles