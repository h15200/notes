// definitions of header files are in .cpp files, not .h

#include <iostream>
#include "chapter8.h"

int foo;

void print_foo() {
  // foo is defined in chapter8_use.cpp
  std::cout << foo << std::endl;
  return;
}

void print(int i) {
  std::cout << i << std::endl;
  return;
}