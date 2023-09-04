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
  - uint may be used in low level protocol tcp/ip stuff, but it's somewhat rare
- don't type a bigger into to a smaller one. Always bring the smaller one up to avoid weird bit wise behavior
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

- go doesn't have `enums` but `iota` is used for the same mechanism
- use a `const` block and set the first item as iota, which starts at `0` by default

```

const (
_ = iota
blueCar // this is 1
greeCar // this is 2
redCar // 3
)
// iota starts at 0, then increments automatically

```

- often used with bitwise operators

```
Flagup Flags = 1 << iota // iota is 1
FlagBroadcast   // 2
FlagLoopback         // 4
FlagPointToPoint       // 8
FlagMulticast     // 16

// makes it easy to combine Flagup | FlagLoopback with bits

```

- possible to ignore values with underscore

```
const (
_            = iota // ignore 0
KiB ByteSize = 1 << (10 * iota) // sets the pattern starting here at iota = 1
GiB
TiB
PiB
EiB
)
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

### multiple unknown arguments

- the `...` operator AFTER the arg but BEFORE the type, it's an unknown amount
- only the LAST parameter in the list can be variable

```

func do(name string, nums ...int) int {

   // nums is a slice of ints

}
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
```

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

#### Unpacking a slice

- use `...` AFTER the slice to unpack
- `s:= []int{1,2,3,4}   someFunc(s...)`

```
s := []string{"a", "b", "c"}
s = append(s, s) // does not work because you can't add a slice as a string (in this case)
s = append(s, s...) // now s is {"a", "b", "c", "a", "b", "c"}

// used often in splicing a slice

s := []int{1,2,2,3,4,5}
s = append(s[:2], s[3:]...) // the first param is an actual slice, but the second param are multiple ints -> {1,2,3,4,5}

```

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
Page int `json:"page"` // this says in json formatting, the property name will be lowercase "page"
Words []string `json:"words,omitempty"` // in json, property will be lowercase "words" and don't include if empty
}

- making the value lowercase is a common workaround because most structs need
  to be exportable, meaning uppercase! json values are conventionally lowercase.
  all fields of a struct MUST be uppercase for any kind of encoding!
  struct tags will override this formatting in json

#### empty structs

- like empty Interfaces, empty structs can be useful in specific situations

- there is no `set` in go, so the workaround is:
  `var isPresent map[string]struct{}` - here we have a string set that's just using the key and the value is nothing, or an empty struct. - this takes up less space than a `bool` value mapping

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

## interfaces

- an interface is a type in Go, but an abstract type. All other types (structs, custom types)
  are concrete types
- an interface can be the input of a function or a method
- if not initialized, the default value of an interface is `nil`
  - digging in, an interface has 2 parts:
  1. a value or pointer of some Type
  2. a pointer to the the specific type information to check for methods
  - an interface is `nil` if BOTH of these parts are `nil`
- best practices
  1. Let consumers define interfaces
  2. Re-use standard interfaces when possible
  3. Keep interface declarations small
  4. Compose one-method interfaces into larger ones if needed
  5. Avoid coupling interfaces to particular types. make sure it's generic to as many types as possible
  6. Accept interfaces in functions, but return concrete types (exception being error interface should be returned)
- put the least restriction on what params you accept (the minimal interface)
- same for the output. Make it as flexible as possible

## method receivers gotchas

- a method may take a `pointer` or `value` receiver, but not both
- as a rule you need a pointer receiver for methods that mutate the type

### method receiver type compatibility

- Go will try to infer the passed in type (value or pointer) regardless of
  what the method is specifying as a type. It will automatically deference or
  add the address-of operator.

- The ONLY exception, a concrete value which is an R-value (the right hand
  side of a declaration) can NOT be used to call a method with a pointer receiver.
  All other combos will work [value receiver, value method call], [value receiver,
  pointer method call], [pointer receiver, pointer method call]

- As best practice, if one method of a type needs to take a pointer receiver,
  then ALL of its methods should take pointers!!! (though there are exceptions)

### method values

- a method can be stored to be used later. this will capture the receiver in a closure

```
func (p Person) Do(word string) string {
        return something using p.Name and input word
    }

func main {
        p := Person{Name: "Kai"}
        DoLater = p.Do

        // if you use it later, you have access to person p from within that DoLater
    }
```

- when using this technique, it's important to note if the method takes in a value
  or a pointer.
- if it takes a value, the closure will be based on the author time of the DoLater call
- if it's a pointer, any re-assignment of p Person, even after the author time of the DoLater
  call will CHANGE the closure to the newer assignment

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

### fmt.Printf verb types

%v - the actual value of variable turned into a string
%T - TYPE of value ex. num, string, float
%d - type coercion of int -> string `fmt.Printf("You're %d years old", age)`
%f - float -> string. option to set decimal place `fmt.Printf("Your test average is %.2f", gpa)` - 3.80
%q - puts double quotes around string

## concurrency

- parts of the program may execute independently in some non-deterministic (possibly partial) order
- you can still have concurrency with a single-core processor. you're just going
  back and forth between programs during idle time. ex do stuff while you wait
  for a server response
- `parallelism` can only happen on a multi-core processor. Parallelism makes
  programs faster, but concurrency does NOT!

- because concurrency has built in non-deterministic ordering, there will
  always be race conditions when dealing with shared data. possible solutions include:

  - not sharing anything (safe, but inconvenient)
  - make the shared thing read-only (slightly more convenient)
  - allow only one writer to the shared thing at a time (mutex)
  - make certain operations sequential (transactions. makes program safe but slower)

- in `go`, we use multiple cores for parallelism AND concurrency
- solving concurrency (race condition) issues is done with `channels` and `go routines`

- in `go`, goroutines, channels, and wait groups abstract a lot of concurent
  and parallel programming, but traditional synchronization tools like `mutex` are
  availble in package `sync` and `sync atomic`
  - a `mutex` is better than using a semaphore counter of cap 1 with a channel
  - use a `R(ead)W(rite)Mutex` to optimize for reading

### Channels

- 2 main usages:

  - communications tool
  - synchronization tool

- a go data type
- a channel is a one-way communications pipe like the unix `|`
- things go in one end and come out the other in the SAME order
- channels can be closed, in which things stop coming out
- send (write) always happens before a receive (read)
- a way to transfer ownership of data. If only one routine at a time is writing
  a specific data, there will be no race conditions
- multiple readers & writers can share it safely

- channels offer a way to schedule things by communicating sequential processes
- if there are multiple cores, this can be done in parallel

- when passing a `chan` to a function input, you can specify if it's a
  `sender` (write operation) or a `receiver` (read operation).

  - (ch chan<- int) is a write-end channel
  - (ch <-chan) is a read-end channel

- A channel is ready to write if:

  - it has buffer space or
  - at least one reader is ready to read

- A channel is ready to read if:

  - it has unread data in its buffer, or
  - at least one writer is ready to write, or
  - it is closed (yes, you can ready from a closed channel!)
    - in this case, if it was a buffered channel, the receiver will continue
      reading values from a closed channel until you reach the end, where you'll
      get the zero value and !ok

- when closing a channel, there is still a zero value of that channel type inside,
  so receiving from a closed `chan int` will yield `0`. the second `ok` val will be false in this case

- a nil channel can be reverted back unlike a closed channel. Can be used to block
  a channel until a later time

### wait groups

- a wait group is used to wait until all go routines finish
- the flow is Add to wait group, do a go routine, then call Done, then the
  execution will pick up from after Wait()
- always call wg.Add(1) BEFORE a goroutine starts or a wg.Wait() is called!

### concurrency gotchas

1. race conditions where unprotected read & writes overlap

   - can be detected with the `-race` arg after `go run`
   - there is some data that is written to and two goroutines can do it at the same time
   - can be fixed with a mutex or a channel
   - often happens with web server logic since go http library uses concurrency
     and paralellism (with multi core machines0)

   ```
   // example of race condition

   var someInt = 0
   func handler(w http.ResponseWriter, req *http.Request) {
       // for every request, increment
       someInt++  // this is UNSAFE because a server may take requests at
       // the same time in parallel. int will probably be LOWER than
       // total number of requests

       }
   ```

2. deadlocks when no goroutine can make progress

   - goroutines are blocked on empty channels
   - goroutines are blocked waiting on a mutext that never unlocks
   - goroutines are prevented from running
   - some deadlocks will be detected automatically, but not all
   - often happens in unbuffered channels with no actions or forgetting
     to unlock a mutex

   ```
   // deadlock ex 1

   func main() {
           ch := make(chan bool)

           go func(ok bool) {
               // this never runs, so nothing is sent to ch
               if ok {
                       ch <- ok
                   }


               }(false)
       }

    // this will never run since there is no data on the channel
       <-ch   // since there is no sending, there is no receiving
   ```

```
// deadlock ex 2

func main() {
var m sync.Mutex

      done := make(chan bool)

      go func() {
                m.Lock()
                // forgets to unlock here
          }()

      go func() {
          time.Sleep(1)

          m.Lock()
          defer m.Unlock()

          done <- true
          }()

        <-done // this will never run since the first func does not unlock

```

3. goroutine leaks

- hangs on an empty or locked channel
- not a deadlock; other routines make progress
- often found by looking at pprof output
- typically a leaking socket will cause this

```
// ex of goroutine leak
func finishReq(timeout time.Duration) *obj {
        ch := make(chan obj)

        go func() {
            ... // some kind of work that takes a long time
                ch <- fn()
            }()

        select {
                case res := <-ch:
                  return res
                case <-time.After(timeout):
                  return nil
            }
            // since the channel is never written to, this is a bug
            // the solution is to add a buffer to the channel. It will still
            // not reach case res := <-ch, but the go func will still run since
            it's able to write to the buffer, even if that info is never used
    }
```

4. channel errors

- trying to send on a closed channel
- trying to send or receive on a nil channel
- closing a nil channel
- attempting to close a channel twice

5. other errors

- goroutine closure capture over a reference that mutates

```
// BAD example
for i := 0; i < 10; i++ {
        go func() {
            fmt.Println(i) // i uses the same pointer on every loop, so this is a mutating value
            // the goroutine is closing over i, which keeps changing. not good
            // in this example, all goroutines will print the LAST idx of the loop


            }()
    }

// GOOD example
for j := 0; < 10 ; j++ {
        go func(j int) {
            // stuff with j is ok here since it's the value at that moment

            }(j)
    }

// also you can do localI = i // closure capture

```

- misuse of Mutext

  - deadlock ex. 3 the DINING PHILOSPHERS problem. There are 2 philosphers, one knife, and one fork if one grabs a fork and looks for a knife, but the other grabbed a knife and is looking for a fork, neither eats

  ```// highlights drawbacks of mutex. Ordering matters func main() { var m1, m2 sync>Mutex done := make(chan bool) go func() { m1.Lock() defer m1.Unlock() time.Sleep(1)
    m2.Lock()
    defer m2.Unlock()

  done <- true
  }()

  go func() {
  m2.Lock()
  defer m2.Unlock()
  time.Sleep(1)
  m1.Lock()
  defer m1.Unlock()

            done <- true

  }()

  <-done
  <-done

  }

  // SOLUTION - when using multiple mutex, always use them in the SAME ORDER!

  ```

- misuse of WaitGroup
  - always call wg.Add() BEFORE starting any go routines or calling wg.Wait()
- misuse of select: possibly the most difficult one to debug
  1. `default` is ALWAYS active
  2. a `nil` channel is always ignored
  3. a full channel for send is always skipped over, and an empty channel for read is skipped over
  4. a "done" (closed) channel is just another channel
  5. available channels are selected at RANDOM, and the ordering of the code doesn't matter!

## error handling

- an error in Go is an `interface`
- good practice to wrap errors to show the stack. `fmt.Errorf with %w` will do the trick

- failing vs exception handling (aka graceful degradation)
  - exception handling introduces invisible control paths and is harder to analyze
- in Go, exception handling is not supported OFFICIALLY
- Practically, it does in the form of `panic & recover`
  - `panic` in a function will still cause deferred function calls to run after
  - if you have `recover` logic in a defer statement, you can unwind and keep the program going
- generally, `panic` and `recover` are NOT recommended in Go.

- when your program has a logic bug, "fail hard, fail fast!". exit the program, don't abuse `recover`
  - logs are often noisy
  - better to immediately crash a server than to log
  - we want the reason of failure as close as possible in time and space to the code
  - in a distributed system, crash failures are the safest type to handle
    - better to fail than to be a zombie and corrupt the DB or crasy other systems

## reflection (as in self-reflection)

- `interface{}` has no methods, so it doesn't restrict any behavior. `any` type
- an empty interface is a generic type, but sometimes we need a "real" type
- solution is to use `type assertion` or `downcast` with the syntax `value.(T)`

```
// when given a deep struct that was Unmarshalled from an unknown json

switch r.Item {
    case "itemTypeOne" :
      inner, ok := raw["itemTypeOne"].(string); ok {
              // if the value is string, do something
          }

    case "itemTypeTwo" :
       // etc.


    }

```

- the `reflect` package can be used to compare things you can't compare like slices

### switching on type

- a switch statement can be used to look at types. It can be a concrete type OR an interface!

```
switch a := unknownThing.(type) { // note that "type" is a keyword here
        case string: // the cases do not need quotes, just type names
           // stuff using a
        case Stringer:
          // stuff using a.String()
    }
```

### mechanical sympathy in go

- a slice or struct with values is more performant than a linked list or other
  data types that use pointers because they use continguous, sequential blocks of memory
- in the same way, chaining functions/methods is chaining pointers. Don't make
  unnecessary methods that call other methods.
