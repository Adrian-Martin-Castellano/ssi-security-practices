// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 9: SSI - RSA Cryptosystem & Primality Testing
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 09/04/2025

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>

/**
 * @brief Computes (base^exp) % mod efficiently using binary modular exponentiation.
 */
long long ModularExponentiation(long long base, long long exp, long long mod) {
  long long result = 1;
  long long current_base = base % mod;
  long long current_exp = exp;
  while (current_exp > 0) {
    if (current_exp % 2 != 0) {
      result = (result * current_base) % mod;
      current_exp -= 1;
    } else {
      current_base = (current_base * current_base) % mod;
      current_exp /= 2;
    }
  }
  return result;
}

/**
 * @brief Verifies whether a number is prime using the Lehman-Peralta probabilistic test.
 * @param p The target integer to evaluate.
 * @param iterations The total validation loops to execute (confidence control).
 * @return true If the number is likely prime.
 * @return false If the number is definitively composite.
 */
bool LehmanPeraltaTest(long long p, int iterations = 10) {
  if (p < 2) return false;
  long long small_primes[] = {2, 3, 5, 7, 11};
  for (long long prime : small_primes) {
    if (p == prime) return true;
    if (p % prime == 0) return false;
  }
  
  std::srand(std::time(nullptr)); 
  bool contains_minus_one = false;
  
  for (int i = 0; i < iterations; ++i) {
    long long a = 2 + std::rand() % (p - 1);
    long long exponent = (p - 1) / 2;
    long long remainder = ModularExponentiation(a, exponent, p);
    
    if (remainder != 1 && remainder != p - 1) return false;
    if (remainder == p - 1) contains_minus_one = true;
  }
  
  return contains_minus_one;
}

/**
 * @brief Calculates the Extended Euclidean Algorithm to solve Bezout's coefficients.
 */
long long ExtendedGCD(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long long x1, y1;
  long long gcd = ExtendedGCD(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return gcd;
}

/**
 * @brief Computes the modular multiplicative inverse using Extended Euclidean data.
 */
long long ModularInverse(long long d, long long phi_n) {
  long long x, y;
  long long gcd = ExtendedGCD(d, phi_n, x, y);
  if (gcd != 1) return -1; 
  return (x % phi_n + phi_n) % phi_n; 
}

/**
 * @brief Determines the maximal text blocks operational sizing for a given modulus n.
 */
int DetermineBlockSize(long long n) {
  int block_size = 1;
  while (block_size <= 100) {
    if ((std::pow(26, block_size - 1) < n) && (n < std::pow(26, block_size))) {
      return block_size;
    }
    block_size++;
  }
  return block_size;
}

int main() {
  std::string input_text;
  long long prime_p, prime_q, public_d;

  std::cout << "Enter the plaintext to encrypt: ";
  std::getline(std::cin >> std::ws, input_text);
  std::cout << "Enter the first prime number (p): ";
  std::cin >> prime_p;
  std::cout << "Enter the second prime number (q): ";
  std::cin >> prime_q;
  std::cout << "Enter the public exponent key (d): ";
  std::cin >> public_d;

  if (LehmanPeraltaTest(prime_p)) {
    std::cout << "-> Parameter 'p' passes primality criteria.\n";
  } else {
    std::cout << "-> Error: Parameter 'p' is composite.\n";
    return 1;
  } 
  if (LehmanPeraltaTest(prime_q)) {
    std::cout << "-> Parameter 'q' passes primality criteria.\n";
  } else {
    std::cout << "-> Error: Parameter 'q' is composite.\n";
    return 1;
  }

  long long phi_n = (prime_p - 1) * (prime_q - 1);
  long long x, y;
  long long gcd = ExtendedGCD(public_d, phi_n, x, y);

  if (gcd == 1) {
    std::cout << "-> Success: Public exponent 'd' is coprime to phi(n).\n";
  } else {
    std::cout << "-> Error: Public exponent 'd' is not coprime to phi(n).\n";
    return 1;
  }

  std::cout << "GCD(d, phi(n)) = " << gcd << std::endl;
  long long private_e = ModularInverse(public_d, phi_n);
  std::cout << "Modular inverse (private exponent e) = " << private_e << std::endl;

  long long n = prime_p * prime_q;
  std::cout << "Modulus (n = p * q) = " << n << std::endl;

  int chunk_limit = DetermineBlockSize(n);
  int effective_block_size = --chunk_limit;
  std::cout << "Operational Block Size: " << effective_block_size << std::endl;

  std::string clean_text;
  for (char c : input_text) {
    if (std::isalpha(c)) {
      clean_text += std::toupper(c);
    }
  }

  std::cout << "\n--- Processing RSA Blocks (Base-26 Coding) ---" << std::endl;
  for (size_t i = 0; i < clean_text.length(); i += effective_block_size) {
    std::string block = clean_text.substr(i, effective_block_size);
    while (block.length() < static_cast<size_t>(effective_block_size)) {
      block += 'X'; 
    }

    long long block_value = 0;
    int power_index = 0;
    
    for (int j = block.length() - 1; j >= 0; --j) {
      if (!std::isalpha(block[j])) continue;
      block_value += (static_cast<int>(block[j]) - 'A') * std::pow(26, power_index);
      power_index++;
    }

    long long encrypted_block = ModularExponentiation(block_value, private_e, n);
    
    std::cout << "Block \"" << block << "\" -> Decimal Base-26 Value: " << block_value << " -> Encrypted Representation: " << encrypted_block << std::endl;
  }

  return 0;
}