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

//! ex 8
