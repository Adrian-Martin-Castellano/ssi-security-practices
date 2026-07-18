# AES-128 Cipher Block Chaining (CBC) Implementation

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** July 2026  

## Overview

This repository features the implementation for **Practice 7**, expanding upon core Rijndael symmetric transformation structures to deploy the **Cipher Block Chaining (CBC)** mode of operation. By injecting an Initialization Vector (IV) and chaining sequence execution dependencies across blocks, the pipeline eliminates structural pattern leakage, assuring solid cryptographic diffusion even across identical input frames.

## CBC Mode Mechanical Design

The chaining structure interlocks blocks sequentially using a feedback design rule:

*   **First Block Initialization:** The initial cleartext frame is combined against the user-supplied **Initialization Vector (IV)** using an initial bitwise XOR layer before running core AES encryption.
*   **Subsequent Block Chaining:** Every trailing cleartext block updates its feedback path by running an XOR layer against the exact **ciphertext block generated directly before it**.

## Getting Started

### Prerequisites
A stable modern development toolset supporting the standard **C++17** target specification pipeline (`g++` or `clang++`).

### Compilation
Build the binary target from your local workspace console:

```bash
g++ -std=c++17 aes128_cbc.cc -o aes_cbc_encoder
```

## Sample Terminal Output

### Execution Command

Run the compiled standalone utility directly from your local prompt:

```bash
./aes128_cbc_encoder
```

### Trace Sample Log

```text
Key (32 hex digits, no spaces): 000102030405060708090a0b0c0d0e0f
IV (32 hex digits, no spaces):  112233445566778899aabbccddeeff00
Plaintext Block 1 (32 hex digits, no spaces): 00112233445566778899aabbccddeeff
Plaintext Block 2 (32 hex digits, no spaces): 00000000000000000000000000000000

--- AES-128 CBC Output ---
Ciphertext Block 1: 52 14 a0 c1 c8 44 26 fa ad b8 a0 ad e1 83 a6 d4 
Ciphertext Block 2: a2 fa bd a7 ac d2 89 cf de e1 56 fd b4 10 da d9
```