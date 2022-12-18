# Python 3 cheatsheet

## quick env

- for interactive python, just run `python3` in terminal
- to quit, `quit()`

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

## string template literals (v. 3.6+)

- prepending with `f` will format the string with literals

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
