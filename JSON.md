Proper way to write json is single quotes around everything and double quotes around the keys

`let someJson = '{"key": value, "key2": value2}'`

how you can call JSON.parse(someJson) to make a JS object out of the JSON

You can also JSON.parse numbers, quots around numbers (both returns the num) booleans, and quotes around booleans (both return booleans) but not strings even if they are single, then double quoted

Also as a reminder, keys are all strings in js objects.
const obj = { 2: 2 } works, but it really means "2": 2

So to call obj value with the key, "2", you need bracket notation.
obj[2] // returns the NUMBER 2

JSON.stingify() will reverse this and turn JS objects into a JSON string.
This is useful when deep comparing arrays or objects.

one array or obj is never === to another, but
JSON.stringify(arr) === JSON.stringify(arr)
