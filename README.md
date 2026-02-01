# HashMap & Dictionary (C++)

## Overview

This project implements a generic **HashMap** data structure in C++, along with
a specialized **Dictionary** class built on top of it.

## Project Structure

``` text
.
├── CMakeLists.txt
├── Makefile
├── demo/
│   └── main.cpp            # Demo program showcasing HashMap & Dictionary
└── src/
    ├── HashMap.hpp         # Generic hash map implementation
    └── Dictionary.hpp      # Dictionary specialization (string → string)
```

## Building with Makefile

### Requirements
- C++17-compatible compiler (GCC / Clang / MinGW)
- make
- Linux / macOS / Windows (MinGW / MSYS2 / WSL)

### Build
From the project root:

``` bash
make
```

### Run
Linux / macOS:

``` bash
./demo
```

Windows (PowerShell / CMD):

``` bash
demo.exe
``` 


## Building with CMake

### Requirements
- CMake ≥ 3.16
- C++17-compatible compiler

### Build
From the project root:

``` bash
cmake -S . -B build
cmake --build build
``` 

### Run

Linux / macOS:

``` bash
./build/demo
``` 

Windows:

``` bash
build\demo.exe
``` 


## Demo 

The demo (`demo/main.cpp`) demonstrates:

### HashMap
- Default construction
- Insertion and automatic resizing
- Lookup (`contains_key`, `at`)
- Exception handling for invalid access
- Erase and shrink behavior
- Copy construction and equality
- `operator[]` default insertion
- Iteration using const iterators

### Dictionary
- Insertion via `operator[]`
- Custom exception on invalid erase
- Semantic difference from HashMap

Example output:

``` text
=== HashMap / Dictionary demo ===
empty hashmap size= 0 capacity= 16 load factor= 0
hashmap[100] default-inserts:
after inserting 0..15 size= 17 capacity= 32 load factor= 0.53125
contains 1? true
at(1) = a
[expected] at(-1) threw: no such key exists!
after erasing 0..8 size= 8 capacity= 32 load factor= 0.25
hashmap == copy? true
hashmap == copy after change? false
iterating (first few):
100 ->
9 -> a
10 -> a
11 -> a
dict['apple'] = fruit
[expected] dict.erase('missing') threw: Invalid Key!
``` 

Developed by Bella Shmuylovich as part of an academic project
