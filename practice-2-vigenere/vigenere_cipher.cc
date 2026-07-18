// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Course: 3rd
// Practice 2: SSI
// Author: Adrián Martín Castellano
// Email: alu0101547619@ull.edu.es
// Date: 12/02/2025

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <locale>
#include <codecvt>

/**
 * @brief Removes tildes and accent marks from Spanish vowels.
 * @param c The wide character to process.
 * @return The upper-case equivalent character without tildes.
 */
wchar_t RemoveTildes(wchar_t c) {
  switch (c) {
    case L'á': case L'Á': return L'A';
    case L'é': case L'É': return L'E';
    case L'í': case L'Í': return L'I';
    case L'ó': case L'Ó': return L'O';
    case L'ú': case L'Ú': return L'U';
    default: return c;
  }
}

/**
 * @brief Sanitizes a wide string by removing spaces and accent marks, converting to uppercase.
 * @param str The original wide string.
 * @return The sanitized uppercase wide string.
 */
std::wstring ProcessString(const std::wstring& str) {
  std::wstring result;
  for (wchar_t c : str) {
    if (c != L' ') result += std::towupper(RemoveTildes(c));
  }
  return result;
}

/**
 * @brief Prints the interactive menu options to the standard console.
 */
void PrintMenu() {
  std::wcout << L"Choose an option:\n";
  std::wcout << L"   1) Encrypt message\n";
  std::wcout << L"   2) Decrypt message\n";
  std::wcout << L"   3) Exit\n";
  std::wcout << L"\nChosen option: ";
}

/**
 * @brief Computes the Vigenère shift for encryption.
 * @param message_num Numerical index of the plaintext letter.
 * @param key_num Numerical index of the key letter.
 * @return Numerical index of the resulting ciphertext letter.
 */
int EncryptShift(int message_num, int key_num) {
  int result = message_num + key_num;
  return result % 26;
}

/**
 * @brief Computes the Vigenère shift for decryption.
 * @param message_num Numerical index of the ciphertext letter.
 * @param key_num Numerical index of the key letter.
 * @return Numerical index of the resulting plaintext letter.
 */
int DecryptShift(int message_num, int key_num) {
  int result = message_num - key_num;
  return (result + 26) % 26;
}

int main() {
  // Configure console environment to native Unicode / UTF-8 specs
  std::locale::global(std::locale(""));
  std::wcout.imbue(std::locale(""));
  std::wcin.imbue(std::locale(""));

  std::wstring original_message, key, message_aux;
  int option = -1, key_repetitions;
  std::wstring alphabet = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  std::wcout << L"Welcome to the Vigenere Cipher Program\n";
  while (option != 0) {
    PrintMenu();
    std::wcin >> option;
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');

    if (option <= -1 || option >= 4) {
      std::wcout << L"Invalid option, please choose again.\n\n";
      continue;
    }

    switch (option) {
      case 1:
        original_message.clear();
        message_aux.clear();
        key.clear();        
        std::wcout << L"Enter the keyword: ";
        std::wcin >> key;
        key = ProcessString(key);
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
        
        std::wcout << L"Enter the plaintext message: ";
        std::getline(std::wcin, original_message);
        message_aux = ProcessString(original_message);
        
        std::wcout << L"\nPlaintext:      ";
        for (size_t i = 0; i < message_aux.size(); i++) {
          std::wcout << message_aux[i];
          if ((i + 1) % key.size() == 0) std::wcout << L" ";
        }
        std::wcout << std::endl;
        
        std::wcout << L"Key:            ";
        if (message_aux.size() / key.size() >= 1) {
          if (message_aux.size() % key.size() != 0) {
            key_repetitions = (message_aux.size() / key.size()) + 1;
          } else {
            key_repetitions = message_aux.size() / key.size();
          }
        } else {
          key_repetitions = 1;
        }
        for (int i = 0; i < key_repetitions; i++) {
          std::wcout << key << L" ";
        }
        std::wcout << std::endl;
        
        std::wcout << L"Ciphertext:     ";
        for (size_t i = 0; i < message_aux.size(); i++) {
          int message_num = message_aux[i] - L'A';
          int key_num = key[i % key.size()] - L'A';
          std::wcout << alphabet[EncryptShift(message_num, key_num)];
          if ((i + 1) % key.size() == 0) std::wcout << L" ";
        }
        std::wcout << L"\n\n";
        break;

      case 2:
        original_message.clear();
        message_aux.clear();
        key.clear();
        std::wcout << L"Enter the keyword: ";
        std::wcin >> key;
        key = ProcessString(key);
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), L'\n');
        
        std::wcout << L"Enter the ciphertext message: ";
        std::getline(std::wcin, original_message);
        message_aux = ProcessString(original_message);
        
        std::wcout << L"\nCiphertext:     ";
        for (size_t i = 0; i < message_aux.size(); i++) {
          std::wcout << message_aux[i];
          if ((i + 1) % key.size() == 0) std::wcout << L" ";
        }
        std::wcout << std::endl;
        
        std::wcout << L"Key:            ";
        if (message_aux.size() / key.size() >= 1) {
          if (message_aux.size() % key.size() != 0) {
            key_repetitions = (message_aux.size() / key.size()) + 1;
          } else {
            key_repetitions = message_aux.size() / key.size();
          }
        } else {
          key_repetitions = 1;
        }
        for (int i = 0; i < key_repetitions; i++) {
          std::wcout << key << L" ";
        }
        std::wcout << std::endl;
        
        std::wcout << L"Plaintext:      ";
        for (size_t i = 0; i < message_aux.size(); i++) {
          int message_num = message_aux[i] - L'A';
          int key_num = key[i % key.size()] - L'A';
          std::wcout << alphabet[DecryptShift(message_num, key_num)];
          if ((i + 1) % key.size() == 0) std::wcout << L" ";
        }
        std::wcout << L"\n\n";
        break;

      case 3:
        return 0;
    }
  }
  return 0;
}