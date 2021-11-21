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

// #include <iostream>
// #include <vector>
// #include <string>

// int main() {
//   std::cout << "Please enter a bunch of strings separated by a space but do NOT use the word poop. Press control-D twice when you're done.\n\n";
//   std::vector<std::string> words;
//   for (std::string word; std::cin >> word;) {
//     words.push_back(word);
//   }
//   std::cout << "\n \n You said: \n\n";
//   for (std::string word : words) {
//     if (word == "poop") {
//       std::cout << "beep" << "\n";
//     } else {
//       std::cout << word << "\n";
//     }
//   }
    
//   return 0;
// }

//! drill

#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>

double ConvertToMeter(double num, std::string unit) {
  if (unit == "cm") {
    return num / 100;
  } else if (unit == "in") {
    return num * 2.54 / 100;
  } else if (unit == "ft") {
    return num * 12 * 2.54 / 100;
  } else if (unit == "m") {
    return num;
  } else {
    return 0;
  }
}

int main() {
  std::cout << "Enter a bunch of floats with units cm, m, in, or ft (ex 23.1 cm) and press \"|\"\n";
  double min = std::numeric_limits<double>::max();
  double max = std::numeric_limits<double>::min();
  double sum_meter_vals = 0;
  int num_values = 0;
  std::vector<double> meter_vector{};

  double num;
  std::string unit;
  while (std::cin >> num >> unit) {
    if (unit != "m" && unit != "ft" && unit!= "cm" && unit!= "in") {
      std::cout << "Illegal unit name\n";
      return 1;
    }
    ++num_values;
    double meter_value = ConvertToMeter(num, unit);
    sum_meter_vals += meter_value;
    meter_vector.push_back(meter_value);
    if (meter_value < min) {
      min = meter_value;
    } if (meter_value > max) {
      max = meter_value;
    }
  }

  std::cout << "Maximum value entered was " << max << "m\n";
  std::cout << "Minimum value entered was " << min << "m\n";
  std::cout << "Number of values entered was " << num_values << "\n";
  std::cout << "Sum of all values is " << sum_meter_vals << "m\n";
  
  std::sort(meter_vector.begin(), meter_vector.end());
  std::cout << "Listing all values in increasing order: \n"; 
  for (double val : meter_vector) {
    std::cout << val << "m\n"; 
  }

  return 0;
}



