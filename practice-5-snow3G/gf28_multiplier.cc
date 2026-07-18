// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 5: SSI
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 12/03/2025

#include <iostream>
#include <bitset>
#include <sstream>

/**
 * @brief Performs Galois Field GF(2^8) multiplication using the peasant algorithm.
 * @param first_byte First polynomial operand represented as an 8-bit bitset.
 * @param second_byte Second polynomial operand represented as an 8-bit bitset.
 * @param irreducible_poly The irreducible polynomial constant used for reduction on overflow.
 * @return std::bitset<8> The 8-bit polynomial product result.
 */
std::bitset<8> GaloisFieldMultiply(std::bitset<8> first_byte, std::bitset<8> second_byte, std::bitset<8> irreducible_poly) {
  std::bitset<8> result, aux = first_byte;
  if (second_byte[0] == 1) result = first_byte; 
  
  for (size_t i = 1; i < second_byte.size(); i++) {
    if (aux[7] == 1) {
        aux <<= 1;
        aux[0] = 0;
        aux ^= irreducible_poly; 
    } else {
        aux <<= 1;
        aux[0] = 0;
    }
    if (second_byte[i] == 1) result ^= aux;
  }
  return result;
}

int main() {
  std::string first_byte_str, second_byte_str;
  std::bitset<8> irreducible_poly;
  std::string algorithm;
  unsigned int decimal_first, decimal_second;

  std::cout << "First byte (hex): ";
  std::cin >> first_byte_str;
  std::cout << "Second byte (hex): ";
  std::cin >> second_byte_str;
  std::cout << "Algorithm (AES / SNOW_3G): ";
  std::cin >> algorithm;
  std::cout << "\n---------------------------\n\n";

  if (algorithm == "AES") 
    irreducible_poly = std::bitset<8>("00011011"); 
  else if (algorithm == "SNOW_3G") 
    irreducible_poly = std::bitset<8>("10101001"); 
  else {
    std::cerr << "Error: Algorithm not supported.\n";
    return 1;
  }

  std::stringstream ss1;
  ss1 << std::hex << first_byte_str;
  ss1 >> decimal_first;

  std::stringstream ss2;
  ss2 << std::hex << second_byte_str;
  ss2 >> decimal_second;

  std::bitset<8> first_byte(decimal_first);
  std::bitset<8> second_byte(decimal_second);

  std::cout << "First byte (bin):       " << first_byte << std::endl;
  std::cout << "Second byte (bin):      " << second_byte << std::endl;
  std::cout << "Irreducible poly (bin): " << irreducible_poly << std::endl;
  std::cout << "Multiplication result:  " << GaloisFieldMultiply(first_byte, second_byte, irreducible_poly) << std::endl;

  return 0;
}