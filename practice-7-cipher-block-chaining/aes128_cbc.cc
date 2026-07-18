// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 7: SSI - Cipher Block Chaining (CBC) Mode
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 26/03/2025

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <string>
#include <cstring>

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
 * @brief Populates a 4x4 matrix from a raw hex string using column-major order.
 * @param hex_str Hexadecimal input string.
 * @param matrix Destination 4x4 cryptographic state matrix.
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
 * @brief Multiplies two bytes within the Galois Field GF(2^8) using Rijndael modular reduction.
 * @param a First multiplier byte.
 * @param b Second multiplier byte.
 * @return uint8_t Product byte over GF(2^8).
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
 * @brief Maps each byte of the matrix non-linearly using the AES S-Box lookup framework.
 * @param state The input 4x4 active block matrix.
 * @param result The output transformed 4x4 state matrix.
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
 * @brief Shifts rows cyclically to the left using incremental structural offsets.
 * @param state The current 4x4 operation state matrix.
 */
void ShiftRows(uint8_t state[4][4]) {
  std::swap(state[1][0], state[1][1]);
  std::swap(state[1][1], state[1][2]);
  std::swap(state[1][2], state[1][3]);

  std::swap(state[2][0], state[2][2]);
  std::swap(state[2][1], state[2][3]);

  std::swap(state[3][0], state[3][3]);
  std::swap(state[3][1], state[3][3]);
  std::swap(state[3][2], state[3][3]);
}

/**
 * @brief Mixes column equations over GF(2^8) via matrix-vector multiplication.
 * @param state The active 4x4 input block matrix.
 * @param result The mixed 4x4 output destination matrix.
 */
void MixColumn(uint8_t state[4][4], uint8_t result[4][4]) {
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
 * @brief Blends a specific scheduling round key into the active text state via bitwise XOR.
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
 * @brief Cyclically rotates a 4-byte word vector sequence one space to the left.
 * @param word Target 4-element byte array.
 */
void RotWord(uint8_t word[4]) {
  uint8_t temp = word[0];
  word[0] = word[1];
  word[1] = word[2];
  word[2] = word[3];
  word[3] = temp;
}

/**
 * @brief Non-linearly substitutes each byte in a 4-byte word array via S-Box lookup.
 * @param word Target 4-element byte array.
 */
void SubWord(uint8_t word[4]) {
  for (int i = 0; i < 4; i++) {
    uint8_t row = word[i] >> 4;
    uint8_t col = word[i] & 0x0F;
    word[i] = S_BOX[row][col];
  }
}

/**
 * @brief Derives the 11 scheduling round keys from the initial 128-bit master key matrix.
 * @param key Initial 128-bit master cipher key matrix.
 * @param round_keys Complete destination structure hosting the 11 derived subkeys.
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
 * @brief Combines two independent 4x4 matrix blocks utilizing a bitwise XOR operation.
 * @param block1 First input state matrix.
 * @param block2 Second input state matrix.
 * @param result Combined output destination matrix.
 */
void XorBlocks(uint8_t block1[4][4], uint8_t block2[4][4], uint8_t result[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i][j] = block1[i][j] ^ block2[i][j];
    }
  }
}
  
/**
 * @brief Encrypts a single standalone text block through the core AES framework.
 * @param key Initial master encryption key matrix.
 * @param block Targeted input plaintext state matrix.
 * @param ciphertext Output encrypted block destination matrix.
 */
void EncryptBlock(uint8_t key[4][4], uint8_t block[4][4], uint8_t ciphertext[4][4]) {
  uint8_t result[4][4], result_add[4][4], result_mix[4][4];
  uint8_t round_keys[11][4][4];
  KeyExpansion(key, round_keys);
  AddRoundKey(round_keys[0], block, result);
  for (int iteration = 1; iteration < 10; iteration++) {
    SubBytes(result, result);
    ShiftRows(result);
    MixColumn(result, result_mix);
    AddRoundKey(round_keys[iteration], result_mix, result_add);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
          result[i][j] = result_add[i][j];
      }
    }
  }
  SubBytes(result, result);
  ShiftRows(result);
  AddRoundKey(round_keys[10], result, result_add);
  std::memcpy(ciphertext, result_add, 16 * sizeof(uint8_t));
}

/**
 * @brief Prints a standard cryptographic state matrix out to terminal using hex column-major formatting.
 * @param block Target 4x4 operation matrix.
 */
void PrintBlock(const uint8_t block[4][4]) {
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      std::cout << std::hex << std::setw(2) << std::setfill('0') 
                << static_cast<int>(block[row][col]) << " ";
    }
  }
  std::cout << std::dec << std::endl;
}
  
int main() {
  std::string key_str, iv_str;
  std::cout << "Key (32 hex digits, no spaces): ";
  std::cin >> key_str;
  std::cout << "IV (32 hex digits, no spaces):  ";
  std::cin >> iv_str;

  uint8_t master_key[4][4], initialization_vector[4][4];
  StoreHexInput(key_str, master_key);
  StoreHexInput(iv_str, initialization_vector);
  
  const int total_blocks = 2;
  std::vector<std::string> plaintext_blocks(total_blocks);
  for (int i = 0; i < total_blocks; i++) {
    std::cout << "Plaintext Block " << i + 1 << " (32 hex digits, no spaces): ";
    std::cin >> plaintext_blocks[i];
  }
  
  uint8_t previous_block[4][4];
  std::memcpy(previous_block, initialization_vector, 16 * sizeof(uint8_t));
  
  std::cout << "\n--- AES-128 CBC Output ---" << std::endl;
  for (int i = 0; i < total_blocks; i++) {
    uint8_t clear_block[4][4], xor_block[4][4], encrypted_block[4][4];
    StoreHexInput(plaintext_blocks[i], clear_block);
    
    XorBlocks(clear_block, previous_block, xor_block);
    EncryptBlock(master_key, xor_block, encrypted_block);
    
    std::cout << "Ciphertext Block " << i + 1 << ": ";
    PrintBlock(encrypted_block);
    std::memcpy(previous_block, encrypted_block, 16 * sizeof(uint8_t));
  }
  return 0;
}