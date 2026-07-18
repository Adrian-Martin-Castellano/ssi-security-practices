# Diffie-Hellman Key Exchange Protocol Implementation

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** April 2025  

## Overview

This repository contains the implementation for **Practice 8**, introducing asymmetric cryptographic paradigms. The program simulates the traditional **Diffie-Hellman Key Exchange** protocol, allowing two remote entities (Alice and Bob) to safely establish a mutual, shared cryptographic secret key over an unsecure, public communications channel.

The underlying mathematical engine relies heavily on **Square-and-Multiply Modular Exponentiation**, mitigating integer overflow errors and drastically cutting down runtime complexity to logarithmic bounds $\mathcal{O}(\log(\text{exp}))$.

## Protocol Mechanics

1.  **Public Parameters:** A public prime modulus ($p$) and a generator base ($\alpha$) are explicitly declared.
2.  **Private Selections:** Both parties choose private integers independently ($x_A$ for Alice, $x_B$ for Bob).
3.  **Public Exchange Calculation:**
    *   Alice derives $y_A = \alpha^{x_A} \pmod p$
    *   Bob derives $y_B = \alpha^{x_B} \pmod p$
4.  **Shared Secret Resolution:**
    *   Alice computes $k = (y_B)^{x_A} \pmod p$
    *   Bob computes $k = (y_A)^{x_B} \pmod p$
    *   Mathematical identity ensures both sides compute identical values: $k = \alpha^{x_A \cdot x_B} \pmod p$.

## Compilation & Usage

### Compilation
Compile the project binary using any modern C++17 compiler via console:

```bash
g++ -std=c++17 diffie_hellman.cc -o dh_exchange
```

## Sample Terminal Output

### Execution Command

Run the compiled standalone utility directly from your local prompt:

```bash
./dh_exchange
```

### Trace Sample Log

```text
Enter a prime number (p): 13
Enter alpha number (alpha < p): 4
Enter Alice's secret key (xA): 5
Enter Bob's secret key (xB): 2

--- Diffie-Hellman Results ---
Public Parameters:  p = 13, alpha = 4
Secret Keys:        xA = 5, xB = 2
Public Exchanges:   yA = 10, yB = 3
Shared Secret Key:  k = 9
```