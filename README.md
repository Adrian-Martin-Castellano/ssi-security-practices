# Computer Systems Security (SSI) - Practical Assignments

**Course:** 3rd Year - Grado en Ingeniería Informática  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Academic Year:** 2024/2025  
**Student:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  

## Overview

This repository contains the complete set of laboratory practices and programming assignments developed for the **Computer Systems Security** (*Seguridad en Sistemas Informáticos - SSI*) course. The curriculum covers fundamental cryptographic paradigms, spanning classical ciphers, modern symmetric block ciphers, public-key infrastructures (asymmetric cryptography), and advanced mathematical validation techniques over finite fields.

All implementations are written in **C++17** with a focus on mathematical accuracy, modularity, and prevention of integer overflow scenarios.

## Laboratory Practices Index

The repository is structured sequentially, moving from classical cryptography to symmetric frameworks, and finally into modern asymmetric mathematical ecosystems:

| Practice | Cryptographic Paradigm & Core Concept | Implementation Link |
| :---: | :--- | :---: |
| **01** | **Classical Substitution Ciphers** (Caesar & Vigenère) | [View Code](./practice-1-vernam/) |
| **02** | **Stream Ciphers & Pseudorandomness** (RC4 Stream Cipher) | [View Code](./practice-2-vigenere/) |
| **03** | **Linear Feedback Shift Registers** (A5/1 Stream Cipher Engine) | [View Code](./practice-3-chacha20/) |
| **04** | **Data Encryption Standard Foundations** (DES Key Generation) | [View Code](./practice-4-CA-generator-in-GPS/) |
| **05** | **DES Round Operations** (Feistel Cipher Internal Functions) | [View Code](./practice-5-snow3G/) |
| **06** | **Advanced Encryption Standard Core** (AES-128 Internal Transformations) | [View Code](./practice-6-AES/) |
| **07** | **Symmetric Block Cipher Modes** (AES-128 Cipher Block Chaining - CBC) | [View Code](./practice-7-cipher-block-chaining/) |
| **08** | **Asymmetric Key Exchange** (Diffie-Hellman Protocol) | [View Code](./practice-8-Diffie-Helman/) |
| **09** | **Asymmetric Encryption & Primality** (RSA Cryptosystem & Lehman-Peralta) | [View Code](./practice-9-rsa/) |
| **10** | **Advanced Public Key Frameworks** (Elliptic Curve Cryptography & Koblitz) | [View Code](./practice-10-elliptic-curve-cryptography/) |

> *Note: Click on the links in the "Implementation Link" column to access the source code, specific compilation notes, and comprehensive mathematical breakdowns for each assignment.*

## Global Compilation & Requirements

### Technical Stack
*   **Language Specification:** C++17
*   **Compiler Infrastructure:** `g++` (GCC v9.0+) or `clang++`

### Generic Build Workflow
Every practice can be compiled from the terminal using standard optimization flags. For example, to compile the final Elliptic Curve Cryptography assignment:

```bash
cd practice10
g++ -std=c++17 elliptic_curve_crypto.cc -o ecc_suite
./ecc_suite
```

## Key Academic Takeaways
Through this course, I have designed, engineered, and verified the low-level building blocks of modern information security protocols:

1. **Bit-Level Manipulation:** Developing customized permutation matrices ($P$-Boxes), substitution layers ($S$-Boxes), and cyclic shifts required by SPN (Substitution-Permutation Network) designs like AES.
2. **Arithmetic over Finite Fields:** Implementing operations within Galois Fields ($\mathbb{F}_{2^8}$ / $\text{GF}(2^8)$) for AES columns mixing, and binary modular exponentiation algorithms for sub-exponential calculations.
3. **Modern Hard Mathematical Problems:** Engineering security proofs based on the Discrete Logarithm Problem (DLP), Integer Factorization Problem (IFP), and Elliptic Curve Discrete Logarithm Problem (ECDLP).