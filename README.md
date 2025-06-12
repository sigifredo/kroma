# Kroma

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

Kroma is a personal project dedicated to creating a programming language for artists, creators, and developers looking to experiment with interactive, generative, and creative media. Its goal is to combine the power of programming languages ​​like Python and JavaScript.

# 🧪 Unit Testing in Kroma

This project uses [Catch2](https://github.com/catchorg/Catch2) (version 3) to implement unit tests in C++.

## Running Unit Tests

To run all unit tests:

```bash
mkdir build
cd build
cmake -DBUILD_TESTS=TRUE ..
make
./bin/kroma_tests
```

## Build in release mode

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
