# Python 3 cheatsheet

## quick env

- for interactive python, just run `python3` in terminal
- to quit, `quit()`

## variable assignments

- generally, use the `let` version without a declaration
- `num = 5`
- multiple vars `a, b = 4, 6`
- swapping vars `a, b = b, a`
- inline conditional assignment `a = List[idx] if idx >= 0 else None`

## infinity

- float("-inf"), float("inf")
- if you need int infinity, - infinity, import math and `a, b = math.inf, -math.inf`

## types

- check by `type(variable)`
- force by `int(thing)` or `float(thing)`
- digit strings can be converted to int

```
sVal = "123"
nVal =  int(sVal) # number 123
```

## equality checking

- in Python, `==` means are "are they the same?", meaning two arrays will be == even if they don't have the same reference
- to check exact equality (in the sense of javascript), use the keyword `is` or `is not`
- `is` only works with numbers, Lists, Dicts but not strings
- `0 == 0.0` True
- `0 is 0.0` False
- [1,2] == [1,2] True
- [1,2] is [1,2] False
- [1,2] is not [1,2] True
- `"abc" == "abc"` True
- `"abc" is "abc"` Syntax Error!

## diving (in python3 only)

- when dividing, python will always convert to a `float` and is more predictable
- 12 / 4 logs `3.0`
- if you want math.floor(<someDivisionOperation>), use `//`. `12 // 5 # returns 2`

## is whole

-<float>.is_integer() -> returns boolean

- `3.5.is_integer()` -> False
- `3.0.is_integer()` -> True

## string template literals (v. 3.6+)

- prepending with `f` + quotation marks (single or double) will format the string with literals

```
name = 'Patti'
print(f'hello, {name}')
```

## for in loop args

- if 1 arg, just the start value
- if 2 args, start, end
- if 3 args, start, increment, end

```

# reverse for loop

nums = [10,20,30]
for i in range(len(nums) - 1, -1, -1):
print ('item is', nums[i])

```

## try/except

- throw exceptions with try/except

```
try:
  # some code that could fail
except:
  # some action when there is an error
```

## syntax

- use lower_snake_case for variables and function names
- `elif` , not `else if`
- `and` instead of `&&`
- `or` instead of `||`

## fs

- `file_handler = open(myNotes.txt, 'r')` open "read" mode and return handler. "r" is default, but good to be explicit
- `for line in file_handler:` for loop in a file handler defaults to lines of text
- to get the file as 1 string, `file_as_one_string = read(file_handler)` use `read()` on the file_handler (not the atual file)

## Collection type data structures

- a `collection` is the general term for any data structure in Python that allows multiple values
- there are 4 collections in python

1. `List`

- ordered
- mutable
- "[]"
- duplicates allowed

2. `Dictionary`

- ordered (after v3.7!)
- mutable
- "{}"
- no duplicates allowed

3. `Tuple`

- ordered
- immutable
- "()"
- duplicates allowed

4. `Set`

- unordered
- immutable
- "{}
- no duplicates allowed

## range()

- super useful
- returns a `list` of 0 index nums
- ex1. `range(5)` -> [0,1,2,3,4]
- ex2. `range(len(['hi','there']))` -> same as `range(2)`, which is [0,1]

## slicing strings and arrays

- syntax is [<startingIdx>:<lastIdxNotIncluded>]
- if blank, will default to first idx of collection for start and end of collection for end

```
arr = ['a', 'b', 'c']
sliced_arr = arr[0:2]
# returns ['a', 'b']
```

## declaring collections

- class constructor form (slower! do not use)

  - `my_list = list(['a', 'b', 'c'])`
  - `my_dict = dict({'a': 'hello'})`

- literal form
  - `my_list = ['a', 'b', 'c']`
  - `my_dict = {'a': 'hello'}`

## str.split()

- without any args, it defaults to "smart" splitting on all whitespace, multiple whitespaces, and newline
  ```
  str = "hello     there      with    whitespaces"
  arr = str.split() # ['hello, there, with, whitespces]
  ```

### sorted()

- is not a method, but an individual function called with the list as an arg
- second arg can be `reverse=True` to do descending order

## list

- `List comprehension` is a way to make lists easily from other data structures
- syntax is square brackets with the `comprehension target` (data you want), then a for loop structure over an iterable
- if multiple comprehension targets, must use parethesis
- example with nums from list -> list of nums

  - `list_of_nums_plus_1 = [num + 1 for num in [1,2,3,4,5]]` -> list_of_nums_plus_1 is [2,3,4,5,6]

- example making list of key strings from dict

  - `list_of_strings_dict = [ k for k,v in some_dict.items()]`
  - note that that we're using `k,v` for the data extraction from items(). If you only have k, the k will contain the entire tuple instead of just the key as there is no destructuring

- example making list of tuples of value/key strings (reversed)
  - `list_of_v_k_tuples = [(value,key) for key,value in dict.items()]`

## dictionary

- key doesn't need to be a string. it can be any immutable python object
- `.get(<key>, <defaultIfNotFound>)` looks for a value, but if it doesn't exist returns the provided default val

  - useful for making a counter `cache[key] = cache.get(key, 0) + 1` (if val exists, assign + 1. if not, assign 1)

- `.keys()` will return a list of keys from the dict
  - you can also `list(my_dict)` which will do the same thing
- `.values()` will return a list of values from the dict
- `.items()` will return a `list` of `tuples` of key-value pairs
  - you can easily have access to both key and value with .items by:
  ```
  my_dict = {<some data>}
  for key, value in my_dict.items():
    # do stuff
  ```
  note that destructuring can just be done with comma separated values

## tuple

- tuples can be compared `(1,2,3) < (0,1,5)`
  - is 1 < 0 ? if so, return true. if not, increment both tuple iterations
  - is 2 < 1 ? if so, return true, if not, icrement both
  - is 3 < 5? etc...

## socket library

- built-in support for TCP sockets

```
import socket

my_socket = socket.socket()
my_socket.connect((<hostString>, <portNumber>))

```

## strings

- in python 3, all internal strings are `unicode`
- in python 2, strings and unicode were separate classes

- ASCII charCode can be accessed with `ord('H')` -> 72
- when sending data over the network, `unicode` is sent via utf-8 majority of times
- see `web_client.py` for examples

## class

- all methods (including constructor and destructor functions) take in `self` as the first parameter
- both constructors and destructors are defined like regular methods, `def __init__(self, bla): `
- constructor is `__init__`
- destructor (rarely used) is `__del__` is called on
- when does the destructor run?

  - whenever the instance is garbage collected or destroyed in any other way

  ```
  my_animal = Animal() # runs the constructor
  my_animal = "hi" # the re-assignment destroys the instance, so the destructor will run here!

  ```

- when a class is instantiated, the first variable will be the 2nd parameter of the `__init__` method since the first param is `self`. Class methods will always have 1 extra param compared to the function args

- subclassing or extending a class in Python looks like this

  ```
  class Animal:
    # stuff

  class Dog(Animal):
    # subclass of Animal class

  ```

  - no need to manually call the super class constructor. It will automatically inherit and run the constructor.
  - the arg of the subclass expects the args of the super constructor

## Database

- python ships with SQLite
