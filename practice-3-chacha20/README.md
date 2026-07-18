# ChaCha20 Core Keystream Block Implementation

**Course:** Computer Systems Security / Seguridad en Sistemas Informáticos (SSI) - 3rd Year  
**Institution:** Universidad de La Laguna (ULL) - Escuela Superior de Ingeniería y Tecnología  
**Author:** Adrián Martín Castellano  
**Email:** alu0101547619@ull.edu.es  
**Date:** Feb 2025  

##  Overview

This project provides a software implementation of the core **ChaCha20 symmetric stream cipher block generator** conforming to **RFC 7539** specifications. The program takes an external data vector setting up a $256$-bit secret key, a $32$-bit block counter, and a $96$-bit unique initialization Nonce vector to compute a highly non-linear $512$-bit key pseudo-random stream block via bitwise ARX (Addition-Rotation-XOR) design properties.

## Matrix Architecture & Mapping

The internal system architecture maintains a steady $4 \times 4$ matrix state layout composed of sixteen $32$-bit wide unsigned integers (`uint32_t`), organized as follows:

* **Rows 0-3 ($x_0 \dots x_3$):** Hardcoded protocol constants matching the ASCII string `"expand 32-byte k"` (`0x61707865`, `0x3320646e`, `0x79622d32`, `0x6b206574`).
* **Rows 4-11 ($x_4 \dots x_{11}$):** The $256$-bit secret encryption key split into eight distinct $32$-bit words.
* **Row 12 ($x_{12}$):** The explicit $32$-bit internal block synchronization sequence counter.
* **Rows 13-15 ($x_{13} \dots x_{15}$):** The $96$-bit isolated network transmission Nonce string value.

## Execution Mechanics

The implementation applies a double-round cascading loop schema repeated ten times for a complete set of **20 processing rounds** utilizing optimized bit-shift algorithms:

```markdown
         Odd Rounds (Columns)                     Even Rounds (Diagonals)
     
     QR(x0, x4, x8,  x12) // Col 0            QR(x0, x5, x10, x15) // Diag 1
     QR(x1, x5, x9,  x13) // Col 1            QR(x1, x6, x11, x12) // Diag 2
     QR(x2, x6, x10, x14) // Col 2            QR(x2, x7, x8,  x13) // Diag 3
     QR(x3, x7, x11, x15) // Col 3            QR(x3, x4, x9,  x14) // Diag 4
```

##  Getting Started

### Prerequisites
A standard, modern C++ compiler supporting at least **C++17** or higher (`g++` or `clang++`).

### Compilation
Build the executable from the source directory layout:

```bash
g++ -std=c++17 chacha20_block.cc -o chacha20_encoder
```

##  Usage & Operation Modes

The application relies on input configuration parameter files parsed directly from your CLI parameters.

### Input File Format Requirements
Prepare a raw text file (`input.txt`) detailing your hexadecimal sequences separated by line feeds as follows (the parser automatically processes colon `:` artifacts and updates Little-Endian orientation sequences):

```text
Key: 00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14:15:16:17:18:19:1a:1b:1c:1d:1e:1f
Counter: 00:00:00:01
Nonce: 00:00:00:00:00:00:00:00:00:00:00:09
```

### Execution Command
Run the compiled binary passing your configuration dataset path text target string:

```bash
./chacha20_encoder input.txt
```

## Visualizer Output Traces
Upon execution, the terminal logs the absolute inner lifecycle matrix transformations mapping the internal state progression:

```text
Initial matrix state=
61707865 3320646e 79622d32 6b206574 
03020100 07060504 0b0a0908 0f0e0d0c 
13121110 17161514 1b1a1918 1f1e1d1c 
01000000 00000000 00000000 09000000 

Final internal state after 20 rounds=
2d603a11 cdfc6014 dfb73a30 c6c96bbf 
7d121703 14d18fa7 e3ffc5d5 ab8e5cb8 
17da8c16 ac6445aa f4944d67 cc08e013 
5095d3dc 61eb6e5b cf280cb0 adb77ff0 

Generator output keystream block=
8ed0b276 011cc482 59196762 31e9d133 
80141803 1bda94ab ee09cedd ba9c69c4 
2aed9d26 c37a5abc 0faf667f eb27fd2f 
5195d3dc 61eb6e5b cf280cb0 b6b77ff0
```