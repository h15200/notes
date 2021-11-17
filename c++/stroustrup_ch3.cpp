//! example of using namespace, declaring variables and assigning

// #include <iostream>
// #include <string>

// int main() {
//   std::cout << "Hello! Please enter your first name and press return.\n";
//   std::string firstName;
//   std::cin >> firstName;
//   std::cout << "Hi " << firstName << "!\n";
//   return 1;
// }

//! example of reading multiple inputs 
// #include <iostream>
// #include <string>

// int main() {
//   std::cout << "Hello! Please enter your first name, space, and age and press return.\n";
//   std::string firstName;
//   int age;
  // will read first string as firstName, second string (whatever after 1 whitespace) as age
//   std::cin >> firstName;
//   std::cin >> age;
//   std::cout << "Hi " << firstName << "!\n" << "You are " << age << " years old!\n";
//   return 1;
// }

//! same as above, but cin can be chained like cout
// #include <iostream>

// int main() {
//   std::cout << "Hello! Please enter your first name, space, and age and press return.\n";
//   std::string firstName;
//   int age;
// will read first string as firstName, second string (whatever after 1 whitespace) as age
//   std::cin >> firstName >> age;
//   std::cout << "Hi " << firstName << "(" << age << " years old)!\n";
//   return 1;
// }

//! same as above, but allow for decimal years
// #include <iostream>

// int main() {
//   std::cout << "Hello! Please enter your first name, space, and age and press return.\n";
//   std::string firstName;
//   double age;
//   std::cin >> firstName >> age;
//   std::cout << "Hi " << firstName << "(" << age << " years old)!\n";
//   return 1;
// }

//! using sqrt with <math.h>. Note how you don't need std:: before sqrt even though you are not declaring namespace
// #include <iostream>
// #include <math.h>


// int main() {
//   std::cout << "Hello! Please enter a float.\n";
//   double number;
//   std::cin >> number;
//   std::cout << "The square root of that number is, " << sqrt(number) << "\n";
//   return 1;
// }

//! c-in can be used with a while loop to read a stream of strings
// #include <iostream>
// #include <string>

// int main() {
//   std::cout << "Hello! Please enter a bunch of words!\n";
//   std::string current;
//   while (std::cin >> current) {
//     std::cout << current << "\n";
//   }
//   // this routine will never stop
//   return 1;
// }

//! repeated word detection program
// #include <iostream>
// #include <string>

// int main() {
//   std::cout << "Hello! Please enter a bunch of words!\n";
//   std::string previous;
//   std::string current;
//   while (std::cin >> current) {
//     if (previous == current) {
//       std::cout << "You typed the same word, \"" << previous << "\", twice!";
//     }
//     previous = current;
//   }
//   // this routine will never stop
//   return 1;
// }

//! check out compiler errors by running this
// #include <string>
// int Main() {
//   STRING s = "Goodbye, cruel world!";
//   cOut << S << '\n';
// }

// //! drill
// #include <iostream>
// #include <stdexcept>

// int main() {
//   std::cout << "Enter the person you want to write to and press return.\n";
//   std::string firstName;
//   std::cin >> firstName;
//   std::cout << "\n \n Dear " << firstName << ", \n";
//   std::cout << "   " << "How's it going? I hope you're doing well.\n I miss you. I'm writing this from the living room, right outside your office.\n\n";
//   std::string yourFriend;
//   std::cout << "Please enter friend's name and press enter. \n";
//   std::cin >> yourFriend;
//   char yOrN;
//   std::cout << "Please enter y and press enter if your friend is a cat.\n";
//   std::cin >> yOrN;
//   if (yOrN == 'y') {
//     std::cout << "Please tell " << yourFriend << " to meow.\n";
//   }
//   int age;  
//   std::cout << "What is your age?\n";
//   std::cin >> age;
//   if (age < 0 || age > 110) {
    
//     throw std::invalid_argument("You're kidding!");
//   };
//   std::cout << age << " is a great age!\n" << "I have to make breakfast for us, bye!\n\n";
//   std::cout << "Yours sincerely,\n" << "Hideaki\n"; 
// }
