# C++

- superset of C

## directives

- #include and other preprocessor instructions are called `directives`
- all other code that calls for action are called `statements`

## basic syntax

- start with C lib with brackets<>, then C++ lib with brackets <>, then dev lib (file) with quotes ""
- all quotes in directives and strings must be DOUBLE quotes, not single
- all CHARS (data type with only one char) must be SINGLE quotes
- use namespace std by `using namespace std;` if you don't want to keep typing `std::cout`.
- all files must have a main func
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
