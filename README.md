# Bitwise Buffer Filter Library

## Overview

This is a high-performance, open-source C++ library designed specifically for resource-constrained environments such as embedded systems and microcontrollers. The primary goal is to provide fundamental data structures and utility functions optimized for **speed**, **minimal memory footprint**, and leveraging **bitwise operations**.

## Project Status & Modules

| Module | Status | Description |
| :--- | :--- | :--- |
| **Bitops** | **Completed (Core)** | Optimized functions for hardware register manipulation (set/clear/toggle), bit field packing/unpacking, and low-level bitwise arithmetic (e.g., population count, power-of-two check). |
| **Buffer Library** | **In Development** | Bitwise-optimized Ring Buffers (Circular Queues), Static Queues, and Bit Stream Buffers for robust, lock-free data streaming. |
| **Digital Filters** | **Planned** | Implementation of fixed-point DSP primitives, including highly optimized FIR and IIR filters. |

## 🛠️ Usage (How to Compile)

Since this library relies on modern C++ features (C++11/17), you must explicitly set the language standard when compiling with g++:

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/AvciDogukan/Bitwise-Buffer-Filter-Library
    ```

2.  **Compile with G++ (Example):**
    Compile your application files (`main.cpp`) along with the library source files (`bitops.cpp`):
    ```bash
    g++ -std=c++17 -Wall -O3 main.cpp bitops.cpp -o my_app
    ```
    *(Note: `-O3` ensures maximum performance optimization.)*

## 🤝 Contribution

Contributions are welcome! Please feel free to open issues or submit pull requests for bug fixes, performance improvements, or new primitives aligned with embedded system needs.

## 📄 License

[Specify your chosen license here, e.g., MIT, Apache 2.0]
