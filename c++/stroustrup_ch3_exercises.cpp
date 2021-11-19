//! exercise 2

// #include <iostream>
// #include <stdexcept>

// int main() {
//   std::cout << "Enter number in miles and press return.\n";
//   int miles;
//   std::cin >> miles;
//   if (miles < 0) {
//     throw std::invalid_argument("That is an invalid number");
//   }
//   std::cout << "Converting to kilometers: " << miles << " miles = " << miles * 1.609 << " km \n";
//   return 0;
// }

//! exercise 3
// #include<string>

// int main() {
//   std::string break = "wrong";
//   int if = 0;
//   bool else = true;
//   double continue = 3.4;
// }

//! drill 4
// #include<iostream>
// #include<string>
// #include<stdexcept>

// int main() {
//   std::cout << "Please enter your age.\n";
//   int age;
//   std::cin >> age;
//   if (age < 0 || age > 110) {
//     throw std::invalid_argument("You're kidding!");
//   }
//   std::cout << "That's a great age!\n";
//   return 0;
// }

//! exercise 4
// #include<iostream>
// #include<algorithm>

// int main() {
//   std::cout << "Please enter 2 numbers and press return.\n";
//   int val1;
//   int val2;
//   std::cin >> val1 >> val2;
//   std::cout << "Smaller val is " << std::min(val1, val2) << "\n";
//   std::cout << "Larger val is " << std::max(val1, val2) << "\n";
//   std::cout << "Sum of vals is " << val1 + val2 << "\n";
//   std::cout << "Diff of vals is " << val1 - val2 << "\n";
//   std::cout << "Profuct of vals is " << val1 * val2 << "\n";
//   std::cout << "Ratio of vals is " << val1 / val2 << "\n";
//   return 0;
// }

//! exercise 5
// #include<iostream>
// #include<algorithm>

// int main() {
//   std::cout << "Please enter 2 numbers and press return.\n";
//   double val1;
//   double val2;
//   std::cin >> val1 >> val2;
//   std::cout << "Smaller val is " << std::min(val1, val2) << "\n";
//   std::cout << "Larger val is " << std::max(val1, val2) << "\n";
//   std::cout << "Sum of vals is " << val1 + val2 << "\n";
//   std::cout << "Diff of vals is " << val1 - val2 << "\n";
//   std::cout << "Profuct of vals is " << val1 * val2 << "\n";
//   std::cout << "Ratio of vals is " << val1 / val2 << "\n";
//   return 0;
// }

//! exercise 6

// #include<iostream>

// int main() {
//   std::cout << "Please enter 3 numbers and press return.\n";
//   int val1;
//   int val2;
//   int val3;
//   std::cin >> val1 >> val2 >> val3;
//   int smallest;
//   int middle;
//   int largest;

//   if (val1 >= val2 && val1 >= val3) {
//     largest = val1;
//     if (val2 > val3) {
//       middle = val2;
//       smallest = val3;
//     } else {
//       middle = val3;
//       smallest = val2;
//     }
//   } else if (val2 >= val1 && val2 >= val3) {
//     largest = val2;
//       if (val1 > val3) {
//         middle = val1;
//         smallest = val3;
//       } else {
//         middle = val3;
//         smallest = val1;
//       }
//   } else {
//     largest = val3;
//       if (val2 > val1) {
//         middle = val2;
//         smallest = val1;
//       } else {
//         middle = val1;
//         smallest = val2;
//       }
//   }
//   std::cout << smallest << ", " << middle << ", " << largest << "\n";
//   return 0;
// }

//! exercise 7

// #include<iostream>
// #include<string>

// int main() {
//   std::cout << "Please enter 3 words and press return.\n";
//   std::string val1;
//   std::string val2;
//   std::string val3;
//   std::cin >> val1 >> val2 >> val3;
//   std::string smallest;
//   std::string middle;
//   std::string largest;

//   if (val1 >= val2 && val1 >= val3) {
//     largest = val1;
//     if (val2 > val3) {
//       middle = val2;
//       smallest = val3;
//     } else {
//       middle = val3;
//       smallest = val2;
//     }
//   } else if (val2 >= val1 && val2 >= val3) {
//     largest = val2;
//       if (val1 > val3) {
//         middle = val1;
//         smallest = val3;
//       } else {
//         middle = val3;
//         smallest = val1;
//       }
//   } else {
//     largest = val3;
//       if (val2 > val1) {
//         middle = val2;
//         smallest = val1;
//       } else {
//         middle = val1;
//         smallest = val2;
//       }
//   }
//   std::cout << smallest << ", " << middle << ", " << largest << "\n";
//   return 0;
// }

//! exercise 8

// #include<iostream>

// int main () {
//   std::cout << "Please enter an integer.\n";
//   int evenOrOddInt;
//   std::cin >> evenOrOddInt;
//   if (evenOrOddInt % 2 == 0) {
//     std::cout << evenOrOddInt << " is an even number!\n";
//   } else {
//     std::cout << evenOrOddInt << " is an odd number!\n";
//   }

//   return 0;
// }

//! exercise 9

// #include<iostream>
// #include<string>

// int main() {
//   std::cout << "Please enter a number between 0 and 4.\n";
//   int num;
//   std::cin >> num;

//   std::string translatedStr;
//   switch(num) {
//     case 0: 
//       translatedStr = "zero";
//       break;
//     case 1:
//       translatedStr = "one";
//       break;
//     case 2:
//       translatedStr = "two";
//       break;
//     case 3:
//       translatedStr = "three";
//       break;
//     case 4: 
//       translatedStr = "four";
//       break;
//     default: 
//       translatedStr = "That is not a valid number.";
//   }
//   std::cout << translatedStr << "\n";
//   return 0;
// }

//! exercise 10

// #include<iostream>
// #include<string>

// int main() {
//   std::cout << "Enter an operation (+, -, *, or /) and 2 numbers.\n";
//   std::string op;
//   double float1;
//   double float2;
//   std::cin >> op >> float1 >> float2;
  
//   if (op != "+" && op != "-" && op != "*" && op != "/") {
//     std::cout << "Invalid op!\n";
//   } else if (op == "+") {
//     std::cout << float1 + float2 << "\n";
//   } else if (op == "-") {
//     std::cout << float1 - float2 << "\n";
//   } else if (op == "*") {
//     std::cout << float1 * float2 << "\n";
//   } else if (op == "/") {
//     std::cout << float1 / float2 << "\n";
//   }
//   return 0;
// }

//! exercise 11

#include <iostream>
#include <string>

int main() {
  std::cout << "How many pennies do you have?\n";
  int pennyCount;
  std::cin >> pennyCount;
  std::cout << "How many nickels do you have?\n";
  int nickelCount;
  std::cin >> nickelCount;
  std::cout << "How many dimes do you have?\n";
  int dimeCount;
  std::cin >> dimeCount;
  std::cout << "How many quarters do you have?\n";
  int quarterCount;
  std::cin >> quarterCount;
  std::cout << "How many half dollars do you have?\n";
  int halfDollarCount;
  std::cin >> halfDollarCount;

  if (pennyCount != 1) {
    std::cout << "You have " << pennyCount << " pennies.\n";
  } else if (pennyCount == 1) {
    std::cout << "You have 1 penny.\n";
  }
  if (nickelCount != 1) {
    std::cout << "You have " << nickelCount << " nickels.\n";
  } else if (nickelCount == 1) {
    std::cout << "You have 1 nickel.\n";
  }
  if (dimeCount != 1) {
    std::cout << "You have " << dimeCount << " dimes.\n";
  } else if (dimeCount == 1) {
    std::cout << "You have 1 dime.\n";
  }
  if (quarterCount != 1) {
    std::cout << "You have " << quarterCount << " quarters.\n";
  } else if (quarterCount == 1) {
    std::cout << "You have 1 quarter.\n";
  }
  if (halfDollarCount != 1) {
    std::cout << "You have " << halfDollarCount << " half dollars.\n";
  } else if (halfDollarCount == 1) {
    std::cout << "You have 1 half dollar.\n";
  }

  double totalCents = pennyCount + nickelCount * 5 + dimeCount * 10 + quarterCount * 25 + halfDollarCount * 50;

  std::cout << "The value of all of your coins is $" << totalCents / 100 << "!`\n";

  return 0;
}