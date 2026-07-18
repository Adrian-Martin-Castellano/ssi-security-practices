// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 10: SSI - Elliptic Curve Cryptography
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 24/04/2025

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

int prime_p, param_a, param_b;

struct Point {
  int x, y;
  bool is_infinity;
};

Point CreatePoint(int x, int y) {
  return {x, y, false};
}

Point PointAtInfinity() {
  return {0, 0, true};
}

bool ArePointsEqual(const Point& P, const Point& Q) {
  return (P.is_infinity && Q.is_infinity) || 
         (!P.is_infinity && !Q.is_infinity && P.x == Q.x && P.y == Q.y);
}

int TrueMod(int n, int p) {
  return ((n % p) + p) % p;
}

/**
 * @brief Computes the modular multiplicative inverse using a linear scan.
 */
int ModularInverse(int a, int p) {
  for (int i = 1; i < p; i++) {
    if (TrueMod(a * i, p) == 1)
      return i;
  }
  return -1;
}

/**
 * @brief Checks if a given coordinate pair satisfies the Weierstrass equation: y^2 = x^3 + ax + b (mod p).
 */
bool IsOnCurve(int x, int y) {
  return TrueMod(y * y, prime_p) == TrueMod(x * x * x + param_a * x + param_b, prime_p);
}

/**
 * @brief Generates all finite points belonging to the elliptic curve field group.
 */
std::vector<Point> GenerateCurvePoints() {
  std::vector<Point> points;
  for (int x = 0; x < prime_p; x++) {
    for (int y = 0; y < prime_p; y++) {
      if (IsOnCurve(x, y))
          points.push_back(CreatePoint(x, y));
    }
  }
  return points;
}

/**
 * @brief Performs elliptic curve point addition (P + Q) over GF(p).
 */
Point AddPoints(Point P, Point Q) {
  if (P.is_infinity) return Q;
  if (Q.is_infinity) return P;
  if (P.x == Q.x && TrueMod(P.y + Q.y, prime_p) == 0) return PointAtInfinity();
  
  int lambda;
  if (P.x == Q.x && P.y == Q.y) { // Point doubling logic
    int num = 3 * P.x * P.x + param_a;
    int den = 2 * P.y;
    lambda = TrueMod(num * ModularInverse(den, prime_p), prime_p);
  } else { // Standard point addition
    int num = Q.y - P.y;
    int den = Q.x - P.x;
    lambda = TrueMod(num * ModularInverse(den, prime_p), prime_p);
  }
  
  int x3 = TrueMod(lambda * lambda - P.x - Q.x, prime_p);
  int y3 = TrueMod(lambda * (P.x - x3) - P.y, prime_p);
  return CreatePoint(x3, y3);
}

/**
 * @brief Performs scalar multiplication (n * P) using sequential addition.
 */
Point MultiplyPoint(Point P, int n) {
  Point result = PointAtInfinity();
  for (int i = 0; i < n; i++) {
    result = AddPoints(result, P);
  }
  return result;
}

/**
 * @brief Encodes an integer message into a curve point using Koblitz's method.
 */
Point EncodeMessage(int message, int upper_M) {
  int aux_h = prime_p / upper_M;
  for (int j = 0; j < aux_h; j++) {
    int x = TrueMod(message * aux_h + j, prime_p);
    for (int y = 0; y < prime_p; y++) {
      if (IsOnCurve(x, y))
        return CreatePoint(x, y);
    }
  }
  return PointAtInfinity();
}

/**
 * @brief Computes the smallest power of 2 greater than the message integer.
 */
int CalculateUpperM(int message) {
  int upper_M = 1;
  while (upper_M <= message) {
    upper_M *= 2;
  }
  return upper_M;
}

void PrintPoint(const std::string& label, const Point& P) {
  std::cout << label;
  if (P.is_infinity) std::cout << "Infinity Point (O)";
  else std::cout << "(" << P.x << "," << P.y << ")";
  std::cout << std::endl;
}

int main() {
  int gen_x, gen_y, private_dA, private_dB, raw_message;
  
  std::cout << "--- Elliptic Curve Parameter Configuration ---" << std::endl;
  std::cout << "Enter prime field modulus (p): "; 
  std::cin >> prime_p;
  std::cout << "Enter curve coefficient (a):   "; 
  std::cin >> param_a;
  std::cout << "Enter curve coefficient (b):   "; 
  std::cin >> param_b; 
  std::cout << "Enter generator Point G (x y): "; 
  std::cin >> gen_x >> gen_y;
  std::cout << "Enter Alice's private key (dA): "; 
  std::cin >> private_dA;
  std::cout << "Enter Bob's private key (dB):   "; 
  std::cin >> private_dB;
  std::cout << "Enter plaintext message (integer): "; 
  std::cin >> raw_message;

  int upper_M = CalculateUpperM(raw_message);
  Point base_G = CreatePoint(gen_x, gen_y);
  auto all_points = GenerateCurvePoints();
  
  std::cout << "\n[+] Group Points on Curve: ";
  for (const auto& pt : all_points) std::cout << "(" << pt.x << "," << pt.y << ") ";
  std::cout << "\n";

  Point public_A = MultiplyPoint(base_G, private_dA);
  Point public_B = MultiplyPoint(base_G, private_dB);
  
  PrintPoint("\n-> Alice's Public Key (QA = dA * G): ", public_A);
  PrintPoint("-> Bob's Public Key (QB = dB * G):   ", public_B);

  Point shared_secret_A = MultiplyPoint(public_B, private_dA);
  Point shared_secret_B = MultiplyPoint(public_A, private_dB);
  
  PrintPoint("\n[=] Shared Secret (Alice's side): ", shared_secret_A);
  PrintPoint("[=] Shared Secret (Bob's side):   ", shared_secret_B);
  
  std::cout << "\n--- Koblitz Message Encoding ---" << std::endl;
  std::cout << "Upper Bound M = " << upper_M << std::endl;
  int aux_h = prime_p / upper_M;
  std::cout << "Step parameter h = " << aux_h << " (Valid constraint: " << aux_h << " < " << prime_p << "/" << upper_M << ")" << std::endl;
  
  Point encoded_Qm = EncodeMessage(raw_message, upper_M);
  PrintPoint("-> Message encoded as Point Qm: ", encoded_Qm);

  Point ciphertext_point = AddPoints(encoded_Qm, shared_secret_A);
  std::cout << "\n--- Final Ciphertext Outputs ---" << std::endl;
  PrintPoint("-> Encrypted Message Point (Qm + dA * dB * G): ", ciphertext_point);
  PrintPoint("-> Ephemeral Public Key Sent (QA = dA * G):    ", public_A);

  return 0;
}