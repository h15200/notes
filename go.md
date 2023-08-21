# Golang

- good basic resource is `tour.golang.org`

## general syntax

- NO SEMIs after statements (but often used inline in conditionals and for loops after var declarations)
- Double quotes ONLY (no single quotes unless declaring `runes`)
- comments are same as js, `//` or `/* */`

package or library

go build [filename] - will do nothing if there is no main package anywhere
go run [filename] - will run the file. will usually not work for packages that are not main
go work - will allow for multiple go.mod files if in root directory. - first `go work init`, then add the folders via `go work dir_name`
go doc [packageName]
go doc [packageName.funcName]

## types

- int int8 (-125 ish to +125) int16 int32 int64
- uint uint8 (0 to 255) uint16 uint32 uint64 uintptr
  - best practice is to just use default `int` or `uint` with no number to let Go figure out if your machine is using 32-bit or 64-bit architecture
- byte // alias for uint8 - same as `utf-8`
  - when sending data over the network, data is usually converted into []byte
- rune // alias for int32
  // represents a Unicode code point

  - a `range loop` will treat each char as a int32 or Rune
  - a for loop ove indices and referencing by `myString[i]` will treat char as a uint8 or Byte

- a single quote declaration of a char will be a rune `myRune = 'a'` while a double quote will default to a string
- float32 float64
- complex64 complex128 (square roots, imaginary nums)

## defaults

- unlike JS and undefined, Go has sensible defaults when types and references are declared without init vals
- string ""
- int 0
- float 0
- bool false

## inferring types

- Go will infer the type based on assignment.
- var isTrue = false (defaults to type bool) is the same as var isTrue bool = false
- numbers are inferred as either int32 or int64 (not uint even for positive nums) and floats are always float64.

## var declaration

- declarations can be made on the top, package level or function level
- package level vars can be used by function level because of lexical scope
- If the FIRST char of a package level declaration is capitalized, it can be exported to other packages

`var num int` // if there is no initializer, the type must be written
`num = 32` // now a value is assigned

The above can be written as `var num = 3` // if there is an initializer, the type can be omitted

- Short hand for var initializing (Only inside functions)
  `myNum := 32`
  This shortcut will default to `int` and not `int32` or `int64`

- if you want shorthand to be of a specific type, PRIMITIVE types use () and structs use {}

  - `myNum := int8(20)`
  - `mySlice := structName{'hi', 'there'}`

- to initialize to something that's not inferred `z := float64(1)`

## inline multiple declarations

```
var (
	ToBe   bool       = false
	MaxInt uint64     = 1<<64 - 1
	z      complex128 = cmplx.Sqrt(-5 + 12i)
)
```

using var
`var num1, num2 int` (num1 and num2 must be same type)

using := (again, only inside functions!)
`myNum, myString := 39, "hello!"` (can be different inferred types)

### type conversion

`T(v)` converts the value v to the type T

`i := 31` // declares int i which has value of 31
`u := uint(i)` // declares uint u which has value of 31. int 31 was converted to uint

## constants

Constants can be character, string, boolean, or numeric values
const can't be declared using the := syntax
structs, slices, maps can't be const

convention to capitalize const but only inside functions. Otherwise, it will signal that it should be exported

`const Big = 1000000000`

### enumerated consts and enumerated expressions with iota

```
const (
	_ = iota
	blueCar
	greeCar
	redCar
)
// iota starts at 0, then increments automatically
```

## scoping

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

## functions

- Arg numbers must match when called
- params and returns should be typed

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

### named returns and naked returns (don't use)

returns can be named where you usually type the return, surrounded by parens

```
func someFunc(num int) (myReturn int) {
  myReturn = num + 1
  return
}
// someFunc(3) will return 4
```

this initializes the var, `myReturn` inside the function, and a `return` statement with nothing after will return ALL named returns, in this case `myReturn`

### defer

- a `defer` statement will defer the execution of a function until the surrounding function returns
- the call's arguments are evaluated immediately, but the execution is held off until the surrounding function is done

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
// "Generated!" will print last in either scenario
```

#### multiple defer - stack

defer func returns are stored in a stack (last in, first out) so if there are multiple defer funcs, the LAST one in the code will execute first (in reverse order of appearance of `defer`)

```
func main() {
	fmt.Println("counting")

	for i := 0; i < 10; i++ {
		defer fmt.Println(i)
	}

	fmt.Println("done")
}
```

// prints DONE 9 8 7 6 ... to 0

"Generated" will print right after the return of either scenario

#### defer and panic

- if a function has a panic call and `defer`, the defer call will always still run, so closing resources will still be fine
- when using anonymous defer function calls, a error handler can recover from a panic state

## packages and exporting

- go imports packages from libraries and other files
- when declaring a package, a name is exported ONLY if it begins with a capital letter
- True also for making structs that you want to use inside another package to print

### format package

import "fmt"

fmt.Println() - prints every word with a space and every instance with a new line
fmt.Println("how", "are", "you") -> "How are you"

fmt.Print() - no spaces, no line breaks

fmt.Printf() - takes in a string and variable(s). the variable will replace the `verbs`

```
name := "Patti"

fmt.Printf("hello there, %v", name)
```

#### fmt.Printf verb types

%v - the actual value of variable turned into a string
%T - TYPE of value ex. num, string, float
%d - type coercion of int -> string `fmt.Printf("You're %d years old", age)`
%f - float -> string. option to set decimal place `fmt.Printf("Your test average is %.2f", gpa)` - 3.80
%q - puts double quotes around string

if a variable isn't used but is appended with `, someVar` it will print (EXTRA type=Value)

ex

```
myNum := 10
fmt.Printf("hello there", myNum)

// will print "hello there (EXTRA int=10)"


	// to format the output (right-align), add a number between the % and verb
	fmt.Printf("formatted to 8 spaces. a: %8T, %v\n", a, a)
	fmt.Printf("formatted to 8 spaces. b: %8T, %v\n", b, b)

	// using square bracket after % and before the verb to reuse same param
	// with printf statements, parameter[0] is the string, [1] is the first var, etc..

	fmt.Printf("Reuse the same param a: %8T, %[1]v\n", a)
	fmt.Printf("Reuse the same param b: %8T, %[1]v\n", b)
```

#### fmt.Sprint()

fmt.Sprint(), Sprintln(), Sprintf will output the new string
common usage is `myString := fmt.Sprinf("Let's make a new %v with Sprint", someVar)`
now myString is a new string

since the first arg string can have %v inside, this is also possible:

````

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

#### fmt.Scan()

gets user input. takes in 1 arg, a variable pre-pended by &

fmt.Println("What's your favorite food?")
fmt.Scan(&food)
fmt.Printf("Cool! I like %v too!", food)

### package "math/rand"

package `math/rand` is used for random nums

rand.intn(100) will return num between 0 and 99

HOWEVER, go uses `seeds` to generate random numbers so if the seeds themselves aren'

## go modules

- generally, easiest to just add go mod file `go mod init <name>` at the top
  level of a repo and only have 1

### package "testing"

- see go repo example file hello_test.go
```
````
