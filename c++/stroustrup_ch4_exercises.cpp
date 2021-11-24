//! ex2 - median
// #include <iostream>
// #include <vector>


// int main() {
//   std::vector<double>double_vector{};
//   std::cout << "Please enter a few doubles and terminate with \"|\"\n";
//   for (double vector_item; std::cin >> vector_item;) {
//     double_vector.push_back(vector_item);
//   }
//   int medianIdx = int(double_vector.size() / 2);
//   std::cout << "Median value is " << double_vector[medianIdx] << "\n";


//   return 0;
// }

//! ex3

// #include <iostream>
// #include <vector>
// #include <limits>
// int main() {
//   std::vector<double>distances{};
//   std::cout << "Enter a bunch of flaots and terminate with \"|\" \n";
//   for (double distance; std::cin >> distance;) {
//     distances.push_back(distance);
//   }
//   double total_distance = 0.0;
//   double largest_distance = std::numeric_limits<double>::lower();
//   double smallest_distance = std::numeric_limits<double>::max();
//   for (double d : distances) {
//     if (d > largest_distance) largest_distance = d;
//     if (d < smallest_distance) smallest_distance = d;
//     total_distance += d;
//   }
//   std::cout << "Total is " << total_distance << "\n";
//   std::cout << "Largest val is " << largest_distance << "\n"; 
//   std::cout << "Smallest val is " << smallest_distance << "\n"; 
//   std:: cout << "Average val is " << total_distance / distances.size() << "\n";


//   return 0;
// }

//! ex4 number guessing game

// #include <iostream>

// int main() {
//   // do binary search with io
//   std::cout << "Think of a number beween 1 and 100\n";
//   int left = 1;
//   int right = 100;
//   while (left < right) {
//     int mid = (left + right) / 2;
//     if (mid == left || mid == right) {
//       break;
//     }
//     if (left == right) {
//       std::cout << "The number must be " << left << "!\n";
//       return 0;
//     }
//     std::cout << "Is your number greater or equal to " << mid << " ? (Enter 'y' or 'n')\n";
//     char reply;
//     std::cin >> reply;
//     switch (reply) {
//       case 'y':
//         left = mid;
//         break;
//       case 'n':
//         right = mid - 1;
//         break;
//       default :
//         std::cout << "That's not a valid answer\n";
//         return 1;
//     }
//   }
//   // one of the two
//   std::cout << "Is your number " << left << "?\n";
//   char outer_reply;
//   std::cin >> outer_reply;
//   switch (outer_reply) {
//     case 'y':
//       std::cout << "Yay!\n";
//       return 0;
//     case 'n':
//       std::cout << "It must be " << right << "!\n";
//       return 0;
//   }
// }

//! ex 5 which be becamse 7

// #include <iostream>
// #include<string>

// int main() {
//   std::cout << "Type in 2 numbers and an operation (+, -, x or /)\n";
//   std::string digit_1;
//   std::string digit_2;
//   char operation;
//   std::cin >> digit_1 >> digit_2 >> operation;
//   std::string operation_string;
//   int num_1;
//   int num_2;
//   if (digit_1 == "0" || digit_1 == "zero") {
//     num_1 = 0;
//   } 
//   if (digit_2 == "0" || digit_2 == "zero") {
//     num_2 = 0;
//   }
//   if (digit_1 == "1" || digit_1 == "one") {
//     num_1 = 1;
//   } 
//   if (digit_2 == "1" || digit_2 == "one") {
//     num_2 = 1;
//   }if (digit_1 == "2" || digit_1 == "two") {
//     num_1 = 2;
//   } 
//   if (digit_2 == "2" || digit_2 == "two") {
//     num_2 = 2;
//   }if (digit_1 == "3" || digit_1 == "three") {
//     num_1 = 3;
//   } 
//   if (digit_2 == "3" || digit_2 == "three") {
//     num_2 = 3;
//   }if (digit_1 == "4" || digit_1 == "four") {
//     num_1 = 4;
//   } 
//   if (digit_2 == "4" || digit_2 == "four") {
//     num_2 = 4;
//   }if (digit_1 == "5" || digit_1 == "five") {
//     num_1 = 5;
//   } 
//   if (digit_2 == "5" || digit_2 == "five") {
//     num_2 = 5;
//   }if (digit_1 == "6" || digit_1 == "six") {
//     num_1 = 6;
//   } 
//   if (digit_2 == "6" || digit_2 == "six") {
//     num_2 = 6;
//   }if (digit_1 == "7" || digit_1 == "seven") {
//     num_1 = 7;
//   } 
//   if (digit_2 == "7" || digit_2 == "seven") {
//     num_2 = 7;
//   }if (digit_1 == "8" || digit_1 == "eight") {
//     num_1 = 8;
//   } 
//   if (digit_2 == "8" || digit_2 == "eight") {
//     num_2 = 8;
//   }if (digit_1 == "9" || digit_1 == "nine") {
//     num_1 = 9;
//   } 
//   if (digit_2 == "9" || digit_2 == "nine") {
//     num_2 = 9;
//   }


//   double solution;
//   switch (operation) {
//     case '+':
//       operation_string = "sum";
//       solution = num_1 + num_2;
//       break;
//     case '-':
//       operation_string = "difference";
//       solution = num_1 - num_2;
//       break;
//     case 'x':
//       operation_string = "product";
//       solution = num_1 * num_2;
//       break;
//     case '/':
//       operation_string = "quotient";
//       solution = num_1 / num_2;
//       break;
//     default:
//       std::cout << "Invalid Operation\n";
//       return 1;
//   }
//   std::cout << "The " << operation_string << " of " << num_1 << " and " << num_2 << " is " << solution << "!\n";
//   return 0;
// }

//! ex 6

// #include <iostream>
// #include <string>
// #include <vector>

// int main () {
//   std::vector<std::string>str_v{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
//   std::cout << "Enter a number between 0 and 9\n";
//   std::string user_string;
//   std::cin >> user_string;
//   if (user_string == "zero" || user_string == "0") {
//     std::cout << str_v[0] << "\n";
//   } else if (user_string == "one" || user_string == "1") {
//     std::cout << str_v[1] << "\n";
//   } else if (user_string == "two" || user_string == "2") {
//     std::cout << str_v[2] << "\n";
//   } else if (user_string == "three" || user_string == "3") {
//     std::cout << str_v[3] << "\n";
//   } else if (user_string == "four" || user_string == "4") {
//     std::cout << str_v[4] << "\n";
//   } else if (user_string == "five" || user_string == "5") {
//     std::cout << str_v[5] << "\n";
//   } else if (user_string == "six" || user_string == "6") {
//     std::cout << str_v[6] << "\n";
//   } else if (user_string == "seven" || user_string == "7") {
//     std::cout << str_v[7] << "\n";
//   } else if (user_string == "eight" || user_string == "8") {
//     std::cout << str_v[8] << "\n";
//   } else if (user_string == "nine" || user_string == "9") {
//     std::cout << str_v[9] << "\n";
//   } else {
//     std::cout << "Invalid\n";
//     return 1;
//   }
//   return 0;
// }

//! ex 8

// #include <iostream>

// int CalculateNumberOfDoubles(int total) {
//   int i = 1;
//   int curr = 1;
//   while (true) {
//     std::cout << "Current total is " << curr << " current iteration is " << i << "\n"; 
//     if (curr >= total) {
//       return i;
//     }
//     curr *= 2;
//     ++i;
//   }
// }

// int main() {
//   std::cout << CalculateNumberOfDoubles(1000) << "\n";
//   std::cout << CalculateNumberOfDoubles(1000000) << "\n";
//   std::cout << CalculateNumberOfDoubles(1000000000) << "\n";
//   return 0;
// }

//! ex 9

// #include <iostream>

// int CalculateDoubles(int iterations) {
//   int i = 1;
//   // int curr = 1;
//   double curr = 1.0;
//   while (i <= iterations) {
//     std::cout << "Current total is " << curr << " current iteration is " << i << "\n"; 
//     curr *= 2;
//     ++i;
//   }
//   return curr;
// }

// int main() {
//   std::cout << CalculateDoubles(64) << "\n";
//   return 0;
// }

//! ex 10

// #include <iostream>
// #include <vector>

// int main() {
//   std::cout << "Rock, Paper, Scissors!\n";
//   std::cout << "Enter a number between 1 and 100\n";
//   int computer_int;
//   std::cin >> computer_int;
//   int computer_hand = computer_int % 3;

//   std::cout << "Enter 0 for Rock, 1 for Paper, and 2 for Scissors\n";
//   int user_hand;
//   std::cin >> user_hand;
//   std::vector<std::string>hand_v{"Rock", "Paper", "Scissors"};
  
//   if (user_hand == computer_hand) {
//     std::cout << "The computer chose " << hand_v[computer_hand] << " too! You Tied!\n";
//   }
//   else if (user_hand == 0) {
//     if (computer_hand == 1) {
//       std::cout << "The computer chose " << hand_v[computer_hand] << "! You Lost!\n";
//     } else {
//       std::cout << "The computer chose " << hand_v[computer_hand] << "! You Won!\n";
//     }
//   } else if (user_hand == 1) {
//     if (computer_hand == 2) {
//       std::cout << "The computer chose " << hand_v[computer_hand] << "! You Lost!\n";
//     } else {
//       std::cout << "The computer chose " << hand_v[computer_hand] << "! You Won!\n";
//     }
//   } else if (user_hand == 2){
//     if (computer_hand == 0) {
//       std::cout << "The computer chose " << hand_v[computer_hand] << "! You Lost!\n";
//     } else {
//       std::cout << "The computer chose " << hand_v[computer_hand] << "! You Won!\n";
//     }
//   } else {
//     std::cout << "Invalid user number \n";
//   }
//   return 0;
// }

//! ex 11, then 12

// all primes between 1 and 100
// first prime is 2

// #include <vector>
// #include <iostream>

// std::vector<int> FindPrimesTo(int num) {
//   std::vector<int>primes_v{};
//   if (num < 2) return primes_v;
//   primes_v.push_back(2);
//   int i = 3;
//   while (i <= num) {
//     bool isPrime = true;
//     for (int prime: primes_v) {
//       if (i % prime == 0) {
//         isPrime = false;
//         break;
//       }
//     }
//     if (isPrime == true) {
//       primes_v.push_back(i);
//     }
//     i += 2; 
//   }
  
//   return primes_v;
// }

// int main() {
//   std::vector<int>primes_v = FindPrimesTo(100);
//   std::cout << "Printing all primes: ]n";
//   for (int prime : primes_v) {
//     std::cout << prime << "\n";
//   }
//   return 0;
// }

//! ex 13, then 14 Sieve of Eratosthenes

// #include <vector>
// #include <algorithm>
// #include <iostream>

// std::vector<bool> GetPrimes(int num) {
//   std::vector<bool>prime_v{};
//   for (int i = 0; i <= num; i++) {
//     prime_v.push_back(true);
//   }
//   prime_v[0] = false;
//   prime_v[1] = false;
//   // all nums are in array
//   for (int i = 2; i * i < num; i++) {
//     if (prime_v[i] == true) {
//       for (int j = 2; j * i <= num; j++) {
//         prime_v[i * j] = false;
//       }
//     }
//   }
//   return prime_v;
// }

// int main() {
//   std::cout << "Primes to 100 \n";
//   std::vector<bool>primes_v = GetPrimes(100);
//   for (int i = 0; i < primes_v.size(); i++) {
//     if (primes_v[i] == true) {
//       std::cout << i << " \n";
//     }
//   }
// }

//! ex 15 find n num primes

// all primes between 1 and 100
// first prime is 2

// #include <vector>
// #include <iostream>

// std::vector<int> FindNPrimesTo(int n) {
//   std::vector<int>primes_v{};
//   if (n < 1) return primes_v;
//   primes_v.push_back(2);
//   int i = 3;
//   while (primes_v.size() < n) {
//     bool isPrime = true;
//     for (int prime: primes_v) {
//       if (i % prime == 0) {
//         isPrime = false;
//         break;
//       }
//     }
//     if (isPrime == true) {
//       primes_v.push_back(i);
//     }
//     i += 2; 
//   }
  
//   return primes_v;
// }

// int main() {
//   int n = 1;
//   std::vector<int>primes_v = FindNPrimesTo(10);
//   std::cout << "Printing primes: \n";
//   for (int prime : primes_v) {
//     std::cout << prime << "\n";
//   }
//   return 0;
// }

//! ex 16

// #include <iostream>
// #include <unordered_map>

// int main() {
//   std::unordered_map<int, int> hash = {};
//   std::cout << "Enter a bunch of numbers and terminate with \"|\"\n";
//   for (int input_int; std::cin >> input_int;) {
//     if (hash.find(input_int) != hash.end()) {
//       ++hash[input_int];
//     } else {
//       hash[input_int] = 1;
//     }
//   }

//   int running_max_frequency = 0;
//   int running_num = 0;
//   // this is the while version, which works too

//   // std::unordered_map<int, int>::iterator it = hash.begin();
//   // while (it != hash.end()) {
//   //   if (it->second > running_max_frequency) {
//   //     running_max_frequency = it->second;
//   //     running_num = it->first;
//   //   }
//   //   it++;
//   // }

//   // this for loop version might be easier to read as the declaration is clear
//   for (auto it = hash.begin(); it != hash.end(); it++) {
//     if (it->second > running_max_frequency) {
//       running_max_frequency = it->second;
//       running_num = it->first;
//     }
//   }
//   std::cout << running_num << " appeared " << running_max_frequency << " times, the most!\n";
//   return 0;
// }

//! ex 17

#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>

int main() {
  std::cout << "Enter a bunch of strings and terminate by pressing control + \"d\" twice.\n";
  std::unordered_map<std::string, int> hash {};
  for (std::string input_string; std::cin >> input_string;) {
    if (hash.find(input_string) != hash.end()) {
      // found
      hash[input_string]++;
    } else {
      hash[input_string] = 1;
    }
  }  

  std::string longest_string;
  int running_max_length = std::numeric_limits<int>::lowest();
  std::string shortest_string; 
  int running_min_length = std::numeric_limits<int>::max();
  std::string most_frequent_string;
  int running_max_frequency = 0;

  for (auto it = hash.begin(); it != hash.end(); it++) {

    // wrap the size() in int as it's returning something else
    if (int(it->first.size()) > running_max_length) {
      running_max_length = it->first.size();
      longest_string = it->first; 
    } 
    if (int(it->first.size()) < running_min_length) {
      running_min_length = it->first.size();
      shortest_string = it->first; 
    } 
    if (it->second > running_max_frequency) {
      running_max_frequency = it->second;
      most_frequent_string = it->first;
    }
  }

  std::cout << "\n\n";
  std::cout << "Longest string is " << longest_string << "\n";
  std::cout << "Shortest string is " << shortest_string << "\n";
  std::cout << "Most frequent string is " << most_frequent_string << ", appearing " << running_max_frequency << " times!\n";

  return 0;
}