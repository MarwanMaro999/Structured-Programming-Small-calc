# Machine Language Simulator

## Overview
This project is a C++-based simulator for executing machine language instructions. It reads hexadecimal instructions from a file, processes them, and simulates their execution, providing a step-by-step interface for debugging and visualization.

## Features
- **Hexadecimal Instruction Processing**: Reads and executes machine language instructions.
- **Memory and Register Operations**: Supports loading, storing, and manipulating data in registers and memory.
- **Arithmetic and Data Movement**: Implements operations such as addition and register-to-register transfers.
- **Jump and Control Flow**: Handles conditional and unconditional jumps.
- **Interactive Debugging**: Provides step-by-step execution with the ability to inspect registers, memory, and program state.

## Installation
1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd machine-language-simulator
   ```
2. Compile the program using g++:
   ```bash
   g++ Machine_language.cpp -o simulator
   ```
3. Run the program:
   ```bash
   ./simulator
   ```

## Usage
1. Enter the start address for execution.
2. Load instructions from `Input.txt`.
3. Step through execution and inspect registers, memory, and instructions.
4. Debug execution flow using interactive options.

## Dependencies
- C++ Standard Library
- `Machine_language.h` (Header file for class definitions)
