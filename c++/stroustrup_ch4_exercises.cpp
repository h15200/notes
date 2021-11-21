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
//   double largest_distance = std::numeric_limits<double>::min();
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

#include <iostream>

int main() {
  // do binary search with io
  std::cout << "Think of a number beween 1 and 100\n";
  int left = 1;
  int right = 100;
  while (left < right) {
    int mid = (left + right) / 2;
    if (mid == left || mid == right) {
      break;
    }
    if (left == right) {
      std::cout << "The number must be " << left << "!\n";
      return 0;
    }
    std::cout << "Is your number greater or equal to " << mid << " ? (Enter 'y' or 'n')\n";
    char reply;
    std::cin >> reply;
    switch (reply) {
      case 'y':
        left = mid;
        break;
      case 'n':
        right = mid - 1;
        break;
      default :
        std::cout << "That's not a valid answer\n";
        return 1;
    }
  }
  // one of the two
  std::cout << "Is your number " << left << "?\n";
  char outer_reply;
  std::cin >> outer_reply;
  switch (outer_reply) {
    case 'y':
      std::cout << "Yay!\n";
      return 0;
    case 'n':
      std::cout << "It must be " << right << "!\n";
      return 0;
  }


 
}
