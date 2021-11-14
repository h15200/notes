//! example of using namespace, declaring variables and assigning

// #include <iostream>

// using namespace std;
// int main() {
//   cout << "Hello! Please enter your first name and press return.\n";
//   string firstName;
//   cin >> firstName;
//   cout << "Hi " << firstName << "!\n";
//   return 1;
// }

//! example of reading multiple inputs 
// #include <iostream>

// using namespace std;
// int main() {
//   cout << "Hello! Please enter your first name, space, and age and press return.\n";
//   string firstName;
//   int age;
  // will read first string as firstName, second string (whatever after 1 whitespace) as age
//   cin >> firstName;
//   cin >> age;
//   cout << "Hi " << firstName << "!\n" << "You are " << age << " years old!\n";
//   return 1;
// }

//! same as above, but cin can be chained like cout
// #include <iostream>

// using namespace std;
// int main() {
//   cout << "Hello! Please enter your first name, space, and age and press return.\n";
//   string firstName;
//   int age;
// will read first string as firstName, second string (whatever after 1 whitespace) as age
//   cin >> firstName >> age;
//   cout << "Hi " << firstName << "(" << age << " years old)!\n";
//   return 1;
// }

//! same as above, but allow for decimal years
// #include <iostream>

// using namespace std;
// int main() {
//   cout << "Hello! Please enter your first name, space, and age and press return.\n";
//   string firstName;
//   double age;
//   cin >> firstName >> age;
//   cout << "Hi " << firstName << "(" << age << " years old)!\n";
//   return 1;
// }

//! using sqrt with <math.h>. Note how you don't need std:: before sqrt even though you are not declaring namespace
// #include <iostream>
// #include <math.h>

// using namespace std;
// int main() {
//   cout << "Hello! Please enter a float.\n";
//   double number;
//   cin >> number;
//   cout << "The square root of that number is, " << sqrt(number) << "\n";
//   return 1;
// }

//! c-in can be used with a while loop to read a stream of strings
// #include <iostream>

// using namespace std;
// int main() {
//   cout << "Hello! Please enter a bunch of words!\n";
//   string current;
//   while (cin >> current) {
//     cout << current << "\n";
//   }
//   // this routine will never stop
//   return 1;
// }

//! repeated word detection program
// #include <iostream>

// using namespace std;
// int main() {
//   cout << "Hello! Please enter a bunch of words!\n";
//   string previous;
//   string current;
//   while (cin >> current) {
//     if (previous == current) {
//       cout << "You typed the same word, \"" << previous << "\", twice!";
//     }
//     previous = current;
//   }
//   // this routine will never stop
//   return 1;
// }

//! check out compiler errors by running this
// int Main() {
//   STRING s = "Goodbye, cruel world!";
//   cOut << S << '\n';
// }