// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 3: SSI
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 19/02/2026

#include <iostream>
#include <stdint.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>

#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) ( \
    a += b, d ^= a, d = ROTL(d, 16), \
    c += d, b ^= c, b = ROTL(b, 12), \
    a += b, d ^= a, d = ROTL(d, 8), \
    c += d, b ^= c, b = ROTL(b, 7))
#define ROUNDS 20

/**
 * @brief Performs the ChaCha20 block operation on a 512-bit block.
 * @param out 16-element array containing the output key stream block.
 * @param in 16-element array containing the initialized input state matrix.
 */
void chacha_block(uint32_t out[16], const uint32_t in[16]) {
  uint32_t x[16];

  for (int i = 0; i < 16; i++) {
    x[i] = in[i];
  }
  for (int i = 0; i < ROUNDS; i += 2) {
    // Odd round
    QR(x[0], x[4], x[8], x[12]);  // column 0
    QR(x[1], x[5], x[9], x[13]);  // column 1
    QR(x[2], x[6], x[10], x[14]); // column 2
    QR(x[3], x[7], x[11], x[15]); // column 3

    // Even round
    QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
    QR(x[1], x[6], x[11], x[12]); // diagonal 2
    QR(x[2], x[7], x[8], x[13]);  // diagonal 3
    QR(x[3], x[4], x[9], x[14]);  // diagonal 4
  }
  
  std::cout << "\n\nFinal internal state after 20 rounds=";
  for (int i = 0; i < 16; i++) {
    if (i % 4 == 0) std::cout << std::endl;
    std::cout << std::setw(8) << std::setfill('0') << std::hex << x[i] << " ";
  }

  for (int i = 0; i < 16; ++i) {
    out[i] = x[i] + in[i];
  }
  
  std::cout << "\n\nGenerator output keystream block=";
  for (int i = 0; i < 16; i++) {
    if (i % 4 == 0) std::cout << std::endl;
    std::cout << std::setw(8) << std::setfill('0') << std::hex << out[i] << " ";
  }
  std::cout << std::endl;
}

/**
 * @brief Parses and reads cryptographic components from a configuration file.
 * Automatically strips format noise and handles Little-Endian byte-reversing swaps.
 * @param is Reference to the input configuration ifstream object.
 * @return A vector of parsed hexadecimal sub-strings.
 */
std::vector<std::string> ReadKeyfile(std::ifstream& is) {
  std::string key_line;
  std::getline(is, key_line);
  key_line.erase(std::remove_if(key_line.begin(), key_line.end(), [](unsigned char c) {
    return std::isspace(c) || c == '\r' || c == ':'; 
  }), key_line.end());
  
  std::string counter_line;
  std::getline(is, counter_line);
  counter_line.erase(std::remove_if(counter_line.begin(), counter_line.end(), [](unsigned char c) {
    return std::isspace(c) || c == ':'; 
  }), counter_line.end());

  std::string nonce_line;
  std::getline(is, nonce_line);
  nonce_line.erase(std::remove_if(nonce_line.begin(), nonce_line.end(), [](unsigned char c) {
    return std::isspace(c) || c == ':'; 
  }), nonce_line.end());

  std::vector<std::string> string_vector;
  for (size_t i = 0; i < key_line.size(); i += 8) {
    string_vector.push_back(key_line.substr(i, 8));
  }
  string_vector.push_back(counter_line);
  for (size_t i = 0; i < nonce_line.size(); i += 8) {
    string_vector.push_back(nonce_line.substr(i, 8));
  }

  std::string char_1, char_2, byte_reversal;
  std::vector<std::string> aux_vector;
  for (const auto& hexa_block : string_vector) {
    char_1.clear();
    char_2.clear();
    byte_reversal.clear();
    // Enforce Little-Endian configuration ordering by flipping byte sequences
    for (int j = static_cast<int>(hexa_block.size()) - 2; j >= 0; j -= 2) {
      char_1 = hexa_block[j]; 
      char_2 = hexa_block[j + 1];    
      byte_reversal += char_1 + char_2; 
    }
    aux_vector.push_back(byte_reversal);
  }
  return aux_vector;
}

/**
 * @brief Application entry point.
 */
int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_keyfile_path>\n";
    return 1;
  }

  const uint32_t first_const[4] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574};
  uint32_t out[16], in[16];
  for (int i = 0; i < 4; i++) {
    in[i] = first_const[i];
  }
  
  std::ifstream inputFile(argv[1]);
  if (!inputFile) {
    std::cerr << "Error: Could not open the specified input file.\n";
    return 1;
  }
  
  const std::vector<std::string> conversion = ReadKeyfile(inputFile);
  if (conversion.size() != 12) {
    std::cerr << "Error: Input file does not match the required parameter parameters.\n";
    return 1;
  }

  for (int i = 0; i < 12; i++) {
    std::string hex_block = conversion[i];
    in[i + 4] = std::stoul(hex_block, nullptr, 16);
  }

  std::cout << "Initial matrix state=";
  for (int i = 0; i < 16; i++) {
    if (i % 4 == 0) std::cout << std::endl;
    std::cout << std::setw(8) << std::setfill('0') << std::hex << in[i] << " ";
  }
  std::cout << std::endl;
  
  chacha_block(out, in);

  return 0;
}