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

fmt.Printf() - takes in a string and varible(s). the variable will replace the `verbs`

```
name := "Patti"

fmt.Printf("hello there, %v", name)
```

### fmt.Printf verb types

%v - the actual value of variable
%T - TYPE of value ex. num, string, float
%d - type coersion of int -> string `fmt.Printf("You're %d years old", age)`
%f - float -> string. option to set decimal place `fmt.Printf("Your test average is %.2f", gpa)` - 3.80

if a variable isn't used but is appended with `, someVar` it will print (EXTRA type=Value)

ex

```
myNum := 10
fmt.Printf("hello there", myNum)

// will print "hello there (EXTRA int=10)"
```

### fmt.Sprint()

fmt.Sprint(), Sprintln(), Sprintf will output the new string
common usage is `myString := fmt.Sprinf("Let's make a new %v with Sprint", someVar)`
now myString is a new string

since the first arg string can have %v inside, this is also possible:

```
package main

import "fmt"

func main() {
  template := "I wish I had a %v"
  pet := "puppy"

  var wish string

  wish = fmt.Sprintf(template, pet)

  fmt.Println(wish + !)
}

// PRINTS -> "I wish I had a puppy!"
```

### fmt.Scan()

gets user input. takes in 1 arg, a variable pre-pended by &

fmt.Println("What's your favorite food?")
fmt.Scan(&food)
fmt.Printf("Cool! I like %v too!", food)

## Conditionals

syntax for `if, else if, else` is same as js except parenthesis are optional

## Comparisons

equal is `==`, `!==`

`<, >, ||, &&, !` same as JS

Switch statements same as JS

## Scoping

Like es6, Go is block scoped.
It is possible to have a short declaration inside if and switch statements

```
if product := 8 * 9; product > 60 {
  fmt.Println(product, "  is greater than 60")
}

```

```
switch season := "summer" ; season {
case "summer"
  fmt.Println("Go out and enjoy the sun!")
}
```

Since block scoped, `product` and `season` is not available outside the curly brackets and will throw error on compile

## random nums

package `math/rand` is used for random nums

rand.intn(100) will return num between 0 and 99

HOWEVER, go uses `seeds` to generate random numbers so if the seeds themselves aren't randomized,
the same random number will be generated

using time is a common way to randomize seeds to get random nums

```
package main

import (
  "fmt"
  "math/rand"
  "time"
)

func main() {
  rand.Seed(time.Now().UnixNano())
  fmt.Println(rand.Intn(100))
}
```

## functions

Arg numbers must match when called

params and returns should be typed

```
func specialComputation(x float64) float64 {

}
```

### Go functions can return multiple values.

// declare like this
// for multiple return types, wrap with parens
// return with comma separated values

func returnTwoNums (x, y int) (int, int) {
return x, y
}

// call and assign like this

var num1
var num2
num1, num2 = returnTwoNums(3,4)

### defer

When you want to log something right AFTER the return, but the return happens at different times in code because of conditionals, you can declare `defer` and it will run RIGHT after any return

```
func randomReturn() string {
  defer fmt.Println("Generated!")

  if rand.Intn(100) > 50 {
    return "Returning!"
  }

  fmt.Println("waiting...)

  if rand.Intn(100) < 50 {
    return "Returning later!"
  }

```

"Generated" will print right after the return of either scenario

## addresses and pointers

prepending any var with `&` will refer to the address, the hexidecimal value of where that data lives

a pointer is a variable specifically to store the address. keyword `*`

type can be declared or implied

`var pointer *int` - this means that the variable `pointer` will store the hexidecimal address of the place in memory where an int value is stored

inferred version

someInt := 30
myPointer := &someInt

## Dereferencing (or Indirecting)

It is possible to change the value of a memory address with the pointer.
use the same keyword `*` to dereference a pointer

```
someInt := 30
var myPointer *int
myPointer = &someInt

*myPointer = 40
fmt.Println(someInt) // prints 40, not 30

```

## passing in by pointer

Go functions all use pass-by-value in functions. To go around this, use pointers

```
func addHundred (numPtr *int) {
  *numPtr += 100
}

func main() {
  x := 1
  addHundred(&x)
  fmt.Println(x) // Prints 101
}
```

In the above example, passing in actual x instead of &x would not change the value of var x in main().
