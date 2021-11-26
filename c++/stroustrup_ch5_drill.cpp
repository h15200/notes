#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

int main() {
  try {
    // std::vector<char> v(5);
    // for (int i = 0; i < v.size(); ++i) {
    //   std::cout << "Success!\n";
    // }
    // std::string s = "Success!\n";
    // for (int i = 0; i < s.size(); ++i) {
    //   std::cout << s[i] << std::endl;
    // }
  //  if (true) {
  //    std::cout << "Success!\n";
  //  } else {
  //    std::cout << "Fail!\n";
  //  }

  // std::vector<int> v(5);
  // for (int i = 0; i < v.size(); ++i) {
  //   std::cout << "Success!\n" << v[i] << std::endl;
  // }
  // int i = 0;
  // int j = 9;
  // while (i < 10) {
  //   ++i;
  //   if (j<i) {
  //     std::cout << "Success!\n";
  //   }
  // }
  int x = 4;
  double d = 5 / (x - 2.0);
  std::cout << d << std::endl;
  if (d == 2  + 0.5) {
    std::cout << "Success!\n";
  }

    return 0;
  } catch (const std::exception& err) {
    std::cerr << "error: " << err.what() << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Unknown exception \n";
    return 2;
  }
}