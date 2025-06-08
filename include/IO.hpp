

#ifndef IO_HPP
#define IO_HPP

// own
#include <Token.hpp>

// std
#include <iostream>

std::ostream &operator<<(std::ostream &os, const Token &token);

#endif