# Kroma

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

Kroma is a personal project dedicated to creating a dynamic, simple, and expressive programming language. Its goal is to combine the power of modern C++ with a minimalist syntax inspired by languages like Python and JavaScript. Designed especially for artists, creators, and developers looking to experiment with interactive, generative, and creative media, Kroma aims to be an accessible and versatile tool for artistic prototyping and technological exploration.

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
