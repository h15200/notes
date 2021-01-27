# Golang

- good basic resource is `tour.golang.org`

## general syntax

- NO SEMIs after statements (but often used inline in conditionals and for loops after var declarations)
- Double quotes ONLY (no single quotes)
- comments are same as js, `//` or `/* */`

package or library

go build [filename]
go run [filename]
go doc [packageName]
go doc [packageName.funcName]

## types

bool

string

int int8 (-125 ish to +125) int16 int32 int64
uint uint8 (0 to 255) uint16 uint32 uint64 uintptr

byte // alias for uint8

rune // alias for int32
// represents a Unicode code point

float32 float64

complex64 complex128 (square roots, imaginary nums)

BUT best practice is to just use default `int` or `uint` with no number to let Go figure out if your machine is using 32-bit or 64-bit architecture

## defaults

unlike JS and undefined, Go has sensible defaults when types and references are declared without init vals
string ""
int 0
float 0
bool false

## inferring types

Go will infer the type based on assignment.

var isTrue = false (defaults to type bool) is a same as var isTrue bool = false

numbers are infered as either int32 or int64 (not uint even for positive nums) and floats are always float64.

### var declaration

- declarations can be made on the top, package level or function level
- package level vars can be used by function level because of lexical scope

`var num int` // if there is no initializer, the type must be written
`num = 32` // now a value is asssigned

The above can be written as `var num = 3` // if there is an initializer, the type can be omitted

var num int

- Short hand for var initializing (Only inside functions)
  `myNum := 32`
  This shortcut will default to `int` and not `int32` or `int64`

- to initialize to something that's not inferred `z := float64(1)`

### inline multiple declarations

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
`u := uint(i)` // declares uint u which has value of 31. int 31 was conversted to uint

## constants

Constants can be character, string, boolean, or numeric values
consts can't be declared using the := syntax
structs, slices, maps can't be consts

convention to capitalize consts

`const Big = 1000000000`

## comparisons

equal is `==`, `!==`

`<, >, ||, &&, !` same as JS

Switch statements same as JS

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

- a defer statement will defer the execution of a function until the surrounding function returns
- the call's arguments are evaluated immediately, but the execution is held off untilthe surrounding function is done

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

#### multiple defer - stack

defer func returns are stored in a stack (last in, first out) so if there are multiple defer funcs, the LAST one in the code will execute first

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

## packages and exporting

- go imports packages from libraries and other files
- when declaring a package, a name is exported ONLY if it begins with a capital letter
- True also for making structs that you want to use inside another package to print

### format package

import "fmt"

fmt.Println() - prints every word with a space and every instance with a new line
fmt.Println("how", "are", "you") -> "How are you"

fmt.Print() - no spaces, no linebreaks

fmt.Printf() - takes in a string and varible(s). the variable will replace the `verbs`

```
name := "Patti"

fmt.Printf("hello there, %v", name)
```

#### fmt.Printf verb types

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

#### fmt.Sprint()

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

#### fmt.Scan()

gets user input. takes in 1 arg, a variable pre-pended by &

fmt.Println("What's your favorite food?")
fmt.Scan(&food)
fmt.Printf("Cool! I like %v too!", food)

### package "math/rand"

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

### package "math"

math.Pow

## loop

Go only has one looping construct, `for` loops
Syntax is similar to js, but i is initialized with :=

note: unlike JS, there are no parens around the initializer

`for i := 0; i < 10; i++ {}`

There are 3 statements - init, condition, and post, separated by semi-colons

init `i := 0` executed before the 1st iteration
condition `i < 10` executed and evaluated before every iteration
post `i++` executed at the end of every iteration

### ommiting statements

The init and post statments are optional.

When omitting the init statment, a semicolon can be written optionally.

```
num := 4
for ; num < 2000; { // if num is less than 2000, iterate
num *= 10
}
fmt;Println(num) // 4000
```

Or it can be omitted `for num < 2000 {}`

Note:

- if init AND post statements are omitted, this is the same as a `while` loop
- if the condition statement is omitted, it will be an infinite loop

## conditionals

syntax for `if, else if, else` is same as js except parenthesis are optional, but the brackets are required

like `for`, `if` statements can have an init statement to execute that's only scoped to the conditional (including else if and else blocks)

```
someNum := -22
if n := someNum + 123; n <= 0 {
  // stuff
} else if {
  // STILL have access to n here
} else {
  // STILL have access to n here
}
// n is no longer accessible

```

### switch statements

- each case breaks, so there are no fall-throughs by default

```
switch num := rand.Intn(100); num {
  case num > 50:
    // stuff
  case num > 60:
    // stuff
  default:
}
```

a switch with no specified variable is the same as `switch true`, meaning it's just a series of if-then-else chains
some prefer this to using if-then

```
func main() {
	t := time.Now()
	switch {
	case t.Hour() < 12:
		fmt.Println("Good morning!")
	case t.Hour() < 17:
		fmt.Println("Good afternoon.")
	default:
		fmt.Println("Good evening.")
	}
}
```

## addresses and pointers

prepending any var with `&` will refer to the address, the hexidecimal value of where that data lives

a pointer is a variable specifically to store the address. prepend the type with `*` to say "pointer of that stores the address of this data type"

type can be declared or implied

`var pointer *int` - this means that the variable `pointer` will store the hexidecimal address of the place in memory where an int value is stored

inferred version

someInt := 30
myPointer := &someInt // implies myPointer is a type `*int`

## Dereferencing (or Indirecting)

It is possible to change the value of a memory address with the pointer.
if the same same keyword `*` is on the LEFT side of the equal sign, you can dereference a pointer and set a new value

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

## structs

- a struct is simply a collection of fields
- capitalizing the first letter of the struct name as well as field names is based on if you are exporting it to other packages or not

```
type rectangle struct {
  length int
  width int
}
```

// will not export to other packages because props start LOWERCASE. Must be Uppercase to export

### accessing struct fields

struct fields are accessed using dot notation.

```
type Vertex struct {
	X int
	Y int
}

func main() {
	v := Vertex{1, 2} // creates new instance of Vertex with values
	v.X = 4 // overwrite v.X
	fmt.Println(v.X) // access
}
// prints 4
```

#### inferent shorthand stuct pointers

pointers to structs can assign new values to fields like other pointers, but the `*` is optional and implied

```
type Vertex struct {
	X int
	Y int
}

func main() {
	v := Vertex{1, 2}
	p := &v
	p.X = 1e9
	fmt.Println(v)
}
```

above `p` is type *Vertex (pointer of struct type Vertex)
usually, we'd need to use `*p`to dereference to set a value, but`p.X`on line 502 is the same as `(\*p).X`

#### instantiating a struct

If on package level, use the var keyword

```
type Vertex struct {
	X, Y int
}


// single, package level
var v1 = Vertex{1,2} // note that with this syntax, you MUST match the number of fields with declarations
var badv1 = Vertext{1} // WILL ERROR

// multiple, package level
var (
  v2 = Vertex {}// this will not fail because a completely empty declaration will rely on default values for field type. in this case, int will default to 0
)

func main() {
  // inside a func
  v3 := Vertex{X: 1} // if you explicitly declare the field name as well, all missing fields will use default values
  v4 := &Vertext{1,2} // has type *Vertex
}

printed strings will be:
v1  {1 2}
v2 {0 0}
v3 {1 0}
v4 &{1 2}
*v4 {1 2}

```

### arrays

- type `[n]T` is an array of `n` values of type `T`
- array length is part of its type so they cannot be resized once explicitly typed
- `array` in Go is a SPECIFIC, non-resizable data structure. only use if you know the size

`var a [10] int ` describes an array of 10 items, all being int types

- like js, it uses bracket notation to access values on indices

```
func main() {
	var a [2]string
	a[0] = "Hello"
	a[1] = "World"
	fmt.Println(a[0], a[1])
	fmt.Println(a)

	primes := [6]int{2, 3, 5, 7, 11, 13}
	fmt.Println(primes)
}
// prints
Hello World
[Hello World]
[ 2 3 5 7 11 13]
```

### slices

- unlike an array, a `slice` is dynamically-sized and is closer to what you know as arrays in js
- to express slices, simply leave the size inside `[]` blank. this will create an underlying array, then slice
- in practice, slices are much more common than arrays!

`[]T` is a type slice with unknown size of type `T`

- you can create slices from arrays with arrayName[lowIndex: highIndex] (Excludes the actual highIndex)

```
func main() {
	primes := [6]int{2, 3, 5, 7, 11, 13}

	var s []int = primes[1:4]
	fmt.Println(s)

  // prints [3,5,7]
}
```

- Declaring slices

package level `var mySlice = int[] {2,3}` or
func level `mySlice := int[] {2,3}`

#### mutating slices

Since slices do not actually hold data by value but by reference to the array, changing a slice will change the underlying array as well as all other slices referring to that array

```
func main() {
	names := [4]string{
		"John",
		"Paul",
		"George",
		"Ringo",
	}

	a := names[0:2] // [John, Paul]
	b := names[1:3] // [Paul, George]


	b[0] = XXX
	fmt.Println(a, b) // [XXX, Paul] [Paul, George]
	fmt.
  Println(names) // [John XXX George Ringo]
}
```

- you can even make a slice / array of structs

```
	s := []struct {
		i int
		b bool
	}{
		{2, true},
		{3, false},
		{5, true},
		{7, true},
		{11, false},
		{13, true},
	}
```

#### slice defaults

- lowIndex and highIndex can be omitted to denote min and max

```
var a [10]int
// these slice expressions are equivalent:

a[0:10]
a[:10]
a[0:]
a[:]
```

#### length and capacity

- a slice has both a length and a capacity
- `len` is the number of elements in the slice
- `cap` is the number of elements in the underlying array, counting from the first element IN THE SLICE

`len(sliceName)` and `cap(sliceName)`

- you can extend a slice's length by re-slicing it, provided it has sufficient capacity

```
func main() {
	s := []int{2, 3, 5, 7, 11, 13} // makes an array [6]int , then a slice all
	printSlice(s)
	// prints len=6 cap=6 [2 3 5 7 11 13]

	// Slice the slice to give it zero length.
	s = s[:0]
	printSlice(s)
	// prints len=0 cap=6 []

	// Extend its length.
	s = s[:4]
	printSlice(s)
	// len=4 cap=6 [2 3 5 7]

	// Drop its first two values.
	s = s[2:]
	printSlice(s)
	// len=2 cap=4 [5 7]
}

func printSlice(s []int) {
	fmt.Printf("len=%d cap=%d %v\n", len(s), cap(s), s)
}
```

#### nil slices

- if a slice has 0 capacity and 0 length will be 0 and will `== nil`
- if a slice has one of those cap or len values, it is NOT nil

#### making a slice with a bigger capacity than the length

- keyword `make`

`a := make([]int, 5, 10)`
// makes a slice of all default ints, [0, 0, 0, 0, 0] but has cap of 10

#### slices of slices

- slices can contain other slices

```
board := [][]string{
  []string{"first", "subSlice"},
  []string{"second", "subSlice},
}
```

#### append()

- you can add items to a slice (even nil slices) with the built-in append() function.
- first arg is the slice, then 2nd on are the values you want to append
- if there are not enough capacities, it will build a new array and slice

mySlice := []string{}
append(mySlice, 'hi', 'add', 'these', 'strings')

#### iterating over slices and maps

- keyword `range`
- when ranging over a slice, two values are returned per iteration; index and a copy of the element at that index

```
var nums = []int{1,12,23}

func main() {
  for i, v := range nums {
    fmt.Printf("Index is %d and the Element is %v\n", i, v)
  }
}
// prints
Index is 0 and Element is 1
Index is 1 and Element is 12
Index is 2 and Element is 23
```

### `_`

- if you want to omit the index, use `_`
- if you want to omit the value, use `_` or do nothing and it's implied

`for i, _ := range nums` OR `for i := range nums`
`for _, value := range nums` // can't omit this one

- If you don't use `_` and a real letter and that variable is unused in the body, it will throw an error

- this logic and usage of `_` is true for any func that returns multiple values. If you need the 2nd val only, you must use underscore
