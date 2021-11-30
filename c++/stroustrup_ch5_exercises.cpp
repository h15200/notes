//! ex 2, 3, 4, 5

// #include <iostream>
// #include <stdexcept>

// constexpr double LOWEST_CELSIUS = -273.15;
// constexpr double LOWEST_KELVIN = 0.0;

// double ConvertCelsiusOrKelvin(char k_or_c, double k_or_c_temp) {
//   switch (k_or_c) {
//     case 'c': {
//       double celsius_temp = k_or_c_temp;
//       if (celsius_temp < LOWEST_CELSIUS) {
//         throw std::invalid_argument("Celsius lower bound exceeded\n");
//       }
//       double kelvin_result = celsius_temp + 273.15;
//       return kelvin_result;
//       break;
//     }
//     case 'k': {
//       double kelvin_temp = k_or_c_temp;
//       if (kelvin_temp < LOWEST_KELVIN) {
//         throw std::invalid_argument("Kelvin lower bound exceeded\n");
//       }
//       double celsius_result = kelvin_temp - 273.15;
//       return celsius_result;
//       break;
//     }
//     default :{
//       throw std::invalid_argument("Invalid format\n");
//     }
//   }
// }

// int main() {
//   std::cout << "Enter format of input 'k' for Kelvin, 'c' for Celsius\n";
//   char k_or_c;
//   std::cin >> k_or_c;
//   switch (k_or_c) {
//     case 'k': {
//       double kelvin_temp;
//       std::cout << "Enter number for Kelvin\n";
//       std::cin >> kelvin_temp;
//       try {
//       double celcius_temp = ConvertCelsiusOrKelvin('k', kelvin_temp);
//       std::cout << "Celsius temp is " << celcius_temp << std::endl;
//       } catch (std::invalid_argument& err) {
//         std::cerr << "Error: " << err.what() << std::endl;
//       } catch (...) { // global error handler
//         std::cerr << "General Error\n";
//       }
//       return 0;
//       break;
//     }
//     case 'c': {
//       double celsius_temp;
//       std::cout << "Enter number for Celsius\n";
//       std::cin >> celsius_temp;
//       try {
//       double kelvin_temp = ConvertCelsiusOrKelvin('c', celsius_temp);
//       std::cout << "Kelvin temp is " << kelvin_temp << std::endl;
//       } catch (std::invalid_argument& err) {
//         std::cerr << "Error: " << err.what() << std::endl;
//       } catch (...) { // global error handler
//         std::cerr << "General Error\n";
//       }
//       return 0;
//       break;
//     }

//     default : {
//       std::cerr << ("Invalid format input\n");  
//     }
//   }
// }

//! ex 6

// #include <iostream>
// #include <stdexcept>

// constexpr double LOWEST_CELSIUS = -273.15;
// constexpr double LOWEST_FAHRENHEIT = -459.67;

// double ConvertCelsiusAndFahrenheit(char f_or_c, double f_or_c_temp) {
//   switch (f_or_c) {
//     case 'f': {
//       double fahrenheit_temp = f_or_c_temp;
//       if (fahrenheit_temp < LOWEST_FAHRENHEIT) {
//         throw std::invalid_argument("Fahrenheight lower bound exceeded\n");
//       }
//       double celsius_result = (fahrenheit_temp - 32) *  5 / 9;
//       return celsius_result;
//       break;
//     }
//     case 'c': {
//       double celsius_temp = f_or_c_temp;
//       if (celsius_temp < LOWEST_CELSIUS) {
//         throw std::invalid_argument("Celsius lower bound exceeded\n");
//       }
//       double fahrenheit_result = (celsius_temp * 9 / 5) + 32;
//       return fahrenheit_result;
//       break;
//     }
//     default :{
//       throw std::invalid_argument("Invalid format\n");
//     }
//   }
// }

// int main() {
//   std::cout << "Enter format of input 'f' for Fahrenheit, 'c' for Celsius\n";
//   char f_or_c;
//   std::cin >> f_or_c;
//   switch (f_or_c) {
//     case 'f': {
//       double fahrenheit_temp;
//       std::cout << "Enter number for Fahrenheit\n";
//       std::cin >> fahrenheit_temp;
//       try {
//       double celcius_temp = ConvertCelsiusAndFahrenheit('f', fahrenheit_temp);
//       std::cout << "Celsius temp is " << celcius_temp << std::endl;
//       } catch (std::invalid_argument& err) {
//         std::cerr << "Error: " << err.what() << std::endl;
//       } catch (...) { // global error handler
//         std::cerr << "General Error\n";
//       }
//       return 0;
//       break;
//     }
//     case 'c': {
//       double celsius_temp;
//       std::cout << "Enter number for Celsius\n";
//       std::cin >> celsius_temp;
//       try {
//       double fahrenheit_temp = ConvertCelsiusAndFahrenheit('c', celsius_temp);
//       std::cout << "Fahrenheit temp is " << fahrenheit_temp << std::endl;
//       } catch (std::invalid_argument& err) {
//         std::cerr << "Error: " << err.what() << std::endl;
//       } catch (...) { // global error handler
//         std::cerr << "General Error\n";
//       }
//       return 0;
//       break;
//     }

//     default : {
//       std::cerr << ("Invalid format input\n");  
//     }
//   }
// }

//! ex 8, 9

// #include <iostream>
// #include <vector>
// #include <stdexcept>
// #include <string>

// int main() {
//   try {

//     std::cout << "Enter the number of vals you want to sum\n";
//     int num_to_sum;
//     std::cin >> num_to_sum;
//     if (std::cin.fail() || num_to_sum < 1) {
//       throw std::invalid_argument("Invalid number. Please an integer that is 1 or more\n");
//     }
//     std::cout << "\nEnter a bunch of integers and terminate with ctr + 'd' twice\n";
//     std::vector<int> int_v;
//     std::string user_num;
//     while (std::cin >> user_num) {
//       try {
//       int num = std::stoi(user_num);
//       int_v.push_back(num);
//       } catch (std::invalid_argument& e) {
//         std::cout << "\nError with input. Please enter integer values only\n";
//         return 1;
//       }
//     }
    
//     if (num_to_sum > int_v.size()) {
//       throw std::invalid_argument("Not enough numbers listed\n");
//     }

//     int sum = 0;
//     for (int i = 0; i < num_to_sum; ++i) {
//       sum += int_v[i];
//     }

//     std::cout << "The total is " << sum << std::endl;

//     return 0;
//   } catch (std::exception& e) {
//     std::cout << e.what() << std::endl;
//     return 1;
//   }
// }

//! ex 11 fib

// #include <iostream>
// #include <limits>

// int main() {
//   int first = 1;
//   int second = 1;
//   std::cout << first << std::endl;
//   std::cout << second << std::endl;
//   while (first + second <= std::numeric_limits<int>::max()) {
//     int fib = first + second;
//     if (fib < first) {
//       break;
//       // overflow
//     }
//     std::cout << fib << std::endl;
//     first = second;
//     second = fib;
//   }
//   return 0;
// }

//! ex 12, 13 
// !bulls and cows [1, 3, 5, 7] four distinct single digit ints, same position = bull, num exists = cow

// #include <iostream>
// #include <vector>
// #include <stdexcept>
// #include <string>

// std::vector<int> GenerateRandomArray() {
//   std::srand(std::time(nullptr)); // randomize seed based on current time
//   int rand_one = std::rand() % 10;
//   int rand_two = std::rand() % 10;
//   while (rand_one == rand_two) {
//     rand_two = std::rand() % 10;
//   }
//   int rand_three = std::rand() % 10;
//   while (rand_three == rand_one || rand_three == rand_two) {
//     rand_three = std::rand() % 10;
//   }
//   int rand_four = std::rand() % 10;
//   while (rand_four == rand_one || rand_four == rand_two || rand_four == rand_three) {
//     rand_three = std::rand() % 10;
//   }
//   std::vector<int> int_v;
//   int_v.push_back(rand_one);
//   int_v.push_back(rand_two);
//   int_v.push_back(rand_three);
//   int_v.push_back(rand_four);

//   return int_v;
// }

// int main() {
//   try {
//   std::vector<int> int_v = GenerateRandomArray();
//   bool is_correct = false;
//   std::cout << "Guess my four unique numbers between 0 - 9!\n";

//   while (is_correct == false) {
//     int guess_one;
//     int guess_two;
//     int guess_three;
//     int guess_four;
//     std::cin >> guess_one >> guess_two >> guess_three >> guess_four;
//     if (std::cin.fail() || guess_one < 0 || guess_one > 9 || guess_two < 0 || guess_two > 9 || 
//     guess_three < 0 || guess_three > 9 || guess_four < 0 || guess_four > 9) {
//       throw std::invalid_argument("Error: Enter 4 integers between 0 and 9\n");
//     }
//     if (guess_one == guess_two || guess_one == guess_three || guess_one == guess_four ||
//     guess_two == guess_three || guess_two == guess_four || guess_three == guess_four) {
//       throw std::invalid_argument("Error: Enter 4 unique integars\n");
//     }

//     int bulls = 0;
//     int cows = 0;
//     std::vector<int>unique_num;
//     std::vector<int>::iterator it;

//     it = std::find(int_v.begin(), int_v.end(), guess_one);
//     if (it != int_v.end()) {
//       // found
//       if (std::distance(int_v.begin(), it)  == 0){
//         ++bulls;
//       } else {
//         ++cows;
//       }
//     }
//     unique_num.push_back(guess_one);
//     it = std::find(int_v.begin(), int_v.end(), guess_two);
//     if (it != int_v.end()) {
//       // found
//       if (std::distance(int_v.begin(), it)  == 1) {
//         ++bulls;
//       } else {
//         ++cows;
//       }
//     }
//     it = std::find(int_v.begin(), int_v.end(), guess_three);
//     if (it != int_v.end()) {
//       // found
//       if (std::distance(int_v.begin(), it)  == 2) {
//         ++bulls;
//       } else {
//         ++cows;
//       }
//     }
//     it = std::find(int_v.begin(), int_v.end(), guess_four);
//     if (it != int_v.end()) {
//       // found
//       if (std::distance(int_v.begin(), it)  == 3) {
//         ++bulls;
//       } else {
//         ++cows;
//       }
//     }

//   if (bulls == 4) {
//     break;
//   }

//   std::string bull_appender = "bulls";
//   std::string cow_appender = "cows";
//   if (bulls == 1) bull_appender = "bull";
//   if (cows == 1) cow_appender = "cow";

//   std::cout << bulls << " " << bull_appender << " and " << cows << " " << cow_appender << std::endl;
//   std::cout << "Guess again!\n";


//   }

//   std::cout << "You've won!\n";
//   return 0;
//   } catch (std::invalid_argument& e) {
//     std::cout << e.what() << std::endl;
//     return 1;
//   }
// }

// #include<iostream>
// #include<vector>
// #include<string>
// #include<stdexcept>

// bool IsSunday(std::string str) {
//   if (str == "sun" || str == "Sun" || str == "Aunday" || str == "sunday") {
//     return true;
//   }
//   return false;
// }
// bool IsMonday(std::string str) {
//   if (str == "mon" || str == "Mon" || str == "Monday" || str == "monday") {
//     return true;
//   }
//   return false;
// }

// bool IsTuesday(std::string str) {
//   if (str == "tues" || str == "Tues" || str == "Tuesday" || str == "tuesday") {
//     return true;
//   }
//   return false;
// }
// bool IsWednesday(std::string str) {
//   if (str == "wed" || str == "Wed" || str == "Wednesday" || str == "wednesday") {
//     return true;
//   }
//   return false;
// }
// bool IsThursday(std::string str) {
//   if (str == "thur" || str == "Thur" || str == "Thursday" || str == "thursday") {
//     return true;
//   }
//   return false;
// }
// bool IsFriday(std::string str) {
//   if (str == "fri" || str == "Fri" || str == "Friday" || str == "friday") {
//     return true;
//   }
//   return false;
// }

// bool IsSaturday(std::string str) {
//   if (str == "sat" || str == "Sat" || str == "Saturday" || str == "saturday") {
//     return true;
//   }
//   return false;
// }

// int GetIndexFromStr(std::string str) {
//   if (IsSunday(str) == true) {
//     return 0;
//   } else if (IsMonday(str) == true) {
//     return 1;
//   } else if (IsTuesday(str) == true) {
//     return 2;
//   } else if (IsWednesday(str) == true) {
//     return 3;
//   } else if (IsThursday(str) == true) {
//     return 4;
//   } else if (IsFriday(str) == true) {
//     return 5;
//   } else if (IsSaturday(str) == true) {
//     return 6;
//   } else {
//     return -1;
//   }
// }

// int main() {
//   try {
//     std::vector<int>day_total_val(7); // idx 0 is Sunday, 1 is monday, etc..
    
//     std::cout << "Enter day value pairs like Monday 3 Tuesday 5 Thur -34 and terminate with ctr-d\n";

//     std::string user_input;
//     bool is_string = true; // whether to expect string or num
//     int rejected_times = 0;
//     int curr_idx;

//     while (std::cin >> user_input) {
//       if (is_string == true) {
//         // check string, then parse to appropriate vector index
//         int idx = GetIndexFromStr(user_input);
//         curr_idx = idx;
//         if (idx == -1) ++rejected_times;
//       } else {
//         // check for number
//         if (curr_idx != -1) {
//         try {
//         int val = std::stoi(user_input);
//         day_total_val[curr_idx] += val;
//         } catch (std::invalid_argument& err) {
//           std::cout << "Invalid value\n";
//           return 1;
//         }

//         }
//       }
//       is_string = !is_string;
//     }

//     std::cout << "The results: \n";
//     std::cout << "Sunday total " << day_total_val[0] << std::endl;
//     std::cout << "Monday total " << day_total_val[1] << std::endl;
//     std::cout << "Tuesday total " << day_total_val[2] << std::endl;
//     std::cout << "Wednesday total " << day_total_val[3] << std::endl;
//     std::cout << "Thursday total " << day_total_val[4] << std::endl;
//     std::cout << "Friday total " << day_total_val[5] << std::endl;
//     std::cout << "Saturday total " << day_total_val[6] << std::endl;
//     std:: cout << "Unknown ignored string and value count: " << rejected_times << std::endl;



//   return 0;
//   } catch (std::invalid_argument& err) {
//     std::cout << "Error: " << err.what() << std::endl;
//     return 1;
//   }
// }