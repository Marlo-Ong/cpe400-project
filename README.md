# Dynamic Frequency-Division Multiple Access Protocol
**Authors:** Nicholas Langley and Marlo Ongkingco

**Purpose:** CPE400 Fall 2025 Final Project


## Compilation / Execution Instructions

1. **Install required tools**
   - `g++` with C++17 support (GCC 11+ recommended)
   - `make`
   - No external libraries are required, the project only depends on the C++ standard library.
2. **Build the simulator**
   ```
   make
   ```
   This compiles every `.cpp` file under `src/` into the `sim` executable with `-std=c++17 -Wall -Wextra -pedantic`.
3. **Run the simulator**
   ```
   ./sim
   ```
   Use `./sim` directly to run with the default settings compiled into `main.cpp`.

   Optionally, provide runtime parameters as follows with the command: `./sim [int number of nodes] [int simulation time in ticks] [int total number of channels available]`

   *Providing any invalid input (integer below 1 or non-integer) will run the simulator with the default settings of 6 nodes, 200 ticks, and 12 channels.*
4. **Clean the build artifacts (optional)**
   ```
   make clean
   ```
   Removes the generated `sim` binary if you need a fresh build.
