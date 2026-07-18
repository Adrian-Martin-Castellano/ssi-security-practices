// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 1: SSI
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 05/02/2025

#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
#include <ctime>

/**
 * @brief Prints the menu with the available options for the user.
 * This menu allows the user to choose between encrypting a message,
 * decrypting a message, or exiting the program.
 */
void PrintMenu() {
  std::cout << "Choose an option:\n";
  std::cout << "   1) Encrypt message\n";
  std::cout << "   2) Decrypt message\n";
  std::cout << "   3) Exit\n";
  std::cout << "\nChosen option: ";
}

/**
 * @brief Converts a text message into its binary representation.
 * This function takes a string of text and converts it into a string
 * of binary characters, representing each letter as 8 bits.
 * @param message The text format message to be converted.
 * @return A string containing the binary representation of the message.
 */
std::string ConvertBinary(std::string message) {
  std::string binary;
  for (auto letter : message) {
    binary += std::bitset<8>(letter).to_string();
  }  
  return binary;
}

/**
 * @brief Performs a XOR operation between two binary strings.
 * The function takes two binary character strings of the same length,
 * and applies a bitwise XOR operation between them. The result is a new
 * binary string.
 * @param message The first binary string.
 * @param key The second binary string to be used in the XOR operation.
 * @return A binary string resulting from the XOR operation between message and key.
 */
std::string XOR(std::string message, std::string key) {
  std::string final_message;
  for (size_t i = 0; i < message.size(); i++) {
    if (message[i] == key[i]) final_message += '0';
    if (message[i] != key[i]) final_message += '1';
  }
  return final_message;
}

/**
 * @brief Converts a binary string into its ASCII representation.
 * This function takes a string of bits (in groups of 8) and converts them
 * to their equivalent ASCII characters.
 * @param message The binary character string (in groups of 8 bits).
 * @return The corresponding ASCII format character string.
 */
std::string ConvertASCII(std::string message) {
  std::string final_message;
  for (size_t i = 0; i < message.size(); i += 8) {
    std::bitset<8> bits(message.substr(i, 8));  
    final_message += static_cast<char>(bits.to_ulong()); 
  }
  return final_message;
}

/**
 * @brief Verifies if all characters in a message are printable.
 * This function iterates through the string and checks if all characters
 * fall within the printable range of the ASCII table (32 to 126).
 * @param message The message to be verified.
 * @return true If all characters in the message are printable.
 * @return false If any character is not printable.
 */
bool IsPrintable(const std::string& message) {
  for (char letter : message) {
    if (letter < 32 || letter > 126) {
      return false; 
    }
  }
  return true; 
}

/**
 * @brief Main function that handles the workflow of the encryption and decryption program.
 * 
 * This program allows the user to choose between encrypting or decrypting a message.
 * The encryption and decryption process is performed using a key, which can be
 * randomly generated or manually provided by the user.
 * The message is converted to binary and then the XOR operation is applied between 
 * the message and the key. The program also validates that the key is suitable so 
 * that the resulting text contains only printable characters.
 * 
 * @return 0 Upon successful execution when the user chooses to exit.
 */
int main() {
  std::string key, message, encrypted_message, original_message_binary, encrypted_message_binary;
  int option{-1};
  bool valid_key;
  std::srand(std::time(nullptr)); 
  
  std::cout << "Welcome to the Vernam Cipher Program\n";
  while (option != 0) {
    PrintMenu();
    std::cin >> option;
    if (option <= -1 || option >= 4) {
      std::cout << "Invalid option, please choose again.\n\n";
      continue;
    }
    
    switch (option) {
    case 3:
      return 0;
      break;
    case 1:
      valid_key = false;
      std::cout << "\nEnter the original message to encrypt\n";
      std::cout << "Original message: ";
      std::cin >> message;
      original_message_binary = ConvertBinary(message);
      std::cout << "Original message in binary: " << original_message_binary;
      std::cout << "\nBinary message length: " << original_message_binary.size();
      std::cout << "\n\n1) Generate random key\n";
      std::cout << "2) Enter key manually\n";
      std::cout << "\nChosen option: ";
      std::cin >> option;
      if (option <= 0 || option >= 3) {
        std::cout << "Invalid option, please choose again.\n\n";
        continue;
      }
      if (option == 1) {
        key.clear();
        while (!valid_key) {
          key = "";
          for (size_t i = 0; i < original_message_binary.size() / 8; ++i) {  
            int value = 32 + (std::rand() % (126 - 32 + 1));
            key += std::bitset<8>(value).to_string(); 
          }
          std::string encrypted_message_aux = ConvertASCII(XOR(original_message_binary, key));
          if (IsPrintable(encrypted_message_aux)) valid_key = true; 
        }
        std::cout << "Random key: " << key << std::endl;
      }
      if (option == 2) {
        key.clear();
        while (!valid_key) {
          key = "";
          std::cout << "Enter key in binary: ";
          std::cin >> key;
          if (key.size() != original_message_binary.size()) {
            std::cout << "Incorrect key length.\n\n";
            continue;
          }
          std::string encrypted_message_aux = ConvertASCII(XOR(original_message_binary, key));
          if (IsPrintable(encrypted_message_aux)) { 
            valid_key = true; 
          } else {
            std::cout << "Key results in non-printable characters, please try a different key.\n\n";
          }
        }
      }
      std::cout << "Encrypted message in binary: " << XOR(original_message_binary, key) << std::endl;
      std::cout << "Encrypted message: " << ConvertASCII(XOR(original_message_binary, key)) << std::endl;
      break;
      
    case 2:
      valid_key = false;
      std::cout << "\nEnter the encrypted message to decrypt\n";
      std::cout << "Encrypted message: ";
      std::cin >> encrypted_message;
      encrypted_message_binary = ConvertBinary(encrypted_message);
      std::cout << "Encrypted message in binary: " << encrypted_message_binary;
      std::cout << "\nBinary message length: " << encrypted_message_binary.size();
      std::cout << "\n\n1) Generate random key\n";
      std::cout << "2) Enter key manually\n";
      std::cout << "\nChosen option: ";
      std::cin >> option;
      if (option <= 0 || option >= 3) {
        std::cout << "Invalid option, please choose again.\n\n";
        continue;
      }
      if (option == 1) {
        key.clear();
        while (!valid_key) {
          key = "";
          for (size_t i = 0; i < encrypted_message_binary.size() / 8; ++i) { 
            int value = 32 + (std::rand() % (126 - 32 + 1));
            key += std::bitset<8>(value).to_string(); 
          }
          std::string original_message_aux = ConvertASCII(XOR(encrypted_message_binary, key));
          if (IsPrintable(original_message_aux)) valid_key = true; 
        }
        std::cout << "Random key: " << key << std::endl;
      }
      if (option == 2) {
        key.clear();
        while (!valid_key) {
          key = "";
          std::cout << "Enter key in binary: ";
          std::cin >> key;
          if (key.size() != encrypted_message_binary.size()) {
            std::cout << "Incorrect key length.\n\n";
            continue;
          }
          std::string original_message_aux = ConvertASCII(XOR(encrypted_message_binary, key));
          if (IsPrintable(original_message_aux)) { 
            valid_key = true; 
          } else {
            std::cout << "Key results in non-printable characters, please try a different key.\n\n";
          }
        }
      }
      std::cout << "Decrypted message in binary: " << XOR(encrypted_message_binary, key) << std::endl;
      std::cout << "Decrypted message: " << ConvertASCII(XOR(encrypted_message_binary, key)) << std::endl;
      break;
    }
  }
  return 0;
}