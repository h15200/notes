# C++

- superset of C

## VSC setup

- to change intellisense config, command palette "Edit Configurations" -> C_Cpp.default.cppStandard to whatever version

- to compile using certain versions use flag at end like `-std=c++11`

## google style guide

https://google.github.io/styleguide/cppguide.html#General_Naming_Rules

- use lower_snake_case for variables
- use kCamelCase for `const` (start with lower k then camelCase)
- use MixedStartingWithCapital for function and class names

## upgrades from C

- built-in Boolean and Enumerated types in C++. Those had to be created by user in C
- strings in C were difficult. 2 different ways (as a pointer and as an array of chars). The latter was preferred if there were no space concerns, but still hard to manipulate
- ability to pass in by reference in C++ but not in C. Far easier to reason than using pointers for everything

## directives

- #include and other preprocessor instructions are called `directives`
- all other code that calls for action are called `statements`

## basic syntax

- start with C lib with brackets<>, then C++ lib with brackets <>, then dev lib (file) with quotes ""
- all quotes in directives and strings must be DOUBLE quotes, not single
- all CHARS (data type with only one char) must be SINGLE quotes
- NEVER use `using namespace x` as libraries get updated and you'll need multiple sets of code. There might be an std::something and diffPackge:something.

- all files must have a main func. 'main' needs to be in lowercase, breaking the convention of starting functions with a capitalized letter
- files must be compiled with g++ into executables before being run

## compiler

- a compiler turns `source code` into `object code`. This process varies by language as some languages don't ever get compiled (interpreted languages like JS don't use compilers)
- in the case of C++, source code usually has extension .cpp or .h (header files) and the compiler will turn it into `.obj` (on Windows) or `.o` (on Unix) files. Note that the object code is not portable in different operating systems. An object code compiled from a Windows environment will not be the smae as one in a Unix environment

## linker

- a linker takes the `object code` (compiled from `source code`) and by combining some C++ library code turn it into an executable. Like object code, the OS will dictate the executable file for that specific OS, and they are not portable.

- g++ is a compiler AND a linker, so it takes source code, links it internally, and spits out the executable without the middle `.obj / .o` file creation step.

```
#include <iostream>

int main() {

  std::cout << "Hello World!" << std::endl;
  // std::endl same as \n

  int x;
  std:cin >> x; // stores user input to var x
}

```

## pointers and references

- References `&` are preferred over pointers. Pointers existed in C and are carried over, but references are used more clearly in more modern (Go) languages. When given the choice, always use references instead of pointers.

```
int number = 4;
int& ref_to_num = number;

std:: cout << &number=; // will print the address
// now if number changes or ref_to_num changes, they will both change
```

- pointers are set with the `*` sign

```
int my_num = 3;
int* int_pointer = &my_num; // int* is a pointer to an address of type int
```

```
#include <iostream>
#include <string>

int main() {
  std::string name = "John";
  std::string* ptr = nullptr; // uninitialized pointers must all be set to nullptr

  ptr = &name; // set address

  std::cout << ptr << '\n';
  // hexadecimal address
  std::cout << *ptr << '\n';
  // "John"

  *ptr = "Robin";
  // deferencing pointer address will give the reference, which is the same as changing the `name` var

  std::cout << *ptr << '\n';
  std::cout << name << '\n';

  return 0;
}

```

## functions and references

- if you want a function to change the passed in references, use &

- if you are not changing any values directly but just using it as a component for some logic, use const and `&`

```
#include <iostream>

// means i will never be mutated. using `&` as well saves memory since there is no need to copy the value
int square(int const &i) {

  return i * i;

}

int main() {

  int side = 5;

  std::cout << square(side) << "\n";

}

```

## same else, else if, switch, for loop, keyword "break", "continue" etc.. syntax as js

## do while

```
int price = 300;
do {
  std::cout << "Too expensive!";
} while (price > 500);
```

## for each syntax (list-like structures)

```
int myList[5] = {0, 1, 1, 2, 3};
for (int number : myList) {
  std::cout << number;
}
```

## if the array item type is not identifiable, use keyword auto

```
int myList[5] = {0, 1, 1, 2, 3};
for (auto item : myList) {
  std::cout << item;
}
```

## overload

- functions can be named the same thing if the parameters are named differently
- c++ will pick the correct func based on the args

## constants

- there are 2 types of constants in C++ v.11
  - `const` is used like you would imagine
  - `constexpr` is used at compile time to avoid magic numbers:
  - any variables formed with constant expressions are also constant expressions themselves.
    - `constexpr int ONE = 1; ONE + 2 // ONE + 2 is a constant expression`
    - where as `int val = 10; val + 2 (this is not a constant expression)`

```
constexpr int max = 100;

void use(int n) {
  constexpr int c1 = max + 7;  // fine
  constexpr int c2 = max + 9
  // error: we don't know the value of n at compile time. n is only revealed at run time.
  // for int c2, const should be used instead of constexpr
}
```

## type conversion and beware of math

- 9/4 -> 2, not 2.25. To do that, do 9.0 / 4 to coerce a double float

- to coerce a literal into a type, use syntax `type{thing}`

  - ex. int{'a'} + 1 // turn char 'a' into int and add one

- to coerce a variable, use ()
  - int my_num = 97; char(my_num) // is 'a'

## switch

- only types `int`, `char`, or `enum` types can be used as the comparer
- values inside each `case` must be constant expressions (constexpr) and not variables
- you can chain multiple cases to do common things:
  ```
  switch(char) {
    case 'a': case 'b': case 'b':
      // do stuff
      break;
    case 'd': case 'e': case 'f':
      // do other stuff
      break;
  }
  ```

## vector

- use `#include <vector>`
- declare and init by `vector<int> v = {3, 4, 5, 2};`
- declare size and init DEFAULT vals `vector<std::string> v(4);` a string vector of size 4 that are all ""
- `vector<int> v(4);` // int vector all assigned to 0

### methods

- all vectors have a size method `v.size();`

  - unlike JS, you must add () after size

- `.push_back()` same as push. appends an element to end of vector

## default values

- strings ""
- int 0

## range for loop

- the c++ version of a for-of loop in vectors

```
vector<int> v = {2,3,4,4};
for (int val: v) {
  // val is element for each iteration
}
```

## terminating an input loop

- to stop an int or double loop (a for loop with a std::cin for example), type in "|"
- to stop a string loop, use control + D for Unix and Ctrl + Z for windows

## return type gotchas

- string.size() returns an `unsigned int`, not an int so a comparison with another int will not work properly unless you wrap it with int()
  - when you accidentally compare a signed int with an unsigned int, the compiler will convert the signed int into an unsigned int, which usually makes it much much bigger.

## header files and module organization

- a typical set up will have a header file called `something.h`, a .cpp file with the header definitions, and another cpp file that is using the header
  - in this case the header file is included in both the definition and usage files

## keyword `extern`

- to avoid duplicate variables in header files, use `extern`
- the extern is just a declaration and will need to be initiated or declared again inside the definition file

ex:

```
(in test.h)

extern int my_int;
void SomeFunc();

(in test.cpp)

#include "test.h"
int my_int;

void SomeFunc() {
  return;
}

(in app.cpp)

#include "test.h"

int main() {
  my_int = 3; // this won't work if the re-declaration in test.cpp is missing
}

```
