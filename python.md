# Python 3 cheat sheet

## quick env

- for interactive python, just run `python3` in terminal
- to quit, `quit()`
- style guide https://peps.python.org/pep-0008/
- vscode packages
  - black (the prettier of python)
  - `sourcery` free tier (linter)

## variable assignments

- generally, use the `let` version without a declaration
- `num = 5`
- multiple vars `a, b = 4, 6`
- swapping vars `a, b = b, a`
- inline conditional assignment `a = List[idx] if idx >= 0 else None`

## Typing

- input/outputs can be typed
- variable annotations `is_true: bool = True`

## script vs library best practice

- if it's a script, define a `main` function
- at the end, check for `__name__` and run it
- this is to avoid side effects if you accidentally imports this as a library and signals to others that this is meant to be run directly

```
def main() {
  # add main script logic

}

if __name__ == "__main__":
  main()
```

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

## min(), max(), abs()

- no need to import math
- you can add a `key` arg to use a `lambda` to each iterable
  - ex.
  ```
    my_list = ['hello', 'patricia']
    shortest_str = min(my_list, key=len)
  ```

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

## range() in for loops

- if 1 arg, just the start value
- if 2 args, start, end
- if 3 args, start, increment, end
  `for idx in range(1, len(my_list)):` will increment from 1 to end of list

# reverse for loop

nums = [10,20,30]
for i in range(len(nums) - 1, -1, -1):
print ('item is', nums[i])

### BETTER to use enumerate() for indices

- `for idx,val in enumerate(list_A): `
- remember, this is a tuple unpacking (destructuring), so you need two comma separated values
- if you only need idx and not the val, use `_` to signify you don't need it.
  - `for i,_ in enumerate(list)`

## making a list of the same item x buckets long

- `[0] * 26` will make a list with len 26 with all `0` as values (building alphabet hash)

## List.count

- `my_list.count(None)` - how many None are there in the list

## check for empty list

use `if not my_list` instead of `if not len(list)`

## all()

- `while all(i is None for i in my_list):`

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
- to get the file as 1 string, `file_as_one_string = read(file_handler)` use `read()` on the file_handler (not the actual file)

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

- `row = collections.defaultdict(list)` Makes a dictionary that creates a default list with a new key that doesn't require a separate creation step. `row["new_key"].append(5)` will create the new list in the dict. Useful in caching!

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

- without any args, it defaults to "smart" splitting on all whitespace, multiple whitespace, and newline

```

str = "hello there with whitespace"
arr = str.split() # ['hello, there, with, whitespace]

```

- if you want to split by all chars, you need to use either:

1. `list(str)` (uses the list constructor, so less optimal than option 2)
2. list comprehension `[char for char in some_string]` (better than option 1)
3. unpacking with "*" `[*my_string]`

### sorted()

- is not a method, but an individual function called with the list as an arg
- second arg can be `reverse=True` to do descending order

## list

- `List comprehension` is a way to make lists easily from other data structures
- syntax is square brackets with the `comprehension target` (data you want), then a for loop structure over an iterable
- if multiple comprehension targets, must use parenthesis
- example with nums from list -> list of nums

- `list_of_nums_plus_1 = [num + 1 for num in [1,2,3,4,5]]` -> list_of_nums_plus_1 is [2,3,4,5,6]

- example making list of key strings from dict

- `list_of_strings_dict = [ k for k,v in some_dict.items()]`
- note that that we're using `k,v` for the data extraction from items(). If you only have k, the k will contain the entire tuple instead of just the key as there is no destructuring

- example making list of tuples of value/key strings (reversed)

- `list_of_v_k_tuples = [(value,key) for key,value in dict.items()]`

- to combine two existing lists, for python 3.6+, `combined_list = [*list_a, *list_b]`

- chaining `for` ex. combining a list of inner lists from a matrix
- `combined_list = [char for single_list in matrix for char in single_list]`

## dictionary

- key doesn't need to be a string. it can be any immutable python object (TUPLE)
- you can make a list, than make it a tuple to use a hash like data as a key
- `.get(<key>, <defaultIfNotFound>)` looks for a value, but if it doesn't exist returns the provided default val

- useful for making a counter `cache[key] = cache.get(key, 0) + 1` (if val exists, assign + 1. if not, assign 1)

- `.keys()` will return a list of keys from the dict
- you can also `list(my_dict)` which will do the same thing
- `.values()` will return a list of values from the dict
- `.items()` will return a `list` of `tuples` of key-value pairs
- you can easily have access to both key and value with .items by:

```

my_dict = {<some data>}
for key, value in my_dict.items(): # do stuff

```

note that destructuring can just be done with comma separated values

## tuple

- tuples can be compared `(1,2,3) < (0,1,5)`
- is 1 < 0 ? if so, return true. if not, increment both tuple iterations
- is 2 < 1 ? if so, return true, if not, increment both
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

- sub classing or extending a class in Python looks like this

```

class Animal: # stuff

class Dog(Animal): # subclass of Animal class

```

- no need to manually call the super class constructor. It will automatically inherit and run the constructor.
- the arg of the subclass expects the args of the super constructor

## Database

- python ships with SQLite

## Queues

- use `q = collections.deque([initialVal])` to make a queue
- `q.popleft()` will get the top
- `q.append()` will add to queue

## priority queues

`my_list = [1,2,3,1,5,-1]`
`heapq.heapify(my_list)` doesn't return anything, so call it separately
`heapq.heappop(my_list)`
`heapq.heappush(my_list, val)`
`heap[0]` to just access the top of the heap without popping

## comparator review

- if plugging in custom compare function, return -1 if it's good as is, and return 1 to reverse order

```
# some compare function that takes the bigger of the 2nd index in an iterable
def compare(a, b) -> int:
  if a[2] > b[2]:
    return -1
  else:
    return 1

```

- to plug it in, use `sorted` with the 2nd arg being `key=cmp_to_key(custom_func)`
  `new_list = sorted(nums, key=cmp_to_key(compare))`
