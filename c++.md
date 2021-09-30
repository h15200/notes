# C++

- superset of C

## basic syntax

- start with C lib with brackets<>, then C++ lib with brackets <>, then dev lib (file) with quotes ""
- use namespace std by `using namespace std;` if you don't want to keep typing `std::cout`.
- all files must have a main func
- files must be compiled with g++ into executables before being run

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
