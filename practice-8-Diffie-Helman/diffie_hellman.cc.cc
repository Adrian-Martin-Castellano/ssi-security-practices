// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 8: SSI - Diffie-Hellman Key Exchange
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 02/04/2025

#include <iostream>

/**
 * @brief Computes (base^exp) % mod efficiently using binary modular exponentiation.
 * @param base The base integer (alpha or public keys).
 * @param exp The exponent integer (secret keys).
 * @param mod The prime modulus (p).
 * @return long long The modular exponentiation result.
 */
long long ModularExponentiation(long long base, long long exp, long long mod) {
  long long result = 1;
  long long current_base = base % mod;
  long long current_exp = exp;

  while (current_exp > 0 && current_base > 1) {
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

int main() {
  long long prime_p, alpha, secret_xA, secret_xB;

  std::cout << "Enter a prime number (p): ";
  std::cin >> prime_p;
  std::cout << "Enter alpha number (alpha < p): ";
  std::cin >> alpha;
  std::cout << "Enter Alice's secret key (xA): ";
  std::cin >> secret_xA;
  std::cout << "Enter Bob's secret key (xB): ";
  std::cin >> secret_xB;

  // Calculate public keys (yA and yB)
  long long public_yA = ModularExponentiation(alpha, secret_xA, prime_p);
  long long public_yB = ModularExponentiation(alpha, secret_xB, prime_p);

  // Calculate shared secret key (k)
  // Alice computes: k = (yB)^xA mod p
  // Bob computes:   k = (yA)^xB mod p
  long long shared_secret_k = ModularExponentiation(public_yB, secret_xA, prime_p);

  std::cout << "\n--- Diffie-Hellman Results ---" << std::endl;
  std::cout << "Public Parameters:  p = " << prime_p << ", alpha = " << alpha << std::endl;
  std::cout << "Secret Keys:        xA = " << secret_xA << ", xB = " << secret_xB << std::endl;
  std::cout << "Public Exchanges:   yA = " << public_yA << ", yB = " << public_yB << std::endl;
  std::cout << "Shared Secret Key:  k = " << shared_secret_k << std::endl;

  return 0;
}