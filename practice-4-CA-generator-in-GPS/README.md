# GPS Coarse/Acquisition (C/A) PRN Code Generator

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** Feb 2025  

## Overview

This implementation simulates the generation of **GPS Coarse/Acquisition (C/A) Pseudo-Random Noise (PRN) codes** used for satellite identification in the GPS L1 signal band. The mechanism uses two coupled 10-stage Linear Feedback Shift Registers (LFSR), known as **$G_1$** and **$G_2$**, to build unique **Gold Codes** for up to 32 satellites through phase-selected tapping arrays.

## Mathematical Model & Taps

The structural polynomials defining the linear recurrence feedback logic are:

* **$G_1$ Generator Polynomial:** $1 + X^3 + X^{10}$
* **$G_2$ Generator Polynomial:** $1 + X^2 + X^3 + X^6 + X^8 + X^9 + X^{10}$

Each satellite modulates its transmission by sampling two distinct internal cell outputs from the $G_2$ register block via exclusive XOR additions before merging it with the final output bit of the $G_1$ register.

## Getting Started

### Prerequisites
A standard compiler supporting **C++17** or later features (`g++` or `clang++`).

### Compilation
Compile the binary file directly from your workspace setup:

```bash
g++ -std=c++17 gps_ca_generator.cc -o gps_generator
```

## Usage & Verification Traces

### Execution Command
Run the compiled application binary locally using standard terminal inputs:

```bash
./gps_generator
```

### Trace Sample Log
Choosing Satellite ID 1 and an output constraint parameter of 5 bits will print the following cycle tracking matrix layout on your workspace:

```text
Satellite ID (1-32): 1
Output sequence length: 5
   LFSR1    | Feedback |    LFSR2    | Feedback | C/A PRN Sequence
------------+----------+-------------+----------+-----------------
1111111111  |    0     |  1111111111  |    0     |        0
0111111111  |    1     |  0111111111  |    1     |        1
1011111111  |    1     |  1011111111  |    1     |        0
1101111111  |    1     |  1101111111  |    1     |        0
1110111111  |    1     |  1110111111  |    0     |        1
```