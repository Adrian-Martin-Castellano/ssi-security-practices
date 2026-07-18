// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 6: SSI
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 19/03/2026

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <utility>

const uint8_t S_BOX[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

const uint8_t MIX_COLUMNS[4][4] = {
  {0x02, 0x03, 0x01, 0x01},
  {0x01, 0x02, 0x03, 0x01},
  {0x01, 0x01, 0x02, 0x03},
  {0x03, 0x01, 0x01, 0x02}
};

const uint8_t AES_CONSTANT = 0x1B;

/**
 * @brief Prints the 4x4 cryptographic state matrix in column-major hexadecimal format.
 * @param matrix The 4x4 byte state matrix to print.
 */
void PrintStateMatrix(const uint8_t matrix[4][4]) {
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)matrix[row][col];
    }
  }
}

/**
 * @brief Populates a 4x4 matrix from a raw hexadecimal string using column-major order.
 * @param hex_str Hexadecimal character string.
 * @param matrix The destination 4x4 byte state matrix.
 */
void StoreHexInput(const std::string& hex_str, uint8_t matrix[4][4]) {
  for (int i = 0; i < 16; i++) {
    std::stringstream ss;
    ss << std::hex << hex_str.substr(i * 2, 2);
    int value;
    ss >> value;
    matrix[i % 4][i / 4] = static_cast<uint8_t>(value);
  }
}

/**
 * @brief Multiplies two bytes inside the Galois Field GF(2^8) using the Rijndael reduction rule.
 * @param a First operand byte.
 * @param b Second operand byte.
 * @return uint8_t The product byte.
 */
uint8_t GaloisFieldMultiply(uint8_t a, uint8_t b) {
  uint8_t result = 0;
  uint8_t aux = a;
  for (int i = 0; i < 8; i++) {
      if (b & 1) {
          result ^= aux;
      }
      bool msb_set = (aux & 0x80);
      aux <<= 1;
      if (msb_set) {
          aux ^= AES_CONSTANT;
      }
      b >>= 1;
  }
  return result;
}

/**
 * @brief Swaps bytes non-linearly using the precomputed AES S-Box lookup framework.
 * @param state The current 4x4 operation state matrix.
 * @param result The destination 4x4 operation state matrix.
 */
void SubBytes(uint8_t state[4][4], uint8_t result[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      uint8_t byte = state[i][j];
      uint8_t row = byte >> 4;
      uint8_t col = byte & 0x0F;
      result[i][j] = S_BOX[row][col];
    }
  }
}
  
/**
 * @brief Transposes state matrix rows by cyclically shifting them left by distinct offsets.
 * @param state The current 4x4 operation state matrix.
 */
void ShiftRows(uint8_t state[4][4]) {
  // Row 1: Shift left by 1
  std::swap(state[1][0], state[1][1]);
  std::swap(state[1][1], state[1][2]);
  std::swap(state[1][2], state[1][3]);

  // Row 2: Shift left by 2
  std::swap(state[2][0], state[2][2]);
  std::swap(state[2][1], state[2][3]);

  // Row 3: Shift left by 3
  std::swap(state[3][0], state[3][3]);
  std::swap(state[3][1], state[3][3]);
  std::swap(state[3][2], state[3][3]);
}

/**
 * @brief Mixes column equations over GF(2^8) by performing matrix-vector multiplication.
 * @param state The current 4x4 operation state matrix.
 * @param result The destination 4x4 operation state matrix.
 */
void MixColumns(uint8_t state[4][4], uint8_t result[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) { 
      result[j][i] = 0; 
        for (int k = 0; k < 4; k++) { 
          result[j][i] ^= GaloisFieldMultiply(MIX_COLUMNS[j][k], state[k][i]);
        }
    }
  }
}

/**
 * @brief Blends the subkey mapping matrix onto the operation block via a bitwise XOR operation.
 * @param key Round subkey state matrix.
 * @param state Input block state matrix.
 * @param result Output block state matrix.
 */
void AddRoundKey(uint8_t key[4][4], uint8_t state[4][4], uint8_t result[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i][j] = key[i][j] ^ state[i][j];
    }
  }
}

/**
 * @brief Cyclically rotates a 4-byte word sequence array one space to the left.
 * @param word 4-element byte array target.
 */
void RotWord(uint8_t word[4]) {
  uint8_t temp = word[0];
  word[0] = word[1];
  word[1] = word[2];
  word[2] = word[3];
  word[3] = temp;
}

/**
 * @brief Transforms each byte within a 4-byte word array using S-Box transformations.
 * @param word 4-element byte array target.
 */
void SubWord(uint8_t word[4]) {
  for (int i = 0; i < 4; i++) {
    uint8_t row = word[i] >> 4;
    uint8_t col = word[i] & 0x0F;
    word[i] = S_BOX[row][col];
  }
}

/**
 * @brief Derives the 11 round subkeys from the initial 128-bit encryption cipher key block.
 * @param key Initial 128-bit master key matrix.
 * @param round_keys Full array destination containing the 11 derived subkeys.
 */
void KeyExpansion(uint8_t key[4][4], uint8_t round_keys[11][4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      round_keys[0][i][j] = key[i][j];
    }
  }
  uint8_t temp[4];
  uint8_t rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};
  for (int round = 1; round < 11; round++) {
    for (int i = 0; i < 4; i++) {
      temp[i] = round_keys[round - 1][i][3];
    }
    RotWord(temp);
    SubWord(temp);
    temp[0] ^= rcon[round - 1];
    for (int col = 0; col < 4; col++) {
      for (int row = 0; row < 4; row++) {
        if (col == 0) round_keys[round][row][col] = round_keys[round - 1][row][col] ^ temp[row];
        else round_keys[round][row][col] = round_keys[round - 1][row][col] ^ round_keys[round][row][col - 1];
      }
    }
  }
}

/**
 * @brief Drives the Rijndael processing cipher execution through the 10 iterative rounds.
 * @param key Input encryption master key matrix.
 * @param plaintext Input data stream block matrix.
 */
void RijndaelAlgorithm(uint8_t key[4][4], uint8_t plaintext[4][4]) {
  uint8_t result[4][4], result_add[4][4], result_mix[4][4];
  uint8_t round_keys[11][4][4];
  
  KeyExpansion(key, round_keys);
  AddRoundKey(round_keys[0], plaintext, result);
  
  std::cout << "R0 (Subkey = ";
  PrintStateMatrix(round_keys[0]);
  std::cout << ") = ";
  PrintStateMatrix(result);
  std::cout << std::endl;

  for (int iteration = 1; iteration < 10; iteration++) {
      SubBytes(result, result);
      ShiftRows(result);
      MixColumns(result, result_mix);
      AddRoundKey(round_keys[iteration], result_mix, result_add);
      
      std::cout << "R" << iteration << " (Subkey = ";
      PrintStateMatrix(round_keys[iteration]);
      std::cout << ") = ";
      PrintStateMatrix(result_add);
      std::cout << std::endl;
      
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result[i][j] = result_add[i][j];
        }
    }
  }
  
  SubBytes(result, result);
  ShiftRows(result);
  AddRoundKey(round_keys[10], result, result_add);
  
  std::cout << "R10 (Subkey = ";
  PrintStateMatrix(round_keys[10]);
  std::cout << ") = ";
  PrintStateMatrix(result_add);
  std::cout << std::endl;
}

int main() {
  std::string key_str, plaintext_str;
  std::cout << "Key (hex string):       ";
  std::cin >> key_str;
  std::cout << "Plaintext (hex string): ";
  std::cin >> plaintext_str;
  
  uint8_t key_matrix[4][4], plaintext_matrix[4][4];
  StoreHexInput(key_str, key_matrix);
  StoreHexInput(plaintext_str, plaintext_matrix);
  
  std::cout << "\n--- AES-128 Trace Log ---\n";
  RijndaelAlgorithm(key_matrix, plaintext_matrix);
  
  return 0;
}