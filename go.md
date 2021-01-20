# Golang

NO SEMIs
Double quotes ONLY for strings
comments are same as js, `//` or `/* */`

package or library

go build [filename]
go run [filename]
go doc [packageName]
go doc [packageName.funcName]

## types

bool, string, int, float

ints and floats also have sub types (float16, int32, uint8)
int are either signed (- and +) or not
int8 (-125 ish to + 125)
uint8 (0 to 255)
complex64 (square roots, imaginary nums)

BUT best practice is to just use default `int` or `uint` with no number to let Go figure out if your machine is using 32-bit or 64-bit architecture

## defaults

unlike JS and undefined, Go has sensible defaults
string ""
int 0
float 0
bool false

## Inferring types

Go will infer the type based on assignment.

var isTrue = false (defaults to type bool) is a same as var isTrue bool = false

numbers are infered as either int32 or int64 (not uint even for positive nums) and floats are always float64.

### var declaration and inferring shortcut

syntax shortcut for var myNum = 32 is `myNum := 32`
This shortcut will default to `int` and not `int32` or `int64`

## inline multiple declarations

using var
`var num1, num2 int` (num1 and num2 must be same type)

using :=
`myNum, myString := 39, "hello!"` (can be different inferred types)

## format package

import "fmt"

fmt.Println() - prints every word with a space and every instance with a new line
fmt.Println("how", "are", "you") -> "How are you"

fmt.Print() - no spaces, no linebreaks

fmt.Printf() - can use `verbs` inside strings with %v and comma separated values

```
name := "Patti"

fmt.Printf("hello there, %v", name)
```

### verb types

%v - the actual value of variable
%T - TYPE of value ex. num, string, float
%d - type coersion of int -> string `fmt.Printf("You're %d years old", age)`
%f - float -> string. option to set decimal place `fmt.Printf("Your test average is %.2f", gpa)` - 3.80
