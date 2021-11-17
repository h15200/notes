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