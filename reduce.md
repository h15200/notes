# Reducer Method!

```
let arr = [1,2,3]

arr.reduce(callback(accumulator, currentValue), initialValue)

```
<br/>

## Initial value is optional and is key!


- If there <strong>is</strong> an initial value, then think of them in TEAMS

        [initialValue]   VS    [ 1,2,3] 

  callback is run on 1, 2, and 3 and each result will become the new [initialValue]

 In the callback, the return statement is equal to "the new accumulator equals"
<br/>
<hr/>
<br/>



- If there is <strong>NO</strong> initial value


       [1]          vs     [2,3]
    The array is split up. The first element is the accumulator.
    The current element now starts on 2, and the result of that callback becomes the new accumulator

