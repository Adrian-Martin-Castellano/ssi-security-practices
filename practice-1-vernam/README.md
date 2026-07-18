# Vernam Cipher Implementation in C++

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** February 2025  

## Overview

This repository contains a lightweight, terminal-based implementation of the **Vernam Cipher** (also known as the *One-Time Pad*). The system allows users to interactively encrypt or decrypt string messages using bitwise XOR operations. 

To ensure clean security operations within standard terminal interfaces, the program features built-in validation loops that filter out problematic character sets, forcing the resulting ciphertext or plaintext to fall strictly within the standard printable ASCII range ($32$ to $126$).

## Cryptographic Concept

The Vernam Cipher operates on a basic principle of perfect secrecy under specific conditions:
1. The message string is transformed into an explicit continuous sequence of $8$-bit binary chunks.
2. A binary cryptographic key of the exact same bitwise length is paired with the text.
3. A bitwise logical non-equivalence operation (**XOR**) is performed to safely toggle states:

$$\text{Ciphertext} = \text{Plaintext} \oplus \text{Key}$$
$$\text{Plaintext} = \text{Ciphertext} \oplus \text{Key}$$


## Key Technical Features

* **Polymorphic Key Provisioning:** Users can choose to input their custom binary stream keys manually via terminal strings or delegate task execution to an automated pseudo-random deterministic key generator synced to the system time.
* **Character Constraint Guards:** Includes verification filters that block non-printable system control bytes (characters outside the space-to-tilde ASCII range), requesting key re-generation or notification alerts upon failure.
* **Low-Level Bit Manipulation:** Leverages clean standard C++ `<bitset>` abstractions to easily parse variables back and forth between string blocks and raw binary components.

## Getting Started

### Prerequisites
A standard, modern C++ compiler supporting at least **C++17** or higher (`g++` or `clang++`).

### Compilation
Compile the program directly using your standard compiler via the terminal:

```bash
g++ -std=c++17 main_vernam.cc -o vernam_cipher
```

## Usage & Operation Modes

Launch the compiled executable using:

```bash
./vernam_cipher
```

Upon startup, an interactive runtime loop shell guides you through the available options:

### 1. Encrypt Message
* **Input:** Type your plaintext target word.
* **Key Selection:** Choose to either generate a compatible random key stream automatically or feed an explicit binary key sequence manually.
* **Output:** Displays the binary layout tracking, the absolute bit string length, and the final printable ASCII ciphertext string.

### 2. Decrypt Message
* **Input:** Type the intercepted encrypted ciphertext string.
* **Key Re-entry:** Enter the exact binary key stream string previously utilized.
* **Output:** Computes the reverse XOR operations to cleanly reconstruct and print out the original decrypted plaintext message.