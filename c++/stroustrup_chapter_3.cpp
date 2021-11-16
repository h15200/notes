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

//! drill
#include <iostream>
#include <stdexcept>

using namespace std;
int main() {
  cout << "Enter the person you want to write to and press return.\n";
  string firstName;
  cin >> firstName;
  cout << "\n \n Dear " << firstName << ", \n";
  cout << "   " << "How's it going? I hope you're doing well.\n I miss you. I'm writing this from the living room, right outside your office.\n\n";
  string yourFriend;
  cout << "Please enter friend's name and press enter. \n";
  cin >> yourFriend;
  char yOrN;
  cout << "Please enter y and press enter if your friend is a cat.\n";
  cin >> yOrN;
  if (yOrN == 'y') {
    cout << "Please tell " << yourFriend << " to meow.\n";
  }
  int age;
  cout << "What is your age?\n";
  cin >> age;
  if (age < 0 || age > 110) {
    throw invalid_argument("You're kidding!");
  };
  cout << age << " is a great age!\n" << "I have to make breakfast for us, bye!\n\n";
  cout << "Yours sincerely,\n" << "Hideaki\n"; 
}
