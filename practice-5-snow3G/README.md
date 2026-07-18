# Galois Field $GF(2^8)$ Polynomial Multiplier (SNOW 3G)

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** March 2026  

## Overview

This practice implements polynomial multiplication over the Finite Field **$GF(2^8)$** using the binary peasant algorithm (shift-and-XOR method). The arithmetic tool supports two standardized cryptographic reduction profiles by matching their respective primitive irreducible polynomials: **AES (Rijndael)** and the **SNOW 3G** stream cipher engine.

## Irreducible Polynomials Mapping

Finite field overflow boundaries require conditional bitwise reduction utilizing modular division steps:

* **AES Profile:** $x^8 + x^4 + x^3 + x + 1 \longrightarrow$ Binary mask: `00011011` (`0x1B`)
* **SNOW 3G Profile:** $x^8 + x^7 + x^5 + x^3 + 1 \longrightarrow$ Binary mask: `10101001` (`0xA9`)

## Getting Started

### Prerequisites
A modern compiler supporting the **C++17** structural specification baseline (`g++` or `clang++`).

### Compilation
Compile the utility code directly from your terminal session shell:

```bash
g++ -std=c++17 gf28_multiplier.cc -o gf28_multiplier
```

## Usage & Execution Verification
### Execution Command
Invoke the compiled native binary from your terminal workspace environment:

```bash
./gf28_multiplier
```

### Trace Sample Log
Multiplying two hexadecimal polynomial coordinates (0x57 $\cdot$ 0x13) using the AES configuration yields the following output validation trace:

```text
First byte (hex): 57
Second byte (hex): 13
Algorithm (AES / SNOW_3G): AES

---------------------------

First byte (bin):       01010111
Second byte (bin):      00010011
Irreducible poly (bin): 00011011
Multiplication result:  11000001
```