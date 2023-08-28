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

## range loop gotcha

- the value returned by the 2nd return statement from `range` is a COPY
- if the iterator is big (above 64 bytes), avoid range looping!
- also, if you need to mutate the original, you can't use the 2nd arg

```
s := []string{"hi", "bye"}
for i, word := range s {
        // word is a copy! to mutate original, use s[i] instead
    }
```

- remember that both the index and item in a range loop will reuse the pointer

```

func ex2() {
    // a slice of arrays
items := [][2]byte{
           {1, 2}, {3, 4}, {5, 6},
       }

items_2 := [][]byte{} // a slice of slices

         for _, item := range items {
             items_2 = append(items_2, item[:])
                 // this does not work because item[:] is a POINTER.
                 // item keeps reusing the same address, at the end of the loop, item[:] is
                 // always the last loop, {5,6}
         }

             fmt.Println(items_2) // {5,6},{5,6},{5,6}

// the way to fix this is to make a copy
items_3 := [][]byte{}
         for _, item := range items {
            itemCopy := item   // since item is array, this is a value copy
            items_3 = append(items_3, itemCopy[:]) // convert array to slice with [:]
         }

         fmt.Println(items_3)
}

```

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

## strings are utf-8 encoded to include unicode characters

- length of string is length of bytes!
- unicode chars use multiple bytes

```
s := "あ"
fmt.Println(len(s)) // 3 since 3 bytes


```

- a string can be cast as []byte or []rune

- to get physical length of a string, cast to []rune and then get length

- strings are immutable and passed by reference! a slice of a string
  is just a pointer - the only time a string is copied as value is if it's changed
  `  s := "hello"
s_slice := s[3:] // this is just a pointer to the original segment. no copy was made
new_string := s + ", world" // this is a copied value`

## functions ref vs value

- technically speaking, all paramters are passed by value in Go
  - even pointers are copied, but changing the pointer ends up changing the original
- so in practice, the mental model is:

- primitives, `arrays` and `structs` are passed in by value, meaning they are
  copied. The original does not get mutated

  - any of these however can be passed in by reference is using a pointer as an arg`&array`

  ```
         func do(*a [3]int) {
                 *(a)[3] = 5 // since we are dereferencing the pointer and getting
                 the original, the original array also mutates
             }
       arr := [3]int{1,2,3}
       do(&arr) // although arrays are usually passed in by value, this will allow
       to pass by reference
  ```

- all other complex types `slice`, `chan`, `map` etc.. are passed in by ref

## pointer

- the most confusing part is that `*` is a type like `*int` (a pointer address that
  points to an int) AND it's also used as a dereferencer `num = *numPointer`

- when declaring a func, always use `*` as ref to pointers

```
  func doSomething(n *int) {
  // n is a pointer
  }
```

- when passing IN a pointer, always use the `&` operator in the invocation `doSomething(&myNum) // pointer to myNum is passed in as arg`

### multiple returns

- when there are multiple return values, you must add parens. most commonly
  used for errors
  `func doSomething(a string) (string, error)`

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

### inner functions

- inner functions must be either anonymous and immediately invoked with syntax
  `func (<param> <type) {
    // body
}(<args>)`

OR

- assigned with := `innerFunc := func (<parm> <type>) { // body }`

## inline multiple declarations

```

var (
ToBe bool = false
MaxInt uint64 = 1<<64 - 1
z complex128 = cmplx.Sqrt(-5 + 12i)
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
\_ = iota
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

if product := 8 \* 9; product > 60 {
fmt.Println(product, " is greater than 60")
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

- a `defer` statement will defer the execution of a function until the surrounding function returns. It will run right BEFORE the return statement
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

- defer statements are run in `function scope`, not `block scope`! It will run
  when the function exists, not a loop

- putting a defer statement inside a conditional means that it will run
  only if the conditional runs in that block, but again, it will run at the
  end of the function, not the block that it was declared in!

- for example, this is a BAD usage of defer

```

// passes in a bunch of filenames
func main() {
for i:= 1; i < len(os.Args); i++ {
f, err := os.Open(os.Args[i])
// more stuff...

            defer f.Close()
            }
    }

// since f.Close will ONLY run at the end of main, it could potentially
keep thousands of files open. In this case, it is just better to close
each file after you've processed them, so just f.Close() at the end
of the loop

```

- Unlike a closure, `defer` copies arguments to the call at that line

```

a := 10
defer fmt.Println(a) // here it is copying the value at this point, 10
a = 11
fmt.Println("non defer a", a)

// will print 11, but the defer call will print 10

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


// prints DONE 9 8 7 6 ... to 0

"Generated" will print right after the return of either scenario

#### defer and panic

- if a function has a panic call and `defer`, the defer call will always still run, so closing resources will still be fine
- when using anonymous defer function calls, a error handler can recover from a panic state

## composite (or container) types

### arrays

- syntax `var arr [3]int` // empty array defaults to zero value, or `arr := [...]{1,2,3}`
- arrays are copied. `a := someOtherArray` is not a pointer, but a copy of
  the original array
- arrays use consecutive bytes in memory and must be initialized with a length
- can be used as map key
- since arrays have a fixed length, two arrays of the same len and vals
  can be compared array1 == array2
- often used as a pseudo const

### slices

- a reference to an array
- does not require setting a set length
- three basic ways of declaring:
  - syntax `var s []int` // this is equal to `nil`
  - `s := []int{1,2,3}` // this is empty but not equal to `nil`
  - `s:= make([]int, 3)` // this is empty but not equal to `nil`
- you can still append to a `nil` slice, but it's very important for
some methods lke `json.Marshal(s)`. A nil slice will show up as `null`, while
an empty, non-nil slice will be `[]`
- gotcha: if you `s := make([]int, 5)` you are actually making {0,0,0,0,0}.
Appending values to that will start on the 6th index! what you want for
an empty slice is `s := make([]int, 0, 5)`
- to check to see if a slice is empty for all 3 cases, check len(s) == 0
- has methods like `append` and `copy`
- can not be used as map key

  - `a = append(a, 4)` // append 4 to current slice and overwrite

- slices are pointers to an underlying array
- since it's not a copy, two slices pointing to the same array a and b, `a[1] == b[1]` // true
- slices themselves cannot be comparable
- slices are indexed like in python `s[3:5]`

- if `s := someArray[2:4]` and you slice from that slice, `new_s := s[1:5]` you
are actually slicing from the underlying ARRAY, not that slice. better practice
is to limit the capacity when you first slice from an array. `s := someArray[2:4:2]`
// means slice index 2 to 4, and keep the capacity to just those two!
// by doing that, slicing that new slice out of bounds will fail properly

### maps

- key value pair
- a valid key must be a type that is comparable with `==`, `!=`. arrays are good, slices are not

- syntax `var m map[int]string` creates a `nil` map. not useful since you can't insert
  - empty maps are `nil` but you can still read from it m["the"] // returns empty string
  - insertion attempt will cause `panic`
- `m := make(map[int]string)` creates an empty but non-nil map
- `var m = map[int]string{}` will do the same
  - ok to insert or read
- maps are passed by reference, so no copying. A mutation inside a function
  will also change the original
- maps can't be compared to each other, but as an exception, can compare to `nil`

- to access a key in a map, best practice to use:

`m := make(map[int]string)`

#### maps of structs

- since maps use a hash table that keeps changing the pointer of each entry,
  you will always see a map to struct POINTERS instead

- assigning a map value as a pointer is not allowed, as the address will shift
- in the same way, assigning a slice value with a pointer is also risky

`company := map[string]\*Employee // good`

- if you put literal structs in a map, a lot of operations would not work
  - any pointer related operations or even changing the value of a specific
    employee would fail

### struct tags

- metadata about how to encode in certain protocols like json.
- struct tags must be with backtick literals
- used to encode structs for external use

- the structure is `<keyword>:"<format>,<additionalOptions>"`

type Response struct {
	Page  int      `json:"page"`            // this says in json formatting, the property name will be lowercase "page"
	Words []string `json:"words,omitempty"` // in json, property will be lowercase "words" and don't include if empty
}

- making the value lowercase is a common workaround because most structs need
to be exportable, meaning uppercase! json values are conventionally lowercase.
all fields of a struct MUST be uppercase for any kind of encoding!
struct tags will override this formatting in json



#### empty structs
- like empty Interfaces, empty structs can be useful in specific situations

- there is no `set` in go, so the workaround is:
`var isPresent map[string]struct{}`
    - here we have a string set that's just using the key and the value is nothing, or an empty struct.
    - this takes up less space than a `bool` value mapping

- `done := make(chan struct{})`
    - this is a very cheap channel type with no space required
## go modules

- generally, easiest to just add go mod file `go mod init <name>` at the top
level of a repo and only have 1

- if you need a package that's not in the standard library yet, you need
to run `go get <package name>`. This will create a go.sum file. You'll
then need to sync your current go.mod will with `go mod tidy`


## pointers

- some objects can't be copied safely (mutex, wait groups) and must be used with a pointer
    - any structs that has a mutext must be a pointer
- when data size > 64 bytes, consider pointers (large structs)
- some methods need to mutate the receiver, in which case a pointer is necessary
- some functions like `json.Marshal` require a value to be outside the func

      res := Response{} // struct defined elsewhere
      err := json.Unmarshal(j, &res) // since there is no return val for the struct, needs pointer as 2nd arg
- a pointer may be necessary to signal a `null` object

## OOP in go
- composition-based way of working in OO that has `polymorphism`, `encapsulation` and `abstraction`
- Go does not do `inheritance`, when talking about subclassing (a subclass is always a type of the superclass)
- `polymorphism` through interfaces and composition rather than subclasses and inheritance
- a `class` in Go is a struct with methods
- an `interface` specifies abstract behavior by available function(s). Named with `er` at end "Stringer"
meaning the type must have a String() method available
- a `concrete` type is any struct or other custom type that's declared
```

type Writer interface {
Write([]byte) (int, error)
// all Writers must have a Write() method with these input/output types
}

```
many interfaces are already in the standard lib - fmt.Stringer is an interface
- a `method` is set with a specific type of function with a receiver type that
defines the behavior for that type
- when using custom types that are not structs, you use `underlying` or `base` type
to specify the concrete type

- keep interfaces small, and use composition
```

type Reader interface {
Read(p []byte) (int, error)
}
type Writer interface {
Write(p []byte) (int, error)
}

// use a union. Name it so "er" is only at the very end
type ReadWriter interface {
Reader
Writer
}

// to use this way of composition, you need all interfaces declared on same package

```

## method receivers gotchas

- a method may take a `pointer` or `value` receiver, but not both
- as a rule you need a pointer receiver for methods that mutate the type


## Struct composition and promotion

- a struct can have another struct as a field, called `embedded stuct`
- `embedded` structs are PROMOTED to the level of the inner struct

ex.
```

type Dog struct {
Age int
Color string
}

type DogWithFavoriteFood {
Dog
FavoriteFood string
}

dwff := DogWithFavoriteFood{Dog{age 2, "black"}, kale}
// note that in this declaration, you have to declare a Dog{} literal

// to call the embedded struct, use the embedded fields immediately!
dwff.Age // this is the way. Only ONE dot notation necessary
dwff.Dog.Age // NO!

```
- exception to above is if you had a function that took in a Dog type specifically,
you can pass as an arg DogWithFavoriteFood.Dog

- methods also get promoted! In the example above, any method on `Dog` can
also be called with `DogWithFavoriteFood`. This only happens if DogWithFavoriteFood
does NOT have the same method on itself.


- often packages will lowercase struct fields that they want `encapsulated` and hidden,
and simply make the method names Upper case to export it
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

```
