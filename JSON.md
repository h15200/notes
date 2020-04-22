# JSON

Java Script Object Notation - a string notation for all js objects

When going for JS to JSON, you just put single quotes around everything.
If it already has quotes like in a string, you put SINGLE quotes around the whole thing and double quotes for inner ones.
Object keys will also now have double quotes around them.

SO

Convert js type number into type string
JSON.stringify(5) // '5'

Convert js type string into JSON string
JSON.stringify('hello') // '"hello"'

Array to JSON string
[1,2,3, 'hi'] // '[1,2,3, "hi"]'

Objects to JSON string
{ a: 3, b:5 } // '{"a":3,"b":5}'

Although we call them JSON string, they are treated as JS strings with prototype string methods

To go from JSON string to JS object, you use JSON.parse()

Also as a reminder, keys are all strings in js objects.
const obj = { 2: 2 } works, but it really means "2": 2

So to call obj value with the key, "2", you need bracket notation.
obj[2] // returns the NUMBER 2

JSON.stingify() will reverse this and turn JS objects into a JSON string.
This is useful when deep comparing arrays or objects.

one array or obj is never === to another, but
JSON.stringify(arr) === JSON.stringify(arr)
