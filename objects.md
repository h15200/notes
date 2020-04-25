key in object

the inverse of
`if (key in object)`

needs to be parenthesized like so
`if (!(key in object))`

## Property Descriptor

All object properties (including accessors and methods) have a property descriptor object that shows 4 thigns

1. writable - can value be overwritten?
2. enumerable - will key/value show up in a for - in loop?
3. value - the value attached
4. configuarable - can property definition be changed?

To access it in JS,

`Object.getOwnPropertyDescriptor(obj, key;`

To CHANGE the property descriptor,

`Object.defineProperty(obj, key, { writable: false })`
// now you've changed the property such that its value can't be updated!
