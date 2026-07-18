# RSA Cryptosystem with Lehman-Peralta Primality Test

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** April 2025  

## Overview

This repository features the implementation for **Practice 9**, introducing the fully operational execution flow of the asymmetric **RSA Cryptosystem**. The environment embeds a dedicated probabilistic validation framework leveraging the **Lehman-Peralta Test** to confirm input parameter primality before setting up key infrastructures. Furthermore, string data transitions into active numerical processing values by relying on alphabetic blocking algorithms grouped on Base-26 representations.

## Core Pipeline Components

*   **Lehman-Peralta Primality Verification:** Evaluates candidate parameters $p$ and $q$ to ensure they are primes. It performs modular checks using random witness numbers ($a$) testing if $a^{(p-1)/2} \equiv \pm 1 \pmod p$.
*   **Key Generation:** Computes Euler's totient function $\phi(n) = (p-1)(q-1)$, verifies that the public descriptor $d$ is coprime to it via the Extended Euclidean Algorithm, and extracts the modular multiplicative inverse to establish the working private exponent key $e$.
*   **Base-26 Block Construction:** Segments incoming clean plaintext strings into calculated chunk scales ($j$), converting letters to decimal vectors using structural positional weights:
    $$\text{Value} = \sum_{i=0}^{j-1} (\text{Character}_i - \text{'A'}) \cdot 26^{j-1-i}$$

## Compilation & Usage

### Compilation
Build the source file using standard optimization targets:

```bash
g++ -std=c++17 rsa_cipher.cc -o rsa_encoder
```

## Sample Terminal Output

### Execution Command

Run the compiled standalone utility directly from your local prompt:

```bash
./rsa_encoder
```

### Trace Sample Log

```text
Enter the plaintext to encrypt: MUNDO
Enter the first prime number (p): 19
Enter the second prime number (q): 23
Enter the public exponent key (d): 5
-> Parameter 'p' passes primality criteria.
-> Parameter 'q' passes primality criteria.
-> Success: Public exponent 'd' is coprime to phi(n).
GCD(d, phi(n)) = 1
Modular inverse (private exponent e) = 317
Modulus (n = p * q) = 437
Operational Block Size: 1

--- Processing RSA Blocks (Base-26 Coding) ---
Block "M" -> Decimal Base-26 Value: 12 -> Encrypted Representation: 310
Block "U" -> Decimal Base-26 Value: 20 -> Encrypted Representation: 421
Block "N" -> Decimal Base-26 Value: 13 -> Encrypted Representation: 382
Block "D" -> Decimal Base-26 Value: 3 -> Encrypted Representation: 256
Block "O" -> Decimal Base-26 Value: 14 -> Encrypted Representation: 181
```