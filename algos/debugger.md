# using vsc (or any other) debugger

- for client side code, use the chrome engine (in vsc) or the react dev tools in the rendered browser
- for typescript server side, it's more straight forward https://code.visualstudio.com/docs/typescript/typescript-debugging

## breakpoint

- setting a breakpoint specifies a place in code and takes a snapshot of all variables at that point. it "pauses" the program at that line
- note that the code ON the line has NOT run yet. If a breakpoint is on line 5, it has executed all the code up UNTIL the code on line 5.

## main navigation tools

### continue (play button)

- moves to the next breakpoint

### step over (right arrow)

- moves to the next line. This will execute all the code from the previous breakpoint and display all updated data

### step into (down arrow)

- if the current line calls a function, go in that that call stack

### stop out of (up arrow)

- go out of the current scope of the breakpoint. return out

- NOTE! When you step OUT of a scope, you will go to the line where that function was called. Unlike breakpoints, in this case, the highlighted line has already been executed

### dynamic navigation

- simply add new breakpoints during the debug session and press continue to jump to the next line
