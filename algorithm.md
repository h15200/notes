# list of algorithm patterns

## solve 24 solve24('1234') // "(1+2+3)\*4"

See code. The hardest one so far to date (4-30-20)!

## for recursive functions that aren't sequential

Use an object to store all solved index values. see partitionFunction.js
This is called memoization!

## balanced parens

Instead of using difficult regex, better to use a Stack to keep track of most recent open brackets.

Strategy

make a bracket pair cache like
{
'{' : '}',
'(' : ')'
}

Stack can be used as a simple array but using push and pop (last one in, first one out)

loop through string and IF opening brackets, push to stack.
Else if closing brackets, check to see if the POP value of the stack matches.
If not, return false

After loop, if there are any items inside the stack, it was never closed

## merge sort

return all array length 1 or less

separate into left and right

make a helper merge

return merge(recursive(left), recursive(right))

## Kadane's algo

max subset

brute force-

if you get the max subset of all that ENDS on index 0, then 1, then 2, that is brute force.

ex [1,2,3]

index 0 -> possible substrings that ENDS in 1 = only [1]
index 1 -> [2], [1+2]
index 2 -> [3], [3+2], [3+2+1]

Kadane's algo dictates that at each index, all you need is to compare the num itself with the max subset of the previous.

SO

[1,2,3]

max = currSubset = index[0]

then in second index, new subset is either prev subset or prev subset + current item

etc..
