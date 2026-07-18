# Elliptic Curve Cryptography (ECC) & Koblitz Message Encoding

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Technology  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** April 2025  

## Overview

This repository represents the final capstone work (**Practice 10**) for the academic term, exploring advanced public-key mechanics through **Elliptic Curve Cryptography (ECC)**. The application simulates a full cryptographic cycle over prime finite fields $\mathbb{F}_p$: computing subgroup coordinates, executing an Elliptic Curve Diffie-Hellman (**ECDH**) key exchange, scaling mapping constraints through **Koblitz's encoding**, and creating an ElGamal-style encrypted transmission envelope.

## Mathematical Design & Mechanics

The system operates under short Weierstrass curves defined by the group equation:
$$y^2 \equiv x^3 + ax + b \pmod p$$

*   **Point Addition & Doubling:** Handles standard chord-tangent operations over $\mathbb{F}_p$. Whenever $P = Q$, the gradient calculation defaults to group tangent derivation $\lambda = \frac{3x_1^2 + a}{2y_1}$.
*   **ECDH Exchange:** Alice and Bob compute matching shared keys dynamically since multiplication is commutative across scalar distributions: $K_{shared} = d_A \cdot (d_B \cdot G) = d_B \cdot (d_A \cdot G)$.
*   **Koblitz Numeric Encoding:** Converts an integer message $m$ into a valid point coordinate pair by scaling intervals using a step variable $h = \lfloor p / M \rfloor$. It tests values $x = m \cdot h + j$ for $0 \le j < h$ sequentially until a quadratic residue exists under the target modulus.

## Compilation & Execution

### Compilation
Compile the source distribution utilizing a traditional modern target environment:

```bash
g++ -std=c++17 elliptic_curve_crypto.cc -o ecc_crypto_suite
```

## Sample Terminal Output

### Execution Command

Run the compiled standalone utility directly from your local prompt:

```bash
./ecc_crypto_suite
```

### Trace Sample Log

```text
--- Elliptic Curve Parameter Configuration ---
Enter prime field modulus (p): 23
Enter curve coefficient (a):   1
Enter curve coefficient (b):   1
Enter generator Point G (x y): 3 10
Enter Alice's private key (dA): 4
Enter Bob's private key (dB):   7
Enter plaintext message (integer): 3

[+] Group Points on Curve: (0,1) (0,22) (1,7) (1,16) (3,10) (3,13) (4,0) ...

-> Alice's Public Key (QA = dA * G): (7,11)
-> Bob's Public Key (QB = dB * G):   (13,16)

[=] Shared Secret (Alice's side): (19,5)
[=] Shared Secret (Bob's side):   (19,5)

--- Koblitz Message Encoding ---
Upper Bound M = 4
Step parameter h = 5 (Valid constraint: 5 < 23/4)
-> Message encoded as Point Qm: (17,3)

--- Final Ciphertext Outputs ---
-> Encrypted Message Point (Qm + dA * dB * G): (19,18)
-> Ephemeral Public Key Sent (QA = dA * G):    (7,11)
```