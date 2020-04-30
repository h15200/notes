# Regular Expressions - also called Regex

## Usage

/actualRegex / flags

/hi/

## .test() regex method

.test()

`/hi/.test("hi there!")` // returns true

## flags

Flags can be used to alter regex.

`i`
The “i” flag will match all upper-lower case combination
`/dog/i.test(string);` will look for dog, Dog, doG, DOG, dOG etc..

`g`
global - match all instances and not just the first. Moot in .test, but useful in .match
see below

## str.match()

Is a string method that takes regex as the parameter as opposed to .text() being a regex method that takes on a string.

Will return array with match or null if no match.
If a g flag (see below) is used, it will return all match instacnes.
If no g flag, additional properties will be returned in the array of the FIRST match

`“I really really really like dogs!”.match(/really/g);` returns [“really”, “really”, “really]

You can stack flags like /dog/gi - dog in any casing, look for multiple matches

## Regex operators

### or operator

```
const string = “i love my dog”
const regex = /cat | bird | dog/
regex.test(string);   // returns true
```

### . wildcard

`.` is a wildcard. It takes up one char but it could be any char.
/do./ includes dog, do3, doK, do<, do5, even do + whitespace

### ^ first character (NOT inside square bracket character classes)

Outside character sets, ^ is used to check the first characters of a string
`/^hi/.test(“hi. How are you?”);` // returns true
`/^hi/.test(“Patti, hi. How are you?”);` //returns false

### \$ last character (NOT inside square bracket character classes)

a dollar sign AFTER the regex WITHOUT character sets [] will search for the word at the very end of the string.

NOTE the syntax! Dollar sign is AFTER the last string

`/^FIRST/`
`/LAST$/`

`/you?$/.test(“Patti, hi. How are you?”);` // returns true

### + One plus occurances

The + sign will look for 1 OR more instances

`“Hello, long island”.match(/L+/gi);` //will return [‘ll’, ‘l’, ‘l’]

### \* Zero or more occurances

The \* sign will look for at least 0 occurrences and is written AFTER the applied char.

In this example, 't' is what is applied with \*, meaning there can be no 't' after go, or a million 't'

`/got*/.test(string)` //will return true for strings 'go', 'got', 'gotttttt', 'goti', 'gottti'

#### Default bahavior when str.match(regex) with \*

When using `*`, with str.match(), JS must choose the substring that matches

`hiiii!".match(/hi*/)`
In this example, 'h', 'hi', 'hii', 'hiii', and 'hiiii' are ALL matches for `/h*/`
By default, JS will choose the longest string available (greediest) in this case 'hiiii'

Even for global flags, js will choose for each instance

`“H, hi, hiiii”.match(/hi*/gi);` // will return “H, hi, hiiii”

#### Changing default behavior from greedy to lazy when using str.match() with ?

using `?` right after the `*` operator will change to lazy, which is the smallest occurance of `*` char:

`“H, hi, hiiii”.match(/hi\*?/gi);` // will return “H, h, h”

### Question mark

`?` is used to denote lazy match when applied RIGHT AFTER `*?` OR right after occurance `{1,3}?`
If being used OUTSIDE these two circumstances, it is used as an operator to indicate zero or one element.

Applies to the element BEFORE the question mark

`str.match(/12B?/gi)` // searches for 12 AND 12B. B is optional

## Character class []

A character class placed inside squre brackets represent possibilities for ONE char and
provides and alternative to using `|` OR operator depending on your circumstance

`/do[gt]/` will look for dog | dot

### Hyphen - inside character classes

Hyphen will do all characters in between `/[a-d]pple]/` // apple, bpple, cpple, dpple
Hyphen can do numbers as well and can be combined with letters `/[a-d3-5]/` // a,b,c,d,3,4,5

### NOT operator ^ INSIDE character classes

Putting `^` first inside a character class denotes NOT operator

`/[^aeiou0-9]/ig` // match all characters that are NOT vowels or nums, even whitespace, any casing, and multiple instances

### Shorthand Character classes

#### \w

`[a-zA-Z0-9_]` can be shortened to `\w`
This case will match a single character that is any letter, any number, or underscore.

Using `string.match(/\w/g);` will return an array of every character

#### /W

`\W` is the OPPOSITE of `/a-zA-Z0-9_/`, meaning anything that's not a letter, number, or underscore.
Includes whitespace and ALL punctuation, so very useful to `str.split(/\W/)`. This will turn most strings into an array of words

#### \d

All numbers

#### \D

all non numbers

#### \s

All whitespace

#### \S

all NON whitespace

### Lower and upper number of matches

Curly brackets can be applied right after a char to specificy custom number of occurances (like + or \*)

`/a{1,3}` one to three occurances of 'a'

#### Default is greediest when using {} and .match()

If you are using `{}` along with str.match(), JS will match with the greediest by default (like when using `*` and `match()`)

`“Gaaaaa”.match(/a{1,3}/g);` // will return “aaa”, “aa” because the highest occurance, 3 is available and becomes the first match. There are only 2 remaning 'a's, and that becomes the second match.

#### Change default match to laziest with ?

add question mark OUTSIDE the curly braces to get the laziest matches
`“Gaaaaa”.match(/a{1,3}?/g);` // adding ? and lazy wil return “a”, “a”, “a”, “a”, “a’
Note that right now having 35 a’s in the string will still be true for checking /a{3,5}/
To limit the return to only 5 “a”s, do something like /Ga{3-5}[^a]/

#### Just using the minimum bound

You can just apply min {3,} but MAKE SURE there is no whitespace after comma.

`/a{5,}/` // at least five or more

#### exact occurance

To get the exact number of letters, just use one number without any commas in curly -
`a{4}`

### Useful string.replace() with regex

replace()

`string.replace(regex, newstring)` //can be used to match and replace a string

backslash UPPERCASE “W” will search for the opposite of `/a-zA-Z0-9\_/`
USE THIS to strip everything except letters (including punctuation and whitespace)

let newStr = str.replace(/[^a-za-z]+/ig ,"") // replace NOT letters with an empty string '', leaving only words. Strips all punctuation and whitespace.

### To match a dollar amount format

`/^\d{1,}(\.\d{0,2})?\$/`

### Positive and Negative Lookaheads

Lookaheads are used to look for a pattern in a string without actually matching.
Syntax is `(?=REGEX)`

`/(?=\d{,3}/`

let password = “abc123”
let posLook = /(?=\d{3,}/
posLook.test(password); //returns true
