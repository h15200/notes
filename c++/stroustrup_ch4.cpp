// ! pg 111 try this

// #include <iostream>

// int main() {
//   int curr = 97;
//   while (curr <= 122) {
//     std::cout << char(curr) << "  " << curr << "\n";
//     curr++;
//   }
//   return 0;
// }

//! pg 113

// #include <iostream>

// int main() {
//   const int kFirstLetterOfAlphabet = 97;
//   for (int i = 0; i < 26; i++) {
//     std::cout << char(kFirstLetterOfAlphabet + i) << "   " << kFirstLetterOfAlphabet + i<< "\n";
//   }
//   return 0;
// }

//! pg 116 

// #include <iostream>

// int Square(int num) {
//   int total = 0;
//   for (int i = 1; i <= num; i++) {
//     total += num;
//   }
//   return total;
// }

// int main() {
//   std::cout << Square(3) << "\n";
//   return 0;
// }

//! pg 125

#include <iostream>
#include <vector>
#include <string>

int main() {
  std::cout << "Please enter a bunch of strings separated by a space but do NOT use the word poop. Press control-D twice when you're done.\n\n";
  std::vector<std::string> words;
  for (std::string word; std::cin >> word;) {
    words.push_back(word);
  }
  std::cout << "\n \n You said: \n\n";
  for (std::string word : words) {
    if (word == "poop") {
      std::cout << "beep" << "\n";
    } else {
      std::cout << word << "\n";
    }
  }
    
  return 0;
}

