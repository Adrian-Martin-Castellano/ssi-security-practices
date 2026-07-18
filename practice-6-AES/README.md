# AES-128 (Rijndael) Block Cipher Implementation

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** March 2026  

## Overview

This practice features a step-by-step trace implementation of the standard **AES-128 (Advanced Encryption Standard)** block cipher engine, operating natively under the Rijndael specification schema. The code inputs a 128-bit master key alongside a 128-bit plaintext block to output intermediate hexadecimal state matrices throughout the full 10-round substitution-permutation lifecycle.

## Core Crypto Pipeline Components

Every processing loop iteration (Rounds 1 to 9) leverages an array of dedicated non-linear and algebraic diffusion layers:

1. **`SubBytes`**: A non-linear byte substitution layer utilizing the static AES S-Box affine transformation mapping matrix.
2. **`ShiftRows`**: A cyclic row transposition step providing inter-column statistical diffusion properties.
3. **`MixColumns`**: A linear matrix multiplication operation handled over the Galois Field $GF(2^8)$ using the Rijndael reduction standard ($0x1B$).
4. **`AddRoundKey`**: A basic bitwise XOR masking operation blending the state block against schedule subkeys.

## Getting Started

### Prerequisites
A stable C++ execution suite environment supporting the standard **C++17** target compilation baseline (`g++` or `clang++`).

### Compilation
Build the executable pipeline target through your terminal terminal workflow:

```bash
g++ -std=c++17 aes128_core.cc -o aes_encoder
```

## Usage & Verification Traces

### Execution Command
Run the compiled standalone utility directly from your local prompt:

```bash
./aes_encoder
```

### Trace Sample Log
Supplying standard test vector structures outputs a clean round-by-round execution audit profile:

```text
Key (hex string):       000102030405060708090a0b0c0d0e0f
Plaintext (hex string): 00112233445566778899aabbccddeeff

--- AES-128 Trace Log ---
R0 (Subkey = 000102030405060708090a0b0c0d0e0f) = 00102030405060708090a0b0c0d0e0ff
R1 (Subkey = d6aa74fdd2af72fadaa678f1d6ab76fe) = 89c81418a166be2f7a550f757f59d283
...
R10 (Subkey = 13111d7fe3944a17f307a78b4d2b30c5) = 69c4e0d86a7b0430d8cdb78070b4c55a
```