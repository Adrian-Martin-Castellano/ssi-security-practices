# Vigenère Cipher Implementation in C++

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** February 2025  

## Overview

This repository provides an interactive terminal-based program implementing the classical **Vigenère Cipher**. It enables users to perform algebraic encryption and decryption of textual data using a repeating alphabetic keyword. 

To maintain robust compatibility with standard regional alphabets, this application relies natively on wide character streams (`std::wstring`) and local unicode environments. This allows it to seamlessly sanitize text by automatically stripping out empty white spaces, removing local accent markers (tildes), and matching character blocks to standard alphabetic matrix structures.

## Cryptographic Concept

The Vigenere Cipher applies a polyalphabetic substitution principle where each letter of a plaintext message is shifted along the Latin alphabet sequence according to a corresponding character in a periodic encryption key. 

Mathematically, given a message character $M_i$ and a key stream character $K_i$ mapped to numerical values within the range $[0, 25]$ ($A=0, B=1, \dots, Z=25$), the transformations are governed by modular arithmetic equations:

### Encryption
$$C_i = (M_i + K_i) \pmod{26}$$

### Decryption
$$M_i = (C_i - K_i + 26) \pmod{26}$$


## Key Technical Features

* **Advanced String Normalization:** Features automated string parsing engines that cleanly scrub regional irregularities (such as mapping `á`, `é`, `í`, `ó`, `ú` variants into non-accented equivalents) and format raw input strings directly into compact block strings.
* **Stream Formatting Blocks:** Automatically splits output visualizations by grouping terminal text into segments matching the exact string size of the user's password key for easier visualization and debugging.
* **Native Unicode Localization Integration:** Leverages system `locale` imbuing directly onto standard IO channels (`wcout`, `wcin`), preventing terminal parsing distortion or character drop exceptions during multi-byte runtime interactions.


## Getting Started

### Prerequisites
A standard, modern C++ compiler supporting at least **C++17** or higher (`g++` or `clang++`).

### Compilation
Compile the program directly using your standard compiler via the terminal:

```bash
g++ -std=c++17 vigenere_cipher.cc -o vigenere_cipher
```

## Usage & Operation Modes

Launch the compiled executable using:

```bash
./vigenere_cipher
```

Upon startup, an interactive runtime loop shell guides you through the available options:

### 1. Encrypt Message
* **Input:** Enter your target secret keyword, followed by the explicit plaintext message line.
* **Formatting:** The application automatically filters special characters and prints your text matched alongside the required repeating keystream blocks.
* **Output:** Displays the processed plaintext structure, the expanded key sequence, and the final encrypted Uppercase Ciphertext.

### 2. Decrypt Message
* **Input:** Enter the target symmetric encryption password key along with the intercepted ciphertext.
* **Output:** Subtracts the matching key indices mod 26 to successfully output and print the original plaintext message.