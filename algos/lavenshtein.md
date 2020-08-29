# Turn str1 into str2 using INSERT, DELETE, or REPLACE actions with the minimum number of moves

## Logic

str1 = yargs
str2 = args

Think about each operation as a LAST action after a series of sub problems (dynamic programming)

- What is INSERTION?

  'hello' -> 'bug'

  1. Find min moves to turn 'hello' into 'bu' ('bug' - 'g')
  2. str1 is now 'bu' so simply add 1 insert action to make 'bug'

  Formula is the subproblem of (str1 -> str2 - 1 char) PLUS 1

- What is REPLACEMENT?

'hel' -> 'ap'

1. Ignore the last char for both for now and turn str1 - char into str2 - char, so 'he' into 'a'
2. now you have 'al' -> 'ap', so plus one to replace that last char that was ignored.

Formula is ( (str1 - 1 char) -> (str2 - 1 char) ) PLUS 1

- What is DELETION?

  'benny' -> 'test'

  1. Turn 'benny' minus 1 char, 'benn' into all of str2 'benn' -> 'test'
  2. now we have 'testy' -> 'test', so add 1 delete operation

  Formula is (str1 - 1 char -> str2) PLUS 1

- What if chars are equal?
  If chars are equal, it's the same as deleting them from both strings.
  ex. 'jacko' -> 'hello' SAME as min('jack' -> 'hell')

Write a 2 dimension array with empty strings (so length of strings + 1 for cols and rows)

fill out min to turn vertical values into the horizontal ones ie "" to A, "" to R,
for rows and cols

```
   "" | A | R | G | S
""  0 | 1   2   3   4
Y   1 | fill these out based on condition + 1, or take diagonal if chars are equal
A   2 |
R   3 |
G   4 |
```
